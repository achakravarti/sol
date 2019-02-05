/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/test.t.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the unit testing module.
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




#include "./suite.h"




/*
 *      DESC_INIT_01 - description for sol_tsuite_init() unit test #1
 */
#define DESC_INIT_01 "sol_tsuite_init() should through SOL_ERNO_PTR when" \
                     " passed a null pointer for @tsuite"




/*
 *      test_init_01() - sol_tsuite_init() unit test #1
 */
static sol_erno
test_init_01(void)
{
SOL_TRY:
                /* sol_tsuite_init() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init (0));

SOL_CATCH:
                /* check test condition described by DESC_INIT_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      __sol_tsuite_test() - declared in sol/test/suite.h
 */
extern sol_erno
__sol_tsuite_test(sol_tlog *log,
                  int      *pass,
                  int      *fail,
                  int      *total
                 )
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* initialise test suite */
        sol_try (sol_tsuite_init2 (ts, log));

                /* register test cases */
        sol_try (sol_tsuite_register (ts, test_init_01, DESC_INIT_01));

                /* execute test cases */
        sol_try (sol_tsuite_exec (ts));

                /* return test counts */
        sol_try (sol_tsuite_pass  (ts, pass));
        sol_try (sol_tsuite_fail  (ts, fail));
        sol_try (sol_tsuite_total (ts, total));

                /* wind up */
        sol_tsuite_term (ts);

SOL_CATCH:
                /* wind up and throw current exception */
        sol_tsuite_term (ts);
        sol_throw       ();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

