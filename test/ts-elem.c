/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-elem.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the element interface
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




static void mock_dispose(sol_ptr **disp)
{
        (void) disp;
}




static sol_erno mock_cmp(const sol_ptr *lhs,
                         const sol_ptr *rhs,
                         SOL_BOOL *cmp)
{
        (void) lhs;
        (void) rhs;
        (void) cmp;

        return SOL_ERNO_NULL;
}




static sol_erno meta_new_test1(void)
{
        #define META_NEW_TEST1 "sol_elem_meta_new() throws SOL_ERNO_PTR if" \
                               " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 1;

SOL_TRY:
        sol_try (sol_elem_meta_new(SOL_PTR_NULL, ID, SZ));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        return sol_erno_get();
}




static sol_erno meta_new_test2(void)
{
        #define META_NEW_TEST2 "sol_elem_meta_new() throws SOL_ERNO_RANGE if" \
                               " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
        sol_try (sol_elem_meta_new(&meta, ID, SZ));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




static sol_erno meta_new2_test1(void)
{
        #define META_NEW2_TEST1 "sol_elem_meta_new2() throws SOL_ERNO_PTR if" \
                                " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 1;

SOL_TRY:
        sol_try (sol_elem_meta_new2(SOL_PTR_NULL, ID, SZ, mock_dispose));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        return sol_erno_get();
}




static sol_erno meta_new2_test2(void)
{
        #define META_NEW2_TEST2 "sol_elem_meta_new2() throws SOL_ERNO_RANGE" \
                                " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
        sol_try (sol_elem_meta_new2(&meta, ID, SZ, mock_dispose));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




static sol_erno meta_new2_test3(void)
{
        #define META_NEW2_TEST3 "sol_elem_meta_new2() throws SOL_ERNO_PTR" \
                                " if passed a null pointer for @disp"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
        sol_try (sol_elem_meta_new2(&meta, ID, SZ, SOL_PTR_NULL));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




static sol_erno meta_new3_test1(void)
{
        #define META_NEW3_TEST1 "sol_elem_meta_new3() throws SOL_ERNO_PTR if" \
                                " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 1;

SOL_TRY:
        sol_try (sol_elem_meta_new3(SOL_PTR_NULL,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        return sol_erno_get();
}




static sol_erno meta_new3_test2(void)
{
        #define META_NEW3_TEST2 "sol_elem_meta_new3() throws SOL_ERNO_RANGE" \
                                " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
        sol_try (sol_elem_meta_new3(&meta, ID, SZ, mock_dispose, mock_cmp));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




static sol_erno meta_new3_test3(void)
{
        #define META_NEW3_TEST3 "sol_elem_meta_new3() throws SOL_ERNO_PTR" \
                                " if passed a null pointer for @disp"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
        sol_try (sol_elem_meta_new3(&meta, ID, SZ, SOL_PTR_NULL, mock_cmp));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




static sol_erno meta_new4_test1(void)
{
        #define META_NEW4_TEST1 "sol_elem_meta_new4() throws SOL_ERNO_PTR if" \
                                " passed a null pointer for @meta"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 1;

SOL_TRY:
        sol_try (sol_elem_meta_new4(SOL_PTR_NULL,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        return sol_erno_get();
}




static sol_erno meta_new4_test2(void)
{
        #define META_NEW4_TEST2 "sol_elem_meta_new4() throws SOL_ERNO_RANGE" \
                                " passed zero for @sz"
        const sol_index ID = (sol_index) 1;
        const sol_index SZ = (sol_index) 0;

        auto sol_elem_meta *meta = SOL_PTR_NULL;

SOL_TRY:
        sol_try (sol_elem_meta_new4(&meta,
                                    ID,
                                    SZ,
                                    mock_dispose,
                                    mock_cmp,
                                    mock_cmp,
                                    mock_cmp));

SOL_CATCH:
        sol_erno_set(sol_erno_get() == SOL_ERNO_RANGE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
        sol_elem_meta_free(&meta);
        return sol_erno_get();
}




extern sol_erno __sol_tests_elem(sol_tlog *log,
                                 sol_uint *pass,
                                 sol_uint *fail,
                                 sol_uint *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

        sol_try (sol_tsuite_init2(ts, log));

        sol_try (sol_tsuite_register(ts, meta_new_test1, META_NEW_TEST1));
        sol_try (sol_tsuite_register(ts, meta_new_test2, META_NEW_TEST2));

        sol_try (sol_tsuite_register(ts, meta_new2_test1, META_NEW2_TEST1));
        sol_try (sol_tsuite_register(ts, meta_new2_test2, META_NEW2_TEST2));
        sol_try (sol_tsuite_register(ts, meta_new2_test3, META_NEW2_TEST3));

        sol_try (sol_tsuite_register(ts, meta_new3_test1, META_NEW3_TEST1));
        sol_try (sol_tsuite_register(ts, meta_new3_test2, META_NEW3_TEST2));
        sol_try (sol_tsuite_register(ts, meta_new3_test3, META_NEW3_TEST3));

        sol_try (sol_tsuite_register(ts, meta_new4_test1, META_NEW4_TEST1));
        sol_try (sol_tsuite_register(ts, meta_new4_test2, META_NEW4_TEST2));

        sol_try (sol_tsuite_exec(ts));
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
SOL_FINALLY:
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

