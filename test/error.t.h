/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/error.t.h
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It declares the test cases for the exception handling module.
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
 *      BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAt
 *      YOU HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/




#if !defined __SOL_EXCEPTION_HANDLING_MODULE_TESTS
#define      __SOL_EXCEPTION_HANDLING_MODULE_TESTS




#include "../inc/error.h"




/*
 *      __DESC_ASSERT_01 - description for sol_assert() unit test #1
 *
 *      The __DESC_ASSERT_01 symbolic constant describes the unit test conducted
 *      by the __test_assert_01() test case declared below.
 */
#define __DESC_ASSERT_01 "sol_assert() must not throw an error for a" \
                         " predicate that evaluates to true"




/*
 *      __DESC_ASSERT_02 - description for sol_assert() unit test #2
 *
 *      The __DESC_ASSERT_02 symbolic constant describes the unit test conducted
 *      by the __test_assert_02() test case declared below.
 */
#define __DESC_ASSERT_02 "sol_assert() must throw an error for a" \
                         " predicate that evaluates to false"




/*
 *      __DESC_TRY_01 - description for sol_try() unit test #1
 *
 *      The __DESC_TRY_01 symbolic constant describes the unit test conducted by
 *      the __test_try_01() test case declared below.
 */
#define __DESC_TRY_01 "sol_try() must not throw an error for a function that" \
                      " returns a SOL_ERNO_NULL error code"




/*
 *      __DESC_TRY_02 - description for sol_try() unit test #2
 *
 *      The __DESC_TRY_02 symbolic constant describes the unit test conducted by
 *      the __test_try_02() test case declared below.
 */
#define __DESC_TRY_02 "sol_try() must throw an error for a function that" \
                      " returns an error code other than SOL_ERNO_NULL"




/*
 *      __test_assert_01() - sol_assert() unit test #1
 *
 *      The __test_assert_01() test case performs the unit test described by the
 *      __DESC_ASSERT_01 symbolic constant defined above.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_TEST if this test fails
 */
extern sol_erno
__test_assert_01(void);




/*
 *      __test_assert_02() - sol_assert() unit test #2
 *
 *      The __test_assert_02() test case performs the unit test described by the
 *      __DESC_ASSERT_02 symbolic constant defined above.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_TEST if this test fails
 */
extern sol_erno
__test_assert_02(void);




/*
 *      __test_try_01() - sol_try() unit test #1
 *
 *      The __test_try_01() test case performs the unit test described by the
 *      __DESC_TRY_01 symbolic constant defined above.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_TEST if this test fails
 */
extern sol_erno
__test_try_01(void);




/*
 *      __test_try_02() - sol_try() unit test #2
 *
 *      The __test_try_01() test case performs the unit test described by the
 *      __DESC_TRY_01 symbolic constant defined above.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_TEST if this test fails
 */
extern sol_erno
__test_try_02(void);




#endif /* !defined __SOL_EXCEPTION_HANDLING_MODULE_TESTS */

