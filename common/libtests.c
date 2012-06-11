#include "libtests.h"

int test_count = 0, failcount = 0, check_type = 0;

void set_check_type (int type)
{
    assert ((type == SOFT_CHECK) || (type == HARD_CHECK));
    check_type = type;
}
int check (char * filename)
{
    int failcount = 0;
    assert (filename);
    FILE * fp = fopen (filename, "r");
    if (NULL == fp) {
        return -1;
    }

    char * line = calloc (sizeof (char), 2 * NAMELEN);
    size_t dummy = 0;
    ssize_t read;
    char buf_old [NAMELEN] = "", buf_exp [NAMELEN] = "";

    while ((read = getline (&line, &dummy, fp)) != -1) {
        char *ptr;
        int i = 0;

        if (*line == '#') {
            /* Ignore comment lines */
            continue;
        }
        d_printf ("-----------------------------------------\n");
        d_printf ("Got %s len = %d\n", line, strlen (line));

        if ((ptr = strchr (line, '\n')) != NULL)
            *ptr = '\0';

        ptr = line;

        /* Clear buffers from last iteration */
        for (i = 0; i < NAMELEN; i++) {
            buf_old [i] = buf_exp [i] = 0;
        }

        i = 0;
        while (*ptr && *ptr != ':') {
            buf_old [i] = *ptr;
            i++;
            ptr++;
        }
        ptr++; /* Skip over the colon*/
        i = 0;
        while (*ptr) {
            buf_exp [i] = *ptr;
            ptr++;
            i++;
        }
        ptr = NULL;
        test_count ++;
        d_printf ("buf_old = [%s] buf_exp = [%s]\n", buf_old, buf_exp);
        d_printf ("Running test #%d, input name is [%s]\n", test_count, buf_old);

        /* Now, run the check */
        char * actual_result = new_name (buf_old);
        if (0 == strcmp (actual_result, buf_exp)) {
            continue;
        } else {
            failcount++;
            if (check_type == SOFT_CHECK) {
                fprintf (stderr, "Expected new name: [%s], Actual : [%s]\n",
                         buf_exp, actual_result);
                return -1;
            } else {
                assert (failcount == 1);
                fprintf (stderr, "Expected new name: %s, Actual : %s\n",
                         buf_exp, actual_result);
                fprintf (stderr, "%d/%d tests passed\n", (test_count - 1), test_count);
                exit (-1);
            }
        }
    }
    d_printf ("%d strings found\n", test_count);
    fclose (fp);
    free (line);
    return test_count;
}

int run_tests(int verbose)
{
    check (TEST_DATA_FILE);
    if (verbose) {
        printf ("%d/%d tests passed\n", (test_count - failcount), test_count);
    }
    return -failcount;
}
