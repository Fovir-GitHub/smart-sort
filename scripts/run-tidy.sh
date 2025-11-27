#!/usr/bin/env bash
set -e

GCC_BIN=g++

INCLUDES=$(echo | $GCC_BIN -E -x c++ - -v 2>&1 | \
           sed -n '/#include <...> search starts here:/,/End of search list./p' | \
           grep -v '#' | grep -v "End of search" | sed 's|^| -I|')

BUILD_DIR=build
FILES=$(find src -name "*.cpp" -o -name "*.h")

FAILED=0

for f in $FILES; do
    echo "Running clang-tidy on $f ..."
    clang-tidy "$f" -p "$BUILD_DIR" -- $INCLUDES || FAILED=1
done

if [ $FAILED -ne 0 ]; then
    echo "clang-tidy found issues!"
    exit 1
fi
