#include "libcleanup.h"
extern char *newname;		/* From libcleanup.so */

void run_tests(int verbose)
{
    assert(0 == strcmp(new_name("a-b.c"), "a.c"));
    assert(0 == strcmp(new_name("a__b-c.c"), "a__b.c"));
    assert(0 == strcmp(new_name("aaa-bbb.ext"), "aaa.ext"));
    assert(0 == strcmp(new_name("a_b_c_d-e.mp4"), "a_b_c_d.mp4"));
    assert(0 == strcmp(new_name("filename_-rem.mp4"), "filename.mp4"));
    assert(0 == strcmp(new_name("a-b-c.mp4"), "a.mp4"));
    assert(0 == strcmp(new_name("-name.mp4"), "name.mp4"));
    assert(0 == strcmp(new_name("__.mp4"), "__.mp4"));
    assert(0 == strcmp(new_name("____.mp4"), "____.mp4"));
    assert(0 == strcmp(new_name("--.mp4"), "--.mp4"));
    assert(0 == strcmp(new_name("a_-_b.mp4"), "a_b.mp4"));

    if (verbose) {
        printf ("10/10 tests passed\n");
    }
}

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
