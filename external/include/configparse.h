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


#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H

/**
 * @brief: configparse library is part of the util library project
 *         This library is used to parse INI configuration file, and is designed for
 *         easy and simple usage.
 * 
 * @note: the purpose of this library is to parse the INI file, and read the key-value pair,
 *        so the functions provided which not include writing operation.
 * 
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief: the callback function type
 * When the section, key, value is parsed, the callback function will be called
 */
typedef void (*configparse_callback_t)(void * data, const char * section, const char * key, const char * value);

/**
 * @brief: the configparse object
 * @param filename: the filename of the INI file
 * @param ini_file: the file pointer of the INI file
 */
struct configparse{
    const char * filename;
    FILE * ini_file;
};

/**
 * @brief: initialize the configparse object
 * @param this: the configparse object
 * @param filename: the filename of the INI file
 * @return: true if successful, false otherwise
 */
extern bool init_configparse(struct configparse * this, const char * filename);

/**
 * @brief: get the value of the key in the section
 * @param this: the configparse object
 * @param section: the section of the key
 * @param key: the key of the value
 * @return: the value of the key in the section
 * 
 * @note: Low performance, only for read specific keys in small file
 *       when read multiple keys use configparse_parse_all function
 */
extern char * configparse_get_value(struct configparse * this, const char * section, const char * key);

/**
 * @brief: parse the whole file
 * @param this: the configparse object
 * @param callback: the callback function
 * @param data: the data to be passed to the callback function
 * 
 * @note: the result will be saved in the callback function, and 'value' is a temporary pointer
 *        so the user should copy the value to a new string using strdup if needed
 */
extern void configparse_parse_all(struct configparse * this, configparse_callback_t callback, void * data);

#ifdef __cplusplus
}
#endif


#endif