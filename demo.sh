#!/bin/bash

PROJECT_DIR=bin
BINARY=solver

if [[ ! -d "${PROJECT_DIR}" ]]
then
    mkdir "${PROJECT_DIR}"
fi

if [[ ! -f "${BINARY}" ]]
then
    pushd ${PROJECT_DIR} && cmake .. && make
    popd
fi

if [[ -f "${BINARY}" ]]
then
    for file in puzzle{1..3}.txt;
    do
        printf "${file}\n"
        ./solver < "${file}";
        printf "\n"
    done
else
    printf "Demo build failed.\n"
fi
