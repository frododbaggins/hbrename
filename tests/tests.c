#include "../common/libtests.h"
extern char *newname;          /* From libcleanup.so */

int main(int argc, char **argv)
{
    int opt, verbose = 0, cmdcheck = 0,soft_hard = 0;
    int tool_test = 0;
    char *cmdarg;
#ifdef DEBUG
    EF_ALLOW_MALLOC_0 = 1;
    EF_DISABLE_BANNER = 1;
#endif
    while ((opt = getopt(argc, argv, "ts:hvc:")) != -1) {
        switch (opt) {
        case 'v':
            verbose = 1;
            break;
        case 'c':
            if(strcmp(optarg, "")) {
                // truncate to NAMELEN (255) chars when computing new name
                    cmdarg = malloc(NAMELEN);
                    strncpy(cmdarg, optarg, NAMELEN-1);
                    strcat(cmdarg,"\0");
                    cmdcheck = 1;
            } else {
                fprintf (stderr, "-c option requires an argument\n");
                return -1;
            }
            break;
        case '?':
            fprintf (stderr, "Unexpected option found - exiting\n");
            exit (-1);
        case 's':
            soft_hard = atoi(optarg);
            if ((soft_hard != 0) && (soft_hard != 1)) {
                d_printf ("Obtained value = %d for soft_hard, setting to default (0)\n", soft_hard);
                soft_hard = 0; /* SOFT_CHECK is the default type */
            }
            break;
        case 'h':
            fprintf (stderr, "%s [-s -h -v -c -t] \n", argv [0]);
            fprintf (stderr, "\t-s : Enables soft checking. This means that errors\
                                   \n\t     do not halt a test and thus testing can continue.\n");
            fprintf (stderr,
                     "\t-v : Verbose mode\n \t-c : Tests a name given on the command line and returns the new name.\n");
            fprintf (stderr, "\t-h : Prints this message.\n");
            fprintf (stderr, "\t-t : Tests the cleanup tool separately as an independent executable.\n");
            fprintf (stderr, "\t     Without this option, the libcleanup API is tested.\n");
            exit (0);
            break;
        case 't':
            tool_test = 1;
            break;
        default:
            verbose = 0;
        }
    }
    assert ((verbose == 0) || (verbose == 1));
    newname = malloc(NAMELEN * sizeof(char));
    if (cmdcheck) {
        printf("%s\n", new_name(cmdarg));
        free (cmdarg);
        free(newname);
        return 0;
    }
    set_check_type (soft_hard);
    int tests_status;
    if (tool_test) {
        tests_status = test_cleanup_tool (verbose);
    } else {
        tests_status = test_libcleanup (verbose);
    }
    free(newname);
    return tests_status;
}
