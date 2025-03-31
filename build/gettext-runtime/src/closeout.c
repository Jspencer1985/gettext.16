/* closeout.c - simplified implementation */
#include "closeout.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>  /* Make sure this is properly included for strerror */

void close_stdout(void) {
    if (fclose(stdout) != 0) {
        fprintf(stderr, "Error closing stdout: %s\n", strerror(errno));
        exit(1);
    }
}
