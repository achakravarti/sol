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
 *      DESC_INIT_01 - description for sol_tsuite_init() unit test #1
 */
#define DESC_INIT_01 "sol_tsuite_init() should throw SOL_ERNO_PTR when" \
                     " passed a null pointer for @tsuite"




/*
 *      DESC_INIT2_01 - description for sol_tsuite_init2() unit test #1
 */
#define DESC_INIT2_01 "sol_tsuite_init2() should throw SOL_ERNO_PTR when" \
                      " passed a null pointer for @tsuite"




/*
 *      DESC_INIT2_02 - description for sol_tsuite_init2() unit test #2
 */
#define DESC_INIT2_02 "sol_tsuite_init2() should throw SOL_ERNO_PTR when" \
                      " passed a null pointer for @tlog"




/*
 *      DESC_REGISTER_01 - description for sol_tsuite_register() unit test #1
 */
#define DESC_REGISTER_01 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                         " when passed a null pointer for @tsuite"




/*
 *      DESC_REGISTER_02 - description for sol_tsuite_register() unit test #2
 */
#define DESC_REGISTER_02 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                         " when passed a null pointer for @tcase"




/*
 *      DESC_REGISTER_03 - description for sol_tsuite_register() unit test #3
 */
#define DESC_REGISTER_03 "sol_tsuite_register() should throw SOL_ERNO_PTR" \
                         " when passed a null pointer for @desc"




/*
 *      DESC_REGISTER_04 - description for sol_tsuite_register() unit test #4
 */
#define DESC_REGISTER_04 "sol_tsuite_register() should throw SOL_ERNO_STR" \
                         " when passed an empty string for @desc"




/*
 *      DESC_PASS_01 - description for sol_tsuite_pass() unit test #1
 */
#define DESC_PASS_01 "sol_tsuite_pass() should throw SOL_ERNO_PTR when passed" \
                     " a null pointer for @tsuite"




/*
 *      DESC_PASS_02 - description for sol_tsuite_pass() unit test #2
 */
#define DESC_PASS_02 "sol_tsuite_pass() should throw SOL_ERNO_PTR when passed" \
                     " a null pointer for @pass"




/*
 *      DESC_PASS_03 - description for sol_tsuite_pass() unit test #3
 */
#define DESC_PASS_03 "sol_tsuite_pass() should set an initial value of 0 for"  \
                     " the total number of passed test cases when initialised" \
                     " through sol_tsuite_init()"




/*
 *      DESC_PASS_04 - description for sol_tsuite_pass() unit test #4
 */
#define DESC_PASS_04 "sol_tsuite_pass() should set an initial value of 0 for"  \
                     " the total number of passed test cases when initialised" \
                     " through sol_tsuite_init2()"




/*
 *      DESC_FAIL_01 - description for sol_tsuite_fail() unit test #1
 */
#define DESC_FAIL_01 "sol_tsuite_fail() should throw SOL_ERNO_PTR when passed" \
                     " a null pointer for @tsuite"




/*
 *      DESC_FAIL_02 - description for sol_tsuite_fail() unit test #2
 */
#define DESC_FAIL_02 "sol_tsuite_fail() should throw SOL_ERNO_PTR when passed" \
                     " a null pointer for @fail"




/*
 *      DESC_FAIL_03 - description for sol_tsuite_fail() unit test #3
 */
#define DESC_FAIL_03 "sol_tsuite_fail() should set an initial value of 0 for"  \
                     " the total number of failed test cases when initialised" \
                     " through sol_tsuite_init()"




/*
 *      DESC_FAIL_04 - description for sol_tsuite_fail() unit test #4
 */
#define DESC_FAIL_04 "sol_tsuite_fail() should set an initial value of 0 for"  \
                     " the total number of failed test cases when initialised" \
                     " through sol_tsuite_init2()"



/*
 *      DESC_TOTAL_01 - description for sol_tsuite_total() unit test #1
 */
#define DESC_TOTAL_01 "sol_tsuite_total() should throw SOL_ERNO_PTR when" \
                      " passed a null pointer for @tsuite"




/*
 *      DESC_TOTAL_02 - description for sol_tsuite_total() unit test #2
 */
#define DESC_TOTAL_02 "sol_tsuite_total() should throw SOL_ERNO_PTR when" \
                      " passed a null pointer for @total"




/*
 *      DESC_EXEC_01 - description for sol_tsuite_exec() unit test #1
 */
#define DESC_EXEC_01 "sol_tsuite_exec() should throw SOL_ERNO_PTR when" \
                     " passed a null pointer for @tsuite"




/*
 *      DESC_EXEC_02 - description for sol_tsuite_exec() unit test #2
 */
#define DESC_EXEC_02 "sol_tsuite_exec() should call the test logging callback" \
                     " if @tsuite has been initialised with sol_tsuite_init2()"




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
 */
static void
tlog_dummy(char     const *desc, /* test case description */
           sol_erno const erno   /* test case error code  */
          )
{
                /* set tlog_called flag true if this callback has been called
                 * with the required params; @erno can't be 9999 as no error
                 * code has been defined by the exception handling module as
                 * such. */
        if (desc && *desc && erno != 9999) {
                tlog_called = 1;
        }
}




