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
 *      SOL_TSUITE_MAXTCASE - maximum number of test cases in a test suite
 *
 *      The SOL_TSUITE_MAXTCASE symbolic constant defines the maxiumum number of
 *      test cases that can be registered in one test suite. The cap limit of
 *      128 test cases is expected to be more than adequate for most situations.
 */
#define SOL_TSUITE_MAXTCASE 128




/*
 *      SOL_TCASE_MAXDESCLEN - maximum length of test case description
 *
 *      The SOL_TCASE_MAXDESCLEN symbolic constant defines the maximum length of
 *      the description for a test case. The limit of 128 characters (including
 *      the terminating null character) should be adequate for most situations.
 */
#define SOL_TCASE_MAXDESCLEN 128




/*
 *      sol_tcase - test case callback
 *
 *      The sol_tcase callback function defines a test case that may be executed
 *      as part of a test suite abstracted by the sol_tsuite type defined below.
 *      The test case callback is defined by client code, and needs to be
 *      registered with a test suite through the sol_tsuite_register() function
 *      in order to be executed. The test case callback is required to return an
 *      error code indicating whether or not it passed.
 *
 *      Return:
 *        - SOL_ERNO_NULL if the test case passes
 *        - A context-sensitive error code if the test case fails
 */
typedef sol_erno (sol_tcase)(void);




/*
 *      sol_tlog - test suite logging callback
 *        - desc: unit test description
 *        - erno: error code returned by a test case
 *
 *      The sol_tlog callback function defines the logging mechanism that is to
 *      be used by a sol_tsuite test suite to log the results of its registered
 *      test cases when they are executed through sol_tsuite_exec().
 *
 *      The sol_tlog callback is defined by client code, and plugged into a test
 *      suite through the sol_tsuite_init2() function. If this callback function
 *      is available to a test suite, it will be passed the description @desc of
 *      each test case executed, along with the error code @erno returned by the
 *      test case.
 */
typedef void (sol_tlog)(const char *desc,
                        sol_erno erno);




/*
 *      sol_tsuite - test suite
 *
 *      The sol_tsuite type abstracts a test suite. A test suite is a collection
 *      of related test cases, each of which is defined by a sol_tcase callback
 *      function.
 *
 *      Although the sol_tsuite type is defined as a transparent type so that it
 *      has no dependence on heap memory interfaces (which may not be available
 *      in freestanding environments), it should be treated as an opaque type,
 *      and unsed only through its interface functions declared below.
 */
typedef struct __sol_tsuite {
        int total;
        int fail;
        char desc[SOL_TSUITE_MAXTCASE][SOL_TCASE_MAXDESCLEN];
        sol_tcase *tcase[SOL_TSUITE_MAXTCASE];
        sol_tlog *tlog;
} sol_tsuite;




/*
 *      sol_tsuite_init() - initialises test suite
 *        - tsuite: contextual test suite
 *
 *      The sol_tsuite_init() interface function initialises a test suite
 *      @tsuite to its default state. This function **must** be called before
 *      calling any of the other interface functions of sol_tsuite, other than
 *      the overloaded sol_tsuite_init2() function.
 *
 *      This function initialises @tsuite without hooking up a logging callback
 *      function, and so is suitable for use in freestanding environments, or in
 *      situations where logging of the unit tests is not required. If logging
 *      of the test cases is required, then the overloaded version
 *      sol_tsuite_init2() should be used instead.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed
 */
extern sol_erno sol_tsuite_init(sol_tsuite *tsuite);




