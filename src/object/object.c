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

#define OBJECT_PATH_DIR_SIZE                2
#define OBJECT_PATH_FILE_SIZE               38
#define OBJECT_TYPE_SIZE                    16

// Make sure the buffer size is large enough to hold the compressed file header
#define OBJECT_RAW_FILE_HEADER_BUFFER_SIZE  64
#define OBJECT_FILE_HEADER_BUFFER_SIZE      128

/**
 * @brief: <type> <size>\0 
 * OBJECT_RAW_FILE_HEADER_BUFFER_SIZE : Read a chuck of 64 bytes for compressed file header
 * OBJECT_FILE_HEADER_BUFFER_SIZE     : Read a chuck of 128 bytes for decompressed file header
 */

void object_init(struct object * this, struct repository * repo, const char * sha1){
    char object_path[PATH_MAX] = {0};
    strcpy(object_path, repo->gitlet_repo_path);
    strcat(object_path, "/objects/");

    // get the object path from the sha1
    strncpy(object_path + strlen(object_path), sha1, OBJECT_PATH_DIR_SIZE);
    strcat(object_path, "/");
    strncpy(object_path + strlen(object_path), sha1 + OBJECT_PATH_DIR_SIZE, OBJECT_PATH_FILE_SIZE);

    // check the file exist
    if (!exists(object_path)){
        gitlet_panic("Not a valid object name: %s", sha1);
    }

    FILE * raw_file_stream = fopen(object_path, "rb");
    if (raw_file_stream == NULL){
        gitlet_panic("Failed to open the object file: %s", object_path);
    }

    unsigned char * compressed_file_header = (unsigned char *)malloc(OBJECT_RAW_FILE_HEADER_BUFFER_SIZE);
    unsigned char * decompressed_file_header = (unsigned char *)malloc(OBJECT_FILE_HEADER_BUFFER_SIZE);

    if (compressed_file_header == NULL || decompressed_file_header == NULL){
        gitlet_panic("Failed to allocate memory for the raw file header buffer");
    }
    
    // read the compressed file header
    if (fread((void *)compressed_file_header, 1, OBJECT_RAW_FILE_HEADER_BUFFER_SIZE, raw_file_stream)
        != OBJECT_RAW_FILE_HEADER_BUFFER_SIZE){
        if (!feof(raw_file_stream)) {
            gitlet_panic("Failed to read the raw file header");
        }
    }

    uLongf decompressed_file_header_size = OBJECT_FILE_HEADER_BUFFER_SIZE;
    int result = uncompress((Bytef *)decompressed_file_header, &decompressed_file_header_size, 
    (Bytef *)compressed_file_header, OBJECT_RAW_FILE_HEADER_BUFFER_SIZE);

    if (result != Z_OK){
        // Just skip the error, only the type and size are needed
        if (result == Z_BUF_ERROR || result == Z_DATA_ERROR){ }
        else{
            gitlet_panic("Failed to decompress the raw file header");
        }
    }

    /// TODO: Check the buffer bug here
    // get the type of the object
    char type_buffer[OBJECT_TYPE_SIZE] = {0};
    strncpy(type_buffer, (char *)decompressed_file_header, OBJECT_TYPE_SIZE);
    char * space_ptr = (char *)memchr(type_buffer, ' ', OBJECT_TYPE_SIZE);
    if (space_ptr == NULL){
        gitlet_panic("Invalid object type: %s", type_buffer);
    }
    *space_ptr = '\0';
    
    if (str_equals(type_buffer, "blob")){
        this->type = OBJECT_TYPE_BLOB;
    } else if (str_equals(type_buffer, "tree")){
        this->type = OBJECT_TYPE_TREE;
    } else if (str_equals(type_buffer, "commit")){
        this->type = OBJECT_TYPE_COMMIT;
    } else if (str_equals(type_buffer, "tag")){
        this->type = OBJECT_TYPE_TAG;
    } else {
        gitlet_panic("Invalid object type: %s", type_buffer);
    }

    // get the size of the object
    char * check_ptr = NULL;
    this->file_size = strtoull(strchr((char *)decompressed_file_header, ' ') + 1, &check_ptr, 10);
    if (check_ptr == NULL || *check_ptr != '\0'){
        gitlet_panic("Invalid object size object file may be corrupted");
    }

    free(compressed_file_header);
    free(decompressed_file_header);
    fclose(raw_file_stream);
}