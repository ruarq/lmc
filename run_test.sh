#!/bin/bash

./build.sh $1

if [ $3 ]
then
	iters=$3
else
	iters=1
fi

if [ $1 ]
then
	for ((i = 1; i <= $iters; ++i))
	do
		echo "==== Running test $i ===="
		bin/$1/lmc --benchmark $(find perf_tests/$2 -name "*.lm")
	done
else
	echo "No such file or directory"
fi
