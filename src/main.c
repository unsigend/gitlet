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

// standard library headers
#include <stdio.h>
#include <stdlib.h>

// command module headers
#include <command/command.h>

// util module headers
#include <util/error.h>
#include <util/str.h>

// gitlet global config
#include <global/config.h>

/**
 * @brief: The main function of the gitlet program
 *        Just as a sub-command dispatcher, it will check and map the sub-command to the corresponding 
 *        function.
 * @note: The argv and argv will dispatch to the function, and only the arguments after the sub-command
 *        will be passed to the function (eg. gitlet add -a file1 file2  argv = [-a, file1, file2] argc = 3)
 */

int main(int argc, char *argv[]) {

    if (argc == 1){
        // no sub-command just show help information and exit
        gitlet_run_command("help", 0, NULL);
    }else{
        // if the the second argument is not a sub-command
        if (str_start_with(argv[1], "-") || str_start_with(argv[1], "--")){
            if (str_equals(argv[1], "-h") || str_equals(argv[1], "--help")){
                gitlet_run_command("help", 0, NULL);
            }else if (str_equals(argv[1], "-v") || str_equals(argv[1], "--version")){
                fprintf(stdout, "gitlet version %s\n", GITLET_VERSION_STRING);
            }else{
                gitlet_panic("%s is not a gitlet command. See \'gitlet --help\'", argv[1]);
            }
        }
        // if the second argument is a sub-command
        else{
            if (!gitlet_run_command(argv[1], argc - 2, argv + 2)){
                gitlet_panic("\'%s\' is not a gitlet command. See \'gitlet --help\'", argv[1]);
            }
        }
    }
    
    return EXIT_SUCCESS;
}