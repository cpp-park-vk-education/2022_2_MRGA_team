#!/usr/bin/env bash

VALGRIND_LOG="valgrind.log"
NO_LOST_PATTERN="All heap blocks were freed -- no leaks are possible"
NO_ERROR_PATTERN="ERROR SUMMARY: 0 errors"

rm -f VALGRIND_LOG

valgrind --tool=memcheck --show-leak-kinds=all --leak-check=summary --leak-check=full --track-origins=yes --log-file=${VALGRIND_LOG} build/tests/interface_tests || exit 1
NO_LOST=$(grep "${NO_LOST_PATTERN}" "${VALGRIND_LOG}")
NO_ERROR=$(grep "${NO_ERROR_PATTERN}" "${VALGRIND_LOG}")
if [ -z "${NO_LOST}" ] || [ -z "${NO_ERROR}" ]; then cat "${VALGRIND_LOG}"; exit 1; fi
echo " ***** SUCCESS MEMTEST *****"
