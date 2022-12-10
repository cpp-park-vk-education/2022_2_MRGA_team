#!/usr/bin/env bash
set -e

project_dir=$(pwd)

cd build/
lcov -d tests  -t "tests/interface_tests" -o coverage.info -c --include "$project_dir/tests/*"
genhtml -o report coverage.info
