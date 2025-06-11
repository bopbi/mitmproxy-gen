#!/bin/sh

# Name of your main C source file
MAIN_FILE="main.c"
# Name of the SQLite amalgamation source file
SQLITE_FILE="sqlite3.c"
# Output executable name
OUTPUT="config-gen"

# Compile using gcc
gcc "$MAIN_FILE" "$SQLITE_FILE" -o "$OUTPUT"

if [ $? -eq 0 ]; then
    echo "Build successful. Run ./$OUTPUT"
else
    echo "Build failed."
fi
