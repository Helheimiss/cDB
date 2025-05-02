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
        return 1;
    }
    return 0;
}