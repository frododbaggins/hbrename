#include "../common/libcleanup.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

extern char *newname;		/* From libcleanup.so */
int main(int argc, char **argv)
{
    int opt, quiet;
    while ((opt = getopt(argc, argv, "q")) != -1) {
        switch (opt) {
        case 'q':
            quiet = 1;
            break;
        default:
            quiet = 0;
        }
    }
    assert ((quiet == 0) || (quiet == 1));
    const char *execname = "cleanup";
    DIR *dir = opendir(".");
    if (NULL == dir) {
	perror(strerror(errno));
	exit(-1);
    }
    d_printf("opened . \n");
    struct dirent *dirent = NULL;
    newname = malloc(NAMELEN * sizeof(char));
    if (NULL == newname) {
	fprintf(stderr, "Error allocating memory\n");
	closedir(dir);
	exit(-1);
    }

    while (NULL != (dirent = readdir(dir))) {
        if(!strcmp (dirent->d_name, execname)){
            continue;
        }
	d_printf("file name %s\n", dirent->d_name);
#ifdef _DIRENT_HAVE_D_TYPE
	if (dirent->d_type == DT_REG) {
	    newname = new_name(dirent->d_name);
	    if (strcmp(newname, dirent->d_name)) {
		int ret = -1;
		struct stat statbuf;
		/* check if file with proposed new name already exists */
		ret = stat(newname, &statbuf);
		if (-1 == ret) {
		    ret = rename(dirent->d_name, newname);
                    if (!quiet) {
                        printf ("%s -> %s\n", dirent->d_name, newname);
                    }
		    if (ret) {
			perror(strerror(errno));
			closedir(dir);
			free(newname);
			exit(-2);
		    }
		} else {
		    /* File with proposed new name exists.
		       Do nothing. */
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
