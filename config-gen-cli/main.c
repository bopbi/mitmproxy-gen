#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

void create_url_pattern(sqlite3 *db) {
    char url[256];
    printf("Enter URL pattern: ");
    scanf("%255s", url);

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO url_pattern (url_pattern) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, url, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("URL pattern added.\n");
        } else {
            printf("Failed to add URL pattern: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void update_url_pattern(sqlite3 *db) {
    int id;
    char new_url[256];
    printf("Enter ID to update: ");
    scanf("%d", &id);
    printf("Enter new URL pattern: ");
    scanf("%255s", new_url);

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE url_pattern SET url_pattern=? WHERE id=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, new_url, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("URL pattern updated.\n");
        } else {
            printf("Failed to update URL pattern: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void read_url_patterns(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, url_pattern FROM url_pattern;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        printf("ID\tURL Pattern\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%d\t%s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to fetch url patterns.\n");
    }
}

void delete_url_pattern(sqlite3 *db) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    char *err_msg = 0;
    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM url_pattern WHERE id=%d;", id);
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("URL pattern deleted.\n");
    }
}

void url_pattern_menu(sqlite3 *db) {
    int choice;
    do {
        printf("\n--- URL Pattern Menu ---\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_url_pattern(db); break;
            case 2: read_url_patterns(db); break;
            case 3: update_url_pattern(db); break;
            case 4: delete_url_pattern(db); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

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
    }

    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. URL Pattern CRUD\n");
        // Add entries for other tables here, e.g. 2. Label CRUD, 3. Url Label CRUD, etc.
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: url_pattern_menu(db); break;
            // case 2: label_menu(db); break; // Implement as above
            // etc.
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
