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
