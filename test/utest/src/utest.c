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
 * This file is part of the utest library.
 * Implement the core logic of the utest library.
 */

#include <stdio.h>
#include <stdarg.h>
#include <utest/utest_internals.h>

#define _ASCII_COLOR_RED        "\033[31m"
#define _ASCII_COLOR_GREEN      "\033[32m"
#define _ASCII_COLOR_YELLOW     "\033[33m"
#define _ASCII_COLOR_BLUE       "\033[34m"
#define _ASCII_COLOR_MAGENTA    "\033[35m"
#define _ASCII_COLOR_CYAN       "\033[36m"
#define _ASCII_COLOR_WHITE      "\033[37m"
#define _ASCII_COLOR_RESET      "\033[0m"
#define _ASCII_COLOR_BOLD       "\033[1m"

UtestStateType   _GlobalTestState;

static UtestCaseType    _CurrentTestCase;
static UtestSuiteType   _CurrentTestSuite;

static void PrintUtestVersion(){
    fprintf(stdout, "Utest version: %d.%d\n", _UTEST_VERSION_MAJOR, _UTEST_VERSION_MINOR);
}
static void TestCasePrintResult(UtestResultType result){
    if (_GlobalTestState.Flags & UTEST_FLAG_SHOW_CASE){
        if (_GlobalTestState.Flags & UTEST_FLAG_SHOW_SUITE){
            fprintf(stdout, " |- ");
        }
        if (result == UTEST_RESULT_SUCCESS){
            fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED " _ASCII_COLOR_RESET "]");
        } else if (result == UTEST_RESULT_FAILURE){
            fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED " _ASCII_COLOR_RESET "]");
        }else if (result == UTEST_RESULT_RUNNING){
            fprintf(stdout, "[" _ASCII_COLOR_YELLOW "RUNNING" _ASCII_COLOR_RESET "]");
        }
        fprintf(stdout, "  TEST CASE: %s\n", _CurrentTestCase.TestCaseName);
    }
}
static void TestSuitePrintResult(UtestResultType result){
    if (_GlobalTestState.Flags & UTEST_FLAG_SHOW_SUITE){
        if (result == UTEST_RESULT_SUCCESS){
            fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED " _ASCII_COLOR_RESET "]");
        } else if (result == UTEST_RESULT_FAILURE){
            fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED " _ASCII_COLOR_RESET "]");
        }else if (result == UTEST_RESULT_RUNNING){
            fprintf(stdout, "[" _ASCII_COLOR_YELLOW "RUNNING" _ASCII_COLOR_RESET "]");
        }
        fprintf(stdout, "  TEST SUITE: %s\n", _CurrentTestSuite.TestSuiteName);
    }
}
static void PrintNextLine(){
    if ((_GlobalTestState.Flags & UTEST_FLAG_SHOW_SUITE) &&
        (_GlobalTestState.Flags & UTEST_FLAG_SHOW_CASE)){
        fputc('\n', stdout);
    }
}
static void PrintAssertErrorPrefix(){
    fprintf(stdout, "   ");
    if (_GlobalTestState.Flags & UTEST_FLAG_SHOW_CASE){
        if (_GlobalTestState.Flags & UTEST_FLAG_SHOW_SUITE){
            fprintf(stdout, " |- ");
        }
    }
}

void UtestBegin(){
    // initialize the global state
    _GlobalTestState.PassedTestCases = 0;
    _GlobalTestState.FailedTestCases = 0;
    _GlobalTestState.TotalTestCases = 0;
    _GlobalTestState.Flags = UTEST_FLAG_DEFAULT;
    // initialize the current test case
    _CurrentTestCase.TestCaseName = NULL;
    _CurrentTestCase.IsFailed = false;
    // initialize the current test suite
    _CurrentTestSuite.TestSuiteName = NULL;
    _CurrentTestSuite.IsFailed = false;

    // print the version
    PrintUtestVersion();
}

void UtestEnd(){
    if (_GlobalTestState.Flags & UTEST_FLAG_STYLE_FULL){
        fprintf(stdout, "====================\n");
        fprintf(stdout, "TOTAL  : %llu\n", _GlobalTestState.TotalTestCases);
        fprintf(stdout, "PASSED : %llu\n", _GlobalTestState.PassedTestCases);
        fprintf(stdout, "FAILED : %llu\n", _GlobalTestState.FailedTestCases);
        fprintf(stdout, "====================\n");
    }else{
        fprintf(stdout, "PASSED : %llu/%llu\n", _GlobalTestState.PassedTestCases, 
                _GlobalTestState.TotalTestCases);
    }
}

void UtestRunTestCase(UTEST_GENERAL_FUNC_PTR test_case_ptr, UTEST_STRING_TYPE test_case_name){
    _CurrentTestCase.TestCaseName = test_case_name;
    _CurrentTestCase.IsFailed = false;
    test_case_ptr();
    if (_CurrentTestCase.IsFailed){
        _GlobalTestState.FailedTestCases++;
        _CurrentTestSuite.IsFailed = true;
        TestCasePrintResult(UTEST_RESULT_FAILURE);
    }else{
        _GlobalTestState.PassedTestCases++;
        TestCasePrintResult(UTEST_RESULT_SUCCESS);
    }
    _GlobalTestState.TotalTestCases++;
}

void UtestRunTestSuite(UTEST_GENERAL_FUNC_PTR test_suite_ptr, UTEST_STRING_TYPE test_suite_name){
    _CurrentTestSuite.TestSuiteName = test_suite_name;
    _CurrentTestSuite.IsFailed = false;

    TestSuitePrintResult(UTEST_RESULT_RUNNING);
    test_suite_ptr();
    if (_CurrentTestSuite.IsFailed){
        TestSuitePrintResult(UTEST_RESULT_FAILURE);
    }else{
        TestSuitePrintResult(UTEST_RESULT_SUCCESS);
    }
    PrintNextLine();
}
void UtestAssertionError(UTEST_STRING_TYPE file, UTEST_INT_TYPE line, const char * format_msg, ...){
    if ( (!(_GlobalTestState.Flags & UTEST_FLAG_STOP_ON_FAILURE) ) 
    ||  (!(_CurrentTestCase.IsFailed))){

        TestCasePrintResult(UTEST_RESULT_FAILURE);
        _CurrentTestCase.IsFailed = true;

        PrintAssertErrorPrefix();
        fprintf(stdout, "%s:%lld failure", file, line);
        PrintNextLine();

        PrintAssertErrorPrefix();
        va_list args;
        va_start(args, format_msg);
        vprintf(format_msg, args);
        va_end(args);

        PrintNextLine();
    }
}