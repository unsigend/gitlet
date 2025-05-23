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

#ifndef UTEST_INTERNALS_H
#define UTEST_INTERNALS_H
/**
 * @file utest_internals.h
 * @version 1.0
 * @date 2025-05-16
 * @author QIU YIXIANG
 * @brief This file contains the internal definitions and declarations for the utest library.
 *        If you are using the utest library, you should not need to include this file directly.
 *        Instead, you should include the utest.h file.
 */

#ifdef __cplusplus
extern "C" {
#endif 

#include <stddef.h>
#include <string.h>

#include <utest/utest_types.h>

extern UtestStateType   _GlobalTestState;

extern void UtestBegin();
extern void UtestEnd();
extern void UtestRunTestCase(UTEST_GENERAL_FUNC_PTR test_case_ptr, UTEST_STRING_TYPE test_case_name);
extern void UtestRunTestSuite(UTEST_GENERAL_FUNC_PTR test_suite_ptr, UTEST_STRING_TYPE test_suite_name);
extern void UtestAssertionError(UTEST_STRING_TYPE FILE, UTEST_INT_TYPE LINE, const char * format_msg, ...);

#ifdef __cplusplus
}  
#endif

/* utest library version macros */
#define _UTEST_VERSION_MAJOR       1
#define _UTEST_VERSION_MINOR       0

/* utility macros */
#define _UTEST_STRINGIFY(X)         # X
#define UTEST_STRINGIFY(X)          _UTEST_STRINGIFY(X)
#define UTEST_CONCATENATE(A, B)     A ## B
#define UTEST_CONCATENATE3(A, B, C) UTEST_CONCATENATE(A, UTEST_CONCATENATE(B, C))

/* flags for utest library */
#undef UTEST_FLAG_NONE
#undef UTEST_FLAG_SHOW_CASE
#undef UTEST_FLAG_SHOW_SUITE
#undef UTEST_FLAG_STYLE_FULL
#undef UTEST_FLAG_STOP_ON_FAILURE
#undef UTEST_FLAG_DEFAULT

#define UTEST_FLAG_NONE                 0x00
#define UTEST_FLAG_SHOW_CASE            0x01
#define UTEST_FLAG_SHOW_SUITE           0x02
#define UTEST_FLAG_STYLE_FULL           0x04
#define UTEST_FLAG_STOP_ON_FAILURE      0x08
#define UTEST_FLAG_DEFAULT              (UTEST_FLAG_SHOW_CASE | UTEST_FLAG_SHOW_SUITE \
                                        | UTEST_FLAG_STYLE_FULL | UTEST_FLAG_STOP_ON_FAILURE)

/* implementation of core macros */                              
#define _UTEST_BEGIN()                              UtestBegin()
#define _UTEST_END()                                UtestEnd()                  
#define _UTEST_SET_FLAG(UTEST_FLAG)                 _GlobalTestState.Flags |= UTEST_FLAG
#define _UTEST_CLEAR_FLAG(UTEST_FLAG)               _GlobalTestState.Flags &= ~(UTEST_FLAG)
#define _UTEST_FLAG_RESET()                         _GlobalTestState.Flags = UTEST_FLAG_DEFAULT
#define _UTEST_TEST_CASE(TEST_CASE_NAME)            static void UTEST_CONCATENATE(utest_case_, TEST_CASE_NAME)(void)
#define _UTEST_TEST_SUITE(TEST_SUITE_NAME)          void UTEST_CONCATENATE(utest_suite_, TEST_SUITE_NAME)(void)
#define _UTEST_RUN_TEST_CASE(TEST_CASE_NAME)        UtestRunTestCase(UTEST_CONCATENATE(utest_case_, TEST_CASE_NAME),        \
                                                    UTEST_STRINGIFY(TEST_CASE_NAME))
#define _UTEST_RUN_TEST_SUITE(TEST_SUITE_NAME)      UtestRunTestSuite(UTEST_CONCATENATE(utest_suite_, TEST_SUITE_NAME),     \
                                                    UTEST_STRINGIFY(TEST_SUITE_NAME))

/* Assertion Macros */ 

/* boolean expression */
#define _EXPECT_TRUE(EXPRESSION)                                                    \
    if (!(EXPRESSION)){                                                             \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(EXPRESSION) " was true, actual was false");       \
    }
