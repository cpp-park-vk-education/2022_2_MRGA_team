#!/usr/bin/env bash

cd build || exit
echo $PWD
lcov -t "tests/connector_test" -o coverage.info -c -d lib/CMakeFiles/connector.dir