#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "response_body.h"

void create_response_body(sqlite3 *db) {
    char response_body[256];
    printf("Enter Response Body name (256 char): ");
    scanf("%255s", response_body);

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO response_body (name) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, response_body, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("response_body added.\n");
        } else {
            printf("Failed to add response_body: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void update_response_body(sqlite3 *db) {
    int id;
    char new_response_body[256];
    printf("Enter ID to update: ");
    scanf("%d", &id);
    printf("Enter new Response Body: ");
    scanf("%255s", new_response_body);

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE response_body SET name=? WHERE id=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, new_response_body, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("response_body updated.\n");
        } else {
            printf("Failed to update response_body: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

void read_response_body(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, name FROM response_body;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        printf("ID\tresponse_body\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%d\t%s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to fetch Response Bodys.\n");
    }
}

void delete_response_body(sqlite3 *db) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    char *err_msg = 0;
    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM response_body WHERE id=%d;", id);
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Response Body deleted.\n");
    }
}
