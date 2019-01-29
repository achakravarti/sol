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
 *      (c) 2018 Abhishek Chakravarti
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
 *      unit_pass - passed unit test counter
 *
 *      The unit_pass global variable keeps track of the number of unit tests
 *      that have been successfully executed. It is initialised to zero since no
 *      unit tests have been executed on initalisation of the unit testing
 *      module. This variable is related to the unit_fail global declared below.
 */
static int unit_pass = 0;




/*
 *      unit_fail - failed unit test counter
 *
 *      The unit_fail global variable, similar to the unit_pass global declared
 *      above, keeps track of the the number of unit tests that did **not**
 *      pass. It is also initialised to zero as no unit tests have been executed
 *      at the time of initialising the unit testing module.
 */
static int unit_fail = 0;




/*
 *      LOG_MAXPATHLEN - maximum length of log path
 *
 *      The LOG_MAXPATHLEN symbolic constant defines the maximum number of
 *      characters that are assumed to be in the log file path. I think it's
 *      safe to assume that a maximum length of 256 characters should be more
 *      than adequate for all use cases.
 */
#define LOG_MAXPATHLEN 256




/*
 *      log_path - path to log file
 *
 *      The log_path global variable is a buffer to hold the path to the file
 *      which will be used to log the results of the executed unit tests. The
 *      length of the log_path variable is set to the LOG_MAXPATHLEN symbolic
 *      constant defined above.
 */
static char log_path [LOG_MAXPATHLEN];




/*
 *      log_cbk - logging callback
 *
 *      The log_cbk global variable points to the callback function used to log
 *      the test results for each unit test that is executed.
 */
static sol_test_log *log_cbk;




/*
 *      unit_init() - initialises unit test globals
 *
 *      The unit_init() utility function initialises the the unit test globals
 *      to their default value of zero. When the unit testing module is started,
 *      no unit tests have been executed, so it makes sense to set the test
 *      counters to zero.
 */
static inline void
unit_init(void)
{
        unit_pass = 0;
        unit_fail = 0;
}




/*
 *      log_init() - initialises logging globals
 *        - path: path to log file
 *        - cbk : logging callback
 *
 *      The log_init() utility function initialises the logging global
 *      variables. It does so by assigning these variables the arguments passed
 *      through its parameters @path and @cbk. @path is copied on to the log
 *      file path global using the standard strcpy() algorithm. We're not calling
 *      strcpy() directly as we would have to include the standard <string.h>
 *      header file which isn't available in freestanding environments.
 *
 *      This function assumes that both @path and @cbk are valid, leaving it up
 *      to the calling function to ensure that this is so.
 */
static inline void
log_init(char         const *path,
         sol_test_log const *cbk
        )
{
        register char *itr;

        log_cbk = cbk;

        itr = log_path;
        while ((*itr++ = *path++));
}




/*
 *      sol_test_init() - declared in sol/inc/test.h
 *
 *      The sol_test_init() interface function needs only to initialise the unit
 *      test counters; it does so by calling the unit_init() utility function.
 */
extern void
sol_test_init(void)
{
        unit_init();
}




/*
 *      sol_test_init2() - declared in sol/inc/test.h
 *
 *      The sol_test_init2() interface function needs to initialise both the
 *      unit test counters and the logging global variables through the
 *      unit_init() and log_init() utility functions respectively. The logging
 *      variables are initialised only if the arguments to the parameters @path
 *      and @cbk are valid.
 */
extern void
sol_test_init2(char         const *path,
               sol_test_log const *cbk
              )
{
        unit_init ();

        if (cbk && path && *path)
                log_init (path, cbk);
}




/*
 *      sol_test_exit() - declared in sol/inc/test.h
 *
 *      The sol_test_exit() interface function works by returning the unit test
 *      counters through @pass and @fail.
 */
extern void
sol_test_exit(int *pass,
              int *fail
             )
{
        *pass = unit_pass;
        *fail = unit_fail;
}




/*
 *      sol_test_exec() - declared in sol/inc/test.h
 *
 *      The sol_test_exec() interface function runs the unit test @cbk, updating
 *      the appropriate test counter depending on whether @cbk passed or failed.
 *      Furthermore, the test result is logged by calling the logging callback
 *      function (if it's available). Both @desc and @cbk are checked for
 *      validity at the outset.
 */
extern int
sol_test_exec(char          const *desc,
              sol_test_unit const *cbk
             )
{
        auto int erno;

        if (!(cbk && desc && *desc))
                return -1;

        if ((erno = cbk ()))
                unit_fail ++;
        else
                unit_pass ++;

        if (log_cbk)
                log_cbk (desc, erno);

        return erno;
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

