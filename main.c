#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int32_t file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file) 
    {
        fclose(file);
        return 1;
    }
    return 0;
}

#define MAX_DATA_TYPE_SIZE 2
typedef enum
{
    INT,
    SHORT,
    FLOAT
} DATA_TYPE;

#define MAX_DATA_STRUCT_NAME 20
typedef struct
{
    DATA_TYPE d_type;
    char d_name[MAX_DATA_STRUCT_NAME];
} DATA_STRUCT;



#define MAX_DB_NAME_SIZE 20
#define MAX_DB_NAME_CDB_SIZE (MAX_DB_NAME_SIZE+5)


int32_t create_cDB(const char DB_name[MAX_DB_NAME_SIZE], const DATA_STRUCT fields[], size_t count_fields) 
{
    if (DB_name == NULL || fields == NULL || count_fields == 0) 
    {
        fprintf(stderr, "0x10000001: invalid parameters\n");
        return 0x10000001;
    }
    

    const size_t DB_name_len = strlen(DB_name);
    if (DB_name_len == 0 || DB_name_len >= MAX_DB_NAME_SIZE) 
    {
        fprintf(stderr, "0x10000002: the \"%s\" is too long or empty\n", DB_name);
        return 0x10000002;
    }

    
    char DB_name_cdb[MAX_DB_NAME_CDB_SIZE];
    if (snprintf(DB_name_cdb, sizeof(DB_name_cdb), "%s.cdb", DB_name) >= sizeof(DB_name_cdb)) 
    {
        fprintf(stderr, "0x10000004: database name too long\n");
        return 0x10000004;
    }

    
    if (file_exists(DB_name_cdb)) 
    {
        fprintf(stderr, "0x10000003: %s already exists\n", DB_name_cdb);
        return 0x10000003;
    }

    
    FILE *DB_file = fopen(DB_name_cdb, "wb");
    if (DB_file == NULL) 
    {
        fprintf(stderr, "0x10000005: failed to create database file\n");
        return 0x10000005;
    }


    fprintf(DB_file, "cdb metadata:\n");
    fprintf(DB_file, "count_fields %zu\n", count_fields);
    fprintf(DB_file, "cdb fields:\n");

    
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


#define __GETF_SIZE_OF__(a) (sizeof(a) / sizeof(a[0]))
int32_t main()
{
    DATA_STRUCT test1[3];
    test1[0] = create_field(INT, "age");
    test1[1] = create_field(SHORT, "test_short");
    test1[2] = create_field(FLOAT, "test_float");

    int32_t a = create_cDB("test", test1, __GETF_SIZE_OF__(test1));
    printf("\nres: %d\n", a);

    return 0;
}