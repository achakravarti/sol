/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/test.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the unit testing module.
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




#if !defined __SOL_UNIT_TESTING_MODULE
#define __SOL_UNIT_TESTING_MODULE




#include "./error.h"




/*
 *      SOL_ERNO_TEST - unit testing module error
 *
 *      The SOL_ERNO_TEST error code indicates that an error has occured with
 *      the unit testing module while calling one of its interface functions.
 *      Note the this error code is **not** used to indicate a unit test that
 *      has failed, as it would have been successfully executed as far as the
 *      module interface is concerned.
 */
#define SOL_ERNO_TEST -1




/*
 *      sol_test_unit - unit test callback
 *
 *      The sol_test_unit callback function defines the unit test that is to be
 *      executed by the unit testing module of the Sol Library. The unit test
 *      callback is defined by the client code, and executed through the
 *      sol_test_exec() function declared below.
 *
 *      The unit test callback is expected to return an error code indicating
 *      whether or not the test passed. The callback must return a non-zero
 *      error code (except those reserved by the Sol Library) to indicate that
 *      the unit test has failed.
 *
 *      Return:
 *        - 0 if the unit test passes
 *        - Non-zero if the unit test fails
 */
typedef int
(sol_test_unit)(void);




/*
 *      sol_test_log - test logging callback
 *        - desc: unit test description
 *        - erno: error code returned by unit test
 *
 *      The sol_test_log callback function defines the logging mechanism that is
 *      to be used by the unit testing module to log the results of the unit
 *      tests executed through sol_test_exec().
 *
 *      The sol_test_log callback is defined by client code, and plugged in to
 *      the unit testing module through the sol_test_init2() function. If this
 *      callback function is available to the unit testing module, it will be
 *      passed the description @desc of the unit test, and the error code @erno
 *      returned by the unit test.
 */
typedef void
(sol_test_log)(char const *desc,
               int  const erno
              );




typedef struct __sol_test {
        int          pass;
        int          fail;
        sol_test_log *lcbk;
} sol_test;




/*
 *      sol_test_init() - sets up unit testing module
 *
 *      The sol_test_init() interface function initialises the unit testing
 *      module to its default state. This function **must** be called before
 *      calling any of the other interface functions of this module, other than
 *      the overloaded sol_test_init2() function.
 *
 *      This function initialises the unit testing module without hooking up a
 *      logging callback function, and so is suitable for use in freestanding
 *      environments, or in situations where logging of the unit tests is not
 *      required. If logging of the unit test results is required, then the
 *      overloaded version sol_test_init2() should be used instead.
 *
 *      Return:
 *        - 0 if no error occurs
 *        - SOL_ERNO_TEST if an error occurs
 */
extern sol_erno
sol_test_init(sol_test *ctx);




/*
 *      sol_test_init2() - sets up unit testing module
 *        - path: path to log file
 *        - cbk : logging callback
 *
 *      The sol_test_init2() interface function is the overloaded form of the
 *      sol_test_init() function declared above. This function, like its
 *      original form, initialises the unit testing module, but additionally
 *      hooks up a callback function @cbk that is used to log the unit test
 *      results to a file at a given location @path.
 *
 *      Both @path and @cbk are required to be valid pointers, and @path is
 *      additionally required to be a non-null string. However, if these
 *      conditions are not met, then a safe no-op occurs.
 *
 *      Return:
 *        - 0 if no error occurs
 *        - SOL_ERNO_TEST if an error occurs
 */
extern sol_erno
sol_test_init2(sol_test           *ctx,
               sol_test_log const *lcbk
              );




/*
 *      sol_test_exit() - tears down unit testing module
 *
 *      The sol_test_exit() interface function winds up the unit testing module.
 *      This function is expected to be called once all unit tests have been
 *      completed and the unit testing module is no longer required by client
 *      code.
 */
extern void
sol_test_term(sol_test *ctx);




/*
 *      sol_test_pass() - gets passed unit test count
 *        - pass: count of passed unit tests
 *
 *      The sol_test_pass() interface function returns the number of unit tests
 *      that have been successfully executed through the sol_test_exec()
 *      interface function.
 *
 *      The count of successful unit tests is returned through @pass, which is
 *      required to be a valid pointer. Furthermore, the unit testing module
 *      must have been first initialised by a call to either sol_test_init() or
 *      sol_test_init2().
 *
 *      Return:
 *        - 0 if no error occurs
 *        - SOL_ERNO_TEST if an error occurs
 */
extern sol_erno
sol_test_pass(sol_test const *ctx,
              int            *pass
             );




/*
 *      sol_test_fail() - gets failed unit test count
 *        - fail: count of failed unit tests
 *
 *      The sol_test_fail() interface function returns the number of unit tests
 *      that have **not** been successfully executed through the sol_test_exec()
 *      interface function.
 *
 *      The count of unsuccessful unit tests is returned through @fail, which is
 *      expected to be a valid pointer. Furthermore, the unit testing module
 *      must have been first initialised by a call to either sol_test_init() or
 *      sol_test_init2().
 *
 *      Return:
 *        - 0 if no error occurs
 *        - SOL_ERNO_TEST if an error occurs
 */
extern sol_erno
sol_test_fail(sol_test const *ctx,
              int            *fail
             );




/*
 *      sol_test_exec() - executes unit test
 *        - desc: unit test description
 *        - cbk : unit test callback
 *
 *      The sol_test_exec() function executes a unit test defined by client code
 *      through a callback function @cbk with a given description @desc. If the
 *      unit testing module has been initialised with a logging callback through
 *      sol_test_init2(), then this function also logs the result of the unit
 *      test defined by @cbk.
 *
 *      Both @desc and @cbk are required to be valid pointers; additionally,
 *      @desc is required to be a non-null string. If either of these conditions
 *      is not met, then an exception is thrown.
 *
 *      Return:
 *        - 0 if the unit test passes
 *        - SOL_ERNO_TEST if an error occurs on executing the unit test
 *        - An contextual error code if the unit test fails
 */
extern sol_erno
sol_test_exec(sol_test            *ctx,
              char          const *desc,
              sol_test_unit const *cbk
             );




#endif /* !defined __SOL_UNIT_TESTING_MODULE  */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

