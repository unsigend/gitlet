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

#ifndef GITLET_UTIL_STR_H
#define GITLET_UTIL_STR_H

/**
 * @brief: string helper functions
 */

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief: check if the string starts with the prefix
 * @param str: the string to check
 * @param prefix: the prefix to check
 * @return: true if the string starts with the prefix, false otherwise
 */
extern bool str_start_with(const char *str, const char *prefix);
/**
 * @brief: check if the string ends with the suffix
 * @param str: the string to check
 * @param suffix: the suffix to check
 * @return: true if the string ends with the suffix, false otherwise
 */
extern bool str_end_with(const char *str, const char *suffix);

/**
 * @brief: check if the string contains the substring
 * @param str: the string to check
 * @param substr: the substring to check
 * @return: true if the string contains the substring, false otherwise
 */
extern bool str_contains(const char *str, const char *substr);

/**
 * @brief: check if the two strings are equal
 * @param str1: the first string
 * @param str2: the second string
 * @return: true if the two strings are equal, false otherwise
 */
extern bool str_equals(const char *str1, const char *str2);

/**
 * @brief: Hash the null terminated string using SHA1
 * @param buffer: The buffer to store the hash
 * @param str: The string to be hashed
 */
extern void str_hash_sha1(char * restrict buffer, const char * str);

/**
 * @brief: Hash the string with the length using SHA1
 * @param buffer: The buffer to store the hash
 * @param str: The string to be hashed
 * @param len: The length of the string
 */
extern void str_hash_sha1_n(char * restrict buffer, const char * str, size_t len);

/**
 * @brief: Decompress the content using zlib
 * @param src_buffer: The source buffer
 * @param src_size: The size of the source buffer
 * @param dest_buffer: The destination buffer
 * @param dest_size: The size of the destination buffer
 * @param ignore_error: Whether to ignore the error
 * @return: The size of the decompressed content
 */
extern unsigned long str_decompress(const char * src_buffer, size_t src_size, 
    char * dest_buffer, size_t dest_size, bool ignore_error);

/**
 * @brief: Compress the content using zlib
 * @param src_buffer: The source buffer
 * @param src_size: The size of the source buffer
 * @param dest_buffer: The destination buffer
 * @param dest_size: The size of the destination buffer
 * @return: The size of the compressed content
 */
extern unsigned long str_compress(const char * src_buffer, size_t src_size, 
    char * dest_buffer, size_t dest_size);

#endif // GITLET_UTIL_STR_H