#!/usr/bin/env bash
set -e

cd build/
lcov -t "project/client/interface/PartyTime" -o coverage.info -c -d tests/CMakeFiles/interface_tests.dir/
genhtml -o report coverage.info
