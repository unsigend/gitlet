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
#include <stdio.h>

#include <object/repository.h>
#include <util/error.h>
#include <util/str.h>
#include <util/files.h>
#include <global/config.h>


static char gitlet_repo_path[PATH_MAX];

void repository_object_init(struct repository * this, const char * path, bool force){
    this->working_tree_path = path;
    memset(gitlet_repo_path, 0, PATH_MAX);
    strcpy(gitlet_repo_path, this->working_tree_path);
    if (!str_end_with(gitlet_repo_path, "/")){
        strcat(gitlet_repo_path, "/");
    }
    strcat(gitlet_repo_path, ".gitlet");
    this->gitlet_repo_path = gitlet_repo_path;

    // error check
    if (force){
        // only the force option is disable then do the error check
        if (!exists(this->gitlet_repo_path)){
            gitlet_panic("Not a gitlet repository");
        }
    }
}

void repository_create(const char * path){
    struct repository this;

    repository_object_init(&this, path, false);

    /// error checking

    // not a directory
    if (exists(this.working_tree_path) && !is_directory(this.working_tree_path)){
        gitlet_panic("Not a directory: %s", this.working_tree_path);
    }
    // .git filename conflict
    if (exists(this.gitlet_repo_path) && !is_directory(this.gitlet_repo_path)){
        gitlet_panic("unable to mkdir .gitlet: File exists", this.gitlet_repo_path);
    }

    // already a repository
    if (exists(this.gitlet_repo_path)){
        fprintf(stdout, "Reinitialized existing Gitlet repository in %s", this.gitlet_repo_path);
        if (!str_end_with(this.gitlet_repo_path, "/")){
            fprintf(stdout, "/");
        }
        fprintf(stdout, "\n");
        return;
    }

    // create working tree directory
    if (!exists(this.working_tree_path)){
        if (!create_directory(this.working_tree_path)){
            gitlet_panic("fatal: unable to mkdir %s", this.working_tree_path);
        }
    }

    // create .gitlet directory
    if (!create_directory(this.gitlet_repo_path)){
        gitlet_panic("fatal: unable to mkdir %s", this.gitlet_repo_path);
    }else{
        fprintf(stdout, "Initialized empty Gitlet repository in %s", this.gitlet_repo_path);
        if (!str_end_with(this.gitlet_repo_path, "/")){
            fprintf(stdout, "/");
        }
        fprintf(stdout, "\n");
    }

    char path_buffer[PATH_MAX];
    memset(path_buffer, 0, PATH_MAX);

    // create .gitlet/objects directory
    strcpy(path_buffer, this.gitlet_repo_path);
    strcat(path_buffer, "/objects");
    if (!create_directory(path_buffer)){
        gitlet_panic("fatal: unable to mkdir %s", path_buffer);
    }

    // create .gitlet/refs directory
    strcpy(path_buffer, this.gitlet_repo_path);
    strcat(path_buffer, "/refs");
    if (!create_directory(path_buffer)){
        gitlet_panic("fatal: unable to mkdir %s", path_buffer);
    }

    // create .gitlet/refs/heads directory
    strcpy(path_buffer, this.gitlet_repo_path);
    strcat(path_buffer, "/refs/heads");
    if (!create_directory(path_buffer)){
        gitlet_panic("fatal: unable to mkdir %s", path_buffer);
    }

    // create .gitlet/refs/tags directory
    strcpy(path_buffer, this.gitlet_repo_path);
    strcat(path_buffer, "/refs/tags");
    if (!create_directory(path_buffer)){
        gitlet_panic("fatal: unable to mkdir %s", path_buffer);
    }

    // create .gitlet/HEAD file
    strcpy(path_buffer, this.gitlet_repo_path);
    strcat(path_buffer, "/HEAD");
    FILE * file_head = fopen(path_buffer, "w");
    if (file_head == NULL){
        gitlet_panic("fatal: unable to create file %s", path_buffer);
    }
    fprintf(file_head, "ref: refs/heads/master\n");
    fclose(file_head);

    // create .gitlet/config file
    strcpy(path_buffer, this.gitlet_repo_path);
    strcat(path_buffer, "/config");
    if (!create_file(path_buffer)){
        gitlet_panic("fatal: unable to create file %s", path_buffer);
    }

    // create .gitlet/description file
    strcpy(path_buffer, this.gitlet_repo_path);
    strcat(path_buffer, "/description");
    FILE * file_description = fopen(path_buffer, "w");
    if (file_description == NULL){
        gitlet_panic("fatal: unable to create file %s", path_buffer);
    }
    fprintf(file_description, "Unnamed repository; edit this file 'description' to name the repository.\n");
    fclose(file_description);
}
