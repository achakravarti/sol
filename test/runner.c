#include <stdio.h>

#include "../inc/test.h"
#include "../test/error.t.h"




/*
 *      eh_exec() - executes exception handling test suite
 */
static sol_erno
eh_exec(void)
{
        auto sol_tsuite tsuite, *ts = &tsuite;

SOL_TRY:
                /* initialise test suite */
        sol_try (sol_tsuite_init (ts));

                /* register test cases */
        sol_try (sol_tsuite_register (ts, __test_assert_01, __DESC_ASSERT_01));
        sol_try (sol_tsuite_register (ts, __test_assert_02, __DESC_ASSERT_02));
        sol_try (sol_tsuite_register (ts, __test_try_01, __DESC_TRY_01));
        sol_try (sol_tsuite_register (ts, __test_try_02, __DESC_TRY_02));

                /* execute registered test cases and wind up */
        sol_try (sol_tsuite_exec (ts));
        sol_tsuite_term (ts);

SOL_CATCH:
                /* wind up and throw exceptions */
        sol_tsuite_term (ts);
        sol_throw ();
}




/*
 *      main() - main entry point of test runner
 */
int main( void )
{
                /* execute exception handling test suite */
        if (eh_exec ()) {
                return -1;
        }

                /* everything's OK */
        return 0;
}

