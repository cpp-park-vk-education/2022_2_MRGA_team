#!/usr/bin/env bash

set -e
./build/tests/interface_tests
# /build/имя до папки с тестами/имя исполняемого файла для тестов
#                                                            директория которую нужно покрыть тестами
lcov -t build/tests/sync_tests -o coverage.info -c -d build/interface_lib/
genhtml -o build/report/ coverage.info