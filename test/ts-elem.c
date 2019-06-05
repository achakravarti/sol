/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-elem.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the element interface.
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




        /* copy the definition of sol_elem from src/elem.c; this is generally
         * considered very bad practice, but I've made this choice deliberately
         * because I need to access the reference count field for some of the
         * test cases without exposing the internal structure of the type
         * through some header file */
struct __sol_elem {
        sol_ptr *data;
        sol_elem_meta *meta;
        sol_size nref;
};




        /* mock_dispose() mocks the element data dispose delegate */
static void mock_dispose(sol_ptr **elem)
{
        (void) elem;
}




        /* mock_lt() mocks the less than comparison delegate */
static sol_erno mock_lt(const sol_ptr *lhs, const sol_ptr *rhs, SOL_BOOL *lt)
{
        const sol_int LHS = *((sol_int *) lhs);
        const sol_int RHS = *((sol_int *) rhs);

                /* perform comparison */
        *lt = (LHS < RHS);
        return SOL_ERNO_NULL;
}




        /* mock_eq() mocks the equal to comparison delegate */
static sol_erno mock_eq(const sol_ptr *lhs, const sol_ptr *rhs, SOL_BOOL *eq)
{
        const sol_int LHS = *((sol_int *) lhs);
        const sol_int RHS = *((sol_int *) rhs);

                /* perform comparison */
        *eq = (LHS == RHS);
        return SOL_ERNO_NULL;
}




        /* mock_gt() mocks the greater than comparison delegate */
static sol_erno mock_gt(const sol_ptr *lhs, const sol_ptr *rhs, SOL_BOOL *gt)
{
        const sol_int LHS = *((sol_int *) lhs);
        const sol_int RHS = *((sol_int *) rhs);

                /* perform comparison */
        *gt = (LHS > RHS);
        return SOL_ERNO_NULL;
}




        /* meta_new() is a utility function to initialise the minimal element
         * metadata used for testing */
static sol_erno meta_new(sol_elem_meta **meta)
{
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = sizeof (sol_int);

                /* initialise metadata */
        return sol_elem_meta_new(meta, ID, SZ);
}




        /* meta_new2 is a utility function to initialise the full element
         * metadata used for testing */
static sol_erno meta_new2(sol_elem_meta **meta)
{
        const sol_index ID = (sol_index) 6;
        const sol_size SZ = sizeof (sol_int);

                /* initialise metadata */
        return sol_elem_meta_new4(meta,
                                  ID,
                                  SZ,
                                  mock_dispose,
                                  mock_eq,
                                  mock_lt,
                                  mock_gt);
}




        /* new_test1() defines the test case described by NEW_TEST1 */
static sol_erno new_test1(void)
{
        #define NEW_TEST1 "sol_elem_new() throws SOL_ERNO_PTR if" \
                          " passed a null pointer for @elem"
        const int data = 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(SOL_PTR_NULL, meta, (sol_ptr *) &data));

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




        /* new_test2() defines the test case described by NEW_TEST2 */
static sol_erno new_test2(void)
{
        #define NEW_TEST2 "sol_elem_new() throws SOL_ERNO_PTR if" \
                          " passed a null pointer for @meta"
        const int data = 5;

        auto sol_elem *elem = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_new(&elem, SOL_PTR_NULL, (sol_ptr *) &data));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* new_test3() defines the test case described by NEW_TEST3 */
