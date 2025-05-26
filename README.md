<p align="center">
  <img src="assets/logo.png" alt="gitlet logo" width="300"/>
</p>
<p align="center">
  <img src="https://img.shields.io/badge/license-MIT-green" />
  <img src="https://img.shields.io/badge/version-0.1-yellow" />
  <img src="https://img.shields.io/badge/language-C-blue" />
</p>

A Simple and lightweight version control system inspired by Git, implemented in C with Python test support. Gitlet provides core version control features while maintaining a minimal and efficient design. Mainly for studying purpose.

Inspired by: 
- [UC Berkeley CS 61B](https://sp21.datastructur.es/materials/proj/proj2/proj2)
- [Write yourself a git](https://wyag.thb.lt/)

official reference: 
- [git document](https://git-scm.com/docs)

## Table of Contents
- [Supported Operating Systems](#supported-operating-systems)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Building the Project](#building-the-project)
- [Testing](#testing)
- [Available Commands](#available-commands)
- [Contributing](#contributing)

## Supported Operating Systems
Currently only testing and building in these operating systems for test. The project is designed to be portable across Unix-like systems.

- macOS (Darwin)
  - Tested on macOS 24.5.0 and later
  - Requires Homebrew for package management
- Linux
  - Ubuntu/Debian
    - Tested on Ubuntu 22.04 LTS and later
    - Uses apt package manager
  - CentOS/RHEL/Fedora
    - Tested on CentOS 8 and later
    - Uses yum package manager

## Dependencies

### Required Tools
- C Compiler (gcc)
- Make
- Git
- Python 3
- Debugger

### Python Testing Dependencies
- pytest (automatically installed in virtual environment)
  - Used for Python test suite
  - Installed automatically during test setup
  - Version 7.0 or later recommended

## Installation

### macOS
1. Ensure Homebrew is installed
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
2. Install dependencies using make:
   ```bash
   make dep
   ```
   This will automatically:
   - Install gcc, make, lldb, git, and python3
   - Set up the development environment
   - Verify all installations

### Linux
1. For Ubuntu/Debian:
   ```bash
   make dep
   ```
   This will:
   - Update package lists
   - Install build-essential, git, python3, gcc, make, and gdb
   - Set up the development environment

2. For CentOS/RHEL/Fedora:
   ```bash
   make dep
   ```
   This will:
   - Update system packages
   - Install gcc, make, gdb, git, and python3
   - Configure the development environment

## Building the Project
The final building process will build a program called gitlet in the root directory. The build system uses GNU Make and supports both debug and release builds.

### Building the Program
To build the complete program:
```bash
make all
```
This will:
- Create the `gitlet` executable in the root directory
- Compile all source files with optimizations
- Link against required libraries
- Generate debug symbols if DEBUG=1 is set
### Add Program to Global Environment
Using this command to add the program to your global shell environment. And when you want to use test cases for the program you must use it.
```bash
make add-env
```
After this command you just need using `source` to update the variable. 

### Building the Library
It is optional to build the gitlet library:
```bash
make lib
```
This will create `lib/gitlet.a` library.

### Cleaning Build Files
To clean build files:
```bash
make clean
```

To clean all files including Python virtual environment (bad for performance and cache)
```bash
make clean-all
```

## Testing

Gitlet supports a variety of test suites using pytest for Python tests and Utest Framework for C tests. The test system is designed to be comprehensive and easy to use.

To run all tests (both C and Python):
```bash
make test
```

To run C test cases:

```bash
make test-c
```

To run Python test cases:

```bash
make test-py
```

## Available Commands

### Build Commands
- `make all` - Build the complete program
- `make lib` - Build the gitlet library
- `make clean` - Clean build files
- `make clean-all` - Clean all files including Python environment
- `make add-env` - Export the program to the PATH variable

### Test Commands
- `make test` - Run all tests
- `make test-c` - Run C tests only
- `make test-py` - Run Python tests only

### Help
- `make help` - Show available commands and their descriptions

## Contributing

Contributions to Gitlet are welcome! Whether it is bug reports or code contribution.

