#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../include/cDBW/cDBW.h"
#include "../../include/cDBW/cDBW_ERR.h"

#include "../../include/cDB_types/cDB_types.h"


/**
 * @brief create cDB
 * @param DB_name[MAX_DB_NAME_SIZE] db name "example"
 * @return results code
 * @retval 0 - succes
 * @retval 1 - invalid parameters
 * @retval 2 - the "DB_name" is too long or empty
 * @retval 3 - database name too long
 * @retval 4 - failed to create database file
 */
int32_t create_cDB(const char DB_name[MAX_DB_NAME_SIZE]) 
{
    if (DB_name == NULL) 
    {
        fprintf(stderr, "0x10000001: invalid parameters\n");
        return 1;
    }
    

    const size_t DB_name_len = strlen(DB_name);
    if (DB_name_len == 0 || DB_name_len >= MAX_DB_NAME_SIZE) 
    {
        fprintf(stderr, "0x10000002: the \"%s\" is too long or empty\n", DB_name);
        return 2;
    }

    
    char DB_name_cdb[MAX_DB_NAME_CDB_SIZE];
    if (snprintf(DB_name_cdb, sizeof(DB_name_cdb), "%s.cdb", DB_name) >= sizeof(DB_name_cdb)) 
    {
        fprintf(stderr, "0x10000004: database name too long\n");
        return 3;
    }

    // temp
    // if (file_exists(DB_name_cdb)) 
    // {
    //     fprintf(stderr, "0x10000003: %s DB already exists\n", DB_name_cdb);
    //     return create_cDB_ERR_DB_ALREADY_EXISTS;
    // }

    
    FILE *DB_file = fopen(DB_name_cdb, "wb");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x10000005: failed to create database file\n");
        return 4;
    }


    fprintf(DB_file, "cdb metadata:\n");
    fprintf(DB_file, "count_fields %d\n", NONE_FIELDS);
    fprintf(DB_file, "cdb fields:\n");

    // temp
    // for (size_t i = 0; i < count_fields; i++) 
    // {
    //     const size_t name_len = strlen(fields[i].d_name);
    //     fwrite(&fields[i].d_type, MAX_DATA_TYPE_SIZE, 1, DB_file);
    //     fwrite(fields[i].d_name, sizeof(char), name_len, DB_file);
    // }
    // fputc('\n', DB_file);
    
    fclose(DB_file);
    return 0x00000000;
}


/**
 * @brief write fields to cDB
 * @param DB_name_cdb[MAX_DB_NAME_CDB_SIZE] db name "example.cdb"
 * @return results code
 * @retval 0 - succes
 * @retval 1 - invalid parameters
 * @retval 2 - failed to open
 * @retval 3 - failed to read
 */
int32_t write_fields_to_cDB(const char DB_name_cdb[MAX_DB_NAME_CDB_SIZE], const DATA_STRUCT fields[], size_t count_fields)
{
    if (DB_name_cdb == NULL) 
    {
        fprintf(stderr, "0x20000001: invalid parameters\n");
        return 1; // todo
    }


    FILE *DB_file = fopen(DB_name_cdb, "r+b");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x20000002: failed to open\n");
        return 2; // todo
    }


    fscanf(DB_file, "cdb metadata:\n");
    int count_fields_from_file = 0;
    int check_count_fields = fscanf(DB_file, "count_fields %d\n", &count_fields_from_file);
    if (count_fields_from_file == NONE_FIELDS) count_fields_from_file = 0;
    
    
    if (check_count_fields != 1)
    {
        fprintf(stderr, "0x20000003: failed to read\n");        
        return 3; // todo
    }


    fseek(DB_file, 0, SEEK_SET);
    
    fprintf(DB_file, "cdb metadata:\n");
    fprintf(DB_file, "count_fields %d\n", (count_fields+count_fields_from_file));
    fprintf(DB_file, "cdb fields:\n");


    fseek(DB_file, -1, SEEK_END);

    for (size_t i = 0; i < count_fields; i++) 
    {
        const size_t name_len = strlen(fields[i].d_name);
        fwrite(&fields[i].d_type, MAX_DATA_TYPE_SIZE, 1, DB_file);
        fwrite(fields[i].d_name, sizeof(char), name_len, DB_file);
    }
    fputc('\n', DB_file);
    
    fclose(DB_file);
    return 0;
}


/**
 * @brief create field
 * @param DB_name_cdb[MAX_DB_NAME_CDB_SIZE] db name "example.cdb"
 * @return DATA_STRUCT
 * @retval DATA_STRUCT {0} - invalid parameters 
 * @retval DATA_STRUCT {n, n} - succes
 */
DATA_STRUCT create_field(DATA_TYPE d_type, char d_name[MAX_DATA_STRUCT_NAME]) 
{
    DATA_STRUCT temp = {};
    size_t d_name_len = strlen(d_name);

    
    if (d_name_len == 0 || d_name_len >= MAX_DATA_STRUCT_NAME) 
    {
        fprintf(stderr, "0x30000001: invalid parameters\n");
        return temp;
    }

    temp.d_type = d_type;
    
    
    memcpy(temp.d_name, d_name, d_name_len);
    temp.d_name[d_name_len] = '\0';

    return temp;
}