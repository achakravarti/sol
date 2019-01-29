typedef int
(sol_test_unit)(void);

typedef void
(sol_test_log)(char const *desc,
               int  const erno
              );


extern void
sol_test_init(void);


extern void
sol_test_init2(char         const *path,
               sol_test_log const *cbk
              );


extern void
sol_test_pass(int *pass);


extern void
sol_test_fail(int *fail);


extern int
sol_test_exec(char          const *desc,
              sol_test_unit const *cbk
             );


extern void
sol_test_exit(void);

