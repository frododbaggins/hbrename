#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
        char newname[80]="", * argvptr=argv[1], * newnameptr = newname;
	strncpy(newname, argv[1], 79);
	//	printf("name = %s\n", newname);
	while(*argvptr && *argvptr != '-')
	{
		*newnameptr++ = *argvptr++;
	}
	while(*argvptr && *argvptr != '.')
            argvptr++;
	while(*argvptr)
	{
		*newnameptr++ = *argvptr++;
	}
	*newnameptr = 0;
	printf("%s", newname);
	return 0;
}
