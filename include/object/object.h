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

#ifndef GITLET_OBJECT_OBJECT_H
#define GITLET_OBJECT_OBJECT_H

/**
 * @brief: This header provide the uniform abstraction 
 *         for the object in the gitlet.
 */
#include <stdint.h>

/**
 * @brief: The type of the object
 * @param OBJECT_TYPE_BLOB: The blob object
 * @param OBJECT_TYPE_TREE: The tree object
 * @param OBJECT_TYPE_COMMIT: The commit object
 * @param OBJECT_TYPE_TAG: The tag object
 * @param OBJECT_TYPE_UNKNOWN: The unknown object
 */
enum object_type{
    OBJECT_TYPE_BLOB,
    OBJECT_TYPE_TREE,
    OBJECT_TYPE_COMMIT,
    OBJECT_TYPE_TAG,
    OBJECT_TYPE_UNKNOWN,
};

/**
 * @brief: The gitlet object structure
 * @param type: The type of the object
 * @param file_size: The size of the object file
 * @param content: The content of the object
 */
struct object{
    enum object_type type;
    uint64_t file_size;
    unsigned char * content;
};

/**
 * @brief: Read the object from the gitlet repository
 * @param obj: The object to be store the result
 * @param sha1: The sha1 of the object
 */
extern void object_read(struct object * obj, const char * sha1);

/**
 * @brief: Write the object to the gitlet repository
 * @param obj: The object to be written
 */
extern void object_write(struct object * obj);

/**
 * @brief: Add the header to the buffer and hash the file using SHA1, 
 *         write the result to the buffer.
 * @param buffer: The buffer to store the hash the length of the buffer is 40 bytes
 * @param file: The file to be hashed
 */
extern void object_hash(char * buffer, const char * file);

#endif