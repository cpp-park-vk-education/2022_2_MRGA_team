#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck interface_lib/**/*.cpp interface_lib/main.c --enable=all --inconclusive --error-exitcode=1 -I interface_lib/matrix -I interface_lib/matrix -I interface_lib/processes --suppress=missingIncludeSystem

print_header "RUN clang-tidy"
clang-tidy interface_lib/**/*.cpp interface_lib/main.cpp -- -std=gnu99 -Isync_lib/matrix -Iasync_lib/processes -Iasync_lib/matrix

print_header "SUCCESS"