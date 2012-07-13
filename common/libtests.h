#ifndef __LIBTESTS_H__
#define __LIBTESTS_H__

#include "libcleanup.h"
extern char *newname;		/* From libcleanup.so */

#define SOFT_CHECK 0
#define HARD_CHECK 1
#define TEST_DATA_FILE "common/test-input-data"
#define FILE_NOT_FOUND_ERR 1

struct test_data_bufs
{
    char buf_old [NAMELEN],
         buf_exp [NAMELEN];
};
struct test_data_bufs bufs;

int test_cleanup_tool (int verbose);
int test_libcleanup (int verbose);
void set_check_type (int);
#endif
