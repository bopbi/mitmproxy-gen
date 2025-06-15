#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "db_migration.h"

int run_migration(sqlite3 *db, const char *filename) {
    // read migration file
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "cannot open migration.sql file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char *sql = malloc(fsize + 1);
    if (!sql) {
        fprintf(stderr, "Failed to allocate memory for SQL file \n");
        fclose(file);
        return 0;
    }
    fread(sql, 1, fsize, file);
    sql[fsize] = '\0';
    fclose(file);

    char *err_msg = 0;
    int execSQLRC = sqlite3_exec(db, sql, 0, 0, &err_msg);
    free(sql);

    if (SQLITE_OK != execSQLRC) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 0;
    } else {
        printf("Migration created from migration.sql\n");
    }

    return 1;
}
