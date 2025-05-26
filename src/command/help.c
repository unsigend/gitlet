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

#include <command/help.h>

#include <global/config.h>

#include <stdio.h>
#include <stdlib.h>

// print command information and fill the space and left-align
#define PRINT_COMMAND_HELP(CMD, DESC) \
    fprintf(stdout, "   %-12s %s\n", CMD, DESC)
// print group information
#define PRINT_GROUP_BEGIN(MSG) \
    fprintf(stdout, "%s\n", MSG)
// print group end
#define PRINT_GROUP_END() \
    fputc('\n', stdout);

static inline void print_help_header(){
    printf("gitlet version %s\n", GITLET_VERSION_STRING);
    printf("Usage: gitlet [-v | --version] [-h | --help] <command> [<args>]\n\n");
}

static inline void print_help_footer(){
    printf("See \'gitlet --help\' for more information.\n");
    printf("For more detailed documentation, see <%s>\n", GITLET_DOCUMENTATION_URL);
}

static inline void print_help_information(){
    PRINT_GROUP_BEGIN("Setup and Configure Gitlet");
    PRINT_COMMAND_HELP("init", "Create an empty gitlet repository or reinitialize an existing one");
    PRINT_COMMAND_HELP("config", "Set configuration options for gitlet");
    PRINT_GROUP_END();

    PRINT_GROUP_BEGIN("Work on current changes");
    PRINT_COMMAND_HELP("add", "Add files to the staging area");
    PRINT_COMMAND_HELP("rm", "Remove files from the staging area");
    PRINT_GROUP_END();

    PRINT_GROUP_BEGIN("Examine the history and state");
    PRINT_COMMAND_HELP("log", "Show commit logs");
    PRINT_COMMAND_HELP("status", "Show the working tree status");
    PRINT_GROUP_END();
}
void command_help(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    print_help_header();
    print_help_information();
    print_help_footer();
    fflush(stdout);
    exit(EXIT_SUCCESS);
}