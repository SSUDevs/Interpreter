#!/bin/bash

# Nav to Blue_Interpreter dir and start server
cd Blue_Interpreter
node blueApi.js &
# Note: '&' allows the script to continue running while the node server starts in the background.

# Nav back to the root directory
cd ..

# Nav to Frontend dir and start the dev server
cd Frontend
npm run dev &

# Wait for all background processes to finish before exit
wait
