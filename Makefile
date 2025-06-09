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


# Makefile for build gitlet
# Main Makefile

# Variables for paths
BUILD_PATH          	:= 	./build
CONFIG_PATH         	:= 	./config
EXTERNAL_PATH       	:= 	./external
LIB_PATH            	:= 	./lib
TEST_PATH           	:= 	./test
SCRIPT_PATH         	:= 	./script
DEP_PATH            	:= 	$(BUILD_PATH)/dep

OBJ_PATH            	:= 	$(BUILD_PATH)/obj
EXTERNAL_OBJ_PATH   	:= 	$(BUILD_PATH)/external_obj

INCLUDE_PATH        	:= 	./include
SRC_PATH            	:= 	./src

EXTERNAL_INCLUDE_PATH	:= 	$(EXTERNAL_PATH)/include
EXTERNAL_SRC_PATH		:= 	$(EXTERNAL_PATH)/src

# Variables for files
CONFIG_FILE         	:= 	$(CONFIG_PATH)/config.mk

-include $(CONFIG_FILE)

# Variables for GCC compiler
CC                  	:= 	gcc
CXX                 	:= 	g++
AR                      := 	ar
LD                      :=  $(CC)
BASH                    := 	bash
PYTHON               	:= 	python3

# Variable for Host OS
HOST_OS                 := 	$(shell uname -s)

# Variable for GCC compiler flags
CC_FLAGS                :=  -std=c11

ifeq ($(HOST_OS), Linux)
	CC_FLAGS                +=  -fPIC
endif

# Variable for GCC include paths
CC_INCLUDE_PATHS        :=  -I $(INCLUDE_PATH)
CC_INCLUDE_PATHS       	+=  -isystem $(EXTERNAL_INCLUDE_PATH)

# Include the openssl header file
ifeq ($(HOST_OS), Darwin)
CC_INCLUDE_PATHS        +=  -I /opt/homebrew/opt/openssl/include
endif

ifeq ($(HOST_OS), Linux)
CC_INCLUDE_PATHS        +=  -I /usr/include/openssl
endif

# Variable for GCC compiler warnings
CC_WARNINGS            	:= 	-Wall -Wextra -Werror
CC_WARNINGS             +=  -Wextra -Wno-unused-parameter
CC_WARNINGS             +=  -Wno-unused-function

# Variable for GCC debugger flag
CC_DEBUG                :=
ifeq ($(DEBUG), 1)
	CC_DEBUG            +=  -g
endif

# Variable for GCC Optimize flag
CC_OPTIMIZE             :=
ifeq ($(DEBUG), 1)
	CC_OPTIMIZE        	+=  -O0
else
	CC_OPTIMIZE         +=  -O2
endif

CC_DEPENDENCY           :=
CC_DEPENDENCY           +=  -MMD -MP -MF

CC_FLAGS                +=  $(CC_WARNINGS) $(CC_DEBUG) $(CC_OPTIMIZE) $(CC_INCLUDE_PATHS)

# Variable for Linker flags
LD_FLAGS                :=

EXTERNAL_LIBS           :=  -lssl -lcrypto -lz

EXTERNAL_LIB_PATH       :=
ifeq ($(HOST_OS), Darwin)
EXTERNAL_LIB_PATH       +=  -L /opt/homebrew/opt/openssl/lib
endif
ifeq ($(HOST_OS), Linux)
EXTERNAL_LIB_PATH       +=  -L /usr/lib/openssl
endif

LD_FLAGS                +=  $(EXTERNAL_LIBS)
LD_FLAGS                +=  $(EXTERNAL_LIB_PATH)

# Variables for program and library names
PROGRAM_NAME            := 	gitlet
LIBRARY_NAME            := 	$(PROGRAM_NAME)

STATIC_LIBRARY_POSTFIX  := 	.a
ifeq ($(HOST_OS), Darwin)
SHARED_LIBRARY_POSTFIX  := 	.dylib
else
SHARED_LIBRARY_POSTFIX  := 	.so
endif

SRCS                    := 	$(shell find $(SRC_PATH) -type f -name "*.c")
OBJS                    := 	$(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))

EXTERNAL_SRCS           := 	$(shell find $(EXTERNAL_SRC_PATH) -type f -name "*.c")
EXTERNAL_OBJS           := 	$(patsubst $(EXTERNAL_SRC_PATH)/%.c, $(EXTERNAL_OBJ_PATH)/%.o, $(EXTERNAL_SRCS))

# Export variables for sub-makefiles
export PYTHON
export CC
export CC_WARNINGS
export CC_DEBUG
export CC_OPTIMIZE
export CC_DEPENDENCY
export LIBRARY_NAME
export SHARED_LIBRARY_POSTFIX
export STATIC_LIBRARY_POSTFIX
export EXTERNAL_LIBS
export EXTERNAL_LIB_PATH

