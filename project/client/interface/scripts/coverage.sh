#!/usr/bin/env bash
set -e

# cd build/
# # lcov -t "project/client/interface/PartyTime" -o coverage.info -c -d tests/CMakeFiles/interface_tests.dir/
# lcov -d PartyTime  -t "tests/interface_tests" -o coverage.info -c --include "$project_dir/PartyTime/*"
# genhtml -o report coverage.info


project_dir=$(pwd)

cd build/
lcov -d tests  -t "tests/interface_tests" -o coverage.info -c --include "$project_dir/tests/*"
genhtml -o report coverage.info
