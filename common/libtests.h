#ifndef __LIBTESTS_H__
#define __LIBTESTS_H__

#include "libcleanup.h"
extern char *newname;		/* From libcleanup.so */

#define SOFT_CHECK 0
#define HARD_CHECK 1
#define TEST_DATA_FILE "common/test-input-data"
int run_tests(int verbose);
void set_check_type (int);
#endif
