#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 80
int main(int argc, char ** argv)
{
        char newname[NAMELEN]="", * argvptr=argv[1], * newnameptr = newname;

	strncpy(newname, argv[1], NAMELEN - 1);
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
	printf("%s", newname);
	return 0;
}
