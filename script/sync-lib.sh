#!/bin/bash

# A shell script using wget to get the external library form github
# And download the library to the local directory ./external

UTIL_MAIN_URL="https://raw.githubusercontent.com/unsigend/util/main/module"
ROOT_PATH=$(pwd)
EXTERNAL_PATH=$ROOT_PATH/external


# Configparse
wget -O $EXTERNAL_PATH/include/configparse.h $UTIL_MAIN_URL/configparse/include/configparse.h
wget -O $EXTERNAL_PATH/src/configparse.c $UTIL_MAIN_URL/configparse/src/configparse.c

# Argparse
wget -O $EXTERNAL_PATH/include/argparse.h $UTIL_MAIN_URL/argparse/include/argparse.h
wget -O $EXTERNAL_PATH/src/argparse.c $UTIL_MAIN_URL/argparse/src/argparse.c
