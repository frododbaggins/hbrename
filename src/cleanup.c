#include "../common/libcleanup.h"

extern char *newname;		/* From libcleanup.so */
int main(int argc, char **argv)
{
    int opt, quiet = 0;
    while ((opt = getopt(argc, argv, "q")) != -1) {
        switch (opt) {
        case 'q':
            quiet = 1;
            break;
        case '?':
            fprintf (stderr, "Unexpected option - exiting\n");
            exit(0);
        default:
            quiet = 0;
        }
    }
    assert ((quiet == 0) || (quiet == 1));
    const char *execname = "cleanup";
    DIR *dir = opendir(".");
    if (NULL == dir) {
	perror("Could not open \".\"");
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
    /* Preserve newname pointer for free()ing later */
    char * newnamebuf = newname;

    while (NULL != (dirent = readdir(dir))) {
        if(!strcmp (dirent->d_name, execname)){
            continue;
        }
	d_printf("file name %s\n", dirent->d_name);
#ifdef _DIRENT_HAVE_D_TYPE
	if (dirent->d_type == DT_REG) {
	    newnamebuf = new_name(dirent->d_name);
	    if (strcmp(newnamebuf, dirent->d_name)) {
		int ret = -1;
		struct stat statbuf;
		/* check if file with proposed new name already exists */
		ret = stat(newnamebuf, &statbuf);
		if (-1 == ret) {
		    ret = rename(dirent->d_name, newnamebuf);
		    if (ret) {
			fprintf (stderr, "Error renaming file %s ", dirent->d_name);
                        perror (NULL);
			closedir(dir);
			free(newname);
			exit(-2);
		    } else {
                        if (!quiet) {
                            printf ("%s -> %s\n", dirent->d_name, newnamebuf);
                        }
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
