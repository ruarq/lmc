#!/bin/bash

# format the source code
./format.sh

# clean everything
echo ""
echo "==== cleaning release ===="
make clean config=release

# build release mode
./build.sh release
