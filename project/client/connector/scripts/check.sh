#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n\n\t\t***** ${1} *****\n\n"
}



print_header "RUN cppcheck"

interface=lib/interface
implementation=lib/implementation
cppcheckSupress="--suppress=missingIncludeSystem --suppress=unusedFunction"
# shellcheck disable=SC2086
cppcheck lib  --enable=all --inconclusive --error-exitcode=1 -I $interface -I $implementation $cppcheckSupress


print_header "RUN clang-tidy"
source="$implementation/source"
clang-tidy $source/* -warnings-as-errors=* -extra-arg=-std=c++20 -- -I$interface -I$implementation


print_header "RUN cpplint"
filter="-build/c++,-readability,-legal/copyright,-build/namespaces_headers,-build/include_subdir,-whitespace/indent,-runtime/references,-build/namespaces"
cpplint --extensions=c,h,hpp,cpp --filter=$filter --headers=h,hpp $source/* $implementation/* $interface/*


print_header "SUCCESS"
