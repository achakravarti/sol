/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-prim.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the primitives module.
 *
 * Authors:
 *      Abhishek Chakravarti <abhishek@taranjali.org>
 *
 * Copyright:
 *      (c) 2019 Abhishek Chakravarti
 *      <abhishek@taranjali.org>
 *
 * License:
 *      Released under the GNU General Public License version 3 (GPLv3)
 *      <http://opensource.org/licenses/GPL-3.0>. See the accompanying LICENSE
 *      file for complete licensing details.
 *
 *      BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT
 *      YOU HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/




        /* include required header files */
#include "../inc/prim.h"
#include "suite.h"




        /* bool_test1() implements the unit test described by BOOL_TEST1 */
static sol_erno bool_test1(void)
{
        #define BOOL_TEST1 "SOL_BOOL_TRUE must evaluate to 1"

SOL_TRY:
                /* check test condition */
        sol_assert (SOL_BOOL_TRUE == 1, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* bool_test2() implements the unit test described by BOOL_TEST2 */
static sol_erno bool_test2(void)
{
        #define BOOL_TEST2 "SOL_BOOL_FALSE must evaluate to 0"

SOL_TRY:
                /* check test condition */
        sol_assert (SOL_BOOL_FALSE == 0, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* i8_test1() implements the unit test described by I8_TEST1 */
static sol_erno i8_test1(void)
{
        #define I8_TEST1 "size of sol_i8 is at least 8 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_i8) >= 1, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* i16_test1() implements the unit test described by I16_TEST1 */
static sol_erno i16_test1(void)
{
        #define I16_TEST1 "size of sol_i16 is at least 16 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_i16) >= 2, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* __sol_tests_prim() was declared in sol/test/suite.h */
extern sol_erno __sol_tests_prim(sol_tlog *log,
                                 int *pass,
                                 int *fail,
                                 int *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* initialise test suite */
        sol_try (sol_tsuite_init2(ts, log));

                /* register test cases */
        sol_try (sol_tsuite_register(ts, bool_test1, BOOL_TEST1));
        sol_try (sol_tsuite_register(ts, bool_test2, BOOL_TEST2));
        sol_try (sol_tsuite_register(ts, i8_test1, I8_TEST1));
        sol_try (sol_tsuite_register(ts, i16_test1, I16_TEST1));


                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

