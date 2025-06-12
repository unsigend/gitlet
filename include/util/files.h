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

#ifndef GITLET_UTIL_FILES_H
#define GITLET_UTIL_FILES_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Check if a file or directory exists
 * 
 * @param path The path to check
 * @return true if the file or directory exists, false otherwise
 */
extern bool exists(const char * path);

/**
 * @brief Create a directory
 * 
 * @param path The path to the directory
 * @return true if the directory is created, false otherwise
 */
extern bool create_directory(const char * path);

/**
 * @brief Create a file
 * 
 * @param file_name The name of the file
 * @return true if the file is created, false otherwise
 */
extern bool create_file(const char * file_name);

/**
 * @brief Remove a directory
 * 
 * @param path The path to the directory
 * @return true if the directory is removed, false otherwise
 */
extern bool remove_directory(const char * path);

/**
 * @brief Remove a file
 * 
 * @param file_name The name of the file
 * @return true if the file is removed, false otherwise
 */
extern bool remove_file(const char * file_name);

/**
 * @brief Check if a path is a directory
 * 
 * @param path The path to check
 * @return true if the path is a directory, false otherwise
 */
extern bool is_directory(const char * path);

/**
 * @brief Get the size of a file
 * 
 * @param file The file to get the size of
 * @return The size of the file
 */
extern size_t file_size(FILE * file);

#endif // GITLET_UTIL_FILES_H