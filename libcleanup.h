#ifndef __LIBCLEANUP_H__
#define __LIBCLEANUP_H__
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#define NAMELEN 80
char * new_name (char *argv_ptr);
int d_printf (const char * fmt,...);
#endif
