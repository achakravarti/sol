#include "../inc/test.h"


static int unit_pass;
static int unit_fail;
static SOL_TEST_STATUS unit_stat;

#define LOG_MAXPATHLEN 256
static sol_test_log *log_cbk;
static char log_path[LOG_MAXPATHLEN];




static inline void
log_init(char         const *path,
         sol_test_log const *cbk
        )
{
        register char *itr = (log_path);

        log_cbk = (cbk);
        while     ((*itr++ = *path++));
}




extern void
sol_test_init(void)
{
        unit_pass = (0);
        unit_fail = (0);
        unit_stat = (SOL_TEST_STATUS_PENDING);
}




extern void
sol_test_init2(char         const *path,
               sol_test_log const *cbk
              )
{
        sol_test_init ();
        log_init      (path, cbk);
}