static sol_erno new_test3(void)
{
        #define NEW_TEST3 "sol_elem_new() throws SOL_ERNO_PTR if" \
                          " passed a null pointer for @data"

        auto sol_elem *elem = SOL_PTR_NULL;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_free(&elem);
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* copy_test1() defines the test case described by COPY_TEST1 */
static sol_erno copy_test1(void)
{
        #define COPY_TEST1 "sol_elem_copy() throws SOL_ERNO_PTR if @elem" \
                           " is null"
        const sol_int DATA = (sol_int) 5;

        sol_elem_meta *meta; /* element metadata */
        sol_elem *src;       /* source element   */

SOL_TRY:
                /* set up test */
        meta = SOL_PTR_NULL;
        sol_try (meta_new(&meta));
        src = SOL_PTR_NULL;
        sol_try (sol_elem_new(&src, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_copy(SOL_PTR_NULL, src));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&src);

        return sol_erno_get();
}




        /* copy_test2() defines the test case described by COPY_TEST2 */
static sol_erno copy_test2(void)
{
        #define COPY_TEST2 "sol_elem_copy() throws SOL_ERNO_STATE if @elem" \
                           " references a non-null pointer"
        const sol_int DATA = (sol_int) 5;

        sol_elem_meta *meta; /* element metadata */
        sol_elem *src;       /* source element   */

SOL_TRY:
                /* set up test */
        meta = SOL_PTR_NULL;
        sol_try (meta_new(&meta));
        src = SOL_PTR_NULL;
        sol_try (sol_elem_new(&src, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_copy(&src, src));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&src);

        return sol_erno_get();
}




        /* copy_test3() defines the test case described by COPY_TEST3 */
static sol_erno copy_test3(void)
{
        #define COPY_TEST3 "sol_elem_copy() throws SOL_ERNO_PTR if @src" \
                           " is null"

        auto sol_elem_meta *meta; /* element metadata   */
        auto sol_elem *elem;      /* contextual element */

SOL_TRY:
                /* set up test */
        meta = SOL_PTR_NULL;
        sol_try (meta_new(&meta));
        elem = SOL_PTR_NULL;
        sol_try (sol_elem_copy(&elem, SOL_PTR_NULL));

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
        #define COPY_TEST4 "sol_elem_copy() increments the reference" \
                           " count of @src"
        const sol_int DATA = (sol_int) 5;

        auto sol_elem_meta *meta; /* element metadata */
        auto sol_elem *src;       /* source element */
        auto sol_elem *cpy1;      /* 1st copy of @src */
        auto sol_elem *cpy2;      /* 2nd copy of @src */

SOL_TRY:
                /* set up test */
        meta = SOL_PTR_NULL;
        sol_try (meta_new(&meta));
        src = cpy1 = cpy2 = SOL_PTR_NULL;
        sol_try (sol_elem_new(&src, meta, (sol_ptr *)&DATA));
        sol_try (sol_elem_copy(&cpy1, src));
        sol_try (sol_elem_copy(&cpy2, src));

                /* check test condition */
        sol_assert (src->nref == (sol_size) 3, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if an exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&src);
        sol_elem_free(&cpy1);
        sol_elem_free(&cpy2);

        return sol_erno_get();
}




        /* copy_test5() defines the test case described by COPY_TEST5 */
static sol_erno copy_test5(void)
{
        #define COPY_TEST5 "sol_elem_copy() sets @elem to non-null if" \
                           " successful"
        const sol_int DATA = (sol_int) 5;

        auto sol_elem_meta *meta; /* element metadata */
        auto sol_elem *src;       /* source element   */
        auto sol_elem *cpy;       /* copy of @src     */

SOL_TRY:
                /* set up test */
        meta = SOL_PTR_NULL;
        sol_try (meta_new(&meta));
        src = cpy = SOL_PTR_NULL;
        sol_try (sol_elem_new(&src, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_copy(&cpy, src));

                /* check test condition */
        sol_assert (cpy, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by if an exception occurs */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&src);
        sol_elem_free(&cpy);

        return sol_erno_get();
}




        /* id_test1() defines the test case described by ID_TEST1 */
static sol_erno id_test1(void)
{
        #define ID_TEST1 "sol_elem_id() throws SOL_ERNO_PTR if passed" \
                         " a null pointer for @elem"

        auto sol_index id; /* element ID */

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_id(SOL_PTR_NULL, &id));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* id_test2() defines the test case described by ID_TEST2 */
static sol_erno id_test2(void)
{
        #define ID_TEST2 "sol_elem_id() throws SOL_ERNO_PTR if passed" \
                         " a null pointer for @id"
        const sol_int data = (sol_int) 5;

        auto sol_elem *elem = SOL_PTR_NULL;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr *) &data));
        sol_try (sol_elem_id(elem, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* id_test3() defines the test case described by ID_TEST3 */
static sol_erno id_test3(void)
{
        #define ID_TEST3 "sol_elem_id() returns the correct ID"
        const sol_int data = (sol_int) 5;

        auto sol_elem *elem = SOL_PTR_NULL;
        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_index id;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr *) &data));
        sol_try (sol_elem_id(elem, &id));

                /* check test condition */
        sol_assert (id == 5, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* sz_test1() defines the test case described by SZ_TEST1 */
static sol_erno sz_test1(void)
{
        #define SZ_TEST1 "sol_elem_sz() throws SOL_ERNO_PTR if passed" \
                         " a null pointer for @elem"
        auto sol_size sz;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_sz(SOL_PTR_NULL, &sz));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        return sol_erno_get();
}




        /* sz_test2() defines the test case described by SZ_TEST2 */
