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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <command/hash-object.h>
#include <util/error.h>
#include <util/str.h>
#include <util/files.h>
#include <argparse.h>

// gitlet hash-object [-w] [file]
void command_hash_object(int argc, char *argv[]) {
    char current_dir[PATH_MAX];
    memset(current_dir, 0, PATH_MAX);

    if (getcwd(current_dir, PATH_MAX) == NULL){
        gitlet_panic("Failed to get the current working directory");
    }

    struct argparse_description description;
    description._program_name =  NULL;
    description._usage = "gitlet hash-object [file]";
    description._description = "Hash an object";

    bool w_flag = false;

    struct argparse_option options[] = {
        OPTION_GROUP("Options"),
        OPTION_HELP(),
        OPTION_BOOLEAN('w', NULL, "write the object to the repository", &w_flag, NULL, 0),
        OPTION_GROUP_END(),
        OPTION_END()
    };

    struct argparse argparse;
    argparse_init(&argparse, options, &description);

    if (argc == 0){
        argparse_parse(&argparse, 1, (char *[]){"-h"});
    }else{
        const char * last_arg = argv[argc - 1];
        
        if (str_start_with(last_arg, "-") || str_equals(last_arg, "--")){
            argparse_parse(&argparse, argc, argv);
        }else{
            // by default, the last argument is the file to be hashed
            argparse_parse(&argparse, argc - 1, argv + 1);
        }

        if (w_flag){
            /// TODO: Implement write the object to the repository
        }else{
            /// TODO: Implement hash the object
        }

    }
}