#!/usr/bin/env bash

LOG_TEST="test.log"

red='\033[91m'
green='\033[92m'
yellow='\033[103m'
default='\033[0m'

project_dir=$(pwd)
cd build || exit
test_exec=tests/connector_test

lcov -t "$test_exec" -o coverage.info -c -d tests -d lib --include "$project_dir/lib/*"
(genhtml -o report coverage.info --output-directory coverage-report/) > "${LOG_TEST}"
cat "${LOG_TEST}"

ok_lines=true
functions=true

lines=$(grep -Eo '\.\.\.: [0-9]{1,2}.[0-9]' "${LOG_TEST}" | grep -Eo '[0-9]{1,2}.[0-9]' $cov | grep -Eo '[0-9]{2,3}')
functions=$(grep -Eo 's\.\.: [0-9]{1,2}.[0-9]' "${LOG_TEST}" | grep -Eo '[0-9]{1,2}.[0-9]' $cov | grep -Eo '[0-9]{2,3}')

if [[ $lines -ge $1 ]]; then
  printf "\t${green}%s${default}\n" "LINES_SUCCESS"
else
  printf "\t${red}%s${default}\n" "LINES_FAILED"
  ok_lines=false
fi

if [[ $functions -ge $2 ]]; then
  printf "\t${green}%s${default}\n" "FUNCTION_SUCCESS"
else
  printf "\t${red}%s${default}\n" "FUNCTION_FAILED"
  ok_functions=false
fi

if ! ($ok_lines) || ! ($ok_functions) ; then
    printf "\n\t${red}%s${default}\n" "COVERAGE TESTING FAILED"
    if ! ($ok_lines) ; then
      printf "\n\t%s${red}%d%s${default}%s${green}%d%s${default}\n" "Lines coverage is " "$lines" "%" ", but expected: " "$1" "%"
    fi
    if ! ($ok_functions) ; then
          printf "\n\t%s${red}%d%s${default}%s${green}%d%s${default}\n" "Functions coverage is " "$functions" "%" ", but expected: " "$2" "%"
        fi
    exit 1
else
    printf "\n\n\t${green}%s${default}\n" "COVERAGE TESTING PASSED"
    exit 0
fi
