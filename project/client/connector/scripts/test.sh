#!/usr/bin/env bash

echo $PWD
cd build || exit
ctest -VV --output-on-failure