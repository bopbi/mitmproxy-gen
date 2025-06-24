#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "active_mocked_url.h"

void create_active_mocked_url(sqlite3 *db) {
    int url_pattern_id;
    int response_body_template_id;

    printf("Enter Url Pattern ID (Number): ");
    scanf("%d", &url_pattern_id);
    printf("Enter Response Body Template ID (Number): ");
    scanf("%d", &response_body_template_id);

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO active_mocked_url (url_pattern_id, response_body_template_id) VALUES (?,?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, url_pattern_id);
        sqlite3_bind_int(stmt, 2, response_body_template_id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Active Mocked Url added.\n");
        } else {
            printf("Failed to add Active Mocked Url: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void update_active_mocked_url(sqlite3 *db) {
    int id;
    int new_url_pattern_id;
    int new_response_body_template_id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    printf("Enter Url Pattern ID (Number): ");
    scanf("%d", &new_url_pattern_id);
    printf("Enter Response Body Template ID (Number): ");
    scanf("%d", &new_response_body_template_id);

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE active_mocked_url SET url_pattern_id=?, response_body_template_id=? WHERE id=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, new_url_pattern_id);
        sqlite3_bind_int(stmt, 2, new_response_body_template_id);
        sqlite3_bind_int(stmt, 3, id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Active Mocked Url updated.\n");
        } else {
            printf("Failed to update Active Mocked Url: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void read_active_mocked_url(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, url_pattern_id, response_body_template_id FROM active_mocked_url;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        printf("ID\turl_pattern_id\tresponse_body_template_id\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%d\t%d\t%d\n", sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to fetch url labels.\n");
    }
}

void delete_active_mocked_url(sqlite3 *db) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    char *err_msg = 0;
    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM active_mocked_url WHERE id=%d;", id);
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Active Mocked Url deleted.\n");
    }
}
