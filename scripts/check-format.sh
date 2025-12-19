#!/usr/bin/env bash

shopt -s globstar
shopt -s nullglob

exts=(c cpp h hpp)
files=()

for ext in "${exts[@]}"; do
    files+=(src/**/*."$ext")
    files+=(tests/**/*."$ext")
done

failed=0

clang-format -n -Werror "${files[@]}" || failed=1

if [ $failed -ne 0 ]; then
    echo "Run \`just format\` to fix this!"
    exit 1
fi
