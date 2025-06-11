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

#define FILE_BUFFER_SIZE            UINT16_MAX
#define OBJECT_HEADER_SIZE          64
#define SMALL_FILE_BUFFER_SIZE      512

/**
 * @brief: Decompress the file
 * @param file_path: The path to the file to decompress
 * @param decompressed_buffer: The buffer to store the decompressed file
 * @param buffer_size: The size of the buffer
 * 
 * @category: Private
 */
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
    if (compressed_buffer == NULL) {
        fclose(file_stream);
        gitlet_panic("Failed to allocate memory for compressed buffer");
    }
    
    size_t bytes_read = fread(compressed_buffer, 1, file_size, file_stream);
    if (bytes_read != (size_t)file_size){
        free(compressed_buffer);
        fclose(file_stream);
        gitlet_panic("Failed to read the file: %s", file_path);
    }
    fclose(file_stream);

    // decompress the file
    uLongf decompressed_size = buffer_size;
    int result = uncompress((Bytef *)decompressed_buffer, &decompressed_size, (Bytef *)compressed_buffer, file_size);
    if (result != Z_OK){
        free(compressed_buffer);
        gitlet_panic("Failed to decompress the file: %s", file_path);
    }
    free(compressed_buffer);
}

/**
 * @brief: Compress the content
 * @param src_buffer: The source buffer
 * @param src_size: The size of the source buffer
 * @param dest_buffer: The destination buffer
 * @param dest_size: The size of the destination buffer
 * @return: The size of the compressed content
 * 
 */
static uLongf _compress_content(const char * src_buffer, size_t src_size, char * dest_buffer, size_t dest_size){
    // compress the content
    uLongf compressed_size = dest_size;
    int result = compress((Bytef *)dest_buffer, &compressed_size, (Bytef *)src_buffer, src_size);
    if (result != Z_OK){
        if (result == Z_MEM_ERROR){
            gitlet_panic("Out of memory");
        }else if (result == Z_BUF_ERROR){
            gitlet_panic("Buffer too small");
        }else{
            gitlet_panic("Failed to compress the content: %d", result);
        }
    }
    return compressed_size;
}

/**
 * @brief: Add the object header to the file
 * @param file: The file to add the header to
 * @param total_size: The size of the file with header added
 * @return: The file content with header added
 * 
 * @note: The caller should free the returned memory on heap
 * @category: Private
 */
static char * _add_object_header(const char * file, size_t* total_size){
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
        fclose(file_stream);
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
        free(file_content);
        fclose(file_stream);
        gitlet_panic("Run out of header memory");
    }

    // add the file content
    if (fread(current_ptr, 1, file_size, file_stream) != (unsigned long)file_size){
        free(file_content);
        fclose(file_stream);
        gitlet_panic("Failed to read the file: %s", file);
    }
    current_ptr += file_size;
    *total_size = (size_t)(current_ptr - file_content);

    fclose(file_stream);
    return file_content;
}


void object_read(struct object * obj, const char * sha1){
    char object_file_path[PATH_MAX] = {0};
    if (getcwd(object_file_path, PATH_MAX) == NULL){
        gitlet_panic("Failed to get the current working directory");
    }
    
    size_t current_len = strlen(object_file_path);
    if (current_len + 20 >= PATH_MAX) { 
        gitlet_panic("Path too long for object file");
    }
    
    strcat(object_file_path, "/.gitlet/objects/");
    strncpy(object_file_path + strlen(object_file_path), sha1, 2);
    strcat(object_file_path, "/");
    strncpy(object_file_path + strlen(object_file_path), sha1 + 2, 38);
    
    char * decompressed_buffer = (char *)malloc(FILE_BUFFER_SIZE);
    if (decompressed_buffer == NULL) {
        gitlet_panic("Failed to allocate memory for decompressed buffer");
    }
    
    _decompress_file(object_file_path, decompressed_buffer, FILE_BUFFER_SIZE);

    // Parse type
    char * type_buffer = decompressed_buffer;
    char * current_ptr = (char *)strchr(type_buffer, ' ');
    if (current_ptr == NULL){
        free(decompressed_buffer);
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
        free(decompressed_buffer);
        gitlet_panic("Invalid object type: %s", type_buffer);
    }

    // Parse size
    char * check_ptr = current_ptr;
    obj->file_size = strtol(current_ptr, &check_ptr, 10);
    if (*check_ptr != '\0' || obj->file_size < 0){
        free(decompressed_buffer);
        gitlet_panic("Invalid object size: %s", current_ptr);
    }

    // Skip the null terminator after size
    current_ptr = check_ptr + 1;  

    if (obj->file_size > FILE_BUFFER_SIZE){
        // means the object is a large object and the decompressed buffer is not enough
        free(decompressed_buffer);
        gitlet_panic("Object too large: %llu bytes", obj->file_size);
    }else{
        // Store the content
        obj->content = (unsigned char *)malloc(obj->file_size + 1);
        if (obj->content == NULL) {
            free(decompressed_buffer);
            gitlet_panic("Failed to allocate memory for object content");
        }
        strncpy((char *)obj->content, current_ptr, obj->file_size);
        obj->content[obj->file_size] = '\0';
    }

    free(decompressed_buffer);
}
void object_write(char * buffer, const char * file, bool write_to_repo){
    size_t uncompressed_file_size = 0;
    char * file_content_ptr = _add_object_header(file, &uncompressed_file_size);

    str_hash_sha1_n(buffer, file_content_ptr, uncompressed_file_size);

    if (write_to_repo){

        size_t compressed_file_size = uncompressed_file_size < SMALL_FILE_BUFFER_SIZE 
        ? SMALL_FILE_BUFFER_SIZE : uncompressed_file_size;
        
        // get enough memory for the compressed file
        char * compressed_buffer = (char *)malloc(compressed_file_size);
        if (compressed_buffer == NULL){
            free(file_content_ptr);
            gitlet_panic("Failed to allocate memory for the compressed file");
        }

        // compress the file
        uLongf compressed_size = _compress_content(file_content_ptr, uncompressed_file_size, 
            compressed_buffer, compressed_file_size);

        // compute the file path
        char file_path[PATH_MAX] = {0};
        if (getcwd(file_path, PATH_MAX) == NULL){
            free(compressed_buffer);
            free(file_content_ptr);
            gitlet_panic("Failed to get the current working directory");
        }
        strcat(file_path, "/.gitlet/objects/");
        strncpy(file_path + strlen(file_path), buffer, 2);

        // create the directory if it does not exist
        if (!exists(file_path) || !is_directory(file_path)){
            if (!create_directory(file_path)){
                free(compressed_buffer);
                free(file_content_ptr);
                gitlet_panic("Failed to create the directory: %s", file_path);
            }
        }

        strcat(file_path, "/");
        strncpy(file_path + strlen(file_path), buffer + 2, 38);
        
        // write the compressed file to the gitlet repository
        FILE * file_stream = fopen(file_path, "wb");
        if (file_stream == NULL){
            free(compressed_buffer);
            free(file_content_ptr);
            gitlet_panic("Failed to open the file: %s", file_path);
        }
        if (fwrite(compressed_buffer, 1, compressed_size, file_stream) != compressed_size){
            free(compressed_buffer);
            free(file_content_ptr);
            gitlet_panic("Failed to write the compressed file: %s", file_path);
        }
        // free the resources
        fclose(file_stream);
        free(compressed_buffer);
    }

    free(file_content_ptr);
}