/**
 * MIT License
 * 
 * Copyright (c) 2025 QIU YIXIANG
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

/**
 * This file is not part of gitlet
 * @ref: https://github.com/unsigend/util.git
 */

/**
 * Implementation of argparse library
 * Part of the util library project
 */

#include <argparse.h>

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/**
 * @brief: Internal Macros
 */

// ASCII Color Macros
#define ASCII_COLOR_RED     "\033[31m"
#define ASCII_COLOR_GREEN   "\033[32m"
#define ASCII_COLOR_YELLOW  "\033[33m"
#define ASCII_COLOR_BLUE    "\033[34m"
#define ASCII_COLOR_MAGENTA "\033[35m"
#define ASCII_COLOR_CYAN    "\033[36m"
#define ASCII_COLOR_RESET   "\033[0m"

// Buffer Macros
#define CHAR_BUFFER_ALIGN       12
#define CHAR_BUFFER_SIZE        64

// Option Macros
#define OPTION_LONG             0x01
#define OPTION_SHORT            0x02
#define OPTION_BOTH             0x03
#define OPTION_RESULT_UNKNOWN   -1
#define OPTION_RESULT_SUCCESS   0

/**
 * @brief: Private functions implementation
 */


/**
 * @brief: help information display functions
 */
static void argparse_show_option_list(const struct argparse *this){
    for (const struct argparse_option * option = this->_option_list; 
        option->_type != ARGPARSE_OPTION_TYPE_END; option++){
        // the type of the option is group
        if (option->_type == ARGPARSE_OPTION_TYPE_GROUP){
            fprintf(stdout, "%s\n", option->_description);
        }
        // the type of the option is group end
        else if (option->_type == ARGPARSE_OPTION_TYPE_GROUP_END){
            fprintf(stdout, "\n");
        }
        // the type of the option is not group
        else{
            char string_buffer[CHAR_BUFFER_SIZE];
            size_t string_buffer_index = 0;
            memset(string_buffer, 0, CHAR_BUFFER_SIZE);

            if (option->_short_name){
                sprintf(string_buffer + string_buffer_index, "-%c", option->_short_name);
                string_buffer_index += 2;
            }
            if (option->_short_name && option->_long_name){
                sprintf(string_buffer + string_buffer_index, ", ");
                string_buffer_index += 2;
            }
            if (option->_long_name){
                sprintf(string_buffer + string_buffer_index, "--%s", option->_long_name);
                string_buffer_index += 2 + strlen(option->_long_name);
            }
            if (option->_type != ARGPARSE_OPTION_TYPE_BOOL){
                sprintf(string_buffer + string_buffer_index, " <value>");
                string_buffer_index += 8;
            }

            // left align the string buffer with the CHAR_BUFFER_ALIGN
            if (strlen(string_buffer) > CHAR_BUFFER_ALIGN){
                fprintf(stdout, "  %s\n", string_buffer);
                fprintf(stdout, "  %-*s", CHAR_BUFFER_ALIGN, "");
            }else{
                fprintf(stdout, "  %-*s", CHAR_BUFFER_ALIGN, string_buffer);
            }
            if (option->_description){
                fprintf(stdout, "   %s\n", option->_description);
            }
        }
    }
}

static void argparse_show_all(const struct argparse *this){
    if (!this->_description)
        return;
    
    // show the description
    if (this->_description->_description)
        fprintf(stdout, "OVERVIEW : %s\n\n", this->_description->_description);

    // show the program name
    if (this->_description->_program_name)
        fprintf(stdout, "%s ", this->_description->_program_name);
    
    // show the usage
    if (this->_description->_usage)
        fprintf(stdout, "USAGE: %s", this->_description->_usage);

    fprintf(stdout, "\n\n");

    // show the option list
    if (this->_option_list)
        argparse_show_option_list(this);

    // show the epilog
    if (this->_description->_epilog)
        fprintf(stdout, "%s\n", this->_description->_epilog);
}

/**
 * @brief: error handling functions
 */

