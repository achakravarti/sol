/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-error.c
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
 *      BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT
 *      YOU HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/




#include "../inc/test.h"
#include "./suite.h"




/*
 *      mock_assertpass() - simulates success of sol_assert()
 */
static sol_erno mock_assertpass(void)
{
SOL_TRY:
                /* this condition will always pass */
        sol_assert (1 == 1, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      mock_assertfail() - simulates failure of sol_assert()
 */
static sol_erno mock_assertfail(void)
{
SOL_TRY:
                /* this condition will always fail */
        sol_assert (1 != 1, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      mock_trypass() - simulates success of sol_try()
 */
static sol_erno mock_trypass(void)
{
SOL_TRY:
                /* mock_assertpass() is guaranteed to succeed */
        sol_try (mock_assertpass ());

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      mock_tryfail() - simulates failure of sol_try()
 */
static sol_erno mock_tryfail(void)
{
SOL_TRY:
                /* mock_assertfail() is guaranteed to fail */
        sol_try (mock_assertfail ());

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      test_assert1() - sol_assert() unit test #1
 */
static sol_erno test_assert1(void)
{
        #define DESC_ASSERT1 "sol_assert() must not throw an error for a" \
                             " predicate that evaluates to true"
SOL_TRY:
                /* check test condition */
        sol_assert (!mock_assertpass(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      test_assert2() - sol_assert() unit test #2
 */
static sol_erno test_assert2(void)
{
        #define DESC_ASSERT2 "sol_assert() must throw an error for a" \
                             " predicate that evaluates to false"
SOL_TRY:
                /* check test condition */
        sol_assert (mock_assertfail(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      test_try1() - sol_try() unit test #1
 */
static sol_erno test_try1(void)
{
        #define DESC_TRY1 "sol_try() must not throw an error for a function" \
                          " that returns a SOL_ERNO_NULL error code"
SOL_TRY:
                /* check test condition */
        sol_assert (!mock_trypass(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      test_try2() - sol_try() unit test #2
 */
static sol_erno test_try2(void)
{
        #define DESC_TRY2 "sol_try() must throw an error for a function that" \
                          " returns an error code other than SOL_ERNO_NULL"
SOL_TRY:
                /* check test condition */
        sol_assert (mock_tryfail(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      test_get1() - sol_erno_get() unit test #1
 */
static sol_erno test_get1(void)
{
        #define DESC_GET1 "sol_erno_get() must return the current error code"
SOL_TRY:
                /* set up test scenario */
        sol_try (mock_assertfail());

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_TEST == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      __sol_tsuite_error() - declared in sol/test/suite.h
 */
extern sol_erno
__sol_tsuite_error(sol_tlog *log,
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
        sol_try (sol_tsuite_register(ts, test_assert1, DESC_ASSERT1));
        sol_try (sol_tsuite_register(ts, test_assert2, DESC_ASSERT2));
        sol_try (sol_tsuite_register(ts, test_try1, DESC_TRY1));
        sol_try (sol_tsuite_register(ts, test_try2, DESC_TRY2));
        sol_try (sol_tsuite_register(ts, test_get1, DESC_GET1));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* return test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        sol_throw();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

