/**
 * This file is created for testing functions
 *    ████████╗███████╗███████╗████████╗██╗███╗   ██╗ ██████╗     ██╗     ██╗██████╗ 
 *    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██║████╗  ██║██╔════╝     ██║     ██║██╔══██╗
 *       ██║   █████╗  ███████╗   ██║   ██║██╔██╗ ██║██║  ███╗    ██║     ██║██████╔╝
 *       ██║   ██╔══╝  ╚════██║   ██║   ██║██║╚██╗██║██║   ██║    ██║     ██║██╔══██╗
 *       ██║   ███████╗███████║   ██║   ██║██║ ╚████║╚██████╔╝    ███████╗██║██████╔╝
 *       ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚══════╝╚═╝╚═════╝ 
 *       
*/


#include <stdio.h>
#include <stdint.h>


#include "../include/cDB_types/cDB_types.h"

#include "../include/cDBR/cDBR_ERR.h"
#include "../include/cDBR/cDBR.h"

#include "../include/cDBW/cDBW_ERR.h"
#include "../include/cDBW/cDBW.h"



#define __GETF_SIZE_OF__(a) (sizeof(a) / sizeof(a[0]))
int32_t main()
{
    DATA_STRUCT test1[3];
    test1[0] = create_field(INT, "age");
    test1[1] = create_field(SHORT, "test_short");
    test1[2] = create_field(FLOAT, "test_float");

    // int32_t a = create_cDB("test");
    int32_t b = write_fields_to_cDB("test.cdb", test1, __GETF_SIZE_OF__(test1));
    // printf("\nres1: %d\n", a);
    printf("\nres2: %d\n", b);

    return 0;
}