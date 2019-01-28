#include "../inc/test.h"


static int unit_pass;
static int unit_fail;
static SOL_TEST_STATUS unit_stat;

static sol_test_log *log_cbk;
static char *log_path;

extern void
sol_test_init2(char         const *path,
               sol_test_log const *cbk
              )
{
        unit_pass = 0;
        unit_fail = 0;
        unit_stat = SOL_TEST_STATUS_PENDING;

        log_path = path;
        log_cbk  = cbk;
}

