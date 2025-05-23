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

#ifndef UTEST_H
#define UTEST_H

/**
 * The Utest flag is used to control the behavior of the utest library.
 * The default value is UTEST_FLAG_DEFAULT.
 */
#define UTEST_FLAG_NONE
#define UTEST_FLAG_SHOW_CASE
#define UTEST_FLAG_SHOW_SUITE
#define UTEST_FLAG_STYLE_FULL
#define UTEST_FLAG_STOP_ON_FAILURE
#define UTEST_FLAG_DEFAULT

#include <utest/utest_internals.h>

/* core macros */

/**
 * @brief Declare a test case.
 * @param TEST_CASE_NAME The name of the test case.: 
 */
#define UTEST_TEST_CASE(TEST_CASE_NAME)                     _UTEST_TEST_CASE(TEST_CASE_NAME)

/**
 * @brief Run a test case.
 * @param TEST_CASE_NAME The name of the test case.
 * @note This macro is used to run a test case. It should be called in the test suite.
 */
#define UTEST_RUN_TEST_CASE(TEST_CASE_NAME)                 _UTEST_RUN_TEST_CASE(TEST_CASE_NAME)

/**
 * @brief Declare a test suite.
 * @param TEST_SUITE_NAME The name of the test suite.
 */
#define UTEST_TEST_SUITE(TEST_SUITE_NAME)                   _UTEST_TEST_SUITE(TEST_SUITE_NAME)

/**
 * @brief Run a test suite.
 * @param TEST_SUITE_NAME The name of the test suite.
 * @note This macro is used to run a test suite. It should be called in the main function.
 */
#define UTEST_RUN_TEST_SUITE(TEST_SUITE_NAME)               _UTEST_RUN_TEST_SUITE(TEST_SUITE_NAME)

/**
 * @brief Initialize the utest library.
 */
#define UTEST_BEGIN()                                       _UTEST_BEGIN()

/**
 * @brief Finalize the utest library.
 */
#define UTEST_END()                                         _UTEST_END()

/**
 * @brief Set a flag (bitwise) for the utest library.
 * @param UTEST_FLAG The flag to set.
 */
#define UTEST_SET_FLAG(UTEST_FLAG)                          _UTEST_SET_FLAG(UTEST_FLAG)

/**
 * @brief Clear a flag (bitwise) for the utest library.
 * @param UTEST_FLAG The flag to clear.
 */
#define UTEST_CLEAR_FLAG(UTEST_FLAG)                        _UTEST_CLEAR_FLAG(UTEST_FLAG)

/**
 * @brief Reset all flags to the default value.
 */
#define UTEST_FLAG_RESET()                                  _UTEST_FLAG_RESET()


/* integer equal */
#define EXPECT_EQUAL_INT(ACTUAL, EXPECTED)                  _EXPECT_EQUAL_INT(ACTUAL, EXPECTED)
#define EXPECT_EQUAL_INT8(ACTUAL, EXPECTED)                 _EXPECT_EQUAL_INT8(ACTUAL, EXPECTED)
#define EXPECT_EQUAL_INT16(ACTUAL, EXPECTED)                _EXPECT_EQUAL_INT16(ACTUAL, EXPECTED)
#define EXPECT_EQUAL_INT32(ACTUAL, EXPECTED)                _EXPECT_EQUAL_INT32(ACTUAL, EXPECTED)   
#define EXPECT_EQUAL_INT64(ACTUAL, EXPECTED)                _EXPECT_EQUAL_INT64(ACTUAL, EXPECTED)
/* integer not equal */
#define EXPECT_NOT_EQUAL_INT(ACTUAL, EXPECTED)              _EXPECT_NOT_EQUAL_INT(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT8(ACTUAL, EXPECTED)             _EXPECT_NOT_EQUAL_INT8(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT16(ACTUAL, EXPECTED)            _EXPECT_NOT_EQUAL_INT16(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT32(ACTUAL, EXPECTED)            _EXPECT_NOT_EQUAL_INT32(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT64(ACTUAL, EXPECTED)            _EXPECT_NOT_EQUAL_INT64(ACTUAL, EXPECTED)
/* integer greater than */
#define EXPECT_GREATER_INT(ACTUAL, EXPECTED)                _EXPECT_GREATER_INT(ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT8(ACTUAL, EXPECTED)               _EXPECT_GREATER_INT8(ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT16(ACTUAL, EXPECTED)              _EXPECT_GREATER_INT16(ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT32(ACTUAL, EXPECTED)              _EXPECT_GREATER_INT32(ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT64(ACTUAL, EXPECTED)              _EXPECT_GREATER_INT64(ACTUAL, EXPECTED)
/* integer greater than or equal to */
#define EXPECT_GREATER_EQUAL_INT(ACTUAL, EXPECTED)          _EXPECT_GREATER_EQUAL_INT(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_INT8(ACTUAL, EXPECTED)         _EXPECT_GREATER_EQUAL_INT8(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_INT16(ACTUAL, EXPECTED)        _EXPECT_GREATER_EQUAL_INT16(ACTUAL, EXPECTED)   
#define EXPECT_GREATER_EQUAL_INT32(ACTUAL, EXPECTED)        _EXPECT_GREATER_EQUAL_INT32(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_INT64(ACTUAL, EXPECTED)        _EXPECT_GREATER_EQUAL_INT64(ACTUAL, EXPECTED)
/* integer less than */
#define EXPECT_LESS_INT(ACTUAL, EXPECTED)                   _EXPECT_LESS_INT(ACTUAL, EXPECTED)
#define EXPECT_LESS_INT8(ACTUAL, EXPECTED)                  _EXPECT_LESS_INT8(ACTUAL, EXPECTED)
#define EXPECT_LESS_INT16(ACTUAL, EXPECTED)                 _EXPECT_LESS_INT16(ACTUAL, EXPECTED)
#define EXPECT_LESS_INT32(ACTUAL, EXPECTED)                 _EXPECT_LESS_INT32(ACTUAL, EXPECTED)
#define EXPECT_LESS_INT64(ACTUAL, EXPECTED)                 _EXPECT_LESS_INT64(ACTUAL, EXPECTED)
/* integer less than or equal to */
#define EXPECT_LESS_EQUAL_INT(ACTUAL, EXPECTED)             _EXPECT_LESS_EQUAL_INT(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT8(ACTUAL, EXPECTED)            _EXPECT_LESS_EQUAL_INT8(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT16(ACTUAL, EXPECTED)           _EXPECT_LESS_EQUAL_INT16(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT32(ACTUAL, EXPECTED)           _EXPECT_LESS_EQUAL_INT32(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT64(ACTUAL, EXPECTED)           _EXPECT_LESS_EQUAL_INT64(ACTUAL, EXPECTED)