/**
 * @brief: print the internal error message and exit the program
 * @param message: the message to print
 */
static void internal_error(const char *message){
    fprintf(stderr, ASCII_COLOR_RED "INTERNAL ERROR" ASCII_COLOR_RESET ": %s\n", message);
    exit(EXIT_FAILURE);
}

/**
 * @brief: print the error message related to the option and exit the program
 * @param this: the argparse struct
 * @param message: the message to print
 * @param option: the option that is related to the error
 * @param flag: the flag of the option which specify the type of the option
 */
static void option_error(struct argparse* this, const char * message, const struct argparse_option * option, int flag){
    if (this->_description && this->_description->_program_name){
        fprintf(stderr, ASCII_COLOR_RED "%s" ASCII_COLOR_RESET, this->_description->_program_name);
    }else{
        fprintf(stderr, ASCII_COLOR_RED "ERROR" ASCII_COLOR_RESET);
    }

    fprintf(stderr, ": ");
    if (flag & OPTION_SHORT){
        fprintf(stderr, "-%c ", option->_short_name);
    }
    if (flag & OPTION_LONG){
        fprintf(stderr, "--%s ", option->_long_name);
    }
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

/**
 * @brief: option process functions
 */

static void argparse_option_get_value(struct argparse *this, const struct argparse_option *option, int flag){
    if (option->_callback){
        option->_callback(this, option);
    }else{
        const char * success = NULL;
        switch (option->_type){
            case ARGPARSE_OPTION_TYPE_BOOL:
                *(bool*)option->_value = true;
                this->_argc--;
                this->_argv++;
                break;
            case ARGPARSE_OPTION_TYPE_DOUBLE:
                if (this->_argc > 1){
                    if (this->_argv[1][0] == '-' && !isdigit(this->_argv[1][1])){
                        option_error(this, "requires a floating point number", option, flag);
                    }
                    *(double*)option->_value = strtod(this->_argv[1], (char**)&success);
                    if (success == this->_argv[1]){
                        option_error(this, "requires a floating point number", option, flag);
                    }
                    this->_argc -= 2;
                    this->_argv += 2;
                }else{
                    option_error(this, "missing argument", option, flag);
                }
                break;
            case ARGPARSE_OPTION_TYPE_INT:
                if (this->_argc > 1){
                    if (this->_argv[1][0] == '-' && !isdigit(this->_argv[1][1])){
                        option_error(this, "requires a integer number", option, flag);
                    }
                    *(int*)option->_value = strtol(this->_argv[1], (char**)&success, 10);
                    if (success == this->_argv[1]) {
                        option_error(this, "requires a integer number", option, flag);
                    }
                    this->_argc -= 2;
                    this->_argv += 2;
                }else{
                    option_error(this, "missing argument", option, flag);
                }
                break;
            case ARGPARSE_OPTION_TYPE_STRING:
                if (this->_argc > 1){
                    if (this->_argv[1][0] == '-')
                        option_error(this, "missing argument", option, flag);
                    else{
                        *(char**)option->_value = this->_argv[1];
                        this->_argc -= 2;
                        this->_argv += 2;
                    }
                }else{
                    option_error(this, "missing argument", option, flag);
                }
                break;
            default:
                break;
        }
    }
}
static int argparse_short_option(struct argparse *this, const char *short_option){
    if (strlen(short_option) != 1)
        return OPTION_RESULT_UNKNOWN;

    for (const struct argparse_option * option = this->_option_list; 
        option->_type != ARGPARSE_OPTION_TYPE_END; option++){
        if (option->_short_name == short_option[0]){
            argparse_option_get_value(this, option, OPTION_SHORT);
            return OPTION_RESULT_SUCCESS;
        }
    }
    return OPTION_RESULT_UNKNOWN;
}
static int argparse_long_option(struct argparse* this, const char *long_option){
    size_t option_length = strlen(long_option);
    if (option_length < 1)
        return OPTION_RESULT_UNKNOWN;

    for (const struct argparse_option * option = this->_option_list; 
        option->_type != ARGPARSE_OPTION_TYPE_END; option++){
        if (option->_long_name && strcmp(option->_long_name, long_option) == 0){
            argparse_option_get_value(this, option, OPTION_LONG);
            return OPTION_RESULT_SUCCESS;
        }
    }
    return OPTION_RESULT_UNKNOWN;
}
/**
 * @brief: Public API functions implementation
 */
void argparse_init(struct argparse *this, const struct argparse_option *option_list, 
    const struct argparse_description *description){
    this->_argc = 0;
    this->_argv = NULL;
    this->_option_list = option_list;
    this->_description = description;
    this->_flags = ARGPARSE_FLAG_STOP_UNKNOWN_OPTION;
}

void argparse_set_flags(struct argparse *this, argparse_flag flags){
    this->_flags = flags;
}

void argparse_parse(struct argparse *this, int argc, char *argv[]){
    if (argc < 1)
        internal_error("argc is less than 1");

    if (argv == NULL || argv[0] == NULL)
        internal_error("argv is NULL");

    this->_argc = argc;
    this->_argv = argv;

    /**
     * this core logic will not update the internal variables of the argparse
     * it will only process the argc and argv, and dispatch the option to the handler function,
     * then the argc and argv will be updated by the handler function.
     * 
     * @note: the loop will always assume that the argv is pointing to the option, 
     * rather than the argument.
     */
    
    for ( ; this->_argc > 0; ){
        const char * current_option = this->_argv[0];

        if (current_option && current_option[0] == '-'){
            // for long option
            if (current_option[1] == '-'){
                switch (argparse_long_option(this, current_option + 2)){
                    case OPTION_RESULT_SUCCESS:
                        break;
                    case OPTION_RESULT_UNKNOWN:
                        goto unknown_option;
                }
                continue;
            }
            // for short option
            else{
                switch (argparse_short_option(this, current_option + 1)){
                    case OPTION_RESULT_SUCCESS:
                        break;
                    case OPTION_RESULT_UNKNOWN:
                        goto unknown_option;
                }
                continue;
            }
        }
        // for unknown option
        unknown_option:
            if (this->_flags & ARGPARSE_FLAG_IGNORE_UNKNOWN_OPTION){
                this->_argc--;
                this->_argv++;
            }else{
                if (this->_description && this->_description->_program_name){
                    fprintf(stderr, ASCII_COLOR_RED "%s" ASCII_COLOR_RESET, this->_description->_program_name);
                }else{
                    fprintf(stderr, ASCII_COLOR_RED "ERROR" ASCII_COLOR_RESET);
                }
                fprintf(stderr, ": unknown option %s\n", current_option);
                exit(EXIT_FAILURE);
            }
    }
}


/**
 * @brief: build-in callback functions implementation
 */

void argparse_callback_help(struct argparse* this, const struct argparse_option *option){
    (void)option;
    argparse_show_all(this);
    exit(EXIT_SUCCESS);
}

/**
 * @brief: callback function for multiple arguments
 * @note: this callback function consider every multiple arguments pack as a string array
 */
void argparse_callback_multiple_arguments(struct argparse* this, const struct argparse_option *option){
    switch (option->_type){
        case ARGPARSE_OPTION_TYPE_STRING:
            if (option->_callback_data == 0){
                internal_error("the callback data is not set");
            }
            if (this->_argc < 2){
                option_error(this, "missing argument", option, OPTION_BOTH);
            }
            // skip the option
            this->_argc--;
            this->_argv++;

            if (this->_argc < 1 || this->_argv[0][0] == '-'){
                option_error(this, "missing argument", option, OPTION_BOTH);
            }
            // set the callback data to the address of the data array
            *(const char***)option->_value = (const char**)this->_argv;

            // count the number of arguments
            int array_size = 0;
            for (; this->_argc > 0; this->_argc--, this->_argv++){
                if (this->_argv[0][0] == '-'){
                    break;
                }
                array_size++;
            }
            *(int *)option->_callback_data = array_size;
            break;
        default:
            internal_error("the option type is not required to be a multiple arguments");
    }
}