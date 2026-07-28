#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char *argv[])
{

const char *writefile;
const char *writestr;
FILE *fp;
int write_result;
int rc = 0;

/* set up syslog: use LOG_USET facility, include PID, and also 
*echp LOG_ERR meddagees to stderr while we re at it for easier 
*interactive debugging (does not affect syslog content) */

openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
if (argc !=3) {
syslog(LOG_ERR,
          "invalid number of argumnets: %d (expected 2: <writefile> <writestr>)", argc - 1);
fprintf(stderr, "usage: %s <writefile> <writestr>\n", argv[0]);
rc = 1;
goto cleanup;
}

 writefile = argv[1];
    writestr = argv[2];
 
    fp = fopen(writefile, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Could not open file '%s' for writing: %s",
               writefile, strerror(errno));
        rc = 1;
        goto cleanup;
    }
 
    write_result = fputs(writestr, fp);
    if (write_result == EOF) {
        syslog(LOG_ERR, "Could not write to file '%s': %s",
               writefile, strerror(errno));
        rc = 1;
        fclose(fp);
        goto cleanup;
    }
 
    if (fclose(fp) != 0) {
        syslog(LOG_ERR, "Could not close file '%s': %s",
               writefile, strerror(errno));
        rc = 1;
        goto cleanup;
    }
 
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
 
cleanup:
    closelog();
    return rc;
}
