#ifndef RESPONSE_BODY_TEMPLATE_H
#define RESPONSE_BODY_TEMPLATE_H

#include "sqlite3.h"

void create_response_body_template(sqlite3 *db);
void read_response_body_template(sqlite3 *db);
void update_response_body_template(sqlite3 *db);
void delete_response_body_template(sqlite3 *db);

#endif
