#include "libtests.h"

int tests_run = 0, failcount = 0, check_type = 0;
int check (char * old_name, char * expected_new_name)
{
    char * actual_result = new_name (old_name);
    tests_run++;
    if (0 == strcmp (actual_result, expected_new_name)) {
        return 0;
    } else {
        failcount++;
        if (check_type == SOFT_CHECK) {
            printf ("Expected new name: %s, Actual : %s\n",
                    expected_new_name, actual_result);
            return -1;
        } else {
            fprintf (stderr, "Expected new name: %s, Actual : %s\n",
                    expected_new_name, actual_result);
            fprintf (stderr, "%d/%d tests passed\n", (tests_run - failcount), tests_run);
            exit (-failcount);
        }
    }
}

int run_tests(int verbose)
{
    check("a-b.c", "a.c");
    check("a__b-c.c", "a__b.c");
    check("aaa-bbb.ext", "aaa.ext");
    check("a_b_c_d-e.mp4", "a_b_c_d.mp4");
    check("filename_-rem.mp4", "filename.mp4");
    check("a-b-c.mp4", "a.mp4");
    check("-name.mp4", "name.mp4");
    check("__.mp4", "__.mp4");
    check("____.mp4", "____.mp4");
    check("--.mp4", "--.mp4");
    check("a_-_b.mp4", "a_b.mp4");

    if (verbose) {
        printf ("%d/%d tests passed\n", (tests_run - failcount), tests_run);
    }
    return -failcount;
}
