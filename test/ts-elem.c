/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-elem.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the element interface.
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
#include "../inc/dsa.h"
#include "suite.h"




static sol_erno meta_new(sol_elem_meta **meta)
{
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = sizeof (int);

        return sol_elem_meta_new(meta, ID, SZ);
}




        /* new_test1() defines the test case described by NEW_TEST1 */
static sol_erno new_test1(void)
{
        #define NEW_TEST1 "sol_elem_new() throws SOL_ERNO_PTR if" \
                          " passed a null pointer for @elem"
        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto int data = 5;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(SOL_PTR_NULL, meta, (sol_ptr *) &data));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* __sol_tests_elem() was declared in sol/test/suite.h */
extern sol_erno __sol_tests_elem(sol_tlog *log,
                                 sol_uint *pass,
                                 sol_uint *fail,
                                 sol_uint *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* initialise test suite */
        sol_try (sol_tsuite_init2(ts, log));

                /* register sol_elem_new() test cases */
        sol_try (sol_tsuite_register(ts, new_test1, NEW_TEST1));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

