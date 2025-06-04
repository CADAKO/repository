#!/bin/bash

if [ -s src/clang.txt ]
  then
    cat src/clang.txt
    echo "clang-format FAIL"
    exit 1
  else
  echo "clang-format SUCCES"    
fi