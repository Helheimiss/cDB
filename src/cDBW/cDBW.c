#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../include/cDBW/cDBW.h"
#include "../../include/cDBW/cDBW_ERR.h"

#include "../../include/cDB_types/cDB_types.h"


// int32_t create_cDB(const char DB_name[MAX_DB_NAME_SIZE], const DATA_STRUCT fields[], size_t count_fields) 
int32_t create_cDB(const char DB_name[MAX_DB_NAME_SIZE]) 
{
    if (DB_name == NULL) 
    {
        fprintf(stderr, "0x10000001: invalid parameters\n");
        return create_cDB_ERR_INVALID_PARAMETERS;
    }
    

    const size_t DB_name_len = strlen(DB_name);
    if (DB_name_len == 0 || DB_name_len >= MAX_DB_NAME_SIZE) 
    {
        fprintf(stderr, "0x10000002: the \"%s\" is too long or empty\n", DB_name);
        return create_cDB_ERR_IS_TOO_LONG_OR_EMPTY;
    }

    
    char DB_name_cdb[MAX_DB_NAME_CDB_SIZE];
    if (snprintf(DB_name_cdb, sizeof(DB_name_cdb), "%s.cdb", DB_name) >= sizeof(DB_name_cdb)) 
    {
        fprintf(stderr, "0x10000004: database name too long\n");
        return create_cDB_ERR_DATABASE_NAME_TOO_LONG;
    }

    
    // if (file_exists(DB_name_cdb)) 
    // {
    //     fprintf(stderr, "0x10000003: %s DB already exists\n", DB_name_cdb);
    //     return create_cDB_ERR_DB_ALREADY_EXISTS;
    // }

    
    FILE *DB_file = fopen(DB_name_cdb, "wb");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x10000005: failed to create database file\n");
        return create_cDB_ERR_FAILED_TO_CREATE_DATABASE_FILE;
    }


    fprintf(DB_file, "cdb metadata:\n");
    fprintf(DB_file, "count_fields %d\n", 0);
    fprintf(DB_file, "cdb fields:\n");

    
    // for (size_t i = 0; i < count_fields; i++) 
    // {
    //     const size_t name_len = strlen(fields[i].d_name);
    //     fwrite(&fields[i].d_type, MAX_DATA_TYPE_SIZE, 1, DB_file);
    //     fwrite(fields[i].d_name, sizeof(char), name_len, DB_file);
    // }
    // fputc('\n', DB_file);
    
    fclose(DB_file);
    return 0;
}


int32_t write_fields_to_cDB(const char DB_name_cdb[MAX_DB_NAME_CDB_SIZE], const DATA_STRUCT fields[], size_t count_fields)
{
    if (DB_name_cdb == NULL) 
    {
        fprintf(stderr, "0x10000001: invalid parameters\n");
        return 1; // todo
    }


    FILE *DB_file = fopen(DB_name_cdb, "wb");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x10000005: failed to create database file\n");
        return 2; // todo
    }

    // todo

    for (size_t i = 0; i < count_fields; i++) 
    {
        const size_t name_len = strlen(fields[i].d_name);
        fwrite(&fields[i].d_type, MAX_DATA_TYPE_SIZE, 1, DB_file);
        fwrite(fields[i].d_name, sizeof(char), name_len, DB_file);
    }
    fputc('\n', DB_file);
    
    fclose(DB_file);
}


DATA_STRUCT create_field(DATA_TYPE d_type, char d_name[MAX_DATA_STRUCT_NAME]) 
{
    DATA_STRUCT temp = {};
    size_t d_name_len = strlen(d_name);

    
    if (d_name_len == 0 || d_name_len >= MAX_DATA_STRUCT_NAME) 
    {
        fprintf(stderr, "0x20000001: invalid parameters\n");
        return temp;
    }

    temp.d_type = d_type;
    
    
    memcpy(temp.d_name, d_name, d_name_len);
    temp.d_name[d_name_len] = '\0';

    return temp;
}