static sol_erno
tcase_pass(void)
{
SOL_TRY:
                /* this is guaranteed to pass */
        sol_assert (1, SOL_ERNO_TEST);
        tcase_called = 1;

SOL_CATCH:
                /* control will never reach here */
        sol_throw ();
}




/*
 *      test_init_01() - sol_tsuite_init() unit test #1
 */
static sol_erno
test_init_01(void)
{
SOL_TRY:
                /* sol_tsuite_init() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init (0));

SOL_CATCH:
                /* check test condition described by DESC_INIT_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_init2_01() - sol_tsuite_init2() unit test #1
 */
static sol_erno
test_init2_01(void)
{
SOL_TRY:
                /* sol_tsuite_init2() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (0, tlog_dummy));

SOL_CATCH:
                /* check test condition described by DESC_INIT2_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_init2_02() - sol_tsuite_init2() unit test #1
 */
static sol_erno
test_init2_02(void)
{
        auto sol_tsuite ts; /* test suite */

SOL_TRY:
                /* sol_tsuite_init2() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, 0));

SOL_CATCH:
                /* check test condition described by DESC_INIT2_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_register_01() - sol_tsuite_register() unit test #1
 */
static sol_erno
test_register_01(void)
{
        auto sol_tsuite ts; /* test suite */

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (0, test_init_01, "Dummy"));

SOL_CATCH:
                /* check test condition described by DESC_REGISTER_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_register_02() - sol_tsuite_register() unit test #2
 */
static sol_erno
test_register_02(void)
{
        auto sol_tsuite ts; /* test suite */

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (&ts, 0, "Dummy"));

SOL_CATCH:
                /* check test condition described by DESC_REGISTER_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_register_03() - sol_tsuite_register() unit test #3
 */
static sol_erno
test_register_03(void)
{
        auto sol_tsuite ts; /* test suite */

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (&ts, test_register_01, 0));

SOL_CATCH:
                /* check test condition described by DESC_REGISTER_03 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_register_04() - sol_tsuite_register() unit test #4
 */
static sol_erno
test_register_04(void)
{
        auto sol_tsuite ts; /*  test suite */

SOL_TRY:
                /* sol_tsuite_register() should fail with SOL_ERNO_STR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (&ts, test_register_01, ""));

SOL_CATCH:
                /* check test condition described by DESC_REGISTER_04 */
        return SOL_ERNO_STR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_pass_01() - sol_tsuite_pass() unit test #1
 */
static sol_erno
test_pass_01(void)
{
        auto sol_tsuite ts;   /* test suite   */
        auto int        pass; /* passed count */

SOL_TRY:
                /* sol_tsuite_pass() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_pass (0, &pass));

SOL_CATCH:
                /* check test condition described by DESC_PASS_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_pass_02() - sol_tsuite_pass() unit test #2
 */
static sol_erno
test_pass_02(void)
{
        auto sol_tsuite ts; /* test suite */

SOL_TRY:
                /* sol_tsuite_pass() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_pass (&ts, 0));

SOL_CATCH:
                /* check test condition described by DESC_PASS_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_pass_03() - sol_tsuite_pass() unit test #3
 */
static sol_erno
test_pass_03(void)
{
        auto sol_tsuite ts;   /* test suite  */
        auto int        pass; /* passed test cases */

SOL_TRY:
                /* check test condition described by DESC_PASS_03 */
        sol_try (sol_tsuite_init (&ts));
        sol_try (sol_tsuite_pass (&ts, &pass));
        sol_assert (!pass, SOL_ERNO_TEST );

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw ();
}




/*
 *      test_pass_04() - sol_tsuite_pass() unit test #4
 */
static sol_erno
test_pass_04(void)
{
        auto sol_tsuite ts;   /* test suite  */
        auto int        pass; /* passed test cases */

SOL_TRY:
                /* check test condition described by DESC_PASS_04 */
        sol_try (sol_tsuite_init2 (&ts, &tlog_dummy));
        sol_try (sol_tsuite_pass (&ts, &pass));
        sol_assert (!pass, SOL_ERNO_TEST );

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw ();
}




/*
 *      test_fail_01() - sol_tsuite_fail() unit test #1
 */
static sol_erno
test_fail_01(void)
{
        auto sol_tsuite ts;   /* test suite   */
        auto int        fail; /* failed count */

SOL_TRY:
                /* sol_tsuite_fail() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_fail (0, &fail));

SOL_CATCH:
                /* check test condition described by DESC_FAIL_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_fail_02() - sol_tsuite_fail() unit test #2
 */
static sol_erno
test_fail_02(void)
{
        auto sol_tsuite ts; /* test suite */

SOL_TRY:
                /* sol_tsuite_fail() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_fail (&ts, 0));

SOL_CATCH:
                /* check test condition described by DESC_FAIL_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_fail_03() - sol_tsuite_fail() unit test #3
 */
static sol_erno
test_fail_03(void)
{
        auto sol_tsuite ts;   /* test suite        */
        auto int        fail; /* failed test cases */

SOL_TRY:
                /* check test condition described by DESC_PASS_03 */
        sol_try (sol_tsuite_init(&ts));
        sol_try (sol_tsuite_pass(&ts, &fail));
        sol_assert (!fail, SOL_ERNO_TEST);

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      test_fail_04() - sol_tsuite_fail() unit test #4
 */
static sol_erno
test_fail_04(void)
{
    auto sol_tsuite ts;   /* test suite        */
    auto int        fail; /* failed test cases */

SOL_TRY:
                /* check test condition described by DESC_FAIL_04 */
        sol_try (sol_tsuite_init2 (&ts, &tlog_dummy));
        sol_try (sol_tsuite_fail (&ts, &fail));
        sol_assert (!fail, SOL_ERNO_TEST);

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw ();
}




/*
 *      test_total_01() - sol_tsuite_total() unit test #1
 */
static sol_erno
test_total_01(void)
{
        auto sol_tsuite ts;    /* test suite  */
        auto int        total; /* total count */

SOL_TRY:
                /* sol_tsuite_total() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_total (0, &total));

SOL_CATCH:
                /* check test condition described by DESC_TOTAL_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_total_02() - sol_tsuite_total() unit test #2
 */
static sol_erno
test_total_02(void)
{
        auto sol_tsuite ts; /*  test suite */

SOL_TRY:
                /* sol_tsuite_fail() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_total (&ts, 0));

SOL_CATCH:
                /* check test condition described by DESC_TOTAL_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_exec_01() - sol_tsuite_exec() unit test #1
 */
static sol_erno
test_exec_01(void)
{
        auto sol_tsuite ts; /*  test suite */

SOL_TRY:
                /* sol_tsuite_exec() should fail with SOL_ERNO_PTR */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_exec (0));

SOL_CATCH:
                /* check test condition described by DESC_EXEC_01 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      test_exec_02() - sol_tsuite_exec() unit test #2
 */
static sol_erno
test_exec_02(void)
{
        auto sol_tsuite ts; /* test suite */

SOL_TRY:
                /* initialise test suite */
        sol_try (sol_tsuite_init2 (&ts, tlog_dummy));
        sol_try (sol_tsuite_register (&ts, tcase_pass, "TCASE_PASS"));

                /* sol_tsuite_exec() should call tlog_dummy */
        tlog_called = 0;
        sol_try (sol_tsuite_exec (&ts));
        sol_assert (1 == tlog_called, SOL_ERNO_TEST);

SOL_CATCH:
                /* check test condition described by DESC_EXEC_02 */
        return SOL_ERNO_PTR == sol_erno_now ()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      __sol_tsuite_test() - declared in sol/test/suite.h
 */
extern sol_erno
__sol_tsuite_test(sol_tlog *log,
                  int      *pass,
                  int      *fail,
                  int      *total
                 )
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* initialise test suite */
        sol_try (sol_tsuite_init2 (ts, log));

                /* register test cases */
        sol_try (sol_tsuite_register (ts, test_init_01, DESC_INIT_01));
        sol_try (sol_tsuite_register (ts, test_init2_01, DESC_INIT2_01));
        sol_try (sol_tsuite_register (ts, test_init2_02, DESC_INIT2_02));
        sol_try (sol_tsuite_register (ts, test_register_01, DESC_REGISTER_01));
        sol_try (sol_tsuite_register (ts, test_register_02, DESC_REGISTER_02));
        sol_try (sol_tsuite_register (ts, test_register_03, DESC_REGISTER_03));
        sol_try (sol_tsuite_register (ts, test_register_04, DESC_REGISTER_04));
        sol_try (sol_tsuite_register (ts, test_pass_01, DESC_PASS_01));
        sol_try (sol_tsuite_register (ts, test_pass_02, DESC_PASS_02));
        sol_try (sol_tsuite_register (ts, test_pass_03, DESC_PASS_03));
        sol_try (sol_tsuite_register (ts, test_pass_04, DESC_PASS_04));
        sol_try (sol_tsuite_register (ts, test_fail_01, DESC_FAIL_01));
        sol_try (sol_tsuite_register (ts, test_fail_02, DESC_FAIL_02));
        sol_try (sol_tsuite_register (ts, test_fail_03, DESC_FAIL_03));
        sol_try (sol_tsuite_register (ts, test_fail_04, DESC_FAIL_04));
        sol_try (sol_tsuite_register (ts, test_total_01, DESC_TOTAL_01));
        sol_try (sol_tsuite_register (ts, test_total_02, DESC_TOTAL_02));
        sol_try (sol_tsuite_register (ts, test_exec_01, DESC_EXEC_01));
        sol_try (sol_tsuite_register (ts, test_exec_02, DESC_EXEC_02));

                /* execute test cases */
        sol_try (sol_tsuite_exec (ts));

                /* return test counts */
        sol_try (sol_tsuite_pass (ts, pass));
        sol_try (sol_tsuite_fail (ts, fail));
        sol_try (sol_tsuite_total (ts, total));

                /* wind up */
        sol_tsuite_term (ts);

SOL_CATCH:
                /* wind up and throw current exception */
        sol_tsuite_term (ts);
        sol_throw ();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

