# MIT License
#
# Copyright (c) 2025 Qiu Yixiang
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Makefile for build test cases
# Test Case for gitlet library are grouped into different categories:
# - Some of the core features are tested using C : Utest Framework
# - Some of the features are tested using Python : Pytest Framework

# Get these variables from the root Makefile
# export PYTHON
# export CC
# export CC_WARNINGS
# export CC_DEBUG
# export CC_OPTIMIZE
# export CC_DEPENDENCY
# export LIBRARY_NAME
# export LIBRARY_POSTFIX

# Tools variables
PIP                     :=  pip
PYTEST                  :=  pytest

# Main test path
TEST_PATH               :=  ./test
PYTEST_PATH             :=  ./test_python
CTEST_PATH              :=  ./test_c

# Current directory Path
BUILD_PATH              :=  ./build

# Root Path
LIBRARY_PATH 			:= 	../lib
INCLUDE_PATH     		:=  ../include

# Utest path
UTEST_PATH      		:=  ./utest
UTEST_INCLUDE_PATH    	:=  $(UTEST_PATH)/include
UTEST_SRC_PATH        	:=  $(UTEST_PATH)/src

CC_INCLUDES             :=  -I$(INCLUDE_PATH) -I$(UTEST_INCLUDE_PATH)
CC_FLAGS                :=  -std=c11 $(CC_WARNINGS) $(CC_DEBUG) $(CC_OPTIMIZE) $(CC_INCLUDES)

SRCS_C                 :=  $(shell find $(CTEST_PATH) -name "*.c")
OBJS_C                 :=  $(patsubst $(CTEST_PATH)/%.c, $(BUILD_PATH)/%.o, $(SRCS_C))

$(BUILD_PATH)/utest.o: $(UTEST_SRC_PATH)/utest.c
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: $(CTEST_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@

.DEFAULT_GOAL  	:=    test
.PHONY: test clean clean-all test-c test-py py-init

# Test the C test cases
test-c: $(OBJS_C) $(BUILD_PATH)/utest.o
	@$(CC) $(CC_FLAGS) $^ $(LIBRARY_PATH)/$(LIBRARY_NAME)$(LIBRARY_POSTFIX) -o $(BUILD_PATH)/test_c
	@clear
	@$(BUILD_PATH)/test_c

# Test the Python test cases
test-py: py-init
	@$(PYTEST_PATH)/.venv/bin/pytest $(PYTEST_PATH)

# Test all the cases for gitlet library
test: test-c test-py
	
# Clean build files
clean:
	@rm -rf $(BUILD_PATH)

# Clean all build files and cache files
clean-all:
	@$(MAKE) clean
	@rm -rf $(PYTEST_PATH)/**/__pycache__
	@rm -rf $(PYTEST_PATH)/.venv
	@rm -rf .pytest_cache

# Initialize the Python test environment
py-init:
	@if [ ! -d "$(PYTEST_PATH)/.venv" ]; then \
		$(PYTHON) -m venv $(PYTEST_PATH)/.venv; \
		. $(PYTEST_PATH)/.venv/bin/activate; \
		pip install pytest; \
	else \
		. $(PYTEST_PATH)/.venv/bin/activate; \
		if ! pip list | grep -q "^pytest "; then \
			pip install pytest; \
		fi; \
	fi
	@clear
	
	