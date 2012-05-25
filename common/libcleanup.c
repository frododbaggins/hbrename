#include "libcleanup.h"

int d_printf(const char *fmt, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
#endif
    return 0;
}

char *newname = NULL;

/* new_name is the core routine that determines the new name
 * after removing unwanted characters from the given name.
 * The input string is assumed to be writable.
 * Thus, passing literal strings may cause runtime errors.
 */
char *new_name (char *argv_ptr)
{
    assert(argv_ptr);
    assert(newname);
    char *newnameptr = newname;
    char *argvptr = argv_ptr;
    /* Skip leading hyphens */
    while (*argvptr && *argvptr == '-') {
	argvptr++;
    }
    /* At this point, if argvptr points to '.', we have only hyphens in the filename,
     * followed by the extension. We do not want to modify such a name. Let us return it as it is
     */
    if (*argvptr == '.') {
        return argv_ptr;
    }

    /* Do one pass replacing all spaces with underscores */
    char *saved_argv_ptr = argvptr;
    while (*argvptr) {
        if(*argvptr == ' ') {
            *argvptr = '_';
        }
        argvptr++;
    }

    /* The section below is intended to remove _only_ the last hyphen and the part
     * after it, till the period. Any leading hyphens have been removed at this point.
     * Any remaining hyphens are replaced by underscores
     */
    argvptr = saved_argv_ptr;
    argvptr += strlen (argvptr);
    char * dotpos = NULL;
    char * last_hyphen_pos = NULL;
    while ((argvptr != saved_argv_ptr) && *argvptr != '.') {
        argvptr --;
    }
    if (argvptr == saved_argv_ptr) { /* No period in the input name, return as is */
        return argv_ptr;
    }
    dotpos = argvptr; /* Now look for last hyphen */
    while ((argvptr != saved_argv_ptr) && *argvptr != '-') {
        argvptr --;
    }
    if (argvptr == saved_argv_ptr) {
        /* There are no more hyphens in the name.
         * Thus, we return the original input or our transformed
         * string (in case leading hyphens were removed)
         */
        if (argvptr == argv_ptr) {
            return argv_ptr;
        } else {
            return argvptr;
        }
    }
    last_hyphen_pos = argvptr;
    for (char * ptr = saved_argv_ptr; ptr < last_hyphen_pos; ptr++) {
        if (*ptr == '-') {
            *ptr = '_';
        }
    }
    argvptr = saved_argv_ptr;
    strncpy(newname, argvptr, NAMELEN - 1);

    while (*argvptr && *argvptr != '-') {
        /* This set of conditions is to pass the test of
         * a_-_b.c. This example is seen often.
         */
        if ((*argvptr == '_')
            && (*(argvptr+1) == '-')
            && (*(argvptr+2) == '_')) {
            argvptr += 2;
            continue;
        }
        *newnameptr++ = *argvptr++;
    }
    while (*argvptr && *argvptr != '.')
	argvptr++;

    /*
     * Remove trailing '_' from resulting names
     */
    if (*(newnameptr - 1) == '_') {
	newnameptr--;
	while (*newnameptr == '_' && newnameptr != newname)
	    newnameptr--;
	newnameptr++;
    }

    while (*argvptr) {
	*newnameptr++ = *argvptr++;
    }
    *newnameptr = 0;
    return newname;
}
