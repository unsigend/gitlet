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

#include <configparse.h>

#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 512

static bool is_comment(const char * line){
    return line[0] == '#' || line[0] == ';';
}
static bool is_section(const char * line){
    return line[0] == '[' && line[strlen(line) - 2] == ']';
}

bool init_configparse(struct configparse * this, const char * filename){
    if (this == NULL || filename == NULL){
        return false;
    }

    this->filename = filename;
    this->ini_file = fopen(filename, "r");

    if (this->ini_file == NULL){
        return false;
    }
    return true;
}

char * configparse_get_value(struct configparse * this, const char * section, const char * key){
    if (this == NULL || section == NULL || key == NULL){
        return NULL;
    }

    char line_buffer[BUFFER_SIZE];
    memset(line_buffer, 0, BUFFER_SIZE);

    // read the file line by line
    while (fgets(line_buffer, BUFFER_SIZE, this->ini_file) != NULL){
        if (is_comment(line_buffer) || line_buffer[0] == '\n'){
            continue;
        }
        if (is_section(line_buffer)){
            // if the section is the same as the section we are looking for
            if (strncmp(line_buffer + 1, section, strlen(section)) == 0){
                while (fgets(line_buffer, BUFFER_SIZE, this->ini_file) != NULL){
                    if (is_comment(line_buffer)){
                        continue;
                    }
                    if (is_section(line_buffer)){
                        goto fail;
                    }
                    char * skip_space = line_buffer;
                    while (isspace(*skip_space)){
                        skip_space++;
                    }
                    // if the key is the same as the key we are looking for
                    if (strncmp(skip_space, key, strlen(key)) == 0 &&
                    (skip_space[strlen(key)] == '=' || skip_space[strlen(key)] == ' ')){
                        // find the value
                        char * value = strchr(skip_space, '=');
                        if (value == NULL){
                            goto fail;
                        }
                        value++;
                        while (isspace(*value)){
                            value++;
                        }
                        if (*value == '\0'){
                            goto fail;
                        }
                        // remove the trailing newline
                        if (*(value + strlen(value) - 1) == '\n'){
                            *(value + strlen(value) - 1) = '\0';
                        }
                        fseek(this->ini_file, 0, SEEK_SET);
                        return value;
                    }
                }
                goto fail;
            }
            continue;
        } 
    }
fail:
    // set the lseek to the beginning of the file
    fseek(this->ini_file, 0, SEEK_SET);
    return NULL;
}

void configparse_parse_all(struct configparse * this, configparse_callback_t callback, void * data){
    if (this == NULL || callback == NULL){
        return;
    }

    char section_buffer[BUFFER_SIZE];
    char line_buffer[BUFFER_SIZE];
    memset(line_buffer, 0, BUFFER_SIZE);
    memset(section_buffer, 0, BUFFER_SIZE);

    while (fgets(line_buffer, BUFFER_SIZE, this->ini_file) != NULL){
        if (is_comment(line_buffer) || line_buffer[0] == '\n'){
            continue;
        }
        if (is_section(line_buffer)){
            strncpy(section_buffer, line_buffer + 1, strlen(line_buffer) - 3);
            section_buffer[strlen(line_buffer) - 3] = '\0';
            continue;
        }
        char * key = line_buffer;
        while (isspace(*key)){ key++; }

        char * value = strchr(key, '=');
        
        if (value == NULL){
            continue;
        }
        if (*(value - 1) == ' '){
            *(value - 1) = '\0';
        }
        
        do { value++; } while (isspace(*value));
        // remove the trailing newline
        if (*(value + strlen(value) - 1) == '\n'){
            *(value + strlen(value) - 1) = '\0';
        }

        // call the callback function
        callback(data, section_buffer, key, value);
    }

    fseek(this->ini_file, 0, SEEK_SET);
}