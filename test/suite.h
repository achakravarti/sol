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




        /* add header guard */
#if !defined __SOL_LIBRARY_TEST_SUITES
#define __SOL_LIBRARY_TEST_SUITES




        /* include required header files */
#include "../src/api.h"




        /*
         * __sol_tsuite_error() - test suite for exception handling module
         */
extern sol_erno __sol_tsuite_error(sol_tlog *log,
                                   sol_uint *pass,
                                   sol_uint *fail,
                                   sol_uint *total);




        /*
         * __sol_tsuite_test() - test suite for unit testing module
         */
extern sol_erno __sol_tsuite_test(sol_tlog *log,
                                  sol_uint *pass,
                                  sol_uint *fail,
                                  sol_uint *total);




        /*
         * __sol_tsuite_hint() - test suite for compiler hints module
         */
extern sol_erno __sol_tsuite_hint(sol_tlog *log,
                                  sol_uint *pass,
                                  sol_uint *fail,
                                  sol_uint *total);




        /*
         * __sol_tests_env() - test suite for environment module
         */
extern sol_erno __sol_tests_env(sol_tlog *log,
                                sol_uint *pass,
                                sol_uint *fail,
                                sol_uint *total);




        /*
         * __sol_tests_ptr() - test suite for the pointer module
         */
extern sol_erno __sol_tests_ptr(sol_tlog *log,
                                sol_uint *pass,
                                sol_uint *fail,
                                sol_uint *total);




        /*
         * __sol_tests_ptr2() - mock freestanding tests for the pointer module
         */
#if (SOL_ENV_HOSTED_NONE != sol_env_host())
        extern sol_erno __sol_tests_ptr2(sol_tlog *log,
                                         sol_uint *pass,
                                         sol_uint *fail,
                                         sol_uint *total);
#else
#       define __sol_tests_ptr2()
#endif




        /*
         * __sol_tests_log() - test suite for the logging module
         */
extern sol_erno __sol_tests_log(sol_tlog *log,
                                sol_uint *pass,
                                sol_uint *fail,
                                sol_uint *total);




        /*
         * __sol_tests_prim() - test suite for the primitives module
         */
extern sol_erno __sol_tests_prim(sol_tlog *log,
                                 sol_uint *pass,
                                 sol_uint *fail,
                                 sol_uint *total);




        /*
         * __sol_tests_elem_meta() - test suite for the element metadata
         * interface
         */
extern sol_erno __sol_tests_elem_meta(sol_tlog *log,
                                      sol_uint *pass,
                                      sol_uint *fail,
                                      sol_uint *total);




        /*
         * __sol_tests_elem() - test suite for the element interface
         */
extern sol_erno __sol_tests_elem(sol_tlog *log,
                                 sol_uint *pass,
                                 sol_uint *fail,
                                 sol_uint *total);




        /*
         * __sol_tests_suite() - test suite for the list interface
         */
extern sol_erno __sol_tests_list(sol_tlog *log,
                                 sol_uint *pass,
                                 sol_uint *fail,
                                 sol_uint *total);




#endif /* !defined __SOL_LIBRARY_TEST_SUITES */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

