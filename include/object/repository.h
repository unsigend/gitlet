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

#ifndef GITLET_OBJECT_REPOSITORY_H
#define GITLET_OBJECT_REPOSITORY_H

#include <stdbool.h>

struct repository{
    const char * working_tree_path;
    const char * gitlet_repo_path;
};

/**
 * @brief: Initialize the repository object, and do the error check if the check option is enable
 * @param this: The repository object to initialize
 * @param path: The path to the repository
 * @param check: Whether to enable the error check
 */
extern void repository_object_init(struct repository * this, const char * path, bool check);

/**
 * @brief: Create a new repository, if the path does not exist, create a new repository in the path.
 *         And create the directory structure of the repository.
 * @param path: The path to the repository
 */
extern void repository_create(const char * path);

#endif // GITLET_OBJECT_REPOSITORY_H