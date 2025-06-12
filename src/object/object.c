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

#define HEADER_TYPE_MAX_LENGTH      12
#define HEADER_MAX_SIZE             128

/**
 * @brief: Get the object file path
 * @param buffer: The buffer to store the object file path
 * @param buffer_size: The size of the buffer
 * @param sha1: The SHA1 of the object
 */
static inline void _get_object_file_path(char * restrict buffer, size_t buffer_size, 
    const char * restrict sha1){
    if (getcwd(buffer, buffer_size) == NULL){
        gitlet_panic("Failed to get the current working directory");
    }
    strcat(buffer, "/.gitlet/objects/");
    strncpy(buffer + strlen(buffer), sha1, 2);
    strcat(buffer, "/");
    strncpy(buffer + strlen(buffer), sha1 + 2, 38);
}

/**
 * @brief: Read the object header
 * @param buffer: The buffer to read from
 * @param obj: The object to store the result
 */
static void _read_object_header(char * buffer, struct object * obj){
    char _type_buffer[HEADER_TYPE_MAX_LENGTH];
    memset(_type_buffer, 0, HEADER_TYPE_MAX_LENGTH);

    char * _current_ptr = buffer;
    _current_ptr = strchr(_current_ptr, ' ');
    if (_current_ptr == NULL){
        gitlet_panic("Failed to find the space in the buffer");
    }
    *_current_ptr = '\0';

    strcpy(_type_buffer, buffer);
    _current_ptr++;

    if (str_equals(_type_buffer, "blob")){
        obj->type = OBJECT_TYPE_BLOB;
    } else if (str_equals(_type_buffer, "tree")){
        obj->type = OBJECT_TYPE_TREE;
    } else if (str_equals(_type_buffer, "commit")){
        obj->type = OBJECT_TYPE_COMMIT;
    } else if (str_equals(_type_buffer, "tag")){
        obj->type = OBJECT_TYPE_TAG;
    } else {
        gitlet_panic("Invalid object type: %s", _type_buffer);
    }

    char * _dest = NULL;
    obj->file_size = strtol(_current_ptr, &_dest, 10);
    if (*_dest != '\0'){
        gitlet_panic("Invalid object file size: %s", _current_ptr);
    }
    ++_dest;
    obj->content = (unsigned char *)_dest;
}

/**
 * @brief: Write the object header to the buffer
 * @param buffer: The buffer to write to
 * @param obj: The object to write the header to
 * @return: The pointer to the next position in the buffer
 */
static char * _write_object_header(char * buffer, const struct object * obj){
    const char * _type_buffer = NULL;
    switch (obj->type)
    {
    case OBJECT_TYPE_BLOB:
        _type_buffer = "blob";
        break;
    case OBJECT_TYPE_TREE:
        _type_buffer = "tree";
        break;
    case OBJECT_TYPE_COMMIT:
        _type_buffer = "commit";
        break;
    case OBJECT_TYPE_TAG:
        _type_buffer = "tag";
        break;
    default:
        gitlet_panic("Invalid object type: %d", obj->type);
    }

    int written = snprintf(buffer, HEADER_MAX_SIZE, "%s %zu", _type_buffer, (size_t)obj->file_size);
    if (written < 0 || written >= HEADER_MAX_SIZE) {
        gitlet_panic("Failed to write object header: buffer too small or error");
    }
    
    buffer[written] = '\0';
    return buffer + written + 1;
}

