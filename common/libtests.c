#include "libtests.h"

int tests_run = 0, failcount = 0, check_type = 0;

void set_check_type (int type)
{
    assert ((type == SOFT_CHECK) || (type == HARD_CHECK));
    check_type = type;
}
int check (char * old_name, char * expected_new_name)
{
    char * actual_result = new_name (old_name);
    tests_run++;
    if (0 == strcmp (actual_result, expected_new_name)) {
        return 0;
    } else {
        failcount++;
        if (check_type == SOFT_CHECK) {
            fprintf (stderr, "Expected new name: %s, Actual : %s\n",
                    expected_new_name, actual_result);
            return -1;
        } else {
            assert (failcount == 1);
            fprintf (stderr, "Expected new name: %s, Actual : %s\n",
                    expected_new_name, actual_result);
            fprintf (stderr, "%d/%d tests passed\n", (tests_run - 1), tests_run);
            exit (-1);
        }
    }
}

/* When this list is appended to, the value of TEST_COUNT
 * must be updated in libtests.h.
 */
char names [TEST_COUNT][2][NAMELEN] = { "a-b.c", "a.c",
                                        "a__b-c.c", "a__b.c",
                                        "aaa-bbb.ext", "aaa.ext",
                                        "a_b_c_d-e.mp4", "a_b_c_d.mp4",
                                        "filename_-rem.mp4", "filename.mp4",
                                        "a-b-c.mp4", "a_b.mp4",
                                        "-name.mp4", "name.mp4",
                                        "__.mp4", "__.mp4",
                                        "____.mp4", "____.mp4",
                                        "--.mp4", "--.mp4",
                                        "a_-_b.mp4", "a_b.mp4",
                                        "a - b.mp4", "a_b.mp4"};

int run_tests(int verbose)
{
    for (int i = 0 ; i < TEST_COUNT ; i++) {
        d_printf ("Running test #%d, input name is %s\n", i, names[i][0]);
        check (names[i][0], names [i][1]);
    }

    if (verbose) {
        printf ("%d/%d tests passed\n", (tests_run - failcount), TEST_COUNT);
    }
    return -failcount;
}
