#!/bin/bash

CXXFLAGS="-std=c++14 -Wall -Wextra -g"

# strip out source file name extension for binary name and store binary in bin
# folder
if [[ ! -d "./bin" ]]
then
    mkdir bin
fi

BIN_NAME="./bin/$(basename -s .cpp "$1")"
# compiles the simple binary
g++ $CXXFLAGS $1 -o $BIN_NAME

# moves positional cmdline arguments up by 1 so old $1 being source filename is
# lost
shift

# run binary with rest of the cmdline input arguments
$BIN_NAME $@

