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

#ifndef GITLET_COMMAND_H
#define GITLET_COMMAND_H

/**
 * @brief Main header for command module
 */

#include <stddef.h>
#include <stdbool.h>

// type of sub-command handler function
typedef void (*command_handler)(int argc, char *argv[]);

// structure of sub-command
struct command{
    const char * command;
    const command_handler handler;
};

// define the commands list
extern const struct command commands_list[];
// define the size of the commands list
extern const size_t commands_list_size;

/**
 * @brief: Run the sub-command with the given arguments
 * @param command: the command to run
 * @param argc: the number of arguments
 * @param argv: the arguments
 * @return: true if the command is found, false otherwise
 */
extern bool gitlet_run_command(const char * command, int argc, char *argv[]);

#endif 