/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-elem-meta.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the element metadata interface.
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
#include "../inc/dsa.h"
#include "suite.h"




        /* copy the definition of sol_elem_meta from src/elem.c; this is
         * generally considered very bad practice, but I've made this choice
         * deliberately because I need to access the reference count field for
         * some of the test cases without exposing the internal structure of the
         * type through some header file */
struct __sol_elem_meta {
        sol_index id;                    /* element ID             */
        sol_size sz;                     /* element size           */
        sol_size nref;                   /* reference count        */
        sol_elem_delegate_dispose *disp; /* dispose delegate       */
        sol_elem_delegate_eq *eq;        /* == comparison delegate */
        sol_elem_delegate_lt *lt;        /* < comparison delegate  */
        sol_elem_delegate_gt *gt;        /* > comparison delegate  */
};




        /* mock_dispose() mocks a sol_elem_delegate_dispose callback */
static void mock_dispose(sol_ptr **disp)
{
                /* casting to void prevents compiler warnings */
        (void) disp;
}




        /* mock_cmp mocks the sol_elem_delegate_eq, sol_elem_delegate_lt, and
         * sol_elem_delegate_gt callbacks */
static sol_erno mock_cmp(const sol_ptr *lhs,
                         const sol_ptr *rhs,
                         SOL_BOOL *cmp)
{
                /* casting to void prevents compiler warnings */
        (void) lhs;
        (void) rhs;
        (void) cmp;

                /* we're good */
        return SOL_ERNO_NULL;
}




        /* new_test1() defines the test case described by NEW_TEST1 */
