/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/error.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test cases for the exception handling module.
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




#include "./error.h"




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
 *      __test_assert_01() - declared in sol/test/error.h
 */
extern sol_erno
__test_assert_01(void)
{
SOL_TRY:
                /* check test condition described by __DESC_ASSERT_01 */
        sol_assert (!assert_pass (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      __test_assert_02() - declared in sol/test/error.h
 */
extern sol_erno
__test_assert_02(void)
{
SOL_TRY:
                /* check test condition described by __DESC_ASSERT_02 */
        sol_assert (assert_fail (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      __test_try_01() - declared in sol/test/error.h
 */
extern sol_erno
__test_try_01(void)
{
SOL_TRY:
                /* check test condition described by __DESC_TRY_01 */
        sol_assert (!try_pass (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




/*
 *      __test_try_02() - declared in sol/test/error.h
 */
extern sol_erno
__test_try_02(void)
{
SOL_TRY:
                /* check test condition described by __DESC_TRY_01 */
        sol_assert (try_fail (), SOL_ERNO_TEST);

SOL_CATCH:
                /* catch exceptions */
        sol_throw ();
}




