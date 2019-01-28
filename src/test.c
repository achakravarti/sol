#include "../inc/test.h"


static int unit_pass = 0;
static int unit_fail = 0;
static SOL_TEST_STATUS unit_stat = SOL_TEST_STATUS_PENDING;

#define LOG_MAXPATHLEN 256
static sol_test_log *log_cbk;
static char log_path[LOG_MAXPATHLEN];




static inline void
log_init(char         const *path,
         sol_test_log const *cbk
        )
{
        register char *itr;

        log_cbk = cbk;

        itr = log_path;
        while ((*itr++ = *path++));
}




extern void
sol_test_init(void)
{
        unit_pass = 0;
        unit_fail = 0;
        unit_stat = SOL_TEST_STATUS_PENDING;
}




extern void
sol_test_init2(char         const *path,
               sol_test_log const *cbk
              )
{
        sol_test_init ();
        log_init (path, cbk);
}




extern void
sol_test_exit(int *pass,
              int *fail
             )
{
        *pass = unit_pass;
        *fail = unit_fail;
}




extern int
sol_test_exec(char          const *desc,
              sol_test_unit const *cbk
             )
{
        auto int erno;

        if (!(cbk && desc && *desc))
                return -1;

        if ((erno = cbk ()))
                unit_fail++;
        else
                unit_pass++;

        if (log_cbk)
                log_cbk (desc, erno);

        return erno;
}




extern void
sol_test_status(SOL_TEST_STATUS *status)
{
        *status = unit_stat;
}

