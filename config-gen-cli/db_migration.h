#ifndef DB_MIGRATION_H
#define DB_MIGRATION_H

#include "sqlite3.h"

int run_migration(sqlite3 *db, const char *filename);

#endif
