/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-test.c
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




        /* include required header files */
#include "./suite.h"




/*
 *      flag_log - flag to indicate whether mock_log has been called
 */
static int flag_log = 0;




/*
 *      flag_tcase - flag to indicate whether tcase_dummy has been called
 */
static int flag_tcase = 0;




/*
 *      mock_log() - mocks test suite logging callback
 *        - desc: test case description
 *        - erno: test case error code
 */
static void mock_log(const char *desc,
                     const sol_erno erno)
{
                /* set flag_log flag true if this callback has been called
                 * with the required params; @erno can't be 9999 as no error
                 * code has been defined by the exception handling module as
                 * such. */
        if (desc && *desc && erno != 9999) {
                flag_log = 1;
        }
}




/*
 *      mock_pass() - mocks a passing test case
 */
static sol_erno mock_pass(void)
{
SOL_TRY:
                /* this is guaranteed to pass */
        sol_assert (1, SOL_ERNO_TEST);
        flag_tcase = 1;

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      mock_fail() - mocks a failing test case
 */
static sol_erno mock_fail(void)
{
SOL_TRY:
                /* this is guaranteed to fail */
        sol_assert (0, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        flag_tcase = 1;
        return sol_erno_get();
}




/*
 *      test_init1() - sol_tsuite_init() unit test #1
 */
static sol_erno test_init1(void)
{
        #define DESC_INIT1 "sol_tsuite_init() throws SOL_ERNO_PTR when passed" \
                           " a null pointer for @tsuite"
SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init(0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_init2() - sol_tsuite_init2() unit test #1
 */
static sol_erno test_init2(void)
{
        #define DESC_INIT2 "sol_tsuite_init2() throws SOL_ERNO_PTR when" \
                           " passed a null pointer for @tsuite"
SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(0, mock_log));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_init3() - sol_tsuite_init2() unit test #1
 */
static sol_erno test_init3(void)
{
        #define DESC_INIT3 "sol_tsuite_init2() throws SOL_ERNO_PTR when" \
                           " passed a null pointer for @tlog"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, 0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_register1() - sol_tsuite_register() unit test #1
 */
static sol_erno test_register1(void)
{
        #define DESC_REGISTER1 "sol_tsuite_register() throws SOL_ERNO_PTR" \
                               " when passed a null pointer for @tsuite"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_register(0, test_init1, "Dummy"));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_register2() - sol_tsuite_register() unit test #2
 */
static sol_erno test_register2(void)
{
        #define DESC_REGISTER2 "sol_tsuite_register() throws SOL_ERNO_PTR" \
                               " when passed a null pointer for @tcase"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_register(&ts, 0, "Dummy"));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_register3() - sol_tsuite_register() unit test #3
 */
static sol_erno test_register3(void)
{
        #define DESC_REGISTER3 "sol_tsuite_register() throws SOL_ERNO_PTR" \
                               " when passed a null pointer for @desc"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_register(&ts, &mock_pass, 0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_register4() - sol_tsuite_register() unit test #4
 */
static sol_erno test_register4(void)
{
        #define DESC_REGISTER4 "sol_tsuite_register() throws SOL_ERNO_STR" \
                               " when passed an empty string for @desc"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_register(&ts, &mock_pass, ""));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_STR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_register5() - sol_tsuite_register() unit test #5
 */
static sol_erno test_register5(void)
{
        #define DESC_REGISTER5 "sol_tsuite_register() truncates @desc down to" \
                                "SOL_TCASE_MAXDESCLEN if required"
        const char *desc = "This is a very long string that should be truncated"
                           " down to a maximum length defined by the symbolic"
                           " constant SOL_TCASE_MAXDESCLEN. This symbolic"
                           " constant is defined in the sol/inc/test.h header"
                           " file. This description in itself is greater than"
                           " the length limited by the SOL_TCASE_MAXDESCLEN"
                           " symbolic constant";
        register sol_size len = 0;
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, mock_log));
        sol_try (sol_tsuite_register(ts, &mock_pass, desc));
        while (ts->desc[0][len++]); /* NOLINT */

                /* check test condition; len is off by 1 */
        sol_assert (len - 1 <= SOL_TCASE_MAXDESCLEN, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_pass1() - sol_tsuite_pass() unit test #1
 */
static sol_erno test_pass1(void)
{
        #define DESC_PASS1 "sol_tsuite_pass() throws SOL_ERNO_PTR when passed" \
                           " a null pointer for @tsuite"
        auto sol_tsuite ts;
        auto sol_uint pass;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_pass(0, &pass));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_pass2() - sol_tsuite_pass() unit test #2
 */
static sol_erno test_pass2(void)
{
        #define DESC_PASS2 "sol_tsuite_pass() throws SOL_ERNO_PTR when passed" \
                           " a null pointer for @pass"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_pass(&ts, 0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_pass3() - sol_tsuite_pass() unit test #3
 */
static sol_erno test_pass3(void)
{
        #define DESC_PASS3 "sol_tsuite_pass() reports 0 for the number of" \
                           " passed test cases if @tsuite has been "       \
                           " initialised by sol_tsuite_init()"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint pass;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init(ts));
        sol_try (sol_tsuite_pass(ts, &pass));

                /* check test condition */
        sol_assert (!pass, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_pass4() - sol_tsuite_pass() unit test #4
 */
static sol_erno test_pass4(void)
{
        #define DESC_PASS4 "sol_tsuite_pass() reports 0 for the number of" \
                           " passed test cases if @tsuite has been"        \
                           " initialised by sol_tsuite_init2()"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint pass;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, &mock_log));
        sol_try (sol_tsuite_pass(ts, &pass));

                /* check test condition */
        sol_assert (!pass, SOL_ERNO_TEST );

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_pass5() - sol_tsuite_pass() unit test #5
 */
static sol_erno test_pass5(void)
{
        #define DESC_PASS5 "sol_tsuite_pass() reports the correct number of" \
                           " passed test cases"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint pass;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, &mock_log));
        sol_try (sol_tsuite_register(ts, &mock_pass, "Pass"));
        sol_try (sol_tsuite_register(ts, &mock_fail, "Fail"));
        sol_try (sol_tsuite_exec(ts));
        sol_try (sol_tsuite_pass(ts, &pass));

                /* check test condition */
        sol_assert (1 == pass, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_fail1() - sol_tsuite_fail() unit test #1
 */
static sol_erno test_fail1(void)
{
        #define DESC_FAIL1 "sol_tsuite_fail() throws SOL_ERNO_PTR when passed" \
                           " a null pointer for @tsuite"
        auto sol_tsuite ts;
        auto sol_uint fail;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_fail(0, &fail));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_fail2() - sol_tsuite_fail() unit test #2
 */
static sol_erno test_fail2(void)
{
        #define DESC_FAIL2 "sol_tsuite_fail() throws SOL_ERNO_PTR when passed" \
                           " a null pointer for @fail"
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, mock_log));
        sol_try (sol_tsuite_fail(ts, 0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_fail3() - sol_tsuite_fail() unit test #3
 */
static sol_erno test_fail3(void)
{
        #define DESC_FAIL3 "sol_tsuite_fail() reports 0 for the number of" \
                           " failed test cases if @tsuite has been"        \
                           " initialised by sol_tsuite_init()"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint fail;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init(ts));
        sol_try (sol_tsuite_fail(ts, &fail));

                /* check test condition */
        sol_assert (!fail, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_fail4() - sol_tsuite_fail() unit test #4
 */
static sol_erno test_fail4(void)
{
        #define DESC_FAIL4 "sol_tsuite_fail() reports 0 for the number of" \
                           " failed test cases if @tsuite has been"        \
                           " initialised by sol_tsuite_init2()"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint fail;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, &mock_log));
        sol_try (sol_tsuite_fail(ts, &fail));

                /* check test condition */
        sol_assert (!fail, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_fail5() - sol_tsuite_fail() unit test #5
 */
static sol_erno test_fail5(void)
{
        #define DESC_FAIL5 "sol_tsuite_fail() reports the correct number of" \
                           " failed test cases"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint fail;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, &mock_log));
        sol_try (sol_tsuite_register(ts, &mock_pass, "Pass"));
        sol_try (sol_tsuite_register(ts, &mock_fail, "Fail"));
        sol_try (sol_tsuite_exec(ts));
        sol_try (sol_tsuite_fail(ts, &fail));

                /* check test condition */
        sol_assert (1 == fail, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_total1() - sol_tsuite_total() unit test #1
 */
static sol_erno test_total1(void)
{
        #define DESC_TOTAL1 "sol_tsuite_total() throws SOL_ERNO_PTR when" \
                            " passed a null pointer for @tsuite"
        auto sol_tsuite ts;
        auto sol_uint total;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_total(0, &total));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_total2() - sol_tsuite_total() unit test #2
 */
static sol_erno test_total2(void)
{
        #define DESC_TOTAL2 "sol_tsuite_total() throws SOL_ERNO_PTR when" \
                            " passed a null pointer for @total"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_total(&ts, 0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_total3() - sol_tsuite_total() unit test #3
 */
static sol_erno test_total3(void)
{
        #define DESC_TOTAL3 "sol_tsuite_total() reports 0 for the number of" \
                            " total test cases if @tsuite has been"          \
                            " initialised by sol_tsuite_init()"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint total;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init(ts));
        sol_try (sol_tsuite_total(ts, &total));

                /* check test condition */
        sol_assert (!total, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_total4() - sol_tsuite_total() unit test #4
 */
static sol_erno test_total4(void)
{
        #define DESC_TOTAL4 "sol_tsuite_pass() reports 0 for the number of" \
                            " total test cases if @tsuite has been"         \
                            " initialised by sol_tsuite_init2()"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint total;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, &mock_log));
        sol_try (sol_tsuite_total(ts, &total));

                /* check test condition */
        sol_assert (!total, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_total5() - sol_tsuite_total() unit test #5
 */
static sol_erno test_total5(void)
{
        #define DESC_TOTAL5 "sol_tsuite_total() reports the correct number of" \
                            " total test cases"
        auto sol_tsuite __ts, *ts = &__ts;
        auto sol_uint total;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(ts, &mock_log));
        sol_try (sol_tsuite_register(ts, &mock_pass, "Pass"));
        sol_try (sol_tsuite_register(ts, &mock_fail, "Fail"));
        sol_try (sol_tsuite_exec(ts));
        sol_try (sol_tsuite_pass(ts, &total));

                /* check test condition */
        sol_assert (1 == total, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      test_exec1() - sol_tsuite_exec() unit test #1
 */
static sol_erno test_exec1(void)
{
        #define DESC_EXEC1 "sol_tsuite_exec() throws SOL_ERNO_PTR when passed" \
                           " a null pointer for @tsuite"
        auto sol_tsuite ts;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_tsuite_init2(&ts, mock_log));
        sol_try (sol_tsuite_exec(0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_test_exec2() - sol_tsuite_exec() unit test #2
 */
static sol_erno test_exec2(void)
{
        #define DESC_EXEC2 "sol_tsuite_exec() calls the test logging callback" \
                           " if @tsuite has been initialised by"               \
                           " sol_tsuite_init2()"
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* set up test scenario */
        flag_log = 0;
        sol_try (sol_tsuite_init2(ts, mock_log));
        sol_try (sol_tsuite_register(ts, mock_pass, "MOCK_PASS"));
        sol_try (sol_tsuite_exec(ts));

                /* check test condition */
        sol_assert (1 == flag_log, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/*
 *      __sol_tsuite_test() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tsuite_test(sol_tlog *log,
                                  sol_uint *pass,
                                  sol_uint *fail,
                                  sol_uint *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* register test cases */
        sol_try (sol_tsuite_init2(ts, log));
        sol_try (sol_tsuite_register(ts, test_init1, DESC_INIT1));
        sol_try (sol_tsuite_register(ts, test_init2, DESC_INIT2));
        sol_try (sol_tsuite_register(ts, test_init3, DESC_INIT3));
        sol_try (sol_tsuite_register(ts, test_register1, DESC_REGISTER1));
        sol_try (sol_tsuite_register(ts, test_register2, DESC_REGISTER2));
        sol_try (sol_tsuite_register(ts, test_register3, DESC_REGISTER3));
        sol_try (sol_tsuite_register(ts, test_register4, DESC_REGISTER4));
        sol_try (sol_tsuite_register(ts, test_register5, DESC_REGISTER5));
        sol_try (sol_tsuite_register(ts, test_pass1, DESC_PASS1));
        sol_try (sol_tsuite_register(ts, test_pass2, DESC_PASS2));
        sol_try (sol_tsuite_register(ts, test_pass3, DESC_PASS3));
        sol_try (sol_tsuite_register(ts, test_pass4, DESC_PASS4));
        sol_try (sol_tsuite_register(ts, test_pass5, DESC_PASS5));
        sol_try (sol_tsuite_register(ts, test_fail1, DESC_FAIL1));
        sol_try (sol_tsuite_register(ts, test_fail2, DESC_FAIL2));
        sol_try (sol_tsuite_register(ts, test_fail3, DESC_FAIL3));
        sol_try (sol_tsuite_register(ts, test_fail4, DESC_FAIL4));
        sol_try (sol_tsuite_register(ts, test_fail5, DESC_FAIL5));
        sol_try (sol_tsuite_register(ts, test_total1, DESC_TOTAL1));
        sol_try (sol_tsuite_register(ts, test_total2, DESC_TOTAL2));
        sol_try (sol_tsuite_register(ts, test_total3, DESC_TOTAL3));
        sol_try (sol_tsuite_register(ts, test_total4, DESC_TOTAL4));
        sol_try (sol_tsuite_register(ts, test_total5, DESC_TOTAL5));
        sol_try (sol_tsuite_register(ts, test_exec1, DESC_EXEC1));
        sol_try (sol_tsuite_register(ts, test_exec2, DESC_EXEC2));

                /* execute test cases */
        sol_try (sol_tsuite_exec (ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

