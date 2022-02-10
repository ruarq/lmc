#!/bin/bash

# check if an argument was given
if [ $1 ]
then
	if [ $1 == "release" ]
	then
		config="release"
	elif [ $1 == "debug" ]
	then
		config="debug"
	else
		echo "$0: configuration '$1' unknown"
		exit 1
	fi
else
	config="debug"
fi

# format the source code
echo "==== formatting with clang-format ===="
./format.sh

echo ""
echo "==== generating make files ===="

# run premake5
./premake5 gmake2

echo ""
make config=$config
