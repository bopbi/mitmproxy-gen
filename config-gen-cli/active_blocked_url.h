#ifndef ACTIVE_BLOCKED_URL_H
#define ACTIVE_BLOCKED_URL_H

#include "sqlite3.h"

void create_active_blocked_url(sqlite3 *db);
void read_active_blocked_url(sqlite3 *db);
void update_active_blocked_url(sqlite3 *db);
void delete_active_blocked_url(sqlite3 *db);

#endif
