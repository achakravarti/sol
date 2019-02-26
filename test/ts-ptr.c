/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-ptr.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the pointer module.
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
#include "../inc/ptr.h"
#include "./suite.h"




/*
 *      new_01() - sol_ptr_new() unit test #1
 */
static sol_erno new_01(void)
{
        #define NEW_01 "sol_ptr_new() throws SOL_ERNO_PTR when passed a null" \
                       " pointer for @ptr"

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new(SOL_PTR_NULL, sizeof (int)));

SOL_CATCH:
SOL_FINALLY:
                /* check test condition */
        return SOL_ERNO_PTR == sol_erno_get()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      new_02() - sol_ptr_new() unit test #2
 */
static sol_erno new_02(void)
{
        #define NEW_02 "sol_ptr_new() throws SOL_ERNO_PTR when passed a"   \
                       " pointer for @ptr that has already been allocated"
        auto sol_ptr *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new(&ptr, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_new(&ptr, sizeof (int)));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);

                /* check test condition */
        return SOL_ERNO_PTR == sol_erno_get()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      new_03() - sol_ptr_new() unit test #3
 */
static sol_erno new_03(void)
{
        #define NEW_03 "sol_ptr_new() throws SOL_ERNO_RANGE when passed 0" \
                       " for @sz"
        auto sol_ptr *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new(&ptr, 0));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);

                /* check test condition */
        return SOL_ERNO_RANGE == sol_erno_get()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      new_04() - sol_ptr_new() unit test #4
 */
static sol_erno new_04(void)
{
        #define NEW_04 "sol_ptr_new() successfully allocates heap memory"
        auto int *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new((sol_ptr**)&ptr, sizeof (*ptr)));
        *ptr = -612;

                /* check test condition */
        sol_assert (*ptr == -612, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free((sol_ptr**)&ptr);

                /* throw current exception, if any */
        sol_throw();
}




/*
 *      copy_01() - sol_ptr_copy() unit test #1
 */
static sol_erno copy_01(void)
{
        #define COPY_01 "sol_ptr_copy() throws SOL_ERNO_PTR when passed a " \
                        " null pointer for @ptr"
        auto int *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new((sol_ptr*)&src, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_copy(SOL_PTR_NULL, (sol_ptr*)src, sizeof (int)));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free((sol_ptr**)&src);

                /* check test condition */
        return SOL_ERNO_PTR == sol_erno_get()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      copy_02() - sol_ptr_copy() unit test #2
 */
static sol_erno copy_02(void)
{
        #define COPY_02 "sol_ptr_copy() throws SOL_ERNO_PTR when passed a"   \
                        " pointer for @ptr that has already been allocated"
        auto sol_ptr *ptr = SOL_PTR_NULL;
        auto int *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new((sol_ptr*)&src, sizeof (int)), SOL_ERNO_TEST);
        sol_assert (!sol_ptr_new(&ptr, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_copy(ptr, (sol_ptr*)src, sizeof (int)));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);
        sol_ptr_free((sol_ptr**)&src);

                /* check test condition */
        return SOL_ERNO_PTR == sol_erno_get()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      copy_03() - sol_ptr_copy() unit test #3
 */
static sol_erno copy_03(void)
{
        #define COPY_03 "sol_ptr_copy() throws SOL_ERNO_RANGE when passed 0" \
                        " for @sz"
        auto sol_ptr *ptr = SOL_PTR_NULL;
        auto int *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new((sol_ptr**)&src, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_copy(&ptr, (sol_ptr*)src, 0));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);
        sol_ptr_free((sol_ptr**)&src);

                /* check test condition */
        return SOL_ERNO_RANGE == sol_erno_get()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




/*
 *      copy_04() - sol_ptr_copy() unit test #4
 */
static sol_erno copy_04(void)
{
        #define COPY_04 "sol_ptr_copy() throws SOL_ERNO_PTR when passed a" \
                        " null pointer for @src"
        auto sol_ptr *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_copy(&ptr, SOL_PTR_NULL, sizeof (int)));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);

                /* check test condition */
        return SOL_ERNO_PTR == sol_erno_get()
               ? SOL_ERNO_NULL
               : SOL_ERNO_TEST;
}




static sol_erno copy_05(void)
{
        #define COPY_05 "sol_ptr_copy() correctly copies the contents of @src" \
                        " on to @ptr"
        auto int *ptr = SOL_PTR_NULL;
        auto int *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new((sol_ptr**)&src, sizeof (*src)));
        *src = -555;
        sol_try (sol_ptr_copy((sol_ptr**)&ptr, src, sizeof (*ptr)));

                /* check test condition */
        sol_assert (*ptr == -555, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_ptr_free((sol_ptr**)&ptr);
        sol_ptr_free((sol_ptr**)&src);

                /* throw current exception, if any */
        sol_throw();
}




/*
 *      free_01() - sol_ptr_free() unit test #1
 */
static sol_erno free_01(void)
{
        #define FREE_01 "sol_ptr_free() executes even if passed an invalid" \
                        " pointer for @ptr"

                /* set up test scenario */
        sol_ptr_free(SOL_PTR_NULL);
        return SOL_ERNO_NULL;
}




/*
 *      free_02() - sol_ptr_free() unit test #2
 */
static sol_erno free_02(void)
{
        #define FREE_02 "sol_ptr_free() releases the heap memory allocated to" \
                        " @ptr"
        auto int *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new((sol_ptr**) &ptr, sizeof (*ptr)));
        *ptr = 5;
        sol_ptr_free((sol_ptr**) &ptr);

                /* check test condition */
        sol_assert (!ptr, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_throw();
}




/*
 *      __sol_tests_ptr() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tests_ptr(sol_tlog *log,
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
        sol_try (sol_tsuite_register(ts, &new_01, NEW_01));
        sol_try (sol_tsuite_register(ts, &new_02, NEW_02));
        sol_try (sol_tsuite_register(ts, &new_03, NEW_03));
        sol_try (sol_tsuite_register(ts, &new_04, NEW_04));
        sol_try (sol_tsuite_register(ts, &copy_01, COPY_01));
        sol_try (sol_tsuite_register(ts, &copy_02, COPY_02));
        sol_try (sol_tsuite_register(ts, &copy_03, COPY_03));
        sol_try (sol_tsuite_register(ts, &copy_04, COPY_04));
        sol_try (sol_tsuite_register(ts, &copy_05, COPY_05));
        sol_try (sol_tsuite_register(ts, &free_01, FREE_01));
        sol_try (sol_tsuite_register(ts, &free_02, FREE_02));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
SOL_FINALLY:
                /* throw current exception, if any */
        sol_tsuite_term(ts);
        sol_throw();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

