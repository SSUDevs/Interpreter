#!/bin/bash

# Echo commands, see whats goin on
set -x

# Navto Blue_Interpreter dir, install dependencies and run make
cd Blue_Interpreter
npm i
make
cd ..

# Navto Frontend dir and install dependencies
cd Frontend
npm i
cd ..

# Echo a completion message
echo "Build process completed successfully."
