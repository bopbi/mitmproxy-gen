#ifndef URL_LABEL_H
#define URL_LABEL_H

#include "sqlite3.h"

void create_url_label(sqlite3 *db);
void read_url_label(sqlite3 *db);
void update_url_label(sqlite3 *db);
void delete_url_label(sqlite3 *db);

#endif
