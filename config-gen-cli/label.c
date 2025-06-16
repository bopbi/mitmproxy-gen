#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "label.h"

void create_label(sqlite3 *db) {
    char label[256];
    printf("Enter Label name (256 char): ");
    scanf("%255s", label);

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO label (name) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, label, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Label added.\n");
        } else {
            printf("Failed to add Label: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void update_label(sqlite3 *db) {
    int id;
    char new_label[256];
    printf("Enter ID to update: ");
    scanf("%d", &id);
    printf("Enter new Label: ");
    scanf("%255s", new_label);

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE label SET name=? WHERE id=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, new_label, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Label updated.\n");
        } else {
            printf("Failed to update Label: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void read_label(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, name FROM label;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        printf("ID\tLabel\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%d\t%s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to fetch labels.\n");
    }
}

void delete_label(sqlite3 *db) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    char *err_msg = 0;
    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM label WHERE id=%d;", id);
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Label deleted.\n");
    }
}
