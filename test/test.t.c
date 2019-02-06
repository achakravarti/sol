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
#define DESC_INIT_01 "sol_tsuite_init() should throw SOL_ERNO_PTR when" \
                     " passed a null pointer for @tsuite"



/*
 *      DESC_INIT2_01 - description for sol_tsuite_init2() unit test #1
 */
#define DESC_INIT2_01 "sol_tsuite_init2() should throw SOL_ERNO_PTR when" \
                      " passed a null pointer for @tsuite"




/*
 *      DESC_INIT2_02 - description for sol_tsuite_init2() unit test #2
 */
#define DESC_INIT2_02 "sol_tsuite_init2() should throw SOL_ERNO_PTR when" \
                      " passed a null pointer for @tlog"




/*
 *      DESC_REGISTER_01 - description for sol_tsuite_register() unit test #1
 */
#define DESC_REGISTER_01 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                         " when passed a null pointer for @tsuite"




/*
 *      DESC_REGISTER_02 - description for sol_tsuite_register() unit test #2
 */
#define DESC_REGISTER_02 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                         " when passed a null pointer for @tcase"




/*
 *      DESC_REGISTER_03 - description for sol_tsuite_register() unit test #3
 */
#define DESC_REGISTER_03 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                         " when passed a null pointer for @desc"




/*
 *      tlog_dummy() - dummy test suite logging callback
 */
static void
tlog_dummy(char     const *desc, /* test case description */
           sol_erno const erno   /* test case error code  */
          )
{
}




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
 *      test_init2_01() - sol_tsuite_init2() unit test #1
 */
static sol_erno
test_init2_01(void)
{
SOL_TRY:
                /* sol_tsuite_init2() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (0, tlog_dummy));

SOL_CATCH:
                /* check test condition described by DESC_INIT2_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_init2_02() - sol_tsuite_init2() unit test #1
 */
static sol_erno
test_init2_02(void)
{
        auto sol_tsuite ts; /* dummy test suite */

SOL_TRY:
                /* sol_tsuite_init2() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, 0));

SOL_CATCH:
                /* check test condition described by DESC_INIT2_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_register_01() - sol_tsuite_register() unit test #1
 */
static sol_erno
test_register_01(void)
{
        auto sol_tsuite ts; /* dummy test suite */

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2    (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (0, test_init_01, "Dummy"));

SOL_CATCH:
                /* check test condition described by DESC_REGISTER_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_register_02() - sol_tsuite_register() unit test #2
 */
static sol_erno
test_register_02(void)
{
        auto sol_tsuite ts; /* dummy test suite */

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2    (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (&ts, 0, "Dummy"));

SOL_CATCH:
                /* check test condition described by DESC_REGISTER_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_register_03() - sol_tsuite_register() unit test #3
 */
static sol_erno
test_register_03(void)
{
        auto sol_tsuite ts; /* dummy test suite */

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2    (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (&ts, test_register_01, 0));

SOL_CATCH:
                /* check test condition described by DESC_REGISTER_03 */
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
        sol_try (sol_tsuite_register (ts, test_init_01,     DESC_INIT_01));
        sol_try (sol_tsuite_register (ts, test_init2_01,    DESC_INIT2_01));
        sol_try (sol_tsuite_register (ts, test_init2_02,    DESC_INIT2_02));
        sol_try (sol_tsuite_register (ts, test_register_01, DESC_REGISTER_01));
        sol_try (sol_tsuite_register (ts, test_register_02, DESC_REGISTER_02));
        sol_try (sol_tsuite_register (ts, test_register_03, DESC_REGISTER_03));

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

