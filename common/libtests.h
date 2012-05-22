#ifndef __LIBTESTS_H__
#define __LIBTESTS_H__

#include "libcleanup.h"
extern char *newname;		/* From libcleanup.so */

#define SOFT_CHECK 0
#define HARD_CHECK 1
#define TEST_COUNT 12
int run_tests(int verbose);

#endif
