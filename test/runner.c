/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/runner.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test runner to execute all the module test suites.
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
#include <stdio.h>




/*
 *      ts - function pointer to test suites
 */
typedef sol_erno /* error code                */
(ts)(int *pass,  /* passed test cases         */
     int *fail,  /* failed test cases         */
     int *total  /* total test cases executed */
    );




/*
 *      TS_COUNT - count of test suites
 */
#define TS_COUNT 1




/*
 *      TS_ERROR - index of exception handling test suite
 */
#define TS_ERROR 0




/*
 *      ts_hnd - test suite handles
 */
static ts *ts_hnd [TS_COUNT];




/*
 *      ts_pass - count of passed test cases per suite
 */
static int ts_pass [TS_COUNT];




/*
 *      ts_fail - count of failed test cases per suite
 */
static int ts_fail [TS_COUNT];




/*
 *      ts_total - count of total test cases per suite
 */
static int ts_total [TS_COUNT];




/*
 *      ts_init() - initialises test suites
 */
static void
ts_init(void)
{
        register int i; /* iterator */

                /* register test suites */
        ts_hnd [TS_ERROR] = __sol_tsuite_error;

                /* initialise test counters */
        for (i = 0; i < TS_COUNT; i++) {
                ts_pass  [i] = 0;
                ts_fail  [i] = 0;
                ts_total [i] = 0;
        }
}




/*
 *      ts_exec() - executes test suites
 */
static void
ts_exec(void)
{
        register int i; /* iterator */

                /* execute test suites */
        for (i = 0; i < TS_COUNT; i++) {
                ts_hnd [i] (ts_pass + i, ts_fail + i, ts_total + i);
        }
}




/*
 *      ts_term() - winds up test suites
 */
static void
ts_term(void)
{
        register int i;      /* iterator                   */
        auto     int sigmap; /* sigma of passed test cases */
        auto     int sigmaf; /* sigma of failed test cases */
        auto     int sigmat; /* sigma of total test cases  */

                /* initialise sigma test counters */
        sigmap = 0;
        sigmaf = 0;
        sigmat = 0;

                /* compute sigma test counters */
        for (i = 0; i < TS_COUNT; i++) {
                sigmap += ts_pass  [i];
                sigmaf += ts_fail  [i];
                sigmat += ts_total [i];
        }

                /* print sigma test counters */
        printf ("%d test(s) run, %d passed, %d failed\n",
                sigmat,
                sigmap,
                sigmaf
               );
}




/*
 *      main() - main entry point of test runner
 */
int main( void )
{
                /* run test suites */
        ts_init ();
        ts_exec ();
        ts_term ();

                /* everything's OK */
        return 0;
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

