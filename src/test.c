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




static void
tsuite_init(sol_tsuite       *tsuite,
            sol_tlog   const *tlog
           )
{
        register int i;

        tsuite->total = 0;
        tsuite->fail  = 0;
        tsuite->tlog  = tlog;

        for (i = 0; i < SOL_TSUITE_MAXTCASE; i++) {
                *tsuite->desc [i] = '\0';
                tsuite->tcase [i] = 0;
        }
}



/*
 *      sol_test_init() - declared in sol/inc/test.h
 *
 *      The sol_test_init() interface function needs only to initialise the unit
 *      test counters; it does so by calling the unit_init() utility function.
 *      It also sets the mod_init flag to 1 to indicate that unit testing module
 *      has been intialised.
 *
 *      The sol_test_init() function can't fail, so it always returns 0 to
 *      indicate that no error has occured.
 */
extern sol_erno
sol_tsuite_init(sol_tsuite *tsuite)
{
SOL_TRY:
        sol_assert (tsuite, SOL_ERNO_TEST);

        tsuite_init (tsuite, 0);

SOL_CATCH:
        sol_throw ();
}




/*
 *      sol_test_init2() - declared in sol/inc/test.h
 *
 *      The sol_test_init2() interface function needs to initialise both the
 *      unit test counters and the logging global variables through the
 *      unit_init() and log_init() utility functions respectively. The logging
 *      variables are initialised only if the arguments to the parameters @path
 *      and @cbk are valid. Once initialisation is complete, the mod_init flag
 *      is set to 1 to indicate that the unit testing module has been set up.
 */
extern sol_erno
sol_tsuite_init2(sol_tsuite       *tsuite,
                 sol_tlog   const *tlog
                )
{
SOL_TRY:
        sol_assert (tsuite && tlog, SOL_ERNO_TEST);

        tsuite_init (tsuite, tlog);

SOL_CATCH:
        sol_throw ();
}




/*
 *      sol_test_exit() - declared in sol/inc/test.h
 *
 *      The sol_test_exit() interface function resets the unit test counters to
 *      their default value, and sets the internal module initialisation flag to
 *      0 to indicate that unit testing module has been torn down.
 *
 *      This isn't  strictly necessary, but doing so keeps the internal state of
 *      the unit  testing module clean, and ensures that the other interface
 *      functions can't be called without first re-initialising the module.
 */
extern void
sol_tsuite_term(sol_tsuite *tsuite)
{
        if (tsuite)
                tsuite_init (tsuite, 0);
}




extern sol_erno
sol_tsuite_register(sol_tsuite       *tsuite,
                    sol_tcase  const *tcase,
                    char       const *desc
                   )
{
        register char *itr;
        auto     int  len;

SOL_TRY:
        sol_assert (tsuite && tcase && desc && *desc, SOL_ERNO_TEST);
        sol_assert (tsuite->total <= SOL_TSUITE_MAXTCASE, SOL_ERNO_TEST);

        tsuite->tcase [tsuite->total] = tcase;

        itr = tsuite->desc [tsuite -> total];
        len = SOL_TCASE_MAXDESCLEN;
        while (len-- && (*itr++ = *desc++));

        tsuite->total++;

SOL_CATCH:
        sol_throw ();
}




/*
 *      sol_test_pass() - declared in sol/inc/test.h
 *
 *      The sol_test_pass() interface function returns the unit test pass
 *      counter through @pass after checking whether the unit testing module has
 *      been initialised and if @pass is valid.
 */
extern sol_erno
sol_tsuite_pass(sol_tsuite const *tsuite,
                int              *pass
               )
{
SOL_TRY:
        sol_assert (tsuite && pass, SOL_ERNO_TEST);

        *pass = tsuite->total - tsuite->fail;

SOL_CATCH:
        sol_throw ();
}




/*
 *      sol_test_fail() - declared in sol/inc/test.h
 *
 *      The sol_test_fail() interface function returns the unit test fail
 *      counter through @fail after checking whether the unit testing module has
 *      been initialised and if @fail is valid.
 */
extern sol_erno
sol_tsuite_fail(sol_tsuite const *tsuite,
                int              *fail
               )
{
SOL_TRY:
        sol_assert (tsuite && fail, SOL_ERNO_TEST);

        *fail = tsuite->fail;

SOL_CATCH:
        sol_throw ();
}




extern sol_erno
sol_tsuite_total(sol_tsuite const *tsuite,
                 int              *total
                )
{
SOL_TRY:
        sol_assert (tsuite && total, SOL_ERNO_TEST);

        *total = tsuite->total;

SOL_CATCH:
        sol_throw ();
}




/*
 *      sol_test_exec() - declared in sol/inc/test.h
 *
 *      The sol_test_exec() interface function runs the unit test @cbk, updating
 *      the appropriate test counter depending on whether @cbk passed or failed.
 *      Furthermore, the test result is logged by calling the logging callback
 *      function (if it's available). At the outset, this function checks  if
 *      the unit testing module has been intialised, and whether the arguments
 *      for @desc and @cbk are valid.
 */
extern sol_erno
sol_tsuite_exec(sol_tsuite *tsuite)
{
        register int      i;
        auto     sol_erno erno;

SOL_TRY:
        sol_assert (tsuite, SOL_ERNO_TEST);

        tsuite->fail = 0;

        for (i = 0; i < tsuite->total; i++) {
                if ((erno = tsuite->tcase [i] ()))
                        tsuite->fail++;

                if (tsuite->tlog)
                        tsuite->tlog (tsuite->desc [i], erno);
        }

SOL_CATCH:
        sol_throw ();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

