#include "../common/libtests.h"
extern char *newname;          /* From libcleanup.so */

int main(int argc, char **argv)
{
    int opt, verbose = 0, cmdcheck = 0,soft_hard = 0;
    char *cmdarg;
    while ((opt = getopt(argc, argv, "shvc:")) != -1) {
        switch (opt) {
        case 'v':
            verbose = 1;
            break;
        case 'c':
            if(strcmp(optarg, "")) {
                // truncate to NAMELEN (80) chars when computing new name
                    cmdarg = malloc(NAMELEN);
                    strncpy(cmdarg, optarg, NAMELEN-1);
                    strcat(cmdarg,"\0");
                    cmdcheck = 1;
            } else {
                printf ("-c option requires an argument\n");
                return -1;
            }
            break;
        case 's':
            soft_hard = 0;
            break;
        case 'h':
            soft_hard = 1;
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
    int tests_status = run_tests(verbose);
    free(newname);
    return tests_status;
}
