#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../include/cDBR/cDBR.h"
#include "../../include/cDBR/cDBR_ERR.h"
#include "../../include/cDB_types/cDB_types.h"


int32_t file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file) 
    {
        fclose(file);
        return file_exists_ERR_FILE_IS_EXISTS;
    }
    return 0;
}


int32_t get_count_fields(const char *DB_name_cdb)
{
    if (DB_name_cdb == NULL) 
    {
        fprintf(stderr, "0x10000001: invalid parameters\n");
        return -2; // todo
    }


    FILE *DB_file = fopen(DB_name_cdb, "r+b");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x10000005: failed to open\n");
        return -3; // todo
    }


    fscanf(DB_file, "cdb metadata:\n");
    int count_fields_from_file = 0;
    int check_count_fields = fscanf(DB_file, "count_fields %d\n", &count_fields_from_file);
    
    
    if (check_count_fields != 1)
    {
        fprintf(stderr, "0x10000005: failed to read\n");        
        return -4; // todo
    }

    fclose(DB_file);
    return count_fields_from_file;
}