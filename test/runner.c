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
 *      suite - function pointer to test suites
 */
typedef sol_erno        /* error code                */
(suite)(sol_tlog *log,  /* logging callback          */
        int      *pass, /* passed test cases         */
        int      *fail, /* failed test cases         */
        int      *total /* total test cases executed */
       );




/*
 *      SUITE_COUNT - count of test suites
 */
#define SUITE_COUNT 2




/*
 *      SUITE_ERROR - index of exception handling module test suite
 */
#define SUITE_ERROR 0



/*
 *      SUITE_TEST - index of unit testing module test suite
 */
#define SUITE_TEST 1




/*
 *      LOG_ERRMSG - message to indicate error in opening log file
 */
#define LOG_ERRMSG "[!] Warning: couldn\'t open log file for unit tests\n"




/*
 *      LOG_SIGMAMSG - log message for sigma test counters
 */
#define LOG_SIGMAMSG "\n%d test(s) run, %d passed, %d failed\n"




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
static suite *suite_hnd [SUITE_COUNT];




/*
 *      stat__suite - test case statistics for each test suite
 */
static struct {
        int pass   [SUITE_COUNT]; /* passed test cases per suite */
        int fail   [SUITE_COUNT]; /* failed test cases per suite */
        int total  [SUITE_COUNT]; /* total test cases per suite  */
} stat_suite;




/*
 *      stat_sigma - summation statistics for all test suites
 */
static struct {
        int pass;  /* sigma of passed test cases */
        int fail;  /* sigma of failed test cases */
        int total; /* sigma of total test cases  */
} stat_sigma;




/*
 *      log_hnd - handle to test log file
 */
static FILE *log_hnd;




/*
 *      log_init() - initialise test log file
 */
static inline void
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
static inline void
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
static inline void
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
static void
log_sigma(void)
{

                /* print sigma statistics */
        printf (LOG_SIGMAMSG,
                stat_sigma.total,
                stat_sigma.pass,
                stat_sigma.fail
               );

                /* log sigma statistics */
        if (log_hnd) {
                fprintf (log_hnd,
                         LOG_SIGMAMSG,
                         stat_sigma.total,
                         stat_sigma.pass,
                         stat_sigma.fail
                        );
        }
}




/*
 *      stat_init() - initialise test statistics
 */
static void
stat_init(void)
{
        register int i; /* iterator */

                /* initialise test suite statistics */
        for (i = 0; i < SUITE_COUNT; i++) {
                stat_suite.pass  [i] = 0;
                stat_suite.fail  [i] = 0;
                stat_suite.total [i] = 0;
        }

                /* initialise sigma statistics */
        stat_sigma.pass  = 0;
        stat_sigma.fail  = 0;
        stat_sigma.total = 0;
}




/*
 *      stat_sum() - calculates sigma statistics
 */
static void
stat_sum(void)
{
        register int i; /* iterator */

                /* sum test suite statistics */
        for (i = 0; i < SUITE_COUNT; i++) {
                stat_sigma.pass  += stat_suite.pass  [i];
                stat_sigma.fail  += stat_suite.fail  [i];
                stat_sigma.total += stat_suite.total [i];
        }
}




/*
 *      suite_init() - initialises test suites
 */
static void
suite_init(void)
{
                /* register test suites */
        suite_hnd [SUITE_ERROR] = __sol_tsuite_error;
        suite_hnd [SUITE_TEST]  = __sol_tsuite_test;
}




/*
 *      suite_exec() - executes test suites
 */
static void
suite_exec(void)
{
        register int i; /* iterator */

                /* execute test suites */
        for (i = 0; i < SUITE_COUNT; i++) {
                suite_hnd [i] (log_tcase,
                               stat_suite.pass  + i,
                               stat_suite.fail  + i,
                               stat_suite.total + i
                              );
        }
}




/*
 *      main() - main entry point of test runner
 */
int main(int argc, char **argv)
{
                /* initialise */
        log_init   (argc, argv);
        stat_init  ();
        suite_init ();

                /* execute */
        suite_exec ();
        stat_sum   ();
        log_sigma  ();

                /* terminate */
        log_term ();
        return 0;
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