/* unsigned integer equal */
#define EXPECT_EQUAL_UINT(ACTUAL, EXPECTED)                 _EXPECT_EQUAL_UINT(ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT8(ACTUAL, EXPECTED)                _EXPECT_EQUAL_UINT8(ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT16(ACTUAL, EXPECTED)               _EXPECT_EQUAL_UINT16(ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT32(ACTUAL, EXPECTED)               _EXPECT_EQUAL_UINT32(ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT64(ACTUAL, EXPECTED)               _EXPECT_EQUAL_UINT64(ACTUAL, EXPECTED)
/* unsigned integer not equal */
#define EXPECT_NOT_EQUAL_UINT(ACTUAL, EXPECTED)             _EXPECT_NOT_EQUAL_UINT(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT8(ACTUAL, EXPECTED)            _EXPECT_NOT_EQUAL_UINT8(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT16(ACTUAL, EXPECTED)           _EXPECT_NOT_EQUAL_UINT16(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT32(ACTUAL, EXPECTED)           _EXPECT_NOT_EQUAL_UINT32(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT64(ACTUAL, EXPECTED)           _EXPECT_NOT_EQUAL_UINT64(ACTUAL, EXPECTED)
/* unsigned integer greater than */
#define EXPECT_GREATER_UINT(ACTUAL, EXPECTED)               _EXPECT_GREATER_UINT(ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT8(ACTUAL, EXPECTED)              _EXPECT_GREATER_UINT8(ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT16(ACTUAL, EXPECTED)             _EXPECT_GREATER_UINT16(ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT32(ACTUAL, EXPECTED)             _EXPECT_GREATER_UINT32(ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT64(ACTUAL, EXPECTED)             _EXPECT_GREATER_UINT64(ACTUAL, EXPECTED)
/* unsigned integer greater than or equal to */
#define EXPECT_GREATER_EQUAL_UINT(ACTUAL, EXPECTED)         _EXPECT_GREATER_EQUAL_UINT(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT8(ACTUAL, EXPECTED)        _EXPECT_GREATER_EQUAL_UINT8(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT16(ACTUAL, EXPECTED)       _EXPECT_GREATER_EQUAL_UINT16(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT32(ACTUAL, EXPECTED)       _EXPECT_GREATER_EQUAL_UINT32(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT64(ACTUAL, EXPECTED)       _EXPECT_GREATER_EQUAL_UINT64(ACTUAL, EXPECTED)
/* unsigned integer less than */
#define EXPECT_LESS_UINT(ACTUAL, EXPECTED)                  _EXPECT_LESS_UINT(ACTUAL, EXPECTED)
#define EXPECT_LESS_UINT8(ACTUAL, EXPECTED)                 _EXPECT_LESS_UINT8(ACTUAL, EXPECTED)    
#define EXPECT_LESS_UINT16(ACTUAL, EXPECTED)                _EXPECT_LESS_UINT16(ACTUAL, EXPECTED)
#define EXPECT_LESS_UINT32(ACTUAL, EXPECTED)                _EXPECT_LESS_UINT32(ACTUAL, EXPECTED)
#define EXPECT_LESS_UINT64(ACTUAL, EXPECTED)                _EXPECT_LESS_UINT64(ACTUAL, EXPECTED)
/* unsigned integer less than or equal to */
#define EXPECT_LESS_EQUAL_UINT(ACTUAL, EXPECTED)            _EXPECT_LESS_EQUAL_UINT(ACTUAL, EXPECTED) 
#define EXPECT_LESS_EQUAL_UINT8(ACTUAL, EXPECTED)           _EXPECT_LESS_EQUAL_UINT8(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UINT16(ACTUAL, EXPECTED)          _EXPECT_LESS_EQUAL_UINT16(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UINT32(ACTUAL, EXPECTED)          _EXPECT_LESS_EQUAL_UINT32(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UINT64(ACTUAL, EXPECTED)          _EXPECT_LESS_EQUAL_UINT64(ACTUAL, EXPECTED)


