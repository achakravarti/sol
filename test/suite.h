/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/suite.h
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It declares the test suites for all the component modules.
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




#if !defined __SOL_LIBRARY_TEST_SUITES
#define __SOL_LIBRARY_TEST_SUITES


#include "../inc/test.h"


/*
 *      __sol_tsuite_error() - test suite for exception handling module
 */
extern sol_erno __sol_tsuite_error(sol_tlog *log,
                                   int *pass,
                                   int *fail,
                                   int *total);


/*
 *      __sol_tsuite_test() - test suite for unit testing module
 */
extern sol_erno __sol_tsuite_test(sol_tlog *log,
                                  int *pass,
                                  int *fail,
                                  int *total);


/*
 *      __sol_tsuite_hint() - test suite for compiler hints module
 */
extern sol_erno __sol_tsuite_hint(sol_tlog *log,
                                  int *pass,
                                  int *fail,
                                  int *total);




/*
 *      __sol_tests_env() - test suite for environment module
 */
extern sol_erno __sol_tests_env(sol_tlog *log,
                                int *pass,
                                int *fail,
                                int *total);




#endif /* !defined __SOL_LIBRARY_TEST_SUITES */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

