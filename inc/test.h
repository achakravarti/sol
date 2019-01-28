typedef enum sol_test_status {
        SOL_TEST_STATUS_PENDING = -1,
        SOL_TEST_STATUS_PASS,
        SOL_TEST_STATUS_FAIL
} SOL_TEST_STATUS;

typedef int
(sol_test_unit)(void);

typedef void
(sol_test_log)(char const *desc,
               char const *res
              );

extern void
sol_test_init(char         const *fpath,
              sol_test_log const *cbk
             );

extern void
sol_test_exec(sol_test_unit const *cbk,
              char          const *desc
             );

extern void
sol_test_status(SOL_TEST_STATUS *status);

extern void
sol_test_exit(int *pass,
              int *fail
             );

