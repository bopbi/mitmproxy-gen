#ifndef URL_PATTERN_H
#define URL_PATTERN_H

#include "sqlite3.h"

void create_url_pattern(sqlite3 *db);
void read_url_patterns(sqlite3 *db);
void update_url_pattern(sqlite3 *db);
void delete_url_pattern(sqlite3 *db);

#endif
