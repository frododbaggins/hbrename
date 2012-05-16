#include "libtests.h"
extern char *newname;          /* From libcleanup.so */

int main(int argc, char **argv)
{
    int opt, verbose;
    while ((opt = getopt(argc, argv, "v")) != -1) {
        switch (opt) {
        case 'v':
            verbose = 1;
            break;
        default:
            verbose = 0;
        }
    }
    assert ((verbose == 0) || (verbose == 1));
    newname = malloc(NAMELEN * sizeof(char));
    run_tests(verbose);
    free(newname);
    return 0;
}
