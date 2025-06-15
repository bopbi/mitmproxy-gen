#ifndef LABEL_H
#define LABEL_H

#include "sqlite3.h"

void create_label(sqlite3 *db);
void read_label(sqlite3 *db);
void update_label(sqlite3 *db);
void delete_label(sqlite3 *db);

#endif
