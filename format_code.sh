#!/bin/bash

# Format all .cpp and .h files
find . -iname "*.cpp" -o -iname "*.h" | xargs clang-format -i

# Uncomment below to format only staged files
# git diff --name-only --cached | grep -E "\.(cpp|h)$" | xargs clang-format -i
