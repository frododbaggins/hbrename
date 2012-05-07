#include "libcleanup.h"

char *newname = NULL;

char * new_name (char *argv_ptr)
{
        assert (argv_ptr);
        assert (newname);
        char *newnameptr = newname;
        char *argvptr = argv_ptr;
	/* Skip leading hyphens */
        while ( *argvptr && *argvptr == '-')
	{
		argvptr ++;
	}
	/* At this point, if argvptr points to '.', we have only hyphens in the filename,
	 * followed by the extension. We do not want to modify such a name. Let us return it as it is
	 */
	if (*argvptr == '.')
	{
		return argvptr;
	}

	strncpy(newname, argvptr, NAMELEN - 1);

	while(*argvptr && *argvptr != '-')
	{
		*newnameptr++ = *argvptr++;
	}
	while(*argvptr && *argvptr != '.')
		argvptr++;

	/*
	 * Remove trailing '_' from resulting names
	 */
	if (*(newnameptr - 1) == '_')
	{
		newnameptr--;
		while (*newnameptr == '_' && newnameptr != newname)
			newnameptr --;
		newnameptr ++;
	}

	while(*argvptr)
	{
		*newnameptr++ = *argvptr++;
	}
	*newnameptr = 0;
        return newname;
}
