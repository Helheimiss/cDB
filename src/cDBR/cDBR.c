#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../include/cDBR/cDBR.h"
#include "../../include/cDBR/cDBR_ERR.h"
#include "../../include/cDB_types/cDB_types.h"

/**
 * @brief file exists?
 * @return results code
 * @retval 1 - file exists
 * @retval 1 - file does not exist
 */
int32_t file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file) 
    {
        fclose(file);
        return 1;
    }
    return 0x00000000;
}


/**
 * @brief get count fields
 * @return results code
 * @retval -2 - invalid parameters
 * @retval -3 - failed to open
 * @retval -4 - failed to read
 * @retval n count fields
 */
int32_t get_count_fields(const char *DB_name_cdb)
{
    if (DB_name_cdb == NULL) 
    {
        fprintf(stderr, "0x20000001: invalid parameters\n");
        return -2; // todo
    }


    FILE *DB_file = fopen(DB_name_cdb, "r+b");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x20000002: failed to open\n");
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

/**
 * @brief this is cdb?
 * @param DB_name_cdb "name.cdb"
 * @return results code
 * @retval 0 - this is cdb
 * @retval 1 - the DB_name_cdb does not end in .cdb
 * @retval 2 - the DB_name_cdb does not end in .cdb
 * @retval 3 - invalid parameters
 * @retval 4 - failed to open
 * @retval 5 - this is not cdb
 */
int32_t this_is_cDB(const char *DB_name_cdb)
{
    char *temp = strstr(DB_name_cdb, ".cdb");
    if (temp == NULL)
    {
        fprintf(stderr, "1: the DB_name_cdb does not end in .cdb\n");
        return 1; // todo
    }


    if (strcmp(temp, ".cdb") != 0)
    {
        fprintf(stderr, "2: the DB_name_cdb does not end in .cdb\n");
        return 2;
    }
    


    if (DB_name_cdb == NULL) 
    {
        fprintf(stderr, "0x20000001: invalid parameters\n");
        return 3; // todo
    }


    FILE *DB_file = fopen(DB_name_cdb, "r+b");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x20000002: failed to open\n");
        return 4; // todo
    }


    fscanf(DB_file, "cdb metadata:\n");
    int count_fields_from_file = 0;
    int check_count_fields = fscanf(DB_file, "count_fields %d\n", &count_fields_from_file);
    
    
    if (check_count_fields != 1)
    {
        // fprintf(stderr, "0x10000005: failed to read\n");        
        return 5; // todo
    }

    fclose(DB_file);
    return 0;
}