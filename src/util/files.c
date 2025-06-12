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

#include <util/files.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

#define DEFAULT_DIR_PERMISSION  0755

bool exists(const char * path){
    struct stat status;
    return stat(path, &status) == 0;
}

bool create_directory(const char * path){
    return mkdir(path, DEFAULT_DIR_PERMISSION) == 0;
}
bool create_file(const char * file_name){
    FILE * file = fopen(file_name, "w");
    if (file != NULL){
        fclose(file);
        return true;
    }
    return false;
}

bool remove_directory(const char * path){
    return rmdir(path) == 0;
}
bool remove_file(const char * file_name){
    return remove(file_name) == 0;
}

bool is_directory(const char * path){
    struct stat status;
    return stat(path, &status) == 0 && S_ISDIR(status.st_mode);
} 

size_t file_size(FILE * file){
    fseek(file, 0, SEEK_END);
    size_t _size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return _size;
}