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

#ifndef GITLET_UTIL_MACROS_H
#define GITLET_UTIL_MACROS_H

/**
 * @brief : helper macros 
*/

// get the size of an array
#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

// concatenate two strings
#define _STRINGIFY(X)   #X
#define STRINGIFY(X)    _STRINGIFY(X)

// concatenate macros
#define _CONCAT(X, Y)       X##Y
#define CONCAT(X, Y)        _CONCAT(X, Y)
#define CONCAT3(X, Y, Z)    CONCAT(CONCAT(X, Y), Z)


/**
 * @brief : Utility macros for ASCII color codes
 * 
 */
#define ASCII_COLOR_RED     "\033[31m"
#define ASCII_COLOR_GREEN   "\033[32m"
#define ASCII_COLOR_YELLOW  "\033[33m"
#define ASCII_COLOR_BLUE    "\033[34m"
#define ASCII_COLOR_MAGENTA "\033[35m"
#define ASCII_COLOR_CYAN    "\033[36m"
#define ASCII_COLOR_RESET   "\033[0m"

#endif // GITLET_UTIL_MACROS_H