#define _EXPECT_FALSE(EXPRESSION)                                                   \
    if ((EXPRESSION)){                                                              \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(EXPRESSION) " was false, actual was true");       \
    }

/* pointer assertion */
#define _EXPECT_NULL(POINTER)                                                       \
    if ((POINTER) != NULL){                                                         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(POINTER) " was NULL, actual was not NULL");       \
    }
        
#define _EXPECT_NOT_NULL(POINTER)                                                   \
    if ((POINTER) == NULL){                                                         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(POINTER) " was not NULL, actual was NULL");       \
    }

/* string assertion */
#define _EXPECT_EQUAL_STRING(ACTUAL, EXPECTED)                                      \
    if (strcmp((ACTUAL), (EXPECTED)) != 0){                                         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " == \"%s\","                             \
        " actual was \"%s\"", EXPECTED, ACTUAL);                                    \
    }              
#define _EXPECT_NOT_EQUAL_STRING(ACTUAL, EXPECTED)                                  \
    if (strcmp((ACTUAL), (EXPECTED)) == 0){                                         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " != \"%s\","                             \
        " actual was \"%s\"", EXPECTED, ACTUAL);                                    \
    }     
#define _EXPECT_GREATER_STRING(ACTUAL, EXPECTED)                                    \
    if (strcmp((ACTUAL), (EXPECTED)) <= 0){                                         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " > \"%s\","                              \
        " actual was \"%s\"", EXPECTED, ACTUAL);                                    \
    }
#define _EXPECT_GREATER_EQUAL_STRING(ACTUAL, EXPECTED)                              \
    if (strcmp((ACTUAL), (EXPECTED)) < 0){                                          \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " >= \"%s\","                             \
        " actual was \"%s\"", EXPECTED, ACTUAL);                                    \
    }
#define _EXPECT_LESS_STRING(ACTUAL, EXPECTED)                                       \
    if (strcmp((ACTUAL), (EXPECTED)) >= 0){                                         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " < \"%s\","                              \
        " actual was \"%s\"", EXPECTED, ACTUAL);                                    \
    }
#define _EXPECT_LESS_EQUAL_STRING(ACTUAL, EXPECTED)                                 \
    if (strcmp((ACTUAL), (EXPECTED)) > 0){                                          \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " <= \"%s\","                             \
        " actual was \"%s\"", EXPECTED, ACTUAL);                                    \
    }

/* float assertion */
#define _EXPECT_EQUAL_FLOAT(ACTUAL, EXPECTED)                                       \
    if ((ACTUAL) != (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " == %f,"                                 \
        " actual was %f", EXPECTED, ACTUAL);                                        \
    }
#define _EXPECT_NOT_EQUAL_FLOAT(ACTUAL, EXPECTED)                                   \
    if ((ACTUAL) == (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " != %f,"                                 \
        " actual was %f", EXPECTED, ACTUAL);                                        \
    }
#define _EXPECT_GREATER_FLOAT(ACTUAL, EXPECTED)                                     \
    if ((ACTUAL) <= (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " > %f,"                                  \
        " actual was %f", EXPECTED, ACTUAL);                                        \
    }
#define _EXPECT_GREATER_EQUAL_FLOAT(ACTUAL, EXPECTED)                               \
    if ((ACTUAL) < (EXPECTED)){                                                     \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " >= %f,"                                 \
        " actual was %f", EXPECTED, ACTUAL);                                        \
    }
#define _EXPECT_LESS_FLOAT(ACTUAL, EXPECTED)                                        \
    if ((ACTUAL) >= (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " < %f,"                                  \
        " actual was %f", EXPECTED, ACTUAL);                                        \
    }
#define _EXPECT_LESS_EQUAL_FLOAT(ACTUAL, EXPECTED)                                  \
    if ((ACTUAL) > (EXPECTED)){                                                     \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " <= %f,"                                 \
        " actual was %f", EXPECTED, ACTUAL);                                        \
    }

/* double assertion */
#define _EXPECT_EQUAL_DOUBLE(ACTUAL, EXPECTED)                                      \
    if ((ACTUAL) != (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " == %lf,"                                \
        " actual was %lf", EXPECTED, ACTUAL);                                       \
    }
