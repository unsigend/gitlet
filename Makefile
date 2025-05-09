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
LIB_NAME	:= 		gitlet

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
AR  		:= 		ar
ifndef $(LD)
LD			:= 		$(CXX)
endif

# Archive flags
AR_FLAGS	:= 		rcs
# CXX flags for c++
CXX_FLAGS 	:= 		-Wall -Wextra -Werror -Wshadow
CXX_FLAGS 	+= 		-std=c++17
CXX_FLAGS   +=      -O2 

CXX_DEP_FLAGS   	+=  -MMD -MP -MF
CXX_INCLUDE_FLAGS	+= 	-I $(INCLUDE_DIR)

# The OBJS exclude the main.o in root directory
SRCS 		:= 		$(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS 		:= 		$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS 		:= 		$(wildcard $(DEP_DIR)/*.d)

# Make sure include the dependency files
-include $(DEPS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXX_FLAGS) $(CXX_DEP_FLAGS) $(addprefix $(DEP_DIR)/,$(patsubst %.cpp,%.d,$(notdir $<))) \
	$(CXX_INCLUDE_FLAGS) -c $< -o $@
	@echo "  + CXX\t$<"

main.o: main.cpp
	@$(CXX) $(CXX_FLAGS) $(CXX_DEP_FLAGS) $(addprefix $(DEP_DIR)/,$(patsubst %.cpp,%.d,$<)) \
	$(CXX_INCLUDE_FLAGS) -c $< -o $@
	@echo "  + CXX\t$<"

# target definitions 
.DEFAULT_GOAL := help
.PHONY: all clean test help check info

all: check info $(OBJS) main.o
	@$(LD) $(CXX_FLAGS) $(OBJS) main.o -o $(PROG_NAME)
	@echo "  + LD\t$(PROG_NAME)"

export LIB_NAME
test: check $(OBJS)
	@$(AR) $(AR_FLAGS) $(BUILD_DIR)/lib$(LIB_NAME).a $(OBJS)
	@$(MAKE) -j $(THREAD_NUM) -C $(TEST_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(PROG_NAME) main.o
	@$(MAKE) -C $(TEST_DIR) clean

help:
	@echo "Makefile for gitlet Version $(VERSION)"
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