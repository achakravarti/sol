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




#include "suite.h"
#include <stdio.h>




/*
 *      suite - function pointer to test suites
 *        - log  : logging callback
 *        - pass : passed test cases
 *        - fail : failed test cases
 *        - total: total test cases executed
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_TEST if a test case fails
 *        - SOL_ERNO_PTR if an invalid pointer has been referenced
 */
typedef sol_erno (suite)(sol_tlog *log,
                         sol_uint *pass,
                         sol_uint *fail,
                         sol_uint *total);




/*
 *      SUITE - enumerates test suite indices
 *        - SUITE_ERROR: exception handling module test suite
 *        - SUITE_TEST: unit test module test suite
 *        - SUITE_HINT: compiler hints module test
 *        - SUITE_ENV: environment module test
 *        - SUITE_PTR: pointer module test suite
 *        - SUITE_PTR2: freestanding pointer module test suite
 *        - SUITE_LOG: logging module test suite
 *        - SUITE_COUNT: count of test suites
 */
typedef enum {
        SUITE_ERROR,
        SUITE_TEST,
        SUITE_HINT,
        SUITE_ENV,
        SUITE_PTR,
        SUITE_PTR2,
        SUITE_LOG,
        SUITE_PRIM,
        SUITE_ELEM,
        SUITE_COUNT
} SUITE;




/*
 *      LOG_ERRMSG - message to indicate error in opening log file
 */
#define LOG_ERRMSG "[!] Warning: couldn\'t open log file for unit tests\n"




/*
 *      LOG_SIGMAMSG - log message for sigma test counters
 */
#define LOG_SIGMAMSG "\n%lu test(s) run, %lu passed, %lu failed\n"




/*
 *      LOG_PASSMSG - log message for passed test cases
 */
#define LOG_PASSMSG "OK: %s\n"




/*
 *      LOG_FAILMSG - log message for failed test cases
 */
#define LOG_FAILMSG "[!] FAILED: %s [0x%.8lx]\n"




/*
 *      suite_hnd - test suite handles
 */
static suite *suite_hnd[SUITE_COUNT];




/*
 *      stat_suite - test case statistics for each test suite
 *        - pass : passed test cases per suite
 *        - fail : failed test cases per suite
 *        - total: total test cases per suite
 */
static struct {
        sol_uint pass[SUITE_COUNT];
        sol_uint fail[SUITE_COUNT];
        sol_uint total[SUITE_COUNT];
} stat_suite;




/*
 *      stat_sigma - summation statistics for all test suites
 *        - pass : sigma of passed test cases
 *        - fail : sigma of failed test cases
 *        - total: sigma of total test cases
 */
static struct {
        sol_uint pass;
        sol_uint fail;
        sol_uint total;
} stat_sigma;




/*
 *      log_hnd - handle to test log file
 */
static FILE *log_hnd;




/*
 *      log_init() - initialise test log file
 */
static sol_inline void
log_init(int  argc,  /* count of command line arguments */
         char **argv /* command line arguments          */
         )
{
                /* open test log file; show error if failed */
        if (argc == 2 && !(log_hnd = fopen (argv [1], "a+e"))) {
                printf (LOG_ERRMSG);
        }
}




/*
 *      log_term() - terminate test log file
 */
static sol_inline void
log_term(void)
{
                /* release log file if it's open */
        if (log_hnd) {
                fclose (log_hnd);
        }
}




/*
 *      log_tcase() - callback to log test case result
 */
static sol_inline void
log_tcase(char     const *desc, /* test case description            */
          sol_erno const erno   /* error code returned by test case */
         )
{
                /* log message according to test execution status */
        if (log_hnd) {
                erno ? fprintf (log_hnd, LOG_FAILMSG, desc, erno)
                     : fprintf (log_hnd, LOG_PASSMSG, desc);
        }
}




/*
 *      log_sigma() - prints and logs sigma statistics
 */
static void log_sigma(void)
{

                /* print sigma statistics */
        printf(LOG_SIGMAMSG,
               stat_sigma.total,
               stat_sigma.pass,
               stat_sigma.fail);

                /* log sigma statistics */
        if (log_hnd) {
                fprintf(log_hnd,
                        LOG_SIGMAMSG,
                        stat_sigma.total,
                        stat_sigma.pass,
                        stat_sigma.fail);
        }
}




/*
 *      stat_init() - initialise test statistics
 */
static void stat_init(void)
{
        register sol_index i; /* iterator */

                /* initialise test suite statistics */
        for (i = 0; i < SUITE_COUNT; i++) {
                stat_suite.pass[i] = 0;
                stat_suite.fail[i] = 0;
                stat_suite.total[i] = 0;
        }

                /* initialise sigma statistics */
        stat_sigma.pass  = 0;
        stat_sigma.fail  = 0;
        stat_sigma.total = 0;
}




/*
 *      stat_sum() - calculates sigma statistics
 */
static void stat_sum(void)
{
        register sol_index i; /* iterator */

                /* sum test suite statistics */
        for (i = 0; i < SUITE_COUNT; i++) {
                stat_sigma.pass += stat_suite.pass[i];
                stat_sigma.fail += stat_suite.fail[i];
                stat_sigma.total += stat_suite.total[i];
        }
}




/*
 *      suite_init() - initialises test suites
 */
static void suite_init(void)
{
                /* register test suites */
        suite_hnd[SUITE_ERROR] = __sol_tsuite_error;
        suite_hnd[SUITE_TEST] = __sol_tsuite_test;
        suite_hnd[SUITE_HINT] = __sol_tsuite_hint;
        suite_hnd[SUITE_ENV] = __sol_tests_env;
        suite_hnd[SUITE_PTR] = __sol_tests_ptr;
        suite_hnd[SUITE_PTR2] = __sol_tests_ptr2;
        suite_hnd[SUITE_LOG] = __sol_tests_log;
        suite_hnd[SUITE_PRIM] = __sol_tests_prim;
        suite_hnd[SUITE_ELEM] = __sol_tests_elem;
}




/*
 *      suite_exec() - executes test suites
 */
static void suite_exec(void)
{
        register sol_index i; /* iterator */

                /* execute test suites */
        for (i = 0; i < SUITE_COUNT; i++) {
                suite_hnd[i](log_tcase,
                              stat_suite.pass  + i,
                              stat_suite.fail  + i,
                              stat_suite.total + i);
        }
}




/*
 *      main() - main entry point of test runner
 */
int main(int argc, char **argv)
{
                /* initialise */
        log_init(argc, argv);
        stat_init();
        suite_init();

                /* execute */
        suite_exec();
        stat_sum();
        log_sigma();

                /* terminate */
        log_term();
        return stat_sigma.fail;
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

