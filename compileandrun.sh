#!/bin/bash

files=`ls *.c`
if [ -f p ];then
rm p
fi
gcc $files -o p
if [ ! -f p ];then
echo "Compilation Errors found"
else
echo "Build Successful"
./p
fi