static sol_erno sz_test2(void)
{
        #define SZ_TEST2 "sol_elem_sz() throws SOL_ERNO_PTR if passed" \
                         " a null pointer for @sz"
        const sol_int data = (sol_int) 5;

        auto sol_elem *elem = SOL_PTR_NULL;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr *) &data));
        sol_try (sol_elem_sz(elem, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_free(&elem);
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* sz_test3() defines the test case described by SZ_TEST3 */
static sol_erno sz_test3(void)
{
        #define SZ_TEST3 "sol_elem_sz() returns the correct size"
        const sol_int data = (sol_int) 5;

        auto sol_elem *elem = SOL_PTR_NULL;
        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_size sz;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr *) &data));
        sol_try (sol_elem_sz(elem, &sz));

                /* check test condition */
        sol_assert (sz == sizeof(sol_int), SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* data_test1() defines the test case described by DATA_TEST1 */
static sol_erno data_test1(void)
{
        #define DATA_TEST1 "sol_elem_data() throws SOL_ERNO_PTR if passed" \
                           " a null pointer for @elem"

        auto sol_ptr *data = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (sol_elem_data(SOL_PTR_NULL, &data));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_ptr_free((sol_ptr **) &data);
        return sol_erno_get();
}




        /* data_test2() defines the test case described by DATA_TEST2 */
static sol_erno data_test2(void)
{
        #define DATA_TEST2 "sol_elem_data() throws SOL_ERNO_PTR if passed" \
                           " a null pointer for @data"
        const sol_int data = (sol_int) 5;

        auto sol_elem *elem = SOL_PTR_NULL;
        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr *) &data));
        sol_try (sol_elem_data(elem, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_free(&elem);
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




        /* data_test3() defines the test case described by DATA_TEST3 */
static sol_erno data_test3(void)
{
        #define DATA_TEST3 "sol_elem_data() returns the correct data"
        const sol_int data = 5;

        auto sol_elem *elem = SOL_PTR_NULL;
        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_int *chk = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_data(elem, (sol_ptr**) &chk));

                /* check test condition */
        sol_assert (*chk == data, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        sol_ptr_free((sol_ptr **) &chk);
        return sol_erno_get();
}




        /* lt_test1() defines the test case described by LT_TEST1 */
static sol_erno lt_test1(void)
{
        #define LT_TEST1 "sol_elem_lt() throws SOL_ERNO_PTR if @lhs" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;
        auto SOL_BOOL lt;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_lt(SOL_PTR_NULL, elem, &lt));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* lt_test2() defines the test case described by LT_TEST2 */
static sol_erno lt_test2(void)
{
        #define LT_TEST2 "sol_elem_lt() throws SOL_ERNO_PTR if @rhs" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;
        auto SOL_BOOL lt;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_lt(elem, SOL_PTR_NULL, &lt));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* lt_test3() defines the test case described by LT_TEST3 */
static sol_erno lt_test3(void)
{
        #define LT_TEST3 "sol_elem_lt() throws SOL_ERNO_PTR if @lt" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_lt(elem, elem, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* lt_test4() defines the test case described by LT_TEST4 */
static sol_erno lt_test4(void)
{
        #define LT_TEST4 "sol_elem_lt() throws SOL_ERNO_STATE if @lhs" \
                         " and @rhs are of different types"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta1 = SOL_PTR_NULL;
        auto sol_elem_meta *meta2 = SOL_PTR_NULL;
        auto sol_elem *elem1 = SOL_PTR_NULL;
        auto sol_elem *elem2 = SOL_PTR_NULL;
        auto SOL_BOOL lt;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta1));
        sol_try (meta_new2(&meta2));
        sol_try (sol_elem_new(&elem1, meta1, (sol_ptr *) &data));
        sol_try (sol_elem_new(&elem2, meta2, (sol_ptr *) &data));
        sol_try (sol_elem_lt(elem1, elem2, &lt));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta1);
        sol_elem_meta_free(&meta2);
        sol_elem_free(&elem1);
        sol_elem_free(&elem2);
        return sol_erno_get();
}




        /* lt_test5() defines the test case described by LT_TEST5 */
