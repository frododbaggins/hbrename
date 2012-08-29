#ifndef __LIBTESTS_H__
#define __LIBTESTS_H__

#include "libcleanup.h"
#include <regex.h>
extern char *newname;		/* From libcleanup.so */

#define SOFT_CHECK 0
#define HARD_CHECK 1
#define TEST_DATA_FILE "common/test-input-data"
#define FILE_NOT_FOUND_ERR 1

#define TRUE 1
#define FALSE 0
#define IGNORE 2
typedef int bool;

#ifdef DEBUG
extern int EF_ALLOW_MALLOC_0;
#endif

struct test_data_bufs
{
    char buf_old [NAMELEN],
         buf_exp [NAMELEN];
};
struct test_data_bufs bufs;

int test_cleanup_tool (int verbose);
int test_libcleanup (int verbose);
void set_check_type (int);
bool is_well_formatted (char * line);
#endif
