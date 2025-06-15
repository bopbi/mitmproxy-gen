#!/bin/sh

# Name of your main C source file
MAIN_FILE="main.c"
# Name of the SQLite amalgamation source file
SQLITE_FILE="sqlite3.c"

# Name of the migration source file
MIGRATION_FILE="db_migration.c"

# Name of the url_pattern source file
URL_PATTERN_FILE="url_pattern.c"

# Output executable name
OUTPUT="config-gen"

# Compile using gcc
gcc "$MAIN_FILE" "$SQLITE_FILE" "$MIGRATION_FILE" "$URL_PATTERN_FILE" -o "$OUTPUT"

if [ $? -eq 0 ]; then
    echo "Build successful. Run ./$OUTPUT"
else
    echo "Build failed."
fi