/* float assertion */
#define EXPECT_EQUAL_FLOAT(ACTUAL, EXPECTED)                 _EXPECT_EQUAL_FLOAT(ACTUAL, EXPECTED) 
#define EXPECT_NOT_EQUAL_FLOAT(ACTUAL, EXPECTED)             _EXPECT_NOT_EQUAL_FLOAT(ACTUAL, EXPECTED) 
#define EXPECT_GREATER_FLOAT(ACTUAL, EXPECTED)               _EXPECT_GREATER_FLOAT(ACTUAL, EXPECTED) 
#define EXPECT_GREATER_EQUAL_FLOAT(ACTUAL, EXPECTED)         _EXPECT_GREATER_EQUAL_FLOAT(ACTUAL, EXPECTED) 
#define EXPECT_LESS_FLOAT(ACTUAL, EXPECTED)                  _EXPECT_LESS_FLOAT(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_FLOAT(ACTUAL, EXPECTED)            _EXPECT_LESS_EQUAL_FLOAT(ACTUAL, EXPECTED)

/* double assertion */
#define EXPECT_EQUAL_DOUBLE(ACTUAL, EXPECTED)               _EXPECT_EQUAL_DOUBLE(ACTUAL, EXPECTED) 
#define EXPECT_NOT_EQUAL_DOUBLE(ACTUAL, EXPECTED)           _EXPECT_NOT_EQUAL_DOUBLE(ACTUAL, EXPECTED) 
#define EXPECT_GREATER_DOUBLE(ACTUAL, EXPECTED)             _EXPECT_GREATER_DOUBLE(ACTUAL, EXPECTED) 
#define EXPECT_GREATER_EQUAL_DOUBLE(ACTUAL, EXPECTED)       _EXPECT_GREATER_EQUAL_DOUBLE(ACTUAL, EXPECTED) 
#define EXPECT_LESS_DOUBLE(ACTUAL, EXPECTED)                _EXPECT_LESS_DOUBLE(ACTUAL, EXPECTED) 
#define EXPECT_LESS_EQUAL_DOUBLE(ACTUAL, EXPECTED)          _EXPECT_LESS_EQUAL_DOUBLE(ACTUAL, EXPECTED) 

/* string assertion */
#define EXPECT_EQUAL_STRING(ACTUAL, EXPECTED)               _EXPECT_EQUAL_STRING(ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_STRING(ACTUAL, EXPECTED)           _EXPECT_NOT_EQUAL_STRING(ACTUAL, EXPECTED)
#define EXPECT_GREATER_STRING(ACTUAL, EXPECTED)             _EXPECT_GREATER_STRING(ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_STRING(ACTUAL, EXPECTED)       _EXPECT_GREATER_EQUAL_STRING(ACTUAL, EXPECTED)
#define EXPECT_LESS_STRING(ACTUAL, EXPECTED)                _EXPECT_LESS_STRING(ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_STRING(ACTUAL, EXPECTED)          _EXPECT_LESS_EQUAL_STRING(ACTUAL, EXPECTED)

/* pointer assertion */
#define EXPECT_NULL(POINTER)                                _EXPECT_NULL(POINTER)
#define EXPECT_NOT_NULL(POINTER)                            _EXPECT_NOT_NULL(POINTER)

/* boolean expression */
#define EXPECT_TRUE(EXPRESSION)                             _EXPECT_TRUE(EXPRESSION)
#define EXPECT_FALSE(EXPRESSION)                            _EXPECT_FALSE(EXPRESSION)


#endif