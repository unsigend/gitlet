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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include <command/init.h>
#include <global/config.h>
#include <util/error.h>
#include <util/files.h>
#include <object/repository.h>
#include <util/str.h>

#include <argparse.h>

/**
 * @usage: gitlet init [--help | -h] [path]
 */
void command_init(int argc, char *argv[]) {
    char current_path[PATH_MAX];
    if (!getcwd(current_path, PATH_MAX)){
        gitlet_panic("fatal: failed to get current working directory");
    }

    if (argc == 0){
        repository_create(current_path);
    }else{
        struct argparse_description description = {
            "Initialize a new gitlet repository",
            NULL,
            "gitlet init [--help | -h] [path]",
            NULL
        };
        struct argparse_option options[] = {
            OPTION_GROUP("Options"),
            OPTION_HELP(),
            OPTION_GROUP_END(),
            OPTION_END()
        };
        struct argparse argparse;
        argparse_init(&argparse, options, &description);

        const char * dir_path = argv[argc - 1];
        if (str_start_with(dir_path, "-") || str_start_with(dir_path, "--")){
            // the last argument is a option, init at current directory
            argparse_parse(&argparse, argc, argv);
            repository_create(current_path);
        }else{
            // the last argument is a path to the repository
            argc--;
            if (argc != 0){
                argparse_parse(&argparse, argc, argv);
            }
            // path check
            if (str_start_with(dir_path, ".") || str_start_with(dir_path, "..")
            || str_start_with(dir_path, "/")){
                // if the path is a relative path or absolute path, create the repository in the path
                repository_create(dir_path);
            }else{
                // if the path is a directory, create the repository in the the current directory
                strcat(current_path, "/");
                strcat(current_path, dir_path);
                repository_create(current_path);
            }
        }
    }
}