void object_read(struct object * obj, const char * sha1){
    char _file_buffer[PATH_MAX];
    memset(_file_buffer, 0, PATH_MAX);

    _get_object_file_path(_file_buffer, PATH_MAX, sha1);

    if (!exists(_file_buffer)){
        gitlet_panic("Object file not found: %s", _file_buffer);
    }

    // open the object file
    FILE * _file = fopen(_file_buffer, "rb");
    if (_file == NULL){
        gitlet_panic("Failed to open object file: %s", _file_buffer);
    }

    // read the header first
    size_t _compressed_header_size = file_size(_file) < HEADER_MAX_SIZE 
        ? file_size(_file) : HEADER_MAX_SIZE;

    char _compressed_header_buffer[HEADER_MAX_SIZE];
    memset(_compressed_header_buffer, 0, HEADER_MAX_SIZE);

    if (fread(_compressed_header_buffer, 1, _compressed_header_size, _file) 
        != _compressed_header_size){
        fclose(_file);
        gitlet_panic("Failed to read object header: %s", _file_buffer);
    }

    char _decompressed_header_buffer[HEADER_MAX_SIZE * 2];
    memset(_decompressed_header_buffer, 0, HEADER_MAX_SIZE * 2);

    str_decompress(_compressed_header_buffer, _compressed_header_size, 
        _decompressed_header_buffer, HEADER_MAX_SIZE * 2, true);

    _read_object_header(_decompressed_header_buffer, obj);

    if (obj->file_size < HEADER_MAX_SIZE){
        char * _content_ptr = (char *)obj->content;
        obj->content = (unsigned char *)malloc(obj->file_size + 1);
        if (obj->content == NULL){
            fclose(_file);
            gitlet_panic("Failed to allocate memory for object content");
        }
        memcpy(obj->content, _content_ptr, obj->file_size);
        obj->content[obj->file_size] = '\0';
    }else{
        size_t __compressed_buffer_size = file_size(_file);
        char *__compressed_buffer = (char *)malloc(__compressed_buffer_size);

        /**
         * Make sure the decompressed buffer has enough space to store 
         * the decompressed header and the file content
         */
        size_t __decompressed_buffer_size = HEADER_MAX_SIZE + obj->file_size + 1;
        char * __decompressed_buffer = (char *)malloc(__decompressed_buffer_size);
        if (__decompressed_buffer == NULL){
            free(__compressed_buffer);
            fclose(_file);
            gitlet_panic("Failed to allocate memory for decompressed header buffer");
        }
        // read the raw compressed content include the header
        if (fread(__compressed_buffer, 1, __compressed_buffer_size, _file) != __compressed_buffer_size){
            free(__compressed_buffer);
            free(__decompressed_buffer);
            fclose(_file);
            gitlet_panic("Failed to read object content: %s", _file_buffer);
        }

        // decompress the all the content
        str_decompress(__compressed_buffer, __compressed_buffer_size, 
            __decompressed_buffer, __decompressed_buffer_size, false);

        // skip the header and the null terminator
        char * _content_ptr = NULL;
        _content_ptr = memchr(__decompressed_buffer, '\0', HEADER_MAX_SIZE);
        if (_content_ptr == NULL){
            free(__compressed_buffer);
            free(__decompressed_buffer);
            fclose(_file);
            gitlet_panic("Failed to find the null terminator in the decompressed buffer");
        }
        _content_ptr++;

        /**
         * Copy the decompressed content from the buffer to the 
         * object content pointer.
         */
        obj->content = (unsigned char *)malloc(obj->file_size + 1);
        if (obj->content == NULL){
            free(__compressed_buffer);
            free(__decompressed_buffer);
            fclose(_file);
            gitlet_panic("Failed to allocate memory for object content");
        }
        memcpy(obj->content, _content_ptr, obj->file_size);
        obj->content[obj->file_size] = '\0';

        // free the memory for buffer
        free(__compressed_buffer);
        free(__decompressed_buffer);
    }
    fclose(_file);
}

void object_write(char * buffer, const char * file, bool write_to_repo){
    
    FILE * _file = fopen(file, "rb");
    if (_file == NULL){
        gitlet_panic("Failed to open file: %s", file);
    }

    struct object _obj;
    _obj.type = OBJECT_TYPE_BLOB;
    _obj.file_size = file_size(_file);

    /**
     * allocate the memory for the raw buffer : the header + the file content
     */
    char * _raw_buffer = (char *)malloc(_obj.file_size + HEADER_MAX_SIZE);
    if (_raw_buffer == NULL){
        fclose(_file);
        gitlet_panic("Failed to allocate memory for raw buffer");
    }
    /**
     * Write the object header to the buffer, and
     * the return pointer from the function is always
     * non-NULL.
     */
    char * _header_end = _write_object_header(_raw_buffer, &_obj);

    /**
     * Read the rest content from the file, and write it to the buffer.
     */
    if (fread(_header_end, 1, _obj.file_size, _file) != _obj.file_size){
        free(_raw_buffer);
        fclose(_file);
        gitlet_panic("Failed to read file content: %s", file);
    }
    // close the file
    fclose(_file);
    // update the header end pointer
    _header_end += _obj.file_size;

    /**
     * hash the file content after the header is added using SHA1
     */
    str_hash_sha1_n(buffer, _raw_buffer, (size_t)(_header_end - _raw_buffer));

    /**
     * If the write_to_repo flag is true, write the object to the gitlet object data base.
     */
    if (write_to_repo){
        char _object_file_path[PATH_MAX];
        memset(_object_file_path, 0, PATH_MAX);

        if (getcwd(_object_file_path, PATH_MAX) == NULL){
            gitlet_panic("Failed to get the current working directory");
        }

        strcat(_object_file_path, "/");
        strcat(_object_file_path, ".gitlet/objects/");
        strncpy(_object_file_path + strlen(_object_file_path), buffer, 2);

        if (!(exists(_object_file_path) && is_directory(_object_file_path))){
            if (!create_directory(_object_file_path)){
                gitlet_panic("Failed to create directory: %s", _object_file_path);
            }
        }

        strcat(_object_file_path, "/");
        strncpy(_object_file_path + strlen(_object_file_path), buffer + 2, 38);

        FILE * _object_file = fopen(_object_file_path, "wb");
        if (_object_file == NULL){
            gitlet_panic("Failed to open object file: %s", _object_file_path);
        }

        /**
         * Write the compressed content to the object file
         */
        char * _compressed_buffer = (char *)malloc(_obj.file_size + HEADER_MAX_SIZE);
        if (_compressed_buffer == NULL){
            fclose(_object_file);
            gitlet_panic("Failed to allocate memory for compressed buffer");
        }

        // compress the content
        str_compress(_raw_buffer, (size_t)(_header_end - _raw_buffer), 
            _compressed_buffer, _obj.file_size + HEADER_MAX_SIZE);

        if (fwrite(_compressed_buffer, 1, _obj.file_size + HEADER_MAX_SIZE, 
        _object_file) != _obj.file_size + HEADER_MAX_SIZE){
            fclose(_object_file);
            free(_compressed_buffer);
            gitlet_panic("Failed to write object file: %s", _object_file_path);
        }

        fclose(_object_file);
        free(_compressed_buffer);
    }

    // free the memory for raw buffer
    free(_raw_buffer);
}