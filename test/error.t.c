/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/error.t.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the exception handling module.
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
 *      BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAt
 *      YOU HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/




#include "../inc/test.h"
#include "./suite.h"




/*
 *      DESC_ASSERT_01 - description for sol_assert() unit test #1
 */
#define DESC_ASSERT_01 "sol_assert() must not throw an error for a" \
                       " predicate that evaluates to true"




/*
 *      DESC_ASSERT_02 - description for sol_assert() unit test #2
 */
#define DESC_ASSERT_02 "sol_assert() must throw an error for a" \
                         " predicate that evaluates to false"




/*
 *      DESC_TRY_01 - description for sol_try() unit test #1
 */
#define DESC_TRY_01 "sol_try() must not throw an error for a function that" \
                    " returns a SOL_ERNO_NULL error code"




/*
 *      DESC_TRY_02 - description for sol_try() unit test #2
 */
#define DESC_TRY_02 "sol_try() must throw an error for a function that" \
                    " returns an error code other than SOL_ERNO_NULL"




/*
 *      DESC_NOW_01 - description for sol_erno_now() unit test #1
 */
#define DESC_NOW_01 "sol_erno_now() must return the current error code that" \
                    " was thrown by the last calling function"




/*
 *      assert_pass() - simulates success of sol_assert()
 */
static sol_erno
assert_pass(void)
{
SOL_TRY:
                /* this condition will always pass */
        sol_assert (1 == 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* control will never reach here */
        sol_throw ();
}




/*
 *      assert_fail() - simulates failure of sol_assert()
 */
static sol_erno
assert_fail(void)
{
SOL_TRY:
                /* this condition will always fail */
        sol_assert (1 != 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* control will always reach here */
        sol_throw ();
}




/*
 *      try_pass() - simulates success of sol_try()
 */
static sol_erno
try_pass(void)
{
SOL_TRY:
                /* assert_pass() is guaranteed to succeed */
        sol_try (assert_pass ());

SOL_CATCH:
                /* control will never reach here */
        sol_throw ();
}




/*
 *      try_fail() - simulates failure of sol_try()
 */
static sol_erno
try_fail(void)
{
SOL_TRY:
                /* assert_fail() is guaranteed to fail */
        sol_try (assert_fail ());

SOL_CATCH:
                /* control will always reach here */
        sol_throw ();
}




/*
 *      test_assert_01() - sol_assert() unit test #1
 */
static sol_erno
test_assert_01(void)
{
SOL_TRY:
                /* check test condition described by DESC_ASSERT_01 */
        sol_assert (!assert_pass (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      test_assert_02() - sol_assert() unit test #2
 */
static sol_erno
test_assert_02(void)
{
SOL_TRY:
                /* check test condition described by DESC_ASSERT_02 */
        sol_assert (assert_fail (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      test_try_01() - sol_try() unit test #1
 */
static sol_erno
test_try_01(void)
{
SOL_TRY:
                /* check test condition described by DESC_TRY_01 */
        sol_assert (!try_pass (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      test_try_02() - sol_try() unit test #2
 */
static sol_erno
test_try_02(void)
{
SOL_TRY:
                /* check test condition described by DESC_TRY_01 */
        sol_assert (try_fail (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      test_now_01() - sol_erno_now() unit test #1
 */
static sol_erno
test_now_01(void)
{
        auto sol_erno erno;

SOL_TRY:
                /* check test condition described by DESC_NOW_01 */
        erno = assert_fail ();
        sol_assert (erno == sol_erno_now (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      test_try_02() - declared in sol/test/suite.h
 */
extern sol_erno
__sol_tsuite_error(void)
{
        auto sol_tsuite tsuite, *ts = &tsuite;

SOL_TRY:
                /* initialise test suite */
        sol_try (sol_tsuite_init (ts));

                /* register test cases */
        sol_try (sol_tsuite_register (ts, test_assert_01, DESC_ASSERT_01));
        sol_try (sol_tsuite_register (ts, test_assert_02, DESC_ASSERT_02));
        sol_try (sol_tsuite_register (ts, test_try_01, DESC_TRY_01));
        sol_try (sol_tsuite_register (ts, test_try_02, DESC_TRY_02));
        sol_try (sol_tsuite_register (ts, test_now_01, DESC_NOW_01));

                /* execute registered test cases and wind up */
        sol_try (sol_tsuite_exec (ts));
        sol_tsuite_term (ts);

SOL_CATCH:
                /* wind up and throw exceptions */
        sol_tsuite_term (ts);
        sol_throw ();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

