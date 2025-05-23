#ifndef CDBW_H
#define CDBW_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../cDB_types/cDB_types.h"

int32_t create_cDB(const char DB_name[MAX_DB_NAME_SIZE]); // 0x10000000
int32_t write_fields_to_cDB(const char DB_name_cdb[MAX_DB_NAME_CDB_SIZE], const DATA_STRUCT fields[], size_t count_fields); // 0x20000000
DATA_STRUCT create_field(DATA_TYPE d_type, char d_name[MAX_DATA_STRUCT_NAME]); // 0x30000000

#endif