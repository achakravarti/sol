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
#include "../src/api.h"
#include "./suite.h"




/*
 *      test_new1() - sol_ptr_new() unit test #1
 */
static sol_erno test_new1(void)
{
        #define DESC_NEW1 "sol_ptr_new() throws SOL_ERNO_PTR when passed a" \
                          " null pointer for @ptr"

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new(SOL_PTR_NULL, sizeof (int)));

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
 *      test_new2() - sol_ptr_new() unit test #2
 */
static sol_erno test_new2(void)
{
        #define DESC_NEW2 "sol_ptr_new() throws SOL_ERNO_PTR when passed a" \
                          " pointer for @ptr that has already been allocated"
        auto sol_ptr *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new(&ptr, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_new(&ptr, sizeof (int)));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);
        return sol_erno_get();
}




/*
 *      test_new3() - sol_ptr_new() unit test #3
 */
static sol_erno test_new3(void)
{
        #define DESC_NEW3 "sol_ptr_new() throws SOL_ERNO_RANGE when passed 0" \
                          " for @sz"
        auto sol_ptr *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_new(&ptr, 0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_RANGE == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);
        return sol_erno_get();
}




/*
 *      test_new4() - sol_ptr_new() unit test #4
 */
static sol_erno test_new4(void)
{
        #define DESC_NEW4 "sol_ptr_new() successfully allocates heap memory"
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
        return sol_erno_get();
}




/*
 *      test_copy1() - sol_ptr_copy() unit test #1
 */
static sol_erno test_copy1(void)
{
        #define DESC_COPY1 "sol_ptr_copy() throws SOL_ERNO_PTR when passed a " \
                           " null pointer for @ptr"
        auto int *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new((sol_ptr*)&src, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_copy(SOL_PTR_NULL, (sol_ptr*)src, sizeof (int)));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_ptr_free((sol_ptr**)&src);
        return sol_erno_get();
}




/*
 *      test_copy2() - sol_ptr_copy() unit test #2
 */
static sol_erno test_copy2(void)
{
        #define DESC_COPY2 "sol_ptr_copy() throws SOL_ERNO_PTR when passed a" \
                           " pointer for @ptr that has already been allocated"
        auto sol_ptr *ptr = SOL_PTR_NULL;
        auto int *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new((sol_ptr*)&src, sizeof (int)), SOL_ERNO_TEST);
        sol_assert (!sol_ptr_new(&ptr, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_copy(ptr, (sol_ptr*)src, sizeof (int)));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);
        sol_ptr_free((sol_ptr**)&src);
        return sol_erno_get();
}




/*
 *      test_copy3() - sol_ptr_copy() unit test #3
 */
static sol_erno test_copy3(void)
{
        #define DESC_COPY3 "sol_ptr_copy() throws SOL_ERNO_RANGE when passed" \
                           " 0 for @sz"
        auto sol_ptr *ptr = SOL_PTR_NULL;
        auto int *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_assert (!sol_ptr_new((sol_ptr**)&src, sizeof (int)), SOL_ERNO_TEST);
        sol_try (sol_ptr_copy(&ptr, (sol_ptr*)src, 0));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_RANGE == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);
        sol_ptr_free((sol_ptr**)&src);
        return sol_erno_get();
}




/*
 *      test_copy4() - sol_ptr_copy() unit test #4
 */
static sol_erno test_copy4(void)
{
        #define DESC_COPY4 "sol_ptr_copy() throws SOL_ERNO_PTR when passed a" \
                           " null pointer for @src"
        auto sol_ptr *ptr = SOL_PTR_NULL;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_ptr_copy(&ptr, SOL_PTR_NULL, sizeof (int)));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(SOL_ERNO_PTR == sol_erno_get()
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_ptr_free(&ptr);
        return sol_erno_get();
}




static sol_erno test_copy5(void)
{
        #define DESC_COPY5 "sol_ptr_copy() correctly copies the contents of" \
                           " @src on to @ptr"
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
        return sol_erno_get();
}




/*
 *      test_free1() - sol_ptr_free() unit test #1
 */
static sol_erno test_free1(void)
{
        #define DESC_FREE1 "sol_ptr_free() executes even if passed an invalid" \
                           " pointer for @ptr"

                /* set up test scenario */
        sol_ptr_free(SOL_PTR_NULL);
        return SOL_ERNO_NULL;
}




/*
 *      test_free2() - sol_ptr_free() unit test #2
 */
static sol_erno test_free2(void)
{
        #define DESC_FREE2 "sol_ptr_free() releases the heap memory allocated" \
                           " to @ptr"
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
        return sol_erno_get();
}




/*
 *      __sol_tests_ptr() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tests_ptr(sol_tlog *log,
                                sol_uint *pass,
                                sol_uint *fail,
                                sol_uint *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* initialise test suite */
        sol_try (sol_tsuite_init2(ts, log));

                /* register test cases */
        sol_try (sol_tsuite_register(ts, &test_new1, DESC_NEW1));
        sol_try (sol_tsuite_register(ts, &test_new2, DESC_NEW2));
        sol_try (sol_tsuite_register(ts, &test_new3, DESC_NEW3));
        sol_try (sol_tsuite_register(ts, &test_new4, DESC_NEW4));
        sol_try (sol_tsuite_register(ts, &test_copy1, DESC_COPY1));
        sol_try (sol_tsuite_register(ts, &test_copy2, DESC_COPY2));
        sol_try (sol_tsuite_register(ts, &test_copy3, DESC_COPY3));
        sol_try (sol_tsuite_register(ts, &test_copy4, DESC_COPY4));
        sol_try (sol_tsuite_register(ts, &test_copy5, DESC_COPY5));
        sol_try (sol_tsuite_register(ts, &test_free1, DESC_FREE1));
        sol_try (sol_tsuite_register(ts, &test_free2, DESC_FREE2));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

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

