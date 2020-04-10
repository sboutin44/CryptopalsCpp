#!/bin/bash 

set -x
clang-format -style=Google -i src/*.cc inc/*.h
make

