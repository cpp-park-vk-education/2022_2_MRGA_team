#!/usr/bin/env bash

LOG_TEST="../test.log"

red='\033[91m'
green='\033[92m'
yellow='\033[103m'
default='\033[0m'

cd build || exit
lcov -t "tests/connector_test" -o coverage.info -c -d lib/CMakeFiles/connector.dir
(genhtml -o report coverage.info --output-directory coverage-report/) > "${LOG_TEST}"
cat "${LOG_TEST}"

ok_lines=true
functions=true

lines=$(grep -Eo '\.\.\.: [0-9]{1,2}.[0-9]' ../test.log | grep -Eo '[0-9]{1,2}.[0-9]' $cov | grep -Eo '[0-9]{2}')
functions=$(grep -Eo 's\.\.: [0-9]{1,2}.[0-9]' ../test.log | grep -Eo '[0-9]{1,2}.[0-9]' $cov | grep -Eo '[0-9]{2}')

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

