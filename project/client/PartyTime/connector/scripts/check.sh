#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n\n\t\t***** ${1} *****\n\n"
}



print_header "RUN cppcheck"

interface=lib/HttpConnector/interface
implementation=lib/HttpConnector/implementation

http_interface=lib/HttpConnector/interface
http_impl=lib/HttpConnector/implementation/include
store_interface=lib/LocalStorage/interface
store_impl=lib/LocalStorage/implementation/include
ptk_impl=lib/PartyTimeConnector/implementation/include
ptk_interface=lib/PartyTimeConnector/interface

cppcheckSupress="--suppress=missingIncludeSystem --suppress=unusedFunction --suppress=noExplicitConstructor --suppress=uninitvar"
# shellcheck disable=SC2086
cppcheck lib  --enable=all --inconclusive --error-exitcode=1 -I $http_interface -I $http_impl -I $store_interface -I $store_impl -I $ptk_impl -I $ptk_interface $cppcheckSupress


print_header "RUN clang-tidy"
src="lib/HttpConnector/implementation/src/*.cpp"
sr1c="lib/LocalStorage/implementation/src/*.cpp"
src2="lib/PartyTimeConnector/implementation/src/*.cpp"
# clang-tidy $src $src1 $src2 -warnings-as-errors=* -extra-arg=-std=c++20 -- -I$http_interface -I$http_impl -I$store_interface -I$store_impl -I$ptk_impl -I$ptk_interface


print_header "RUN cpplint"
filter="-build/c++,-readability,-legal/copyright,-build/namespaces_headers,-build/include_subdir,-whitespace/indent,-runtime/references,-build/namespaces"
# cpplint --extensions=c,h,hpp,cpp --filter=$filter --headers=h,hpp $http_interface/* $http_impl/* $store_interface/* $store_impl/* $ptk_impl/* $ptk_interface/* $src1 $src2 $src


print_header "SUCCESS"
