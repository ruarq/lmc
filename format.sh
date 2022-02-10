#!/bin/bash

files=$(find src -type f -regex ".*\..pp")
num_files=${#files[@]}
i=1
for file in $files
do
	echo "[$i/$num_files] clang-format : $file"
	clang-format -i $file
	i+=1
done
