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
#include <stddef.h>

#include <util/macros.h>
#include <util/str.h>

#include <command/command.h>

// include all command headers
#include <command/commit.h>
#include <command/add.h>
#include <command/cat-file.h>
#include <command/check-ignore.h>
#include <command/checkout.h>
#include <command/hash-object.h>
#include <command/help.h>
#include <command/init.h>
#include <command/log.h>
#include <command/ls-files.h>
#include <command/ls-tree.h>
#include <command/rev-parse.h>
#include <command/rm.h>
#include <command/show-ref.h>
#include <command/status.h>
#include <command/tag.h>

// type of sub-command handler function
typedef void (*command_handler)(int argc, char *argv[]);

// structure of sub-command
struct command{
    const char * command;
    const command_handler handler;
};

// define the commands list
static const struct command commands_list[] = {
    {"add",             command_add},
    {"cat-file",        command_cat_file},
    {"check-ignore",    command_check_ignore},
    {"checkout",        command_checkout},
    {"commit",          command_commit},
    {"hash-object",     command_hash_object},
    {"help",            command_help},
    {"init",            command_init},
    {"log",             command_log},
    {"ls-files",        command_ls_files},
    {"ls-tree",         command_ls_tree},
    {"rev-parse",       command_rev_parse},
    {"rm",              command_rm},
    {"show-ref",        command_show_ref},
    {"status",          command_status},
    {"tag",             command_tag},
};

bool gitlet_run_command(const char * command, int argc, char *argv[]){
    for (size_t i = 0; i < ARRAY_SIZE(commands_list); i++){
        if (str_equals(command, commands_list[i].command)){
            commands_list[i].handler(argc, argv);
            return true;
        }
    }
    return false;
}