static sol_erno new_test1(void)
{
        #define NEW_TEST1 "sol_elem_meta_new() throws SOL_ERNO_PTR if" \
                          " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(SOL_PTR_NULL, ID, SZ));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* new_test2() defines the test case described by NEW_TEST2 */
static sol_erno new_test2(void)
{
        #define NEW_TEST2 "sol_elem_meta_new() throws SOL_ERNO_RANGE if" \
                          " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&meta, ID, SZ));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new_test3() defines the test case described by NEW_TEST3 */
static sol_erno new_test3(void)
{
        #define NEW_TEST3 "sol_elem_meta_new() sets the internal reference" \
                          " count to 1 when called"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&meta, ID, SZ));

                /* check test condition */
        sol_assert (meta->nref == (sol_size) 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new_test4() defines the test case described by NEW_TEST4 */
static sol_erno new_test4(void)
{
        #define NEW_TEST4 "sol_elem_meta_new() sets @meta to non-null" \
                          " if successful"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&meta, ID, SZ));

                /* check test condition */
        sol_assert (meta, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new2_test1() defines the test case described by NEW2_TEST1 */
static sol_erno new2_test1(void)
{
        #define NEW2_TEST1 "sol_elem_meta_new2() throws SOL_ERNO_PTR if" \
                           " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 1;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new2(SOL_PTR_NULL, ID, SZ, mock_dispose));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* new2_test2() defines the test case described by NEW2_TEST2 */
static sol_erno new2_test2(void)
{
        #define NEW2_TEST2 "sol_elem_meta_new2() throws SOL_ERNO_RANGE" \
                           " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new2(&meta, ID, SZ, mock_dispose));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new2_test3() defines the test case described by NEW2_TEST3 */
static sol_erno new2_test3(void)
{
        #define NEW2_TEST3 "sol_elem_meta_new2() throws SOL_ERNO_PTR" \
                           " if passed a null pointer for @disp"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new2(&meta, ID, SZ, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new2_test4() defines the test case described by NEW2_TEST4 */
static sol_erno new2_test4(void)
{
        #define NEW2_TEST4 "sol_elem_meta_new2() sets the internal reference" \
                           " count to 1 when called"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new2(&meta, ID, SZ, mock_dispose));

                /* check test condition */
        sol_assert (meta->nref == (sol_size) 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new2_test5() defines the test case described by NEW2_TEST5 */
static sol_erno new2_test5(void)
{
        #define NEW2_TEST5 "sol_elem_meta_new2() sets @meta to non-null" \
                           " if successful"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new2(&meta, ID, SZ, mock_dispose));

                /* check test condition */
        sol_assert (meta, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new3_test1() defines the test case described by NEW3_TEST1 */
static sol_erno new3_test1(void)
{
        #define NEW3_TEST1 "sol_elem_meta_new3() throws SOL_ERNO_PTR if" \
                           " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 1;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new3(SOL_PTR_NULL,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* new3_test2() defines the test case described by NEW3_TEST2 */
static sol_erno new3_test2(void)
{
        #define NEW3_TEST2 "sol_elem_meta_new3() throws SOL_ERNO_RANGE" \
                           " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new3(&meta, ID, SZ, mock_dispose, mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new3_test3() defines the test case described by NEW3_TEST3 */
static sol_erno new3_test3(void)
{
        #define NEW3_TEST3 "sol_elem_meta_new3() throws SOL_ERNO_PTR" \
                           " if passed a null pointer for @disp"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new3(&meta, ID, SZ, SOL_PTR_NULL, mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new3_test4() defines the test case described by NEW3_TEST4 */
static sol_erno new3_test4(void)
{
        #define NEW3_TEST4 "sol_elem_meta_new3() throws SOL_ERNO_PTR" \
                           " if passed a null pointer for @eq"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new3(&meta, ID, SZ, mock_dispose, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new3_test5() defines the test case described by NEW3_TEST5 */
static sol_erno new3_test5(void)
{
        #define NEW3_TEST5 "sol_elem_meta_new2() sets the internal reference" \
                           " count to 1 when called"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new3(&meta, ID, SZ, mock_dispose, mock_cmp));

                /* check test condition */
        sol_assert (meta->nref == (sol_size) 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new3_test6() defines the test case described by NEW3_TEST6 */
static sol_erno new3_test6(void)
{
        #define NEW3_TEST6 "sol_elem_meta_new2() sets @meta to non-null" \
                           " if successful"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new3(&meta, ID, SZ, mock_dispose, mock_cmp));

                /* check test condition */
        sol_assert (meta, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new4_test1() defines the test case described by NEW4_TEST1 */
static sol_erno new4_test1(void)
{
        #define NEW4_TEST1 "sol_elem_meta_new4() throws SOL_ERNO_PTR if" \
                           " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 1;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(SOL_PTR_NULL,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* new4_test2() defines the test case described by NEW4_TEST2 */
static sol_erno new4_test2(void)
{
        #define NEW4_TEST2 "sol_elem_meta_new4() throws SOL_ERNO_RANGE" \
                           " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new4_test3() defines the test case described by NEW4_TEST3 */
static sol_erno new4_test3(void)
{
        #define NEW4_TEST3 "sol_elem_meta_new4() throws SOL_ERNO_PTR" \
                           " if passed a null pointer for @disp"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    SOL_PTR_NULL,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new4_test4() defines the test case described by NEW4_TEST4 */
static sol_erno new4_test4(void)
{
        #define NEW4_TEST4 "sol_elem_meta_new4() throws SOL_ERNO_PTR" \
                           " if passed a null pointer for @eq"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    SOL_PTR_NULL,
                                    mock_cmp,
                                    mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new4_test5() defines the test case described by NEW4_TEST5 */
static sol_erno new4_test5(void)
{
        #define NEW4_TEST5 "sol_elem_meta_new4() throws SOL_ERNO_PTR" \
                           " if passed a null pointer for @lt"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    SOL_PTR_NULL,
                                    mock_cmp));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new4_test6() defines the test case described by NEW4_TEST6 */
static sol_erno new4_test6(void)
{
        #define NEW4_TEST6 "sol_elem_meta_new4() throws SOL_ERNO_PTR" \
                           " if passed a null pointer for @lt"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new4_test7() defines the test case described by NEW4_TEST7 */
static sol_erno new4_test7(void)
{
        #define NEW4_TEST7 "sol_elem_meta_new2() sets the internal reference" \
                           " count to 1 when called"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));

                /* check test condition */
        sol_assert (meta->nref == (sol_size) 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* new4_test8() defines the test case described by NEW4_TEST8 */
static sol_erno new4_test8(void)
{
        #define NEW4_TEST8 "sol_elem_meta_new2() sets @meta to non-null" \
                           " if successful"
        const sol_index ID = (sol_index) 1;
        const sol_size SZ = (sol_size) 1;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));

                /* check test condition */
        sol_assert (meta, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* copy_test1() defines the test case described by COPY_TEST1 */
static sol_erno copy_test1(void)
{
        #define COPY_TEST1 "sol_elem_meta_copy() throws SOL_ERNO_PTR if @meta" \
                           " is null"
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = (sol_size) 7;
        auto sol_elem_meta *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&src, ID, SZ));
        sol_try (sol_elem_meta_copy(SOL_PTR_NULL, src));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&src);
        return sol_erno_get();
}




        /* copy_test2() defines the test case described by COPY_TEST2 */
static sol_erno copy_test2(void)
{
        #define COPY_TEST2 "sol_elem_meta_copy() throws SOL_ERNO_STATE if" \
                           " @meta references a non-null pointer"
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = (sol_size) 7;
        auto sol_elem_meta *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&src, ID, SZ));
        sol_try (sol_elem_meta_copy(&src, src));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&src);
        return sol_erno_get();
}




        /* copy_test3() defines the test case described by COPY_TEST3 */
static sol_erno copy_test3(void)
{
        #define COPY_TEST3 "sol_elem_meta_copy() throws SOL_ERNO_PTR if" \
                           " @src is null"
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_copy(&meta, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* copy_test4() defines the test case described by COPY_TEST4 */
static sol_erno copy_test4(void)
{
        #define COPY_TEST4 "sol_elem_meta_copy() increments the reference" \
                           " count of @src"
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = (sol_size) 7;
        auto sol_elem_meta *meta1 = SOL_PTR_NULL;
        auto sol_elem_meta *meta2 = SOL_PTR_NULL;
        auto sol_elem_meta *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&src, ID, SZ));
        sol_try (sol_elem_meta_copy(&meta1, src));
        sol_try (sol_elem_meta_copy(&meta2, src));

                /* check test condition */
        sol_assert (src->nref == (sol_size) 3, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if an exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta1);
        sol_elem_meta_free(&meta2);
        sol_elem_meta_free(&src);
        return sol_erno_get();
}




        /* copy_test5() defines the test case described by COPY_TEST5 */
static sol_erno copy_test5(void)
{
        #define COPY_TEST5 "sol_elem_meta_copy() sets @meta to non-null" \
                           " if successful"
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = (sol_size) 7;
        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem_meta *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&src, ID, SZ));
        sol_try (sol_elem_meta_copy(&meta, src));

                /* check test condition */
        sol_assert (meta, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if an exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_meta_free(&src);
        return sol_erno_get();
}




        /* copy_test6() defines the test case described by COPY_TEST6 */
static sol_erno copy_test6(void)
{
        #define COPY_TEST6 "sol_elem_meta_copy() makes @meta identical to @src"
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = (sol_size) 7;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem_meta *src = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new4(&src,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));
        sol_try (sol_elem_meta_copy(&meta, src));

                /* check test condition */
        sol_assert (meta->id == src->id, SOL_ERNO_TEST);
        sol_assert (meta->sz == src->sz, SOL_ERNO_TEST);
        sol_assert (meta->disp == src->disp, SOL_ERNO_TEST);
        sol_assert (meta->eq == src->eq, SOL_ERNO_TEST);
        sol_assert (meta->gt == src->gt, SOL_ERNO_TEST);
        sol_assert (meta->lt == src->lt, SOL_ERNO_TEST);
        sol_assert (meta->nref == src->nref, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if an exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_meta_free(&src);
        return sol_erno_get();
}




        /* free_test1() defines the test case described by FREE_TEST1 */
static sol_erno free_test1(void)
{
        #define FREE_TEST1 "sol_elem_meta_free() is safe even if @meta" \
                           " is null"

                /* set up test */
        sol_elem_meta_free(SOL_PTR_NULL);
        return SOL_ERNO_NULL;
}




        /* free_test2() defines the test case described by FREE_TEST2 */
static sol_erno free_test2(void)
{
        #define FREE_TEST2 "sol_elem_meta_free() is safe even if @meta" \
                           " is a handle to a null pointer"
        auto sol_elem_meta *meta = SOL_PTR_NULL;

                /* set up test */
        sol_elem_meta_free(&meta);
        return SOL_ERNO_NULL;
}




        /* free_test3() defines the test case described by FREE_TEST3 */
static sol_erno free_test3(void)
{
        #define FREE_TEST3 "sol_elem_meta_free() releases @meta"
        const sol_index ID = 5;
        const sol_size SZ = 6;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&meta, ID, SZ));
        sol_elem_meta_free(&meta);

                /* check test condition */
        sol_assert (!meta, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* free_test4() defines the test case described by FREE_TEST4 */
static sol_erno free_test4(void)
{
        #define FREE_TEST4 "sol_elem_meta_free() accounts for reference" \
                           " counting when releasing @meta"
        const sol_index ID = 5;
        const sol_size SZ = 6;
        auto sol_elem_meta *src = SOL_PTR_NULL;
        auto sol_elem_meta *meta1 = SOL_PTR_NULL;
        auto sol_elem_meta *meta2 = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_meta_new(&src, ID, SZ));
        sol_try (sol_elem_meta_copy(&meta1, src));
        sol_try (sol_elem_meta_copy(&meta2, meta1));
        sol_elem_meta_free(&meta2);

                /* check test condition */
        sol_assert (src && meta1 && !meta2, SOL_ERNO_TEST);
        sol_assert (src->nref == (sol_size) 2, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if exception occurs */

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* __sol_tests_elem_meta() was declared in sol/test/suite.h */
extern sol_erno __sol_tests_elem_meta(sol_tlog *log,
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

                /* register sol_elem_meta_new() test cases */
        sol_try (sol_tsuite_register(ts, new_test1, NEW_TEST1));
        sol_try (sol_tsuite_register(ts, new_test2, NEW_TEST2));
        sol_try (sol_tsuite_register(ts, new_test3, NEW_TEST3));
        sol_try (sol_tsuite_register(ts, new_test4, NEW_TEST4));

                /* register sol_elem_meta_new2() test cases */
        sol_try (sol_tsuite_register(ts, new2_test1, NEW2_TEST1));
        sol_try (sol_tsuite_register(ts, new2_test2, NEW2_TEST2));
        sol_try (sol_tsuite_register(ts, new2_test3, NEW2_TEST3));
        sol_try (sol_tsuite_register(ts, new2_test4, NEW2_TEST4));
        sol_try (sol_tsuite_register(ts, new2_test5, NEW2_TEST5));

                /* register sol_elem_meta_new3() test cases */
        sol_try (sol_tsuite_register(ts, new3_test1, NEW3_TEST1));
        sol_try (sol_tsuite_register(ts, new3_test2, NEW3_TEST2));
        sol_try (sol_tsuite_register(ts, new3_test3, NEW3_TEST3));
        sol_try (sol_tsuite_register(ts, new3_test4, NEW3_TEST4));
        sol_try (sol_tsuite_register(ts, new3_test5, NEW3_TEST5));
        sol_try (sol_tsuite_register(ts, new3_test6, NEW3_TEST6));

                /* register sol_elem_meta_new4() test cases */
        sol_try (sol_tsuite_register(ts, new4_test1, NEW4_TEST1));
        sol_try (sol_tsuite_register(ts, new4_test2, NEW4_TEST2));
        sol_try (sol_tsuite_register(ts, new4_test3, NEW4_TEST3));
        sol_try (sol_tsuite_register(ts, new4_test4, NEW4_TEST4));
        sol_try (sol_tsuite_register(ts, new4_test5, NEW4_TEST5));
        sol_try (sol_tsuite_register(ts, new4_test6, NEW4_TEST6));
        sol_try (sol_tsuite_register(ts, new4_test7, NEW4_TEST7));
        sol_try (sol_tsuite_register(ts, new4_test8, NEW4_TEST8));

                /* register sol_elem_meta_copy() test cases */
        sol_try (sol_tsuite_register(ts, copy_test1, COPY_TEST1));
        sol_try (sol_tsuite_register(ts, copy_test2, COPY_TEST2));
        sol_try (sol_tsuite_register(ts, copy_test3, COPY_TEST3));
        sol_try (sol_tsuite_register(ts, copy_test4, COPY_TEST4));
        sol_try (sol_tsuite_register(ts, copy_test5, COPY_TEST5));
        sol_try (sol_tsuite_register(ts, copy_test6, COPY_TEST6));

                /* register sol_elem_meta_free() test cases */
        sol_try (sol_tsuite_register(ts, free_test1, FREE_TEST1));
        sol_try (sol_tsuite_register(ts, free_test2, FREE_TEST2));
        sol_try (sol_tsuite_register(ts, free_test3, FREE_TEST3));
        sol_try (sol_tsuite_register(ts, free_test4, FREE_TEST4));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