.DEFAULT_GOAL := help
.PHONY: all clean help lib test mkdir-lib dep add-env

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@) $(dir $(DEP_PATH)/$*.d)
	@$(CC) $(CC_FLAGS) $(CC_DEPENDENCY) $(DEP_PATH)/$*.d -c $< -o $@
	@echo " + CC\t$<"

$(EXTERNAL_OBJ_PATH)/%.o: $(EXTERNAL_SRC_PATH)/%.c
	@mkdir -p $(EXTERNAL_OBJ_PATH)
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@echo " + CC\t$<"

# if DEP_PATH exist then search for all .d files in DEP_PATH
ALL_DEPS                := 	$(shell if [ -d $(DEP_PATH) ]; then find $(DEP_PATH) -type f -name "*.d"; fi)
-include $(ALL_DEPS)

# Build the program
all: $(OBJS) $(EXTERNAL_OBJS)
	@$(CC) $(CC_FLAGS) $(LD_FLAGS) $(OBJS) $(EXTERNAL_OBJS) -o $(PROGRAM_NAME)
	@echo " + LD\t$(PROGRAM_NAME)"
	@echo "Build program $(PROGRAM_NAME) successfully in $(CURDIR)"

# Clean all build files
clean:
	@rm -rf $(BUILD_PATH)
	@rm -rf $(LIB_PATH)
	@rm -f $(PROGRAM_NAME)
	@$(MAKE) -C $(TEST_PATH) clean

# Show help
help:
	@echo "Makefile for build $(PROGRAM_NAME)"
	@echo "USAGE:"
	@echo "  make all\t- Build the program"
	@echo "  make clean\t- Clean all build files"
	@echo "  make help\t- Show this help"
	@echo "  make lib\t- Build the $(LIBRARY_NAME) library"
	@echo "  make test\t- Run all test cases"
	@echo "  make test-c\t- Run the C test cases"
	@echo "  make test-py\t- Run the Python test cases"
	@echo "  make dep\t- Install dependencies"
	@echo "  make add-env\t- Export the program to the PATH variable"
	@echo ""

# Test the program library
test: lib all
	@$(MAKE) -j4 -C $(TEST_PATH) test

# Test the C test cases
test-c: lib
	@$(MAKE) -j4 -C $(TEST_PATH) test-c

# Test the Python test cases
test-py: lib all
	@$(MAKE) -j4 -C $(TEST_PATH) test-py

# filter out the main.o file
LIB_OBJS                :=  $(filter-out $(OBJ_PATH)/main.o, $(OBJS))
# Build the library
lib: mkdir-lib $(LIB_OBJS) $(EXTERNAL_OBJS)
	@$(AR) rcs $(LIB_PATH)/lib$(LIBRARY_NAME)$(STATIC_LIBRARY_POSTFIX) $(LIB_OBJS) $(EXTERNAL_OBJS)
	@echo " + AR\tlib$(LIBRARY_NAME)$(STATIC_LIBRARY_POSTFIX)"
	@$(CC) $(CC_FLAGS) $(LD_FLAGS) -shared $(LIB_OBJS) $(EXTERNAL_OBJS) -o $(LIB_PATH)/lib$(LIBRARY_NAME)$(SHARED_LIBRARY_POSTFIX)
	@echo " + LD\tlib$(LIBRARY_NAME)$(SHARED_LIBRARY_POSTFIX)"
	@echo "Build lib$(LIBRARY_NAME)$(STATIC_LIBRARY_POSTFIX) and lib$(LIBRARY_NAME)$(SHARED_LIBRARY_POSTFIX) library in $(LIB_PATH)"

# Make the lib directory
mkdir-lib:
	@mkdir -p $(LIB_PATH)

# Clean all build file and cache (danger for performance)
clean-all:
	@$(MAKE) clean
	@$(MAKE) -C $(TEST_PATH) clean-all

# Install dependencies
dep:
	@$(BASH) $(SCRIPT_PATH)/install-dep.sh

# Export the program to the shell environment
SHELL_NAME = $(shell echo $$SHELL)
add-env:
ifeq ($(SHELL_NAME), /bin/bash)
	@echo 'export PATH="$(CURDIR):$$PATH"' >> ~/.bashrc
	@echo "Use command 'source ~/.bashrc' to update the env variable"
else ifeq ($(SHELL_NAME), /bin/zsh)
	@echo 'export PATH="$(CURDIR):$$PATH"' >> ~/.zshrc
	@echo "Use command 'source ~/.zshrc' to update the env variable"
else ifeq ($(SHELL_NAME), /bin/sh)
	@echo 'export PATH="$(CURDIR):$$PATH"' >> ~/.profile
	@echo "Use command 'source ~/.profile' to update the env variable"
else
	@echo "Unsupported shell: $(SHELL_NAME)"
endif