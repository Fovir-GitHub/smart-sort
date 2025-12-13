#!/usr/bin/env bash
set -e

GCC_BIN=g++

SYSTEM_INCLUDES=$(echo | $GCC_BIN -E -x c++ - -v 2>&1 | \
           sed -n '/#include <...> search starts here:/,/End of search list./p' | \
           grep -v '#' | grep -v "End of search" | \
           sed 's/^[[:space:]]*//' | \
           sed 's/^/-isystem /')

BUILD_DIR=build
FILES=$(find src -name "*.cpp" -o -name "*.h" -o -name "*.hpp")

PROJECT_INCLUDES=$(jq -r '.[0].command' "$BUILD_DIR/compile_commands.json" | \
                   grep -oP '\-I\S+' | tr '\n' ' ')

FAILED=0
for f in $FILES; do
    echo "Running clang-tidy on $f ..."
    clang-tidy "$f" -p "$BUILD_DIR" -- -std=c++20 $PROJECT_INCLUDES $SYSTEM_INCLUDES || FAILED=1
done

if [ $FAILED -ne 0 ]; then
    echo "clang-tidy found issues!"
    exit 1
fi
