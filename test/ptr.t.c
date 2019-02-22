/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ptr.t.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the pointer module.
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
#include "../inc/ptr.h"
#include "./suite.h"




/*
 *      new_01() - sol_ptr_new() unit test #1
 */
static sol_erno new_01(void)
{
        #define NEW_01 "sol_ptr_new() throws SOL_ERNO_PTR when passed a null" \
                       " pointer for @ptr"

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new(SOL_PTR_NULL, sizeof (int)));

SOL_CATCH:
                /* check test condition */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      new_02() - sol_ptr_new() unit test #2
 */
static sol_erno new_02(void)
{
        #define NEW_02 "sol_ptr_new() throws SOL_ERNO_PTR when passed a"   \
                       " pointer for @ptr that has already been allocated"
        auto sol_ptr *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (SOL_ERNO_NULL == sol_ptr_new(&ptr, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_new(&ptr, sizeof (int)));

SOL_CATCH:
                /* check test condition */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      __sol_tests_ptr() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tests_ptr(sol_tlog *log,
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
        sol_try (sol_tsuite_register(ts, &new_01, NEW_01));
        sol_try (sol_tsuite_register(ts, &new_02, NEW_02));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

                /* wind up */
        sol_tsuite_term(ts);

SOL_CATCH:
                /* throw current exception, if any */
        sol_tsuite_term(ts);
        sol_throw();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

