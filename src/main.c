#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#include "../include/cDB_types/cDB_types.h"
#include "../include/cDBR/cDBR.h"
#include"../include/cDBW/cDBW.h"



#define __GETF_SIZE_OF__(a) (sizeof(a) / sizeof(a[0]))
int32_t main()
{
    DATA_STRUCT test1[3];
    test1[0] = create_field(INT, "age");
    test1[1] = create_field(SHORT, "test_short");
    test1[2] = create_field(FLOAT, "test_float");

    // int32_t a = create_cDB("test", test1, __GETF_SIZE_OF__(test1));
    int32_t a = create_cDB("test", NULL, 0);
    printf("\nres: %d\n", a);

    return 0;
}