/*
 *      sol_tsuite_init2() - initialises test suite
 *        - tsuite: contextual test suite
 *        - tlog: test logging callback
 *
 *     The sol_tsuite_init2() interface function is the overloaded form of the
 *     sol_tsuite_init() function declared above. This function, like its
 *     original form, intialises a test suite instance @tsuite, but additionally
 *     hooks up a callback function @tlog that is used to log the test case
 *     results. This function **must** be called before any of the other
 *     sol_tsuite interface functions are invoked on @tsuite, apart from
 *     sol_tsuite_init().
 *
 *     Both @tsuite and @tlog are required to be valid pointers; otherwise, an
 *     exception is thrown.
 *
 *     Return:
 *       - SOL_ERNO_NULL if no error occurs
 *       - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_init2(sol_tsuite *tsuite,
                                 sol_tlog *tlog);




/*
 *      sol_tsuite_term() - terminates a test suite
 *        - tsuite: contextual test suite
 *
 *      The sol_tsuite_term() interface function terminates a test suite
 *      instance @tsuite that was earlier initialised by a call to either
 *      sol_tsuite_init() or sol_tsuite_init2(). Although this function expects
 *      @tsuite to be a valid pointer, a safe no-op occurs if this condition is
 *      not satisfied.
 */
extern void sol_tsuite_term(sol_tsuite *tsuite);




/*
 *      sol_tsuite_register() - registers a test case
 *        - tsuite: contextual test suite
 *        - tcase: test case to register
 *        - desc: test case description
 *
 *     The sol_tsuite_register() interface function registers a test case @tcase
 *     described by @desc with a test suite @tsuite. A test case must first be
 *     registered as part of a test suite before it can be executed. This
 *     function allows a maximum of SOL_TSUITE_MAXTCASE test cases to be
 *     registered with @tsuite, and automatically truncates the length of @desc
 *     to SOL_TCASE_MAXDESCLEN characters if required.
 *
 *     @tsuite, @tcase, and @desc must all be valid pointers, and additionally
 *     @desc must be a non-null string; if any of these conditions is not met,
 *     then an exception is thrown.
 *
 *     Return:
 *       - SOL_ERNO_NULL if no error occurs
 *       - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 *       - SOL_ERNO_STR if @desc is a null string
 *       - SOL_ERNO_RANGE if the limit of registered test cases is exceeded
 */
extern sol_erno sol_tsuite_register(sol_tsuite *tsuite,
                                    sol_tcase *tcase,
                                    const char *desc);




/*
 *      sol_tsuite_pass() - count of passed test cases
 *        - tsuite: contextual test suite
 *        - pass: count of passed test cases
 *
 *      The sol_tsuite_pass() interface function returns the number of test
 *      cases @pass of a test suite @tsuite that have been successfully run
 *      through the sol_tsuite_exec() interface function.
 *
 *      Both @tsuite and @pass are required to be valid pointers, or else an
 *      exception is thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_pass(const sol_tsuite *tsuite,
                                int *pass);




/*
 *      sol_tsuite_fail() - count of failed test cases
 *        - tsuite: contextual test suite
 *        - fail: count of failed test cases
 *
 *      The sol_tsuite_fail() interface function returns the number of test
 *      cases @fail of a test suite @tsuite that have failed when executed
 *      through the sol_tsuite_exec() interface function.
 *
 *      Both @tsuite @fail are required to be valid pointers, or else an
 *      exception is thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_fail(const sol_tsuite *tsuite,
                                int *fail);




/*
 *      sol_tsuite_total() - count of total test cases
 *        - tsuite: contextual test suite
 *        - total: count of total test cases
 *
 *      The sol_tsuite_total() interface function returns the total number of
 *      test cases @total registered with a test suite @tsuite.
 *
 *      Both @tsuite and @total are required to be valid pointers, or else an
 *      exception is thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_total(const sol_tsuite *tsuite,
                                 int *total);




/*
 *      sol_tsuite_exec() - executes registered test cases
 *        - tsuite: contextual test suite
 *
 *      The sol_tsuite_exec() interface function sequentially executes all the
 *      test cases registered with a test suite @tsuite. If @tsuite had been
 *      hooked to a logging callback at the time of initialisation through
 *      sol_tsuite_init2(), then this function also logs the result of each test
 *      case executed.
 *
 *      @tsuite is required to be a valid pointer, or else an exception is
 *      thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid argument is passed
 */
extern sol_erno sol_tsuite_exec(sol_tsuite *tsuite);




#endif /* !defined __SOL_UNIT_TESTING_MODULE  */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