#define _EXPECT_NOT_EQUAL_DOUBLE(ACTUAL, EXPECTED)                                  \
    if ((ACTUAL) == (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " != %lf,"                                \
        " actual was %lf", EXPECTED, ACTUAL);                                       \
    }
#define _EXPECT_GREATER_DOUBLE(ACTUAL, EXPECTED)                                    \
    if ((ACTUAL) <= (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " > %lf,"                                 \
        " actual was %lf", EXPECTED, ACTUAL);                                       \
    }
#define _EXPECT_GREATER_EQUAL_DOUBLE(ACTUAL, EXPECTED)                              \
    if ((ACTUAL) < (EXPECTED)){                                                     \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " >= %lf,"                                \
        " actual was %lf", EXPECTED, ACTUAL);                                       \
    }
#define _EXPECT_LESS_DOUBLE(ACTUAL, EXPECTED)                                       \
    if ((ACTUAL) >= (EXPECTED)){                                                    \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " < %lf,"                                 \
        " actual was %lf", EXPECTED, ACTUAL);                                       \
    }
#define _EXPECT_LESS_EQUAL_DOUBLE(ACTUAL, EXPECTED)                                 \
    if ((ACTUAL) > (EXPECTED)){                                                     \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " <= %lf,"                                \
        " actual was %lf", EXPECTED, ACTUAL);                                       \
    }
/* unsigned integer assertion */
#define _EXPECT_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                             \
    if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) != (UTEST_UINT_TYPE)(TYPE)(EXPECTED)){      \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " == %llu,"                               \
        " actual was %llu", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_NOT_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                         \
    if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) == (UTEST_UINT_TYPE)(TYPE)(EXPECTED)){      \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " != %llu,"                               \
        " actual was %llu", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_GREATER_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                           \
    if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) <= (UTEST_UINT_TYPE)(TYPE)(EXPECTED)){      \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " > %llu,"                                \
        " actual was %llu", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_GREATER_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                     \
    if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) < (UTEST_UINT_TYPE)(TYPE)(EXPECTED)){       \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " >= %llu,"                               \
        " actual was %llu", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_LESS_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                              \
    if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) >= (UTEST_UINT_TYPE)(TYPE)(EXPECTED)){      \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " < %llu,"                                \
        " actual was %llu", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_LESS_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                        \
    if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) > (UTEST_UINT_TYPE)(TYPE)(EXPECTED)){       \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " <= %llu,"                               \
        " actual was %llu", EXPECTED, ACTUAL);                                      \
    }

/* signed integer assertion */
#define _EXPECT_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                              \
    if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) != (UTEST_INT_TYPE)(TYPE)(EXPECTED)){        \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " == %lld,"                               \
        " actual was %lld", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_NOT_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                          \
    if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) == (UTEST_INT_TYPE)(TYPE)(EXPECTED)){        \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " != %lld,"                               \
        " actual was %lld", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_GREATER_INT_TYPE(TYPE, ACTUAL, EXPECTED)                            \
    if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) <= (UTEST_INT_TYPE)(TYPE)(EXPECTED)){        \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " > %lld,"                                \
        " actual was %lld", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_GREATER_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                      \
    if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) < (UTEST_INT_TYPE)(TYPE)(EXPECTED)){         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " >= %lld,"                               \
        " actual was %lld", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_LESS_INT_TYPE(TYPE, ACTUAL, EXPECTED)                               \
    if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) >= (UTEST_INT_TYPE)(TYPE)(EXPECTED)){        \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " < %lld,"                                \
        " actual was %lld", EXPECTED, ACTUAL);                                      \
    }
#define _EXPECT_LESS_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                         \
    if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) > (UTEST_INT_TYPE)(TYPE)(EXPECTED)){         \
        UtestAssertionError(__FILE__, __LINE__,                                     \
        "expect " UTEST_STRINGIFY(ACTUAL) " <= %lld,"                               \
        " actual was %lld", EXPECTED, ACTUAL);                                      \
    }


