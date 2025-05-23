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
#ifndef UTEST_TYPES_H
#define UTEST_TYPES_H

#include <stdbool.h>

typedef signed char         UTEST_INT8_TYPE;
typedef signed short        UTEST_INT16_TYPE;
typedef signed int          UTEST_INT32_TYPE;
typedef long long           UTEST_INT64_TYPE;

typedef unsigned char       UTEST_UINT8_TYPE;
typedef unsigned short      UTEST_UINT16_TYPE;
typedef unsigned int        UTEST_UINT32_TYPE;
typedef unsigned long long  UTEST_UINT64_TYPE;

typedef UTEST_INT64_TYPE    UTEST_INT_TYPE;
typedef UTEST_UINT64_TYPE   UTEST_UINT_TYPE;
typedef float               UTEST_FLOAT_TYPE;
typedef double              UTEST_DOUBLE_TYPE;
typedef bool                UTEST_BOOLEAN_TYPE;
typedef UTEST_UINT_TYPE     UTEST_COUNTER_TYPE;
typedef UTEST_UINT64_TYPE   UTEST_FLAG_TYPE;
typedef const char *        UTEST_STRING_TYPE;

typedef void (*UTEST_GENERAL_FUNC_PTR)(void);

typedef enum{
    UTEST_RESULT_SUCCESS,
    UTEST_RESULT_FAILURE,
    UTEST_RESULT_RUNNING,
} UtestResultType;

typedef enum{
    UTEST_CMP_EQUAL,
    UTEST_CMP_NOT_EQUAL,
    UTEST_CMP_GREATER,
    UTEST_CMP_GREATER_EQUAL,
    UTEST_CMP_LESS,
    UTEST_CMP_LESS_EQUAL,
    UTEST_CMP_NULL,
    UTEST_CMP_NOT_NULL,
} UtestCompareType;

typedef struct{
    UTEST_STRING_TYPE   TestSuiteName;
    UTEST_BOOLEAN_TYPE  IsFailed;
} UtestSuiteType;

typedef struct{
    UTEST_STRING_TYPE TestCaseName;
    UTEST_BOOLEAN_TYPE IsFailed;
} UtestCaseType;

typedef struct{
    UTEST_COUNTER_TYPE PassedTestCases;
    UTEST_COUNTER_TYPE FailedTestCases;
    UTEST_COUNTER_TYPE TotalTestCases;
    UTEST_FLAG_TYPE    Flags;
} UtestStateType;

#endif