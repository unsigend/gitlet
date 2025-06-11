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
#include <sys/stat.h>
#include <openssl/sha.h>

#include <object/object.h>
#include <object/repository.h>
#include <util/files.h>
#include <util/str.h>
#include <util/error.h>


#define SMALL_BUFFER_SIZE           512
#define MEDIUM_BUFFER_SIZE          1024
#define LARGE_BUFFER_SIZE           UINT16_MAX

#define HEADER_TYPE_MAX_LENGTH      12
#define HEADER_MAX_SIZE             128

/**
 * @brief: Read the object header from the buffer
 * @param buffer: The buffer to read from
 * @param obj: The object to store the result
 * @return: The pointer to the file content
 */
static char * _read_object_header(char * buffer, struct object * obj){
    // type buffer
    char type_buffer[HEADER_TYPE_MAX_LENGTH];
    memset(type_buffer, 0, HEADER_TYPE_MAX_LENGTH);

    char * current_ptr = strchr(buffer, ' ');
    if (current_ptr == NULL){
        gitlet_panic("Invalid object file");
    }

    *current_ptr = '\0';
    strcpy(type_buffer, buffer);
    ++current_ptr;

    if (str_equals(type_buffer, "blob")){
        obj->type = OBJECT_TYPE_BLOB;
    }else if (str_equals(type_buffer, "tree")){
        obj->type = OBJECT_TYPE_TREE;
    }else if (str_equals(type_buffer, "commit")){
        obj->type = OBJECT_TYPE_COMMIT;
    }else if (str_equals(type_buffer, "tag")){
        obj->type = OBJECT_TYPE_TAG;
    }else{
        gitlet_panic("Invalid object type: %s", type_buffer);
    }
    
    // get the file size
    char * _dest = NULL;
    obj->file_size = strtol(current_ptr, &_dest, 10);
    if (*_dest != '\0'){
        gitlet_panic("Invalid object file");
    }
    ++_dest;
    current_ptr = _dest;

    return current_ptr;
}

/// TODO: Rebuild this function
/**
 * @brief: Write the object header to the buffer
 * @param file: The file to add the header to
 * @param total_size: The size of the file with header added
 * @return: The file content with header added
 * 
 * @note: The caller should free the returned memory on heap
 * @category: Private
 */
static char * _write_object_header(const char * file, size_t* total_size){
    FILE * file_stream = fopen(file, "rb");
    if (file_stream == NULL){
        gitlet_panic("Failed to open the file: %s", file);
    }

    // get the file size
    fseek(file_stream, 0, SEEK_END);
    long file_size = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);

    // get the memory for the file content and header
    char * file_content = (char *)malloc(file_size + HEADER_MAX_SIZE);
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

    if ((long)(current_ptr - file_content) > HEADER_MAX_SIZE){
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


    char file_path[PATH_MAX];
    memset(file_path, 0, PATH_MAX);

    if (getcwd(file_path, PATH_MAX) == NULL){
        gitlet_panic("Failed to get the current working directory");
    }

    strcat(file_path, "/.gitlet/objects/");
    strncpy(file_path + strlen(file_path), sha1, 2);
    strcat(file_path, "/");
    strncpy(file_path + strlen(file_path), sha1 + 2, 38);

    // check if the file exists
    if (!exists(file_path)){
        gitlet_panic("Object file not found: %s", file_path);
    }

    // open the file
    FILE * object_file = fopen(file_path, "rb");
    if (object_file == NULL){
        gitlet_panic("Failed to open the object file: %s", file_path);
    }

    // get the file size
    fseek(object_file, 0, SEEK_END);
    long file_size = ftell(object_file);
    if (file_size < 0) {
        fclose(object_file);
        gitlet_panic("Failed to get file size: %s", file_path);
    }
    fseek(object_file, 0, SEEK_SET);

    // get the memory for the file content and header
    char * compressed_buffer = (char *)malloc(file_size);
    if (compressed_buffer == NULL){
        fclose(object_file);
        gitlet_panic("Failed to allocate memory for the compressed file");
    }

    // read the file
    if (fread(compressed_buffer, 1, file_size, object_file) != (unsigned long)file_size){
        free(compressed_buffer);
        fclose(object_file);
        gitlet_panic("Failed to read the object file: %s", file_path);
    }

    fclose(object_file);

    size_t decompressed_size;
    bool read_header_only;
    if (file_size < HEADER_MAX_SIZE){
        decompressed_size = file_size;
        read_header_only = false;
    }else{
        // only read the header
        read_header_only = true;
        decompressed_size = HEADER_MAX_SIZE;
    }
    
    char * decompressed_buffer = (char *)malloc(decompressed_size);
    if (decompressed_buffer == NULL){
        free(compressed_buffer);
        gitlet_panic("Failed to allocate memory for the decompressed file");
    }

    str_decompress(compressed_buffer, file_size, decompressed_buffer,
    decompressed_size, read_header_only);

    char * content_ptr = _read_object_header(decompressed_buffer, obj);

    if (read_header_only){
        // free the decompressed buffer and re-malloc a new bigger buffer
        free(decompressed_buffer);
        decompressed_buffer = (char *)malloc(obj->file_size + HEADER_MAX_SIZE);
        if (decompressed_buffer == NULL){
            free(compressed_buffer);
            gitlet_panic("Failed to allocate memory for the decompressed file");
        }
        // re-decompress the content
        str_decompress(compressed_buffer, file_size, decompressed_buffer,
        obj->file_size + HEADER_MAX_SIZE, false);

        char * null_terminator_ptr = memchr(decompressed_buffer, '\0', HEADER_MAX_SIZE);
        if (null_terminator_ptr == NULL){
            free(compressed_buffer);
            free(decompressed_buffer);
            gitlet_panic("Invalid object file: %s", file_path);
        }
        ++null_terminator_ptr;
        obj->content = (unsigned char *)malloc(obj->file_size + 1);
        if (obj->content == NULL){
            free(compressed_buffer);
            free(decompressed_buffer);
            gitlet_panic("Failed to allocate memory for the object content");
        }
        memcpy(obj->content, null_terminator_ptr, obj->file_size);
        obj->content[obj->file_size] = '\0';

        // free the compressed buffer
        free(compressed_buffer);
    }else{
        obj->content = (unsigned char *)malloc(obj->file_size + 1);
        if (obj->content == NULL){
            free(compressed_buffer);
            free(decompressed_buffer);
            gitlet_panic("Failed to allocate memory for the object content");
        }
        memcpy(obj->content, content_ptr, obj->file_size);
        obj->content[obj->file_size] = '\0';

        // free all the resources
        free(compressed_buffer);
        free(decompressed_buffer);
    }
}
void object_write(char * buffer, const char * file, bool write_to_repo){
    size_t uncompressed_file_size = 0;
    char * file_content_ptr = _write_object_header(file, &uncompressed_file_size);

    str_hash_sha1_n(buffer, file_content_ptr, uncompressed_file_size);

    if (write_to_repo){

        size_t compressed_file_size = uncompressed_file_size < SMALL_BUFFER_SIZE 
        ? SMALL_BUFFER_SIZE : uncompressed_file_size;
        
        // get enough memory for the compressed file
        char * compressed_buffer = (char *)malloc(compressed_file_size);
        if (compressed_buffer == NULL){
            free(file_content_ptr);
            gitlet_panic("Failed to allocate memory for the compressed file");
        }

        // compress the file
        uLongf compressed_size = str_compress(file_content_ptr, uncompressed_file_size, 
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