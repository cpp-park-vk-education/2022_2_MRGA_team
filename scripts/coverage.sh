#!/usr/bin/env bash
set -e

cd build/
lcov -t "project/client/interface/PartyTime" -o coverage.info -c -d tests/
genhtml -o report coverage.info


# Полезные пути:
# ../build/project/client/interface/PartyTime/CMakeFiles/PartyTime.dir/main.cpp.o