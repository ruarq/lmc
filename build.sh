#!/bin/bash

# check if an argument was given
if [ $1 ]
then
	config=$1
else
	config="debug"
fi

echo "==== generating make files ===="

# run premake5
premake5 gmake2

echo ""
make config=$config
