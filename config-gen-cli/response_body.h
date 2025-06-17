#ifndef RESPONSE_BODY_H
#define RESPONSE_BODY_H

#include "sqlite3.h"

void create_response_body(sqlite3 *db);
void read_response_body(sqlite3 *db);
void update_response_body(sqlite3 *db);
void delete_response_body(sqlite3 *db);

#endif
