#ifndef CDB_ERRORS_H
#define CDB_ERRORS_H


typedef enum
{
    create_cDB_ERR_INVALID_PARAMETERS              = 0x10000001,
    create_cDB_ERR_IS_TOO_LONG_OR_EMPTY            = 0x10000002,
    create_cDB_ERR_DB_ALREADY_EXISTS               = 0x10000003,
    create_cDB_ERR_DATABASE_NAME_TOO_LONG          = 0x10000004,
    create_cDB_ERR_FAILED_TO_CREATE_DATABASE_FILE  = 0x10000005
} __create_cDB_err__;


typedef enum
{
    create_field_ERR_INVALID_PARAMETERS  = 0x20000001,
} __create_field_err__;


#endif