static sol_erno lt_test5(void)
{
        #define LT_TEST5 "sol_elem_lt() throws SOL_ERNO_STATE if the metadata" \
                         " of @elem does not have a less than delegate defined"
        const sol_int DATA = (sol_int) 5;

        auto sol_elem_meta *meta; /* element metadata  */
        auto sol_elem *lhs;       /* lhs element       */
        auto sol_elem *rhs;       /* rhs element       */
        auto SOL_BOOL lt;         /* comparison result */

SOL_TRY:
                /* init handles */
        meta = SOL_PTR_NULL;
        lhs = rhs = SOL_PTR_NULL;

                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&lhs, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_new(&rhs, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_lt(lhs, rhs, &lt));

SOL_CATCH:
                /* check test condition when exception occurs */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&lhs);
        sol_elem_free(&rhs);

        return sol_erno_get();
}




        /* lt_test6() defines the test case described by LT_TEST6 */
static sol_erno lt_test6(void)
{
        #define LT_TEST6 "sol_elem_lt() correctly executes its less than" \
                         " comparison delegate"
        const sol_int LHSDATA = (sol_int) 4;
        const sol_int RHSDATA = (sol_int) 5;

        auto sol_elem_meta *meta; /* element metadata  */
        auto sol_elem *lhs;       /* LHS element       */
        auto sol_elem *rhs;       /* RHS element       */
        auto SOL_BOOL lt;         /* comparison result */

SOL_TRY:
                /* init handles */
        meta = SOL_PTR_NULL;
        lhs = rhs = SOL_PTR_NULL;

                /* set up test */
        sol_try (meta_new2(&meta));
        sol_try (sol_elem_new(&lhs, meta, (sol_ptr *) &LHSDATA));
        sol_try (sol_elem_new(&rhs, meta, (sol_ptr *) &RHSDATA));

                /* check test condition */
        lt = SOL_BOOL_FALSE;
        sol_try (sol_elem_lt(lhs, rhs, &lt));
        sol_assert (lt, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&lhs);
        sol_elem_free(&rhs);

        return sol_erno_get();
}




        /* eq_test1() defines the test case described by EQ_TEST1 */
static sol_erno eq_test1(void)
{
        #define EQ_TEST1 "sol_elem_eq() throws SOL_ERNO_PTR if @lhs" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;
        auto SOL_BOOL eq;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_eq(SOL_PTR_NULL, elem, &eq));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* eq_test2() defines the test case described by EQ_TEST2 */
