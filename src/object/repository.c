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
#include <sys/stat.h>
#include <unistd.h>

#include <object/repository.h>
#include <util/error.h>
#include <util/files.h>

static char gitlet_repo_path[PATH_MAX];

void repository_object_init(struct repository * this, const char * path, bool force){
    this->working_tree_path = path;
    memset(gitlet_repo_path, 0, PATH_MAX);
    strcpy(gitlet_repo_path, this->working_tree_path);
    strcat(gitlet_repo_path, "/.gitlet");
    this->gitlet_repo_path = gitlet_repo_path;

    // error check
    if (!force){
        // only the force option is disable then do the error check
        if (!exists(this->gitlet_repo_path)){
            gitlet_panic("Not a gitlet repository");
        }
    }
}
