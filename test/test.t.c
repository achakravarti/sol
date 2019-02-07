/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/test.t.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the unit testing module.
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


/*
 *      tlog_called - flag to indicate whether tlog_dummy has been called
 */
static int tlog_called = 0;


/*
 *      tcase_called - flag to indicate whether tcase_dummy has been called
 */
static int tcase_called = 0;


/*
 *      tlog_dummy() - dummy test suite logging callback
 *        - desc: test case description
 *        - erno: test case error code
 */
static void tlog_dummy(const char *desc,
                       const sol_erno erno)
{
                /* set tlog_called flag true if this callback has been called
                 * with the required params; @erno can't be 9999 as no error
                 * code has been defined by the exception handling module as
                 * such. */
        if (desc && *desc && erno != 9999) {
                tlog_called = 1;
        }
}


static sol_erno tcase_pass(void)
{
SOL_TRY:
                /* this is guaranteed to pass */
        sol_assert (1, SOL_ERNO_TEST);
        tcase_called = 1;

SOL_CATCH:
                /* control will never reach here */
        sol_throw();
}


/*
 *      init_01() - sol_tsuite_init() unit test #1
 */
static sol_erno init_01(void)
{
        #define INIT_01 "sol_tsuite_init() should throw SOL_ERNO_PTR when" \
                        " passed a null pointer for @tsuite"
SOL_TRY:
                /* sol_tsuite_init() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init(0));

SOL_CATCH:
                /* check test condition described by INIT_01 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      init2_01() - sol_tsuite_init2() unit test #1
 */
static sol_erno init2_01(void)
{
        #define INIT2_01 "sol_tsuite_init2() should throw SOL_ERNO_PTR when" \
                         " passed a null pointer for @tsuite"
SOL_TRY:
                /* sol_tsuite_init2() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(0, tlog_dummy));

SOL_CATCH:
                /* check test condition described by INIT2_01 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      init2_02() - sol_tsuite_init2() unit test #1
 */
static sol_erno init2_02(void)
{
        #define INIT2_02 "sol_tsuite_init2() should throw SOL_ERNO_PTR when" \
                         " passed a null pointer for @tlog"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_init2() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, 0));

SOL_CATCH:
                /* check test condition described by INIT2_02 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      register_01() - sol_tsuite_register() unit test #1
 */
static sol_erno register_01(void)
{
        #define REGISTER_01 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                            " when passed a null pointer for @tsuite"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_register(0, init_01, "Dummy"));

SOL_CATCH:
                /* check test condition described by REGISTER_01 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      register_02() - sol_tsuite_register() unit test #2
 */
static sol_erno register_02(void)
{
        #define REGISTER_02 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                            " when passed a null pointer for @tcase"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_register(&ts, 0, "Dummy"));

SOL_CATCH:
                /* check test condition described by REGISTER_02 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      register_03() - sol_tsuite_register() unit test #3
 */
static sol_erno register_03(void)
{
        #define REGISTER_03 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                            " when passed a null pointer for @desc"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_register(&ts, register_01, 0));

SOL_CATCH:
                /* check test condition described by REGISTER_03 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      register_04() - sol_tsuite_register() unit test #4
 */
static sol_erno register_04(void)
{
        #define REGISTER_04 "sol_tsuite_register() should throw SOL_ERNO_STR" \
                            " when passed an empty string for @desc"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_STR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_register(&ts, register_01, ""));

SOL_CATCH:
                /* check test condition described by REGISTER_04 */
        return SOL_ERNO_STR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      pass_01() - sol_tsuite_pass() unit test #1
 */
static sol_erno pass_01(void)
{
        #define PASS_01 "sol_tsuite_pass() should throw SOL_ERNO_PTR when" \
                        " passed a null pointer for @tsuite"
        auto sol_tsuite ts;
        auto int pass;

SOL_TRY:
                /* sol_tsuite_pass() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_pass(0, &pass));

SOL_CATCH:
                /* check test condition described by PASS_01 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      pass_02() - sol_tsuite_pass() unit test #2
 */
static sol_erno pass_02(void)
{
        #define PASS_02 "sol_tsuite_pass() should throw SOL_ERNO_PTR when" \
                        " passed a null pointer for @pass"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_pass() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_pass(&ts, 0));

SOL_CATCH:
                /* check test condition described by PASS_02 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      pass_03() - sol_tsuite_pass() unit test #3
 */
static sol_erno pass_03(void)
{
        #define PASS_03 "sol_tsuite_pass() should set an initial value of 0" \
                        " for the total number of passed test cases when"    \
                        " initialised through sol_tsuite_init()"
        auto sol_tsuite ts;
        auto int pass;

SOL_TRY:
                /* check test condition described by PASS_03 */
        sol_try (sol_tsuite_init(&ts));
        sol_try (sol_tsuite_pass(&ts, &pass));
        sol_assert (!pass, SOL_ERNO_TEST);

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw();
}


/*
 *      pass_04() - sol_tsuite_pass() unit test #4
 */
static sol_erno pass_04(void)
{
        #define PASS_04 "sol_tsuite_pass() should set an initial value of 0" \
                        " for the total number of passed test cases when"    \
                        " initialised through sol_tsuite_init2()"
        auto sol_tsuite ts;
        auto int pass;

SOL_TRY:
                /* check test condition described by PASS_04 */
        sol_try (sol_tsuite_init2(&ts, &tlog_dummy));
        sol_try (sol_tsuite_pass(&ts, &pass));
        sol_assert (!pass, SOL_ERNO_TEST );

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw();
}


/*
 *      fail_01() - sol_tsuite_fail() unit test #1
 */
static sol_erno fail_01(void)
{
        #define FAIL_01 "sol_tsuite_fail() should throw SOL_ERNO_PTR when" \
                        " passed a null pointer for @tsuite"
        auto sol_tsuite ts;
        auto int fail;

SOL_TRY:
                /* sol_tsuite_fail() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_fail(0, &fail));

SOL_CATCH:
                /* check test condition described by FAIL_01 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      fail_02() - sol_tsuite_fail() unit test #2
 */
static sol_erno fail_02(void)
{
        #define FAIL_02 "sol_tsuite_fail() should throw SOL_ERNO_PTR when" \
                        " passed a null pointer for @fail"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_fail() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_fail(&ts, 0));

SOL_CATCH:
                /* check test condition described by FAIL_02 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      fail_03() - sol_tsuite_fail() unit test #3
 */
static sol_erno fail_03(void)
{
        #define FAIL_03 "sol_tsuite_fail() should set an initial value of 0" \
                        " for the total number of failed test cases when"    \
                        " initialised through sol_tsuite_init()"
        auto sol_tsuite ts;
        auto int fail;

SOL_TRY:
                /* check test condition described by PASS_03 */
        sol_try (sol_tsuite_init(&ts));
        sol_try (sol_tsuite_pass(&ts, &fail));
        sol_assert (!fail, SOL_ERNO_TEST);

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw();
}


/*
 *      fail_04() - sol_tsuite_fail() unit test #4
 */
static sol_erno fail_04(void)
{
        #define FAIL_04 "sol_tsuite_fail() should set an initial value of 0" \
                        " for the total number of failed test cases when"    \
                        " initialised through sol_tsuite_init2()"
        auto sol_tsuite ts;
        auto int fail;

SOL_TRY:
                /* check test condition described by FAIL_04 */
        sol_try (sol_tsuite_init2(&ts, &tlog_dummy));
        sol_try (sol_tsuite_fail(&ts, &fail));
        sol_assert (!fail, SOL_ERNO_TEST);

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw();
}


/*
 *      total_01() - sol_tsuite_total() unit test #1
 */
static sol_erno total_01(void)
{
        #define TOTAL_01 "sol_tsuite_total() should throw SOL_ERNO_PTR when" \
                         " passed a null pointer for @tsuite"
        auto sol_tsuite ts;
        auto int total;

SOL_TRY:
                /* sol_tsuite_total() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_total(0, &total));

SOL_CATCH:
                /* check test condition described by TOTAL_01 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      total_02() - sol_tsuite_total() unit test #2
 */
static sol_erno total_02(void)
{
        #define TOTAL_02 "sol_tsuite_total() should throw SOL_ERNO_PTR when" \
                         " passed a null pointer for @total"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_fail() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_total(&ts, 0));

SOL_CATCH:
                /* check test condition described by TOTAL_02 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      exec_01() - sol_tsuite_exec() unit test #1
 */
static sol_erno exec_01(void)
{
        #define EXEC_01 "sol_tsuite_exec() should throw SOL_ERNO_PTR when" \
                        " passed a null pointer for @tsuite"
        auto sol_tsuite ts;

SOL_TRY:
                /* sol_tsuite_exec() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_exec(0));

SOL_CATCH:
                /* check test condition described by EXEC_01 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      test_exec_02() - sol_tsuite_exec() unit test #2
 */
static sol_erno exec_02(void)
{
        #define EXEC_02 "sol_tsuite_exec() should call the test logging" \
                        " callback if @tsuite has been initialised with" \
                        " sol_tsuite_init2()"
        auto sol_tsuite ts;

SOL_TRY:
                /* initialise test suite */
        sol_try (sol_tsuite_init2(&ts, tlog_dummy));
        sol_try (sol_tsuite_register(&ts, tcase_pass, "TCASE_PASS"));

                /* sol_tsuite_exec() should call tlog_dummy */
        tlog_called = 0;
        sol_try (sol_tsuite_exec(&ts));
        sol_assert (1 == tlog_called, SOL_ERNO_TEST);

SOL_CATCH:
                /* check test condition described by EXEC_02 */
        return SOL_ERNO_PTR == sol_erno_now()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}


/*
 *      __sol_tsuite_test() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tsuite_test(sol_tlog *log,
                                  int *pass,
                                  int *fail,
                                  int *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* initialise test suite */
        sol_try (sol_tsuite_init2(ts, log));

                /* register test cases */
        sol_try (sol_tsuite_register(ts, init_01, INIT_01));
        sol_try (sol_tsuite_register(ts, init2_01, INIT2_01));
        sol_try (sol_tsuite_register(ts, init2_02, INIT2_02));
        sol_try (sol_tsuite_register(ts, register_01, REGISTER_01));
        sol_try (sol_tsuite_register(ts, register_02, REGISTER_02));
        sol_try (sol_tsuite_register(ts, register_03, REGISTER_03));
        sol_try (sol_tsuite_register(ts, register_04, REGISTER_04));
        sol_try (sol_tsuite_register(ts, pass_01, PASS_01));
        sol_try (sol_tsuite_register(ts, pass_02, PASS_02));
        sol_try (sol_tsuite_register(ts, pass_03, PASS_03));
        sol_try (sol_tsuite_register(ts, pass_04, PASS_04));
        sol_try (sol_tsuite_register(ts, fail_01, FAIL_01));
        sol_try (sol_tsuite_register(ts, fail_02, FAIL_02));
        sol_try (sol_tsuite_register(ts, fail_03, FAIL_03));
        sol_try (sol_tsuite_register(ts, fail_04, FAIL_04));
        sol_try (sol_tsuite_register(ts, total_01, TOTAL_01));
        sol_try (sol_tsuite_register(ts, total_02, TOTAL_02));
        sol_try (sol_tsuite_register(ts, exec_01, EXEC_01));
        sol_try (sol_tsuite_register(ts, exec_02, EXEC_02));

                /* execute test cases */
        sol_try (sol_tsuite_exec (ts));

                /* return test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

                /* wind up */
        sol_tsuite_term(ts);

SOL_CATCH:
                /* wind up and throw current exception, if any */
        sol_tsuite_term(ts);
        sol_throw();
}


/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

