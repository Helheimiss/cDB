#ifndef CDBR_H
#define CDBR_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../cDB_types/cDB_types.h"

int32_t file_exists(const char *filename);
int32_t get_count_fields(const char *DB_name_cdb);

#endif