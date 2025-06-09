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

#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include <argparse.h>

#include <command/cat-file.h>
#include <object/object.h>
#include <object/repository.h>
#include <util/error.h>
#include <util/str.h>
#include <util/files.h>

void command_cat_file(int argc, char *argv[]) {
    char current_dir[PATH_MAX];
    memset(current_dir, 0, PATH_MAX);

    if (getcwd(current_dir, PATH_MAX) == NULL){
        gitlet_panic("Failed to get the current working directory");
    }

    struct argparse_description description;
    description._program_name =  NULL;
    description._usage = "gitlet cat-file [object]";
    description._description = "Display the contents of an object";
    description._epilog = NULL;

    bool t_flag = false;
    bool p_flag = false;
    bool s_flag = false;
    bool e_flag = false;

    struct argparse_option options[] = {
        OPTION_GROUP("Options"),
        OPTION_HELP(),
        OPTION_BOOLEAN('t', NULL, "show object type (one of 'blob', 'tree', 'commit', 'tag', ...)", &t_flag, NULL, 0),
        OPTION_BOOLEAN('p', NULL, "pretty-print the contents of the object", &p_flag, NULL, 0),
        OPTION_BOOLEAN('s', NULL, "show object size", &s_flag, NULL, 0),
        OPTION_BOOLEAN('e', NULL, "check if <object> exists", &e_flag, NULL, 0),
        OPTION_GROUP_END(),
        OPTION_END()
    };

    struct argparse argparse;
    argparse_init(&argparse, options, &description);

    if (argc == 0){
        argparse_parse(&argparse, 1, (char *[]){"-h"});
    }else{
        const char * sha1 = argv[argc - 1];
        
        if (!isxdigit(sha1[0]) || strlen(sha1) != 40){
            // Make sure the last argument is not  help flag
            if (strcmp(sha1, "-h") == 0 || strcmp(sha1, "--help") == 0){
                argparse_parse(&argparse, 1, (char *[]){"-h"});
            }else{
                gitlet_panic("Not a valid object name: %s", sha1);
            }
        }
        if (argc < 2){
            gitlet_panic("only two arguments allowed in <type> <object> mode, not 1");
        }

        argparse_parse(&argparse, argc - 1, argv);

        if (p_flag && (t_flag || s_flag || e_flag)){
            gitlet_panic("options  \'-p\' cannot be used with \'-t\', \'-s\', or \'-e\'");
        }
        if (s_flag && (t_flag || p_flag || e_flag)){
            gitlet_panic("options  \'-s\' cannot be used with \'-t\', \'-p\', or \'-e\'");
        }
        if (e_flag && (t_flag || p_flag || s_flag)){
            gitlet_panic("options  \'-e\' cannot be used with \'-t\', \'-p\', or \'-s\'");
        }
        if (t_flag && (p_flag || s_flag || e_flag)){
            gitlet_panic("options  \'-t\' cannot be used with \'-p\', \'-s\', or \'-e\'");
        }

        struct repository repo;
        repository_object_init(&repo, current_dir, true);

        if (e_flag){
            strcat(current_dir, "/.gitlet/objects/");
            strncpy(current_dir + strlen(current_dir), sha1, 2);
            strcat(current_dir, "/");
            strncpy(current_dir + strlen(current_dir), sha1 + 2, 38);

            if (exists(current_dir)){
                return;
            }else{
                gitlet_panic("fatal: Not a valid object name %s", sha1);
            }
        }

        // Read the object
        struct object obj;
        object_read(&obj, sha1);

        if (t_flag){
            switch (obj.type){
                case OBJECT_TYPE_BLOB:
                    printf("blob\n");
                    break;
                case OBJECT_TYPE_TREE:
                    printf("tree\n");
                    break;
                case OBJECT_TYPE_COMMIT:
                    printf("commit\n");
                    break;
                case OBJECT_TYPE_TAG:
                    printf("tag\n");
                    break;
                default:
                    gitlet_panic("Unknown object type: %s", obj.type);
            }
        }
        else if (p_flag){
            printf("%s", obj.content);
        }
        else if (s_flag){
            printf("%llu\n", obj.file_size);
        }
        
        free(obj.content);
    }
}