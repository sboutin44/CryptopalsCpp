#!/bin/bash 

set -x
clang-format -style=Google -i src/*.cc test/*.cc inc/*.h
make

