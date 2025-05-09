# Makefile for test utility for gitlet
# Simple Makefile :)

# Test Frame work will using Google Test

CXX   	:= 		g++
GCC   	:= 		gcc
LD		:= 		$(CXX)

PROG_NAME  := 		test

# Path variables
CUR_DIR		:= 		.
CASE_DIR	:= 		$(CUR_DIR)/case
BUILD_DIR	:= 		$(CUR_DIR)/build
OBJ_DIR		:= 		$(BUILD_DIR)/obj
DEP_DIR		:= 		$(BUILD_DIR)/dep

# Host OS detection
# This is used to detect the host OS and set the include and library paths for Google Test
HOST_OS	:= 		$(shell uname -s)
ifeq ($(HOST_OS),Linux)
GOOGLE_TEST_INCLUDE_DIR  	:= 	/usr/include/
GOOGLE_TEST_LIB_DIR 		:= 	/usr/lib/
else ifeq ($(HOST_OS),Darwin)
GOOGLE_TEST_INCLUDE_DIR  	:= 	/opt/homebrew/include/
GOOGLE_TEST_LIB_DIR 		:= 	/opt/homebrew/lib/
else ifeq ($(HOST_OS),FreeBSD)
GOOGLE_TEST_INCLUDE_DIR  	:= 	/usr/local/include/
GOOGLE_TEST_LIB_DIR 		:= 	/usr/local/lib/
else
	$(error "Unsupported OS: $(HOST_OS)")
endif

# Include Directories
GITLET_INCLUDE_DIR 			:=  ../include/
GITLET_LIBRARY_DIR          :=  ../build

# C++ compiler flags
CXX_FLAGS 	:= 		-Wall -Wextra -Werror -Wshadow
CXX_FLAGS 	+= 		-std=c++17
CXX_FLAGS   +=      -O2

# Library flags
CXX_LIBS	:= 		-lgtest -lgtest_main -lpthread -l$(LIB_NAME)
CXX_LIBS    +=      -L $(GOOGLE_TEST_LIB_DIR)
CXX_LIBS    +=      -L $(GITLET_LIBRARY_DIR)

# Include flags
CXX_INCLUDE_FLAGS 	:=  -I $(GOOGLE_TEST_INCLUDE_DIR)
CXX_INCLUDE_FLAGS 	+=  -I $(GITLET_INCLUDE_DIR)
CXX_FLAGS   		+=  $(CXX_INCLUDE_FLAGS)

# Dependency flags
CXX_DEPENDENCY_FLAGS :=  -MMD -MP -MF

# Linker flags
LD_FLAGS    :=
LD_FLAGS   	+=      $(CXX_LIBS)

SRCS 		:= 		$(wildcard $(CASE_DIR)/*.cpp)
OBJS 		:= 		$(patsubst $(CASE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS 		:= 		$(patsubst $(CASE_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRCS))

-include $(DEPS)

# general rule for building object files
$(OBJ_DIR)/%.o : $(CASE_DIR)/%.cpp
	@$(CXX) $(CXX_FLAGS) $(CXX_DEPENDENCY_FLAGS) \
	$(addprefix $(DEP_DIR)/, $(patsubst %.cpp,%.d,$(notdir $<))) \
	-c $< -o $@

.DEFAULT_GOAL := test
.PHONY: clean test check

test: check $(OBJS)
	@$(LD) $(LD_FLAGS) $(OBJS) -o $(PROG_NAME) && ./$(PROG_NAME)

check:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(PROG_NAME)