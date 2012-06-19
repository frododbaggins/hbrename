#include "libtests.h"

typedef int bool;
#define IGNORE 2
#define TRUE 1
#define FALSE 0

int test_count = 0, failcount = 0, check_type = 0;
struct test_data_bufs
{
    char buf_old [NAMELEN],
         buf_exp [NAMELEN];
};
struct test_data_bufs bufs;

void set_check_type (int type)
{
    assert ((type == SOFT_CHECK) || (type == HARD_CHECK));
    check_type = type;
}

bool get_single_entry (FILE * fp)
{
    assert ((FILE *) -1 != fp);
    char * line = calloc (sizeof (char), 2 * NAMELEN);
    size_t dummy = 0;
    ssize_t read;
    //    char buf_old [NAMELEN] = "", buf_exp [NAMELEN] = "";

    if ((read = getline (&line, &dummy, fp)) != -1) {
        char *ptr;
        int i = 0;

        if (*line == '#') {
            /* Ignore comment lines */
            bufs.buf_old[0] = '#';
            return IGNORE;
        }
        d_printf ("-----------------------------------------\n");
        d_printf ("Got %s len = %d\n", line, strlen (line));

        if ((ptr = strchr (line, '\n')) != NULL)
            *ptr = '\0';

        ptr = line;

        /* Clear buffers from last iteration */
        for (i = 0; i < NAMELEN; i++) {
            bufs.buf_old [i] = bufs.buf_exp [i] = 0;
        }

        i = 0;
        while (*ptr && *ptr != ':') {
            bufs.buf_old [i] = *ptr;
            i++;
            ptr++;
        }
        ptr++; /* Skip over the colon*/
        i = 0;
        while (*ptr) {
            bufs.buf_exp [i] = *ptr;
            ptr++;
            i++;
        }
        free (line);
        return TRUE;
    } else {
        /* End of file */
        free (line);
        return FALSE;
    }
}

int check (char * filename)
{
    assert (filename);
    FILE * fp = fopen (filename, "r");
    if (NULL == fp) {
        return -1;
    }
    bool ret;
    while (((ret = get_single_entry (fp)) == TRUE) || (ret == IGNORE)) {
        if (bufs.buf_old [0] == '#') {
            /* Ignore comment line */
            continue;
        }
        test_count ++;
        d_printf ("buf_old = [%s] buf_exp = [%s]\n", bufs.buf_old, bufs.buf_exp);
        d_printf ("Running test #%d, input name is [%s]\n", test_count, bufs.buf_old);

        /* Now, run the check */
        char * actual_result = new_name (bufs.buf_old);
        if (0 == strcmp (actual_result, bufs.buf_exp)) {
            continue;
        } else {
            failcount++;
            if (check_type == SOFT_CHECK) {
                fprintf (stderr, "Expected new name: [%s], Actual : [%s]\n",
                         bufs.buf_exp, actual_result);
                return -1;
            } else {
                assert (failcount == 1);
                fprintf (stderr, "Expected new name: %s, Actual : %s\n",
                         bufs.buf_exp, actual_result);
                fprintf (stderr, "%d/%d tests passed\n", (test_count - 1), test_count);
                exit (-1);
            }
        }
    }
    d_printf ("%d strings found\n", test_count);
    fclose (fp);
    return test_count;
}

int run_tests(int verbose)
{
    int ret = check (TEST_DATA_FILE);
    if (ret == -1) {
        fprintf (stderr, "Failed to open test data file\n");
    }
    if (verbose) {
        printf ("%d/%d tests passed\n", (test_count - failcount), test_count);
    }
    return -failcount;
}