#define _EXPECT_EQUAL_UINT(ACTUAL, EXPECTED)            _EXPECT_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_UINT8(ACTUAL, EXPECTED)           _EXPECT_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_UINT16(ACTUAL, EXPECTED)          _EXPECT_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_UINT32(ACTUAL, EXPECTED)          _EXPECT_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_UINT64(ACTUAL, EXPECTED)          _EXPECT_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_NOT_EQUAL_UINT(ACTUAL, EXPECTED)        _EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_UINT8(ACTUAL, EXPECTED)       _EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_UINT16(ACTUAL, EXPECTED)      _EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_UINT32(ACTUAL, EXPECTED)      _EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_UINT64(ACTUAL, EXPECTED)      _EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_GREATER_UINT(ACTUAL, EXPECTED)          _EXPECT_GREATER_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_UINT8(ACTUAL, EXPECTED)         _EXPECT_GREATER_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_UINT16(ACTUAL, EXPECTED)        _EXPECT_GREATER_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_UINT32(ACTUAL, EXPECTED)        _EXPECT_GREATER_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_UINT64(ACTUAL, EXPECTED)        _EXPECT_GREATER_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_GREATER_EQUAL_UINT(ACTUAL, EXPECTED)    _EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_UINT8(ACTUAL, EXPECTED)   _EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_UINT16(ACTUAL, EXPECTED)  _EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_UINT32(ACTUAL, EXPECTED)  _EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_UINT64(ACTUAL, EXPECTED)  _EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_LESS_UINT(ACTUAL, EXPECTED)             _EXPECT_LESS_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_UINT8(ACTUAL, EXPECTED)            _EXPECT_LESS_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_UINT16(ACTUAL, EXPECTED)           _EXPECT_LESS_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_UINT32(ACTUAL, EXPECTED)           _EXPECT_LESS_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_UINT64(ACTUAL, EXPECTED)           _EXPECT_LESS_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_LESS_EQUAL_UINT(ACTUAL, EXPECTED)       _EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_UINT8(ACTUAL, EXPECTED)      _EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_UINT16(ACTUAL, EXPECTED)     _EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_UINT32(ACTUAL, EXPECTED)     _EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_UINT64(ACTUAL, EXPECTED)     _EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_EQUAL_INT(ACTUAL, EXPECTED)             _EXPECT_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_INT8(ACTUAL, EXPECTED)            _EXPECT_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_INT16(ACTUAL, EXPECTED)           _EXPECT_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_INT32(ACTUAL, EXPECTED)           _EXPECT_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_EQUAL_INT64(ACTUAL, EXPECTED)           _EXPECT_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_NOT_EQUAL_INT(ACTUAL, EXPECTED)         _EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_INT8(ACTUAL, EXPECTED)        _EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_INT16(ACTUAL, EXPECTED)       _EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_INT32(ACTUAL, EXPECTED)       _EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_NOT_EQUAL_INT64(ACTUAL, EXPECTED)       _EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_GREATER_INT(ACTUAL, EXPECTED)           _EXPECT_GREATER_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_INT8(ACTUAL, EXPECTED)          _EXPECT_GREATER_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_INT16(ACTUAL, EXPECTED)         _EXPECT_GREATER_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_INT32(ACTUAL, EXPECTED)         _EXPECT_GREATER_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_INT64(ACTUAL, EXPECTED)         _EXPECT_GREATER_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_GREATER_EQUAL_INT(ACTUAL, EXPECTED)     _EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_INT8(ACTUAL, EXPECTED)    _EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_INT16(ACTUAL, EXPECTED)   _EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_INT32(ACTUAL, EXPECTED)   _EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_GREATER_EQUAL_INT64(ACTUAL, EXPECTED)   _EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_LESS_INT(ACTUAL, EXPECTED)              _EXPECT_LESS_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_INT8(ACTUAL, EXPECTED)             _EXPECT_LESS_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_INT16(ACTUAL, EXPECTED)            _EXPECT_LESS_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_INT32(ACTUAL, EXPECTED)            _EXPECT_LESS_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_INT64(ACTUAL, EXPECTED)            _EXPECT_LESS_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#define _EXPECT_LESS_EQUAL_INT(ACTUAL, EXPECTED)        _EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_INT8(ACTUAL, EXPECTED)       _EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_INT16(ACTUAL, EXPECTED)      _EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_INT32(ACTUAL, EXPECTED)      _EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define _EXPECT_LESS_EQUAL_INT64(ACTUAL, EXPECTED)      _EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)
#endif