static sol_erno eq_test2(void)
{
        #define EQ_TEST2 "sol_elem_eq() throws SOL_ERNO_PTR if @rhs" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;
        auto SOL_BOOL eq;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_lt(elem, SOL_PTR_NULL, &eq));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* eq_test3() defines the test case described by EQ_TEST3 */
static sol_erno eq_test3(void)
{
        #define EQ_TEST3 "sol_elem_eq() throws SOL_ERNO_PTR if @eq" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_eq(elem, elem, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* eq_test4() defines the test case described by EQ_TEST4 */
static sol_erno eq_test4(void)
{
        #define EQ_TEST4 "sol_elem_eq() throws SOL_ERNO_STATE if @lhs" \
                         " and @rhs are of different types"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta1 = SOL_PTR_NULL;
        auto sol_elem_meta *meta2 = SOL_PTR_NULL;
        auto sol_elem *elem1 = SOL_PTR_NULL;
        auto sol_elem *elem2 = SOL_PTR_NULL;
        auto SOL_BOOL eq;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta1));
        sol_try (meta_new2(&meta2));
        sol_try (sol_elem_new(&elem1, meta1, (sol_ptr*) &data));
        sol_try (sol_elem_new(&elem2, meta2, (sol_ptr*) &data));
        sol_try (sol_elem_eq(elem1, elem2, &eq));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta1);
        sol_elem_meta_free(&meta2);
        sol_elem_free(&elem1);
        sol_elem_free(&elem2);
        return sol_erno_get();
}




        /* eq_test5() defines the test case described  by EQ_TEST5 */
static sol_erno eq_test5(void)
{
        #define EQ_TEST5 "sol_elem_eq() throws SOL_ERNO_STATE if the metadata" \
                         " of @elem does not have an equal to delegate defined"
        const sol_int DATA = (sol_int) 5;

        auto sol_elem_meta *meta; /* element metadata  */
        auto sol_elem *lhs;       /* lhs element       */
        auto sol_elem *rhs;       /* rhs element       */
        auto SOL_BOOL eq;         /* comparison result */

SOL_TRY:
                /* init handles */
        meta = SOL_PTR_NULL;
        lhs = rhs = SOL_PTR_NULL;

                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&lhs, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_new(&rhs, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_lt(lhs, rhs, &eq));

SOL_CATCH:
                /* check test condition when exception occurs */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&lhs);
        sol_elem_free(&rhs);

        return sol_erno_get();
}




        /* eq_test6() defines the test case described by EQ_TEST6 */
static sol_erno eq_test6(void)
{
        #define EQ_TEST6 "sol_elem_eq() correctly executes its equal to" \
                         " comparison delegate"
        const sol_int LHSDATA = (sol_int) 5;
        const sol_int RHSDATA = (sol_int) 5;

        auto sol_elem_meta *meta; /* element metadata  */
        auto sol_elem *lhs;       /* LHS element       */
        auto sol_elem *rhs;       /* RHS element       */
        auto SOL_BOOL eq;         /* comparison result */

SOL_TRY:
                /* init handles */
        meta = SOL_PTR_NULL;
        lhs = rhs = SOL_PTR_NULL;

                /* set up test */
        sol_try (meta_new2(&meta));
        sol_try (sol_elem_new(&lhs, meta, (sol_ptr *) &LHSDATA));
        sol_try (sol_elem_new(&rhs, meta, (sol_ptr *) &RHSDATA));

                /* check test condition */
        eq = SOL_BOOL_FALSE;
        sol_try (sol_elem_eq(lhs, rhs, &eq));
        sol_assert (eq, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&lhs);
        sol_elem_free(&rhs);

        return sol_erno_get();
}




        /* gt_test1() defines the test case described by GT_TEST1 */
static sol_erno gt_test1(void)
{
        #define GT_TEST1 "sol_elem_gt() throws SOL_ERNO_PTR if @lhs" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;
        auto SOL_BOOL gt;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_gt(SOL_PTR_NULL, elem, &gt));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* gt_test2() defines the test case described by GT_TEST2 */
static sol_erno gt_test2(void)
{
        #define GT_TEST2 "sol_elem_gt() throws SOL_ERNO_PTR if @rhs" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;
        auto SOL_BOOL gt;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_gt(elem, SOL_PTR_NULL, &gt));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* gt_test3() defines the test case described by LT_TEST3 */
static sol_erno gt_test3(void)
{
        #define GT_TEST3 "sol_elem_gt() throws SOL_ERNO_PTR if @gt" \
                         " is null"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta = SOL_PTR_NULL;
        auto sol_elem *elem = SOL_PTR_NULL;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&elem, meta, (sol_ptr*) &data));
        sol_try (sol_elem_gt(elem, elem, SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&elem);
        return sol_erno_get();
}




        /* gt_test4() defines the test case described by GT_TEST4 */
static sol_erno gt_test4(void)
{
        #define GT_TEST4 "sol_elem_gt() throws SOL_ERNO_STATE if @lhs" \
                         " and @rhs are of different types"
        const sol_int data = (sol_int) 5;

        auto sol_elem_meta *meta1 = SOL_PTR_NULL;
        auto sol_elem_meta *meta2 = SOL_PTR_NULL;
        auto sol_elem *elem1 = SOL_PTR_NULL;
        auto sol_elem *elem2 = SOL_PTR_NULL;
        auto SOL_BOOL gt;

SOL_TRY:
                /* set up test */
        sol_try (meta_new(&meta1));
        sol_try (meta_new2(&meta2));
        sol_try (sol_elem_new(&elem1, meta1, (sol_ptr*) &data));
        sol_try (sol_elem_new(&elem2, meta2, (sol_ptr*) &data));
        sol_try (sol_elem_gt(elem1, elem2, &gt));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta1);
        sol_elem_meta_free(&meta2);
        sol_elem_free(&elem1);
        sol_elem_free(&elem2);
        return sol_erno_get();
}




        /* gt_test5() defines the test case described  by GT_TEST5 */
static sol_erno gt_test5(void)
{
        #define GT_TEST5 "sol_elem_gt() throws SOL_ERNO_STATE if the metadata" \
                         " of @elem does not have a greater than delegate"     \
                         " defined"
        const sol_int DATA = (sol_int) 5;

        auto sol_elem_meta *meta; /* element metadata  */
        auto sol_elem *lhs;       /* lhs element       */
        auto sol_elem *rhs;       /* rhs element       */
        auto SOL_BOOL gt;         /* comparison result */

SOL_TRY:
                /* init handles */
        meta = SOL_PTR_NULL;
        lhs = rhs = SOL_PTR_NULL;

                /* set up test */
        sol_try (meta_new(&meta));
        sol_try (sol_elem_new(&lhs, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_new(&rhs, meta, (sol_ptr *) &DATA));
        sol_try (sol_elem_gt(lhs, rhs, &gt));

SOL_CATCH:
                /* check test condition when exception occurs */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&lhs);
        sol_elem_free(&rhs);

        return sol_erno_get();
}




        /* gt_test6() defines the test case described by GT_TEST6 */
static sol_erno gt_test6(void)
{
        #define GT_TEST6 "sol_elem_gt() correctly executes its greater than" \
                         " comparison delegate"
        const sol_int LHSDATA = (sol_int) 5;
        const sol_int RHSDATA = (sol_int) 4;

        auto sol_elem_meta *meta; /* element metadata  */
        auto sol_elem *lhs;       /* LHS element       */
        auto sol_elem *rhs;       /* RHS element       */
        auto SOL_BOOL gt;         /* comparison result */

SOL_TRY:
                /* init handles */
        meta = SOL_PTR_NULL;
        lhs = rhs = SOL_PTR_NULL;

                /* set up test */
        sol_try (meta_new2(&meta));
        sol_try (sol_elem_new(&lhs, meta, (sol_ptr *) &LHSDATA));
        sol_try (sol_elem_new(&rhs, meta, (sol_ptr *) &RHSDATA));

                /* check test condition */
        gt = SOL_BOOL_FALSE;
        sol_try (sol_elem_gt(lhs, rhs, &gt));
        sol_assert (gt, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* tear down test */
        sol_elem_meta_free(&meta);
        sol_elem_free(&lhs);
        sol_elem_free(&rhs);

        return sol_erno_get();
}




        /* __sol_tests_elem() was declared in sol/test/suite.h */
extern sol_erno __sol_tests_elem(sol_tlog *log,
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

                /* register sol_elem_new() test cases */
        sol_try (sol_tsuite_register(ts, new_test1, NEW_TEST1));
        sol_try (sol_tsuite_register(ts, new_test2, NEW_TEST2));
        sol_try (sol_tsuite_register(ts, new_test3, NEW_TEST3));

                /* register sol_elem_copy() test cases */
        sol_try (sol_tsuite_register(ts, copy_test1, COPY_TEST1));
        sol_try (sol_tsuite_register(ts, copy_test2, COPY_TEST2));
        sol_try (sol_tsuite_register(ts, copy_test3, COPY_TEST3));
        sol_try (sol_tsuite_register(ts, copy_test4, COPY_TEST4));
        sol_try (sol_tsuite_register(ts, copy_test5, COPY_TEST5));

                /* register sol_elem_id() test cases */
        sol_try (sol_tsuite_register(ts, id_test1, ID_TEST1));
        sol_try (sol_tsuite_register(ts, id_test2, ID_TEST2));
        sol_try (sol_tsuite_register(ts, id_test3, ID_TEST3));

                /* register sol_elem_sz() test cases */
        sol_try (sol_tsuite_register(ts, sz_test1, SZ_TEST1));
        sol_try (sol_tsuite_register(ts, sz_test2, SZ_TEST2));
        sol_try (sol_tsuite_register(ts, sz_test3, SZ_TEST3));

                /* register sol_elem_data() test cases */
        sol_try (sol_tsuite_register(ts, data_test1, DATA_TEST1));
        sol_try (sol_tsuite_register(ts, data_test2, DATA_TEST2));
        sol_try (sol_tsuite_register(ts, data_test3, DATA_TEST3));

                /* register sol_elem_lt() test cases */
        sol_try (sol_tsuite_register(ts, lt_test1, LT_TEST1));
        sol_try (sol_tsuite_register(ts, lt_test2, LT_TEST2));
        sol_try (sol_tsuite_register(ts, lt_test3, LT_TEST3));
        sol_try (sol_tsuite_register(ts, lt_test4, LT_TEST4));
        sol_try (sol_tsuite_register(ts, lt_test5, LT_TEST5));
        sol_try (sol_tsuite_register(ts, lt_test6, LT_TEST6));

                /* register sol_elem_eq() test cases */
        sol_try (sol_tsuite_register(ts, eq_test1, EQ_TEST1));
        sol_try (sol_tsuite_register(ts, eq_test2, EQ_TEST2));
        sol_try (sol_tsuite_register(ts, eq_test3, EQ_TEST3));
        sol_try (sol_tsuite_register(ts, eq_test4, EQ_TEST4));
        sol_try (sol_tsuite_register(ts, eq_test5, EQ_TEST5));
        sol_try (sol_tsuite_register(ts, eq_test6, EQ_TEST6));

                /* register sol_elem_gt() test cases */
        sol_try (sol_tsuite_register(ts, gt_test1, GT_TEST1));
        sol_try (sol_tsuite_register(ts, gt_test2, GT_TEST2));
        sol_try (sol_tsuite_register(ts, gt_test3, GT_TEST3));
        sol_try (sol_tsuite_register(ts, gt_test4, GT_TEST4));
        sol_try (sol_tsuite_register(ts, gt_test5, GT_TEST5));
        sol_try (sol_tsuite_register(ts, gt_test6, GT_TEST6));

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

