/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-prim.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the primitives module.
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
#include "../inc/prim.h"
#include "suite.h"




        /* bool_test1() implements the unit test described by BOOL_TEST1 */
static sol_erno bool_test1(void)
{
        #define BOOL_TEST1 "SOL_BOOL_TRUE must evaluate to 1"

SOL_TRY:
                /* check test condition */
        sol_assert (SOL_BOOL_TRUE == 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* bool_test2() implements the unit test described by BOOL_TEST2 */
static sol_erno bool_test2(void)
{
        #define BOOL_TEST2 "SOL_BOOL_FALSE must evaluate to 0"

SOL_TRY:
                /* check test condition */
        sol_assert (SOL_BOOL_FALSE == 0, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* w8_test1() implements the unit test described by W8_TEST1 */
static sol_erno w8_test1(void)
{
        #define W8_TEST1 "size of sol_w8 is at least 8 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_w8) >= 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* w16_test1() implements the unit test described by W16_TEST1 */
static sol_erno w16_test1(void)
{
        #define W16_TEST1 "size of sol_w16 is at least 16 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_w16) >= 2, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* w32_test1() implements the unit test described by W32_TEST1 */
static sol_erno w32_test1(void)
{
        #define W32_TEST1 "size of sol_w32 is at least 32 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_w32) >= 4, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* w64_test1() implements the unit test described by W64_TEST1 */
static sol_erno w64_test1(void)
{
        #define W64_TEST1 "size of sol_w64 is at least 64 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_w64) >= 8, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* i8_test1() implements the unit test described by I8_TEST1 */
static sol_erno i8_test1(void)
{
        #define I8_TEST1 "size of sol_i8 is at least 8 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_i8) >= 1, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* i16_test1() implements the unit test described by I16_TEST1 */
static sol_erno i16_test1(void)
{
        #define I16_TEST1 "size of sol_i16 is at least 16 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_i16) >= 2, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* i32_test1() implements the unit test described by I32_TEST1 */
static sol_erno i32_test1(void)
{
        #define I32_TEST1 "size of sol_i32 is at least 32 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_i32) >= 4, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* i64_test1() implements the unit test described by I64_TEST1 */
static sol_erno i64_test1(void)
{
        #define I64_TEST1 "size of sol_i64 is at least 64 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_i64) >= 8, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* u8_test1() implements the unit test described by U8_TEST1 */
static sol_erno u8_test1(void)
{
        #define U8_TEST1 "size of sol_u8 is at least 8 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_u8) >= 1, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* u16_test1() implements the unit test described by U16_TEST1 */
static sol_erno u16_test1(void)
{
        #define U16_TEST1 "size of sol_u16 is at least 16 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_u16) >= 2, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* u32_test1() implements the unit test described by U32_TEST1 */
static sol_erno u32_test1(void)
{
        #define U32_TEST1 "size of sol_u32 is at least 32 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_u32) >= 4, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* u64_test1() implements the unit test described by U64_TEST1 */
static sol_erno u64_test1(void)
{
        #define U64_TEST1 "size of sol_u64 is at least 64 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_u64) >= 8, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* f32_test1() implements the unit test described by F32_TEST1 */
static sol_erno f32_test1(void)
{
        #define F32_TEST1 "size of sol_f32 is at least 32 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_f32) >= 4, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* define the f32_test2() unit test function; this function implements
         * the test case described by the F32_TEST2 symbolic constant */
static sol_erno f32_test2(void)
{
        #define F32_TEST2 "sol_f32_lt() return true if its lhs is less than" \
                          " its rhs"
        const sol_f32 lhs = (sol_f32) 3.141;
        const sol_f32 rhs = (sol_f32) 3.1415;


SOL_TRY:
        sol_assert (sol_f32_lt(lhs, rhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* f32_test3() implements the test case described by F32_TEST3 */
static sol_erno f32_test3(void)
{
        #define F32_TEST3 "sol_f32_eq() returns true if passed two equal" \
                          " sol_f32 values"
        const sol_f32 lhs = (sol_f32) 3.1415;

SOL_TRY:
        sol_assert (sol_f32_eq(lhs, lhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* f32_test4() implements the test case described by F32_TEST4 */
static sol_erno f32_test4(void)
{
        #define F32_TEST4 "sol_f32_gt() returns true if its lhs parameter is" \
                          " greater than its rhs parameter"
        const sol_f32 lhs = 3.1415;
        const sol_f32 rhs = 3.141;

SOL_TRY:
        sol_assert (sol_f32_gt(lhs, rhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* f64_test1() implements the unit test described by F64_TEST1 */
static sol_erno f64_test1(void)
{
        #define F64_TEST1 "size of sol_f64 is at least 64 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_f64) >= 8, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* f64_test2() implements the test case described by F64_TEST2 */
static sol_erno f64_test2(void)
{
        #define F64_TEST2 "sol_f64_lt() returns true when its lhs is less" \
                          " than its rhs"
        const sol_f32 lhs = (sol_f32) 3.1415926;
        const sol_f32 rhs = (sol_f32) 3.14159265;


SOL_TRY:
        sol_assert (sol_f64_lt(lhs, rhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* f64_test3() implements the test case described by F64_TEST3 */
static sol_erno f64_test3(void)
{
        #define F64_TEST3 "sol_f64_eq() returns true if passed two equal" \
                          " sol_f64 values"
        const sol_f64 lhs = (sol_f64) 3.14159265;

SOL_TRY:
        sol_assert (sol_f64_eq(lhs, lhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* f64_test4() implements the test case described by F64_TEST4 */
static sol_erno f64_test4(void)
{
        #define F64_TEST4 "sol_f64_gt() return true if its lhs parameter is" \
                          " greater than its rhs parameter"
        const sol_f32 lhs = 3.14159265;
        const sol_f32 rhs = 3.1415926;

SOL_TRY:
        sol_assert (sol_f64_gt(lhs, rhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* float_test1() implements the unit test described by FLOAT_TEST1 */
static sol_erno float_test1(void)
{
        #define FLOAT_TEST1 "size of sol_float is at least 32 bits"

SOL_TRY:
                /* check test condition */
        sol_assert (sizeof (sol_float) >= 4, SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




        /* float_test2() implements the test case described bh FLOAT_TEST2 */
static sol_erno float_test2(void)
{
        #define FLOAT_TEST2 "sol_float_lt() return true if its lhs is less" \
                            " than its rhs"
        const sol_float lhs = (sol_f32) 3.141;
        const sol_float rhs = (sol_f32) 3.1415;


SOL_TRY:
        sol_assert (sol_float_lt(lhs, rhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* float_test3() implements the test case described by FLOAT_TEST3 */
static sol_erno float_test3(void)
{
        #define FLOAT_TEST3 "sol_float_eq() returns true if passed two equal" \
                            " sol_float values"
        const sol_float lhs = (sol_float) 3.1415;

SOL_TRY:
        sol_assert (sol_float_eq(lhs, lhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* float_test4() implements the test case described by FLOAT_TEST4 */
static sol_erno float_test4(void)
{
        #define FLOAT_TEST4 "sol_float_gt() returns true if its lhs parameter" \
                            " is greater than its rhs parameter"
        const sol_float lhs = 3.1415;
        const sol_float rhs = 3.141;

SOL_TRY:
        sol_assert (sol_float_gt(lhs, rhs), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




        /* __sol_tests_prim() was declared in sol/test/suite.h */
extern sol_erno __sol_tests_prim(sol_tlog *log,
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
        sol_try (sol_tsuite_register(ts, bool_test1, BOOL_TEST1));
        sol_try (sol_tsuite_register(ts, bool_test2, BOOL_TEST2));
        sol_try (sol_tsuite_register(ts, w8_test1, W8_TEST1));
        sol_try (sol_tsuite_register(ts, w16_test1, W16_TEST1));
        sol_try (sol_tsuite_register(ts, w32_test1, W32_TEST1));
        sol_try (sol_tsuite_register(ts, w64_test1, W64_TEST1));
        sol_try (sol_tsuite_register(ts, i8_test1, I8_TEST1));
        sol_try (sol_tsuite_register(ts, i16_test1, I16_TEST1));
        sol_try (sol_tsuite_register(ts, i32_test1, I32_TEST1));
        sol_try (sol_tsuite_register(ts, i64_test1, I64_TEST1));
        sol_try (sol_tsuite_register(ts, u8_test1, U8_TEST1));
        sol_try (sol_tsuite_register(ts, u16_test1, U16_TEST1));
        sol_try (sol_tsuite_register(ts, u32_test1, U32_TEST1));
        sol_try (sol_tsuite_register(ts, u64_test1, U64_TEST1));
        sol_try (sol_tsuite_register(ts, f32_test1, F32_TEST1));
        sol_try (sol_tsuite_register(ts, f32_test2, F32_TEST2));
        sol_try (sol_tsuite_register(ts, f32_test3, F32_TEST3));
        sol_try (sol_tsuite_register(ts, f32_test4, F32_TEST4));
        sol_try (sol_tsuite_register(ts, f64_test1, F64_TEST1));
        sol_try (sol_tsuite_register(ts, f64_test2, F64_TEST2));
        sol_try (sol_tsuite_register(ts, f64_test3, F64_TEST3));
        sol_try (sol_tsuite_register(ts, f64_test4, F64_TEST4));
        sol_try (sol_tsuite_register(ts, float_test1, FLOAT_TEST1));
        sol_try (sol_tsuite_register(ts, float_test2, FLOAT_TEST2));
        sol_try (sol_tsuite_register(ts, float_test3, FLOAT_TEST3));
        sol_try (sol_tsuite_register(ts, float_test4, FLOAT_TEST4));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

