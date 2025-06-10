/**
 * MIT License
 *
 * Copyright (c) 2025 Qiu Yixiang
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <zlib.h>
#include <openssl/sha.h>

#include <object/object.h>
#include <object/repository.h>
#include <util/files.h>
#include <util/str.h>
#include <util/error.h>

#define FILE_BUFFER_SIZE UINT16_MAX
#define OBJECT_HEADER_SIZE          64

static void _decompress_file(const char * file_path, char * decompressed_buffer, size_t buffer_size){
    FILE * file_stream = fopen(file_path, "rb");
    if (file_stream == NULL){
        gitlet_panic("Failed to open the file: %s", file_path);
    }
    
    // get the file size
    fseek(file_stream, 0, SEEK_END);
    long file_size = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);

    // read the entire file
    unsigned char * compressed_buffer = (unsigned char *)malloc(file_size);
    size_t bytes_read = fread(compressed_buffer, 1, file_size, file_stream);
    if (bytes_read != (size_t)file_size){
        gitlet_panic("Failed to read the file: %s", file_path);
    }
    fclose(file_stream);

    // decompress the file
    uLongf decompressed_size = buffer_size;
    int result = uncompress((Bytef *)decompressed_buffer, &decompressed_size, (Bytef *)compressed_buffer, file_size);
    if (result != Z_OK){
        gitlet_panic("Failed to decompress the file: %s", file_path);
    }
    free(compressed_buffer);
}

extern void object_read(struct object * obj, const char * sha1){
    char object_file_path[PATH_MAX] = {0};
    if (getcwd(object_file_path, PATH_MAX) == NULL){
        gitlet_panic("Failed to get the current working directory");
    }
    
    strcat(object_file_path, "/.gitlet/objects/");
    strncpy(object_file_path + strlen(object_file_path), sha1, 2);
    strcat(object_file_path, "/");
    strncpy(object_file_path + strlen(object_file_path), sha1 + 2, 38);
    
    char * decompressed_buffer = (char *)malloc(FILE_BUFFER_SIZE);
    _decompress_file(object_file_path, decompressed_buffer, FILE_BUFFER_SIZE);

    // Parse type
    char * type_buffer = decompressed_buffer;
    char * current_ptr = (char *)strchr(type_buffer, ' ');
    if (current_ptr == NULL){
        gitlet_panic("Invalid object type: %s", type_buffer);
    }
    *current_ptr = '\0';
    current_ptr++;
    
    if (strcmp(type_buffer, "blob") == 0){
        obj->type = OBJECT_TYPE_BLOB;
    }else if (strcmp(type_buffer, "tree") == 0){
        obj->type = OBJECT_TYPE_TREE;
    }else if (strcmp(type_buffer, "commit") == 0){
        obj->type = OBJECT_TYPE_COMMIT;
    }else if (strcmp(type_buffer, "tag") == 0){
        obj->type = OBJECT_TYPE_TAG;
    }else{
        gitlet_panic("Invalid object type: %s", type_buffer);
    }

    // Parse size
    char * check_ptr = current_ptr;
    obj->file_size = strtol(current_ptr, &check_ptr, 10);
    if (*check_ptr != '\0' || obj->file_size < 0){
        gitlet_panic("Invalid object size: %s", current_ptr);
    }

    // Skip the null terminator after size
    current_ptr = check_ptr + 1;  

    if (obj->file_size > FILE_BUFFER_SIZE){
        // means the object is a large object and the decompressed buffer is not enough
        gitlet_panic("Object too large: %llu bytes", obj->file_size);
    }else{
        // Store the content
        obj->content = (unsigned char *)malloc(obj->file_size + 1);
        strncpy((char *)obj->content, current_ptr, obj->file_size);
        obj->content[obj->file_size] = '\0';
    }

    free(decompressed_buffer);
}
void object_write(struct object * obj){

}


void object_hash(char * buffer, const char * file){
    FILE * file_stream = fopen(file, "rb");
    if (file_stream == NULL){
        gitlet_panic("Failed to open the file: %s", file);
    }

    // get the file size
    fseek(file_stream, 0, SEEK_END);
    long file_size = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);

    // get the memory for the file content and header
    char * file_content = (char *)malloc(file_size + OBJECT_HEADER_SIZE);
    if (file_content == NULL){
        gitlet_panic("Failed to allocate memory for the file content and header");
    }

    // add the object type
    char * current_ptr = file_content;
    strncpy(current_ptr, "blob", 4);
    current_ptr += 4;

    // add the space
    *current_ptr = ' ';
    current_ptr++;

    // write the file size to the buffer
    char file_size_str[20] = {0};
    snprintf(file_size_str, 20, "%ld", file_size);
    strncpy(current_ptr, file_size_str, strlen(file_size_str));
    current_ptr += strlen(file_size_str);

    // add the null terminator
    *current_ptr = '\0';
    current_ptr++;

    if ((long)(current_ptr - file_content) > OBJECT_HEADER_SIZE){
        gitlet_panic("Run out of header memory");
    }

    // add the file content
    if (fread(current_ptr, 1, file_size, file_stream) != (unsigned long)file_size){
        gitlet_panic("Failed to read the file: %s", file);
    }
    current_ptr += file_size;

    // hash the file
    str_hash_sha1_n(buffer, file_content, (size_t)(current_ptr - file_content));

    free(file_content);
    fclose(file_stream);
}