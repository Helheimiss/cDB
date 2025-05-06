#ifndef CDB_types_H
#define CDB_types_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../cDB_types/cDB_types.h"

#define MAX_DATA_TYPE_SIZE 2
#define MAX_DATA_STRUCT_NAME 20

#define MAX_DB_NAME_SIZE 20
#define MAX_DB_NAME_CDB_SIZE (MAX_DB_NAME_SIZE+5)


#define NONE_FIELDS -1


typedef enum
{
    INT,
    SHORT,
    FLOAT
} DATA_TYPE;


typedef struct
{
    DATA_TYPE d_type;
    char d_name[MAX_DATA_STRUCT_NAME];
} DATA_STRUCT;


typedef struct
{
    char d_name[MAX_DATA_STRUCT_NAME];
    void *value;
} DATA_VALUE;



#endif