#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

int main() {
    sqlite3 *db;
    int openRC = sqlite3_open("config.sqlite", &db);
    if (SQLITE_OK != openRC) {
        fprintf(stderr, "cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("Database opened successfully \n");

    // read migration.sql
    FILE *file = fopen("migration.sql", "rb");
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
        sqlite3_close(db);
        return 1;
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
        sqlite3_close(db);
    } else {
        printf("Migration created from migration.sql\n");
        sqlite3_close(db);
    }

    return 0;
}
