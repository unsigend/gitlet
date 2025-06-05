#!/bin/bash

# A shell script to install dependencies for gitlet

# check the Operating System
HOST_OS=$(uname -s)

if [ "$HOST_OS" == "Linux" ]; then
    # Check if the system is Ubuntu/Debian
    if [ -f /etc/debian_version ]; then
        # Install dependencies for Ubuntu/Debian
        sudo apt-get update
        sudo apt-get install -y build-essential git python3 python3.10-venv gcc make gdb
        sudo apt-get install -y openssl libssl-dev
    # Check if the system is CentOS/RHEL/Fedora
    elif [ -f /etc/redhat-release ]; then
        # Install dependencies for CentOS/RHEL/Fedora
        sudo yum update -y
        sudo yum install -y gcc make gdb git python3 python3.10-venv build-essential
        sudo yum install -y openssl
    else
        echo "Unsupported Linux distribution for gitlet"
        exit 1
    fi
elif [ "$HOST_OS" == "Darwin" ]; then
    # Check if the system is macOS
    # Check if the brew is installed
    if [ -f /opt/homebrew/bin/brew ]; then
        # Install dependencies for macOS
        brew install gcc
        brew install make
        brew install lldb
        brew install git
        brew install python3
        brew install openssl
    else
        echo "brew is not installed On MacOS"
        exit 1
    fi
else
    echo "Unsupported operating system for gitlet"
    exit 1
fi
