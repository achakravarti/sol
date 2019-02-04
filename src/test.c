/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/src/test.c
 *
 * Description:
 *      This file is part of the internal implementation of the Sol Library.
 *      It implements the unit testing module.
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




/*
 *      Include required header files.
 */
#include "../inc/test.h"




/*
 *      tsuite_init() - initialises test suite member fields
 */
static void
tsuite_init(sol_tsuite *tsuite, /* contextual test suite */
            sol_tlog   *tlog    /* logging callback      */
           )
{
        register int i;

                /* initialise counters and logging callback */
        tsuite->total = 0;
        tsuite->fail  = 0;
        tsuite->tlog  = tlog;

                /* initialise test case callback and description arrays */
        for (i = 0; i < SOL_TSUITE_MAXTCASE; i++) {
                *tsuite->desc [i] = '\0';
                tsuite->tcase [i] = 0;
        }
}




/*
 *      sol_tsuite_init() - declared in sol/inc/test.h
 */
extern sol_erno
sol_tsuite_init(sol_tsuite *tsuite)
{
SOL_TRY:
                /* check preconditions */
        sol_assert (tsuite, SOL_ERNO_PTR);

                /* initialise member fields, setting the logging callback to
                 * null as we don't require it */
        tsuite_init (tsuite, 0);

SOL_CATCH:
                /* throw exceptions */
        sol_throw ();
}




/*
 *      sol_tsuite_init2() - declared in sol/inc/test.h
 */
extern sol_erno
sol_tsuite_init2(sol_tsuite *tsuite,
                 sol_tlog   *tlog
                )
{
SOL_TRY:
                /* check preconditions */
        sol_assert (tsuite && tlog, SOL_ERNO_PTR);

                /* initialise member fields, setting the logging callback to
                 * @tlog */
        tsuite_init (tsuite, tlog);

SOL_CATCH:
                /* throw exceptions */
        sol_throw ();
}




/*
 *      sol_tsuite_term() - declared in sol/inc/test.h
 */
extern void
sol_tsuite_term(sol_tsuite *tsuite)
{
                /* reset member fields, including logging callback, if @tsuite
                 * is valid */
        if (tsuite) {
                tsuite_init (tsuite, 0);
        }
}




/*
 *      sol_tsuite_register() - declared in sol/inc/test.h
 */
extern sol_erno
sol_tsuite_register(sol_tsuite       *tsuite,
                    sol_tcase        *tcase,
                    char       const *desc
                   )
{
        register char *itr;
        auto     int  len;

SOL_TRY:
                /* check preconditions */
        sol_assert (tsuite && tcase && desc, SOL_ERNO_PTR);
        sol_assert (*desc, SOL_ERNO_STR);
        sol_assert (tsuite->total <= SOL_TSUITE_MAXTCASE, SOL_ERNO_RANGE);

                /* add @tcase to first free slot in test case array; the index
                 * of this slot will be equal to the current total number of
                 * registed test cases */
        tsuite->tcase [tsuite->total] = tcase;

                /* add @desc to the first free slot in the test description
                 * array using the strncpy() algorithm; its index will be the
                 * same as that of the test case */
        itr = tsuite->desc [tsuite -> total];
        len = SOL_TCASE_MAXDESCLEN;
        while (len-- && (*itr++ = *desc++)) {
                ;
        }

                /* update total number of registered test cases */
        tsuite->total++;

SOL_CATCH:
                /* throw exceptions */
        sol_throw ();
}




/*
 *      sol_tsuite_pass() - declared in sol/inc/test.h
 */
extern sol_erno
sol_tsuite_pass(sol_tsuite const *tsuite,
                int              *pass
               )
{
SOL_TRY:
                /* check preconditions */
        sol_assert (tsuite && pass, SOL_ERNO_PTR);

                /* return count of passed tests */
        *pass = tsuite->total - tsuite->fail;

SOL_CATCH:
                /* throw exceptions */
        sol_throw ();
}




/*
 *      sol_tsuite_fail() - declared in sol/inc/test.h
 */
extern sol_erno
sol_tsuite_fail(sol_tsuite const *tsuite,
                int              *fail
               )
{
SOL_TRY:
                /* check preconditions */
        sol_assert (tsuite && fail, SOL_ERNO_PTR);

                /* return count of failed tests */
        *fail = tsuite->fail;

SOL_CATCH:
                /* throw exceptions */
        sol_throw ();
}




/*
 *      sol_tsuite_total() - declared in sol/inc/test.h
 */
extern sol_erno
sol_tsuite_total(sol_tsuite const *tsuite,
                 int              *total
                )
{
SOL_TRY:
                /* check preconditions */
        sol_assert (tsuite && total, SOL_ERNO_PTR);

                /* return count of total tests */
        *total = tsuite->total;

SOL_CATCH:
                /* throw exceptions */
        sol_throw ();
}




/*
 *      sol_tsuite_exec() - declared in sol/inc/test.h
 */
extern sol_erno
sol_tsuite_exec(sol_tsuite *tsuite)
{
        register int      i;
        auto     sol_erno erno;

SOL_TRY:
                /* check preconditions */
        sol_assert (tsuite, SOL_ERNO_PTR);

                /* reset count of failed test cases */
        tsuite->fail = 0;

                /* iterate through test case array, executing each in turn and
                 * logging it if the logging callback is available; update count
                 * of failed test cases as required */
        for (i = 0; i < tsuite->total; i++) {
                if ((erno = tsuite->tcase [i] ())) {
                        tsuite->fail++;
                }

                if (tsuite->tlog) {
                        tsuite->tlog (tsuite->desc [i], erno);
                }
        }

SOL_CATCH:
                /* throw exceptions */
        sol_throw ();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

