#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "db_migration.h"
#include "url_pattern.h"
#include "label.h"
#include "url_label.h"

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

void label_menu(sqlite3 *db) {
    int choice;
    do {
        printf("\n--- Label Menu ---\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_label(db); break;
            case 2: read_label(db); break;
            case 3: update_label(db); break;
            case 4: delete_label(db); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

void url_label_menu(sqlite3 *db) {
    int choice;
    do {
        printf("\n--- Url Label Menu ---\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_url_label(db); break;
            case 2: read_url_label(db); break;
            case 3: update_url_label(db); break;
            case 4: delete_url_label(db); break;
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

    if (!run_migration(db, "migration.sql")) {
        sqlite3_close(db);
        return 1;
    }

    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. URL Pattern CRUD\n");
        printf("2. Label CRUD\n");
        printf("3. URL Label CRUD\n");
        // Add entries for other tables here, e.g. 2. Label CRUD, 3. Url Label CRUD, etc.
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: url_pattern_menu(db); break;
            case 2: label_menu(db); break;
            case 3: url_label_menu(db); break;
            // etc.
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
