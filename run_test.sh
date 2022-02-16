#!/bin/bash

./build.sh $1

if [ $1 ]
then
	bin/$1/lmc $(find perf_tests/$2 -name "*.lm")
else
	echo "No such file or directory"
fi
