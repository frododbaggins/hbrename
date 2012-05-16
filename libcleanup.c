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

char *new_name(char *argv_ptr)
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

    strncpy(newname, argvptr, NAMELEN - 1);

    while (*argvptr && *argvptr != '-') {
        if (*argvptr == '_') {
            if(*(argvptr+1) == '-') {
                if (*(argvptr+2) == '_') {
                    argvptr += 2;
                    continue;
                }
            }
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
