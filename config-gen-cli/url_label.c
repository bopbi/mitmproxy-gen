#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "url_label.h"

void create_url_label(sqlite3 *db) {
    int url_pattern_id;
    int label_id;

    printf("Enter Url Pattern ID (Number): ");
    scanf("%d", &url_pattern_id);
    printf("Enter Label ID (Number): ");
    scanf("%d", &label_id);

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO url_label (url_pattern_id, label_id) VALUES (?,?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, url_pattern_id);
        sqlite3_bind_int(stmt, 2, label_id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Url Label added.\n");
        } else {
            printf("Failed to add Url Label: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void update_url_label(sqlite3 *db) {
    int id;
    int new_url_pattern_id;
    int new_label_id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    printf("Enter Url Pattern ID (Number): ");
    scanf("%d", &new_url_pattern_id);
    printf("Enter Label ID (Number): ");
    scanf("%d", &new_label_id);

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE url_label SET url_pattern_id=?, label_id=? WHERE id=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, new_url_pattern_id);
        sqlite3_bind_int(stmt, 2, new_label_id);
        sqlite3_bind_int(stmt, 3, id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Url Label updated.\n");
        } else {
            printf("Failed to update Url Label: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void read_url_label(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, url_pattern_id, label_id FROM url_label;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        printf("ID\turl_pattern_id\tlabel_id\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%d\t%d\t%d\n", sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to fetch url labels.\n");
    }
}

void delete_url_label(sqlite3 *db) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    char *err_msg = 0;
    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM url_label WHERE id=%d;", id);
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Url Label deleted.\n");
    }
}
