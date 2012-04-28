#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NAMELEN 80
#ifdef DEBUG
#define d_printf printf
#else
void d_printf(const char* fmt, ...)
{
}
#endif

void run_tests (void);
char * new_name (char *argv_ptr);
char *newname = NULL;
int main(int argc, char ** argv)
{
        newname = malloc (NAMELEN * sizeof (char));
        run_tests();
        free (newname);
        exit(0);
        DIR* dir = opendir ( "." );
        if (NULL == dir){
            perror (strerror(errno));
            exit (-1);
        }
        d_printf("opened . \n");
        struct dirent * dirent = NULL;
        newname = malloc (NAMELEN * sizeof (char));
        if (NULL == newname){
                fprintf (stderr, "Error allocating memory\n");
                closedir(dir);
                exit(-1);
        }

        while (NULL != (dirent = readdir (dir)))
        {
//                printf ("%s\n", dirent->d_name);
#ifdef _DIRENT_HAVE_D_TYPE
                if (dirent->d_type == DT_REG){
                        newname = new_name(dirent->d_name);
                        if (strcmp (newname, dirent->d_name)){
                                int ret = rename (dirent->d_name, newname);
                                if (ret){
                                        perror (strerror(errno));
                                        closedir(dir);
                                        free (newname);
                                        exit (-2);
                                }
                        }
                }
#else
                /* Do nothing
                   FIXME: Better solution available? */
#endif
        }
        closedir(dir);
        return 0;
}

char * new_name (char *argv_ptr)
{
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

void run_tests(void)
{
#if 0
        char * input_names [9] = { "a_b_c_d-e.mp4",  "a________-rem.mp4", "filename_-rem.mp4",
                                  "a-b-c.mp4", "--.mp4", "____.mp4", "__.mp4", "-name.mp4", "aaa-bbb.ext"};
        char * exp_names [9] = { "a_b_c_d.mp4", "a________.mp4", "filename.mp4", "a.mp4",
                                "--.mp4", "____.mp4", "__.mp4", "-name.mp4", "aaa.ext" };
        int i;
        for (i = 0 ; i < 9; i++)
        {
                int diff = strcmp(new_name(input_names[i]), exp_names[i]);
                if (diff)
                {
                        printf ("old name : %s \t new name: %s\n", new_name(input_names[i]), exp_names[i]);
                }
        }
#endif
        assert ( 0 == strcmp (new_name ("a-b.c"), "a.c"));
        assert ( 0 == strcmp (new_name ("a_b_c_d-e.mp4"), "a_b_c_d.mp4"));
        assert ( 0 == strcmp (new_name ("a________-rem.mp4"), "a________.mp4"));

}
