# MIT License

# Copyright (c) 2025 QIU YIXIANG

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Makefile for gitlet
# building this project for c++

# Meta Data
PROG_NAME	:= 		gitlet
THREAD_NUM	:= 		4
VERSION		:= 		0.1.0

# Path variables
CUR_DIR		:= 		$(CURDIR)
SRC_DIR		:= 		./src
INCLUDE_DIR	:= 		./include
BUILD_DIR	:= 		./build
TEST_DIR	:= 		./test
OBJ_DIR		:= 		$(BUILD_DIR)/obj
DEP_DIR		:= 		$(BUILD_DIR)/dep

# variables for tools
GCC  		:= 		gcc
CXX  		:= 		g++
GDB  		:= 		gdb
ifndef $(LD)
LD			:= 		$(CXX)
endif

# CXX flags for c++
CXX_FLAGS 	:= 		-Wall -Wextra -Werror -Wshadow
CXX_FLAGS 	+= 		-std=c++17
CXX_FLAGS   +=      -O2 

CXX_DEP_FLAGS   	+=      -MMD -MP -MF
CXX_INCLUDE_FLAGS	+= 	-I $(INCLUDE_DIR)

SRCS 		:= 		$(wildcard $(SRC_DIR)/*.cpp)
OBJS 		:= 		$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS 		:= 		$(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRCS))

# Make sure include the dependency files
-include $(DEPS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(CXX) $(CXX_FLAGS) $(CXX_DEP_FLAGS) $(addprefix $(DEP_DIR)/,$(patsubst %.cpp,%.d,$(notdir $<))) \
	$(CXX_INCLUDE_FLAGS) -c $< -o $@
	@echo "  + CXX\t$<"

# target definitions
.DEFAULT_GOAL := help
.PHONY: all clean test help check info

all: check info $(OBJS)
	@$(LD) $(CXX_FLAGS) $(OBJS) -o $(PROG_NAME)
	@echo "  + LD\t$(PROG_NAME)"

test:
	@$(MAKE) -C -j $(THREAD_NUM) $(TEST_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(PROG_NAME)

help:
	@echo "Makefile for gitlet"
	@echo "Copyright (C) 2025 QIU YIXIANG"
	@echo "USAGE:"
	@echo "\tmake help\t\tShow this help message"
	@echo "\tmake all\t\tBuild executable gitlet"
	@echo "\tmake clean\t\tClean build files"
	@echo "\tmake test\t\tRun tests"
	@echo ""

check:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)

info:
	@echo "Building project $(PROG_NAME): "
	@echo "Current Version :  $(VERSION)"