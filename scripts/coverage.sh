#!/usr/bin/env bash

set -e

project_dir=$(pwd)

cd build/
lcov -d project/client/interface/Pages  -t "tests/interface_tests" -o coverage.info -c --include "$project_dir/project/client/interface/Pages"
genhtml -o report coverage.info
