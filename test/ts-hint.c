/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-hint.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the compiler hints module.
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
#include "../inc/hint.h"




/*
 *      gcc_off() - toggles GCC compiler identification off
 */
static void gcc_off(void)
{
        #if (defined __GNUC__)
                #define __sol_test_hint_gcc __GNUC__
                #undef __GNUC__
        #endif
}




/*
 *      clang_off() - toggles CLang compiler identification off
 */
static void clang_off(void)
{
        #if (defined __clang__)
                #define __sol_test_hint_clang __clang__
                #undef __clang__
        #endif
}




/*
 *      gcc_on() - toggles GCC compiler identification on
 */
static void gcc_on(void)
{
        #if (defined __sol_test_hint_gcc)
        #       define __GNUC__ __sol_test_hint_gcc
        #       undef __sol_test_hint_gcc
        #endif
}




/*
 *      clang_on() - toggles CLang compiler identification on
 *
 */
static void clang_on(void)
{
        #if (defined __sol_test_hint_clang)
        #       define __clang__ __sol_test_hint_clang
        #       undef __sol_test_hint_clang
        #endif
}




/*
 *      mock_hot() - mocks definition of hot function
 */
static sol_hot sol_int mock_hot(void)
{
        return 1;
}




/*
 *      mock_cold() - mocks definition of cold function
 */
static sol_cold sol_int mock_cold(void)
{
        return 1;
}




/*
 *      mock_inline() - mocks definition of inline function
 */
static sol_inline sol_int mock_inline(void)
{
        return 1;
}




/*
 *      mock_restrict() - mocks use of restrict pointer
 */
static int mock_restrict(sol_int *sol_restrict ptr)
{
        *ptr = 1;
        return *ptr;
}




/*
 *      likely_01() - sol_likely() unit test #1
 */
#if (defined __GNUC__ || defined __clang__)
static sol_erno likely_01(void)
{
        #define LIKELY_01 "A predicate evaluates correctly to True with a"     \
                          " likely branch prediction hint on a GCC-compatible" \
                          " compiler"

SOL_TRY:
                /* check test condition */
        sol_assert (sol_likely (1), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}
#endif /* (defined __GNUC__ || defined __clang__) */




/*
 *      likely_02() - sol_likely() unit test #2
 */
#if (defined __GNUC__ || defined __clang__)
static sol_erno likely_02(void)
{
        #define LIKELY_02 "A predicate evaluates correctly to False with a"    \
                          " likely branch prediction hint on a GCC-compatible" \
                          " compiler"

SOL_TRY:
                /* check test condition */
        sol_assert (!sol_likely (0), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}
#endif /* (defined __GNUC__ || defined __clang__) */




/*
 *      likely_03() - sol_likely() unit test #3
 */
static sol_erno likely_03(void)
{
        #define LIKELY_03 "A predicate evaluates correctly to True with a" \
                          " likely branch prediction hint on a non GCC-"   \
                          " compatible compiler"

SOL_TRY:
                /* set up test scenario */
        gcc_off();
        clang_off();

                /* check test condition */
        sol_assert (sol_likely (1), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        gcc_on();
        clang_on();
        return sol_erno_get();
}




/*
 *      likely_04() - sol_likely() unit test #4
 */
static sol_erno likely_04(void)
{
        #define LIKELY_04 "A predicate evaluates correctly to False with a" \
                          " likely branch prediction hint on a non GCC-"    \
                          "compatible compiler"

SOL_TRY:
                /* set up test scenario */
        gcc_off();
        clang_off();

                /* check test condition */
        sol_assert (!sol_likely (0), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        gcc_on();
        clang_on();
        return sol_erno_get();
}




/*
 *      unlikely_01() - sol_unlikely() unit test #1
 */
#if (defined __GNUC__ || defined __clang__)
static sol_erno unlikely_01(void)
{
        #define UNLIKELY_01 "A predicate evaluates correctly to True with an" \
                            " unlikely branch prediction hint on a GCC-"      \
                            "compatible compiler"

SOL_TRY:
                /* check test condition */
        sol_assert (sol_unlikely (1), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}
#endif /* (defined __GNUC__ || defined __clang__) */




/*
 *      unlikely_02() - sol_unlikely() unit test #2
 */
#if (defined __GNUC__ || defined __clang__)
static sol_erno unlikely_02(void)
{
        #define UNLIKELY_02 "A predicate evaluates correctly to False with an" \
                            " unlikely branch prediction hint on a GCC-"       \
                            "compatible compiler"

SOL_TRY:
                /* check test condition */
        sol_assert (!sol_unlikely (0), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}
#endif /* (defined __GNUC__ || defined __clang__) */




/*
 *      unlikely_03() - sol_unlikely() unit test #3
 */
static sol_erno unlikely_03(void)
{
        #define UNLIKELY_03 "A predicate evaluates correctly to True with an" \
                            " unlikely branch prediction hint on a non GCC-"  \
                            "compatible compiler"

SOL_TRY:
                /* set up test scenario */
        gcc_off();
        clang_off();

                /* check test condition */
        sol_assert (sol_unlikely (1), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        gcc_on();
        clang_on();
        return sol_erno_get();
}




/*
 *      unlikely_04() - sol_unlikely() unit test #4
 */
static sol_erno unlikely_04(void)
{
        #define UNLIKELY_04 "A predicate evaluates correctly to False with an" \
                            " unlikely branch prediction hint on a non GCC-"   \
                            "compatible compiler"

SOL_TRY:
                /* set up test scenario */
        gcc_off();
        clang_off();

                /* check test condition */
        sol_assert (!sol_unlikely (0), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        gcc_on();
        clang_on();
        return sol_erno_get();
}




/*
 *      hot_01() - sol_hot unit test #1
 */
static sol_erno hot_01(void)
{
        #define HOT_01 "A function marked hot executes successfully on a GCC-" \
                       "compatible compiler"

SOL_TRY:
                /* check test condition */
        sol_assert (mock_hot(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* throw current exception, if any */
        return sol_erno_get();
}




/*
 *      hot_02() - sol_hot unit test #2
 */
static sol_erno hot_02(void)
{
        #define HOT_02 "A function marked hot executes successfully on a non " \
                       " GCC-compatible compiler"

SOL_TRY:
                /* set up test scenario */
        gcc_off();
        clang_off();

                /* check test condition */
        sol_assert (mock_hot(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        gcc_on();
        clang_on();
        return sol_erno_get();
}




/*
 *      cold_01() - sol_cold unit test #1
 */
static sol_erno cold_01(void)
{
        #define COLD_01 "A function marked cold executes successfully on a" \
                        " GCC-compatible compiler"

SOL_TRY:
                /* check test condition */
        sol_assert (mock_cold(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      cold_02() - sol_cold unit test #2
 */
static sol_erno cold_02(void)
{
        #define COLD_02 "A function marked cold executes successfully on a" \
                        " non GCC-compatible compiler"

SOL_TRY:
                /* set up test scenario */
        gcc_off();
        clang_off();

                /* check test condition */
        sol_assert (mock_cold(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        gcc_on();
        clang_on();
        return sol_erno_get();
}




/*
 *      inline_01() - sol_inline unit test #1
 */
static sol_erno inline_01(void)
{
        #define INLINE_01 "A function marked inline executes successfully on" \
                          " a GCC-compatible compiler"

SOL_TRY:
                /* check test condition */
        sol_assert (mock_inline(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      inline_02() - sol_inline unit test #2
 */
static sol_erno inline_02(void)
{
        #define INLINE_02 "A function marked inline executes successfully on" \
                          " a non GCC-compatible compiler"

SOL_TRY:
                /* set up test scenario */
        gcc_off();
        clang_off();

                /* check test condition */
        sol_assert (mock_inline(), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        gcc_on();
        clang_on();
        return sol_erno_get();
}




/*
 *      restrict_01() - sol_restrict unit test #1
 */
static sol_erno restrict_01(void)
{
        #define RESTRICT_01 "A pointer marked restricted behaves as expected"
        auto sol_int tmp = 0;

SOL_TRY:
                /* check test condition */
        sol_assert (mock_restrict(&tmp), SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      __sol_hint_test() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tsuite_hint(sol_tlog *log,
                                  sol_uint *pass,
                                  sol_uint *fail,
                                  sol_uint *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);


                /* register non GCC-compatible specific test cases */
        sol_try (sol_tsuite_init2(ts, log));
        sol_try (sol_tsuite_register(ts, &likely_03, LIKELY_03));
        sol_try (sol_tsuite_register(ts, &likely_04, LIKELY_04));
        sol_try (sol_tsuite_register(ts, &unlikely_01, UNLIKELY_01));
        sol_try (sol_tsuite_register(ts, &unlikely_04, UNLIKELY_04));
        sol_try (sol_tsuite_register(ts, &hot_01, HOT_01));
        sol_try (sol_tsuite_register(ts, &hot_02, HOT_02));
        sol_try (sol_tsuite_register(ts, &cold_01, COLD_01));
        sol_try (sol_tsuite_register(ts, &cold_02, COLD_02));
        sol_try (sol_tsuite_register(ts, &inline_01, INLINE_01));
        sol_try (sol_tsuite_register(ts, &inline_02, INLINE_02));
                sol_try (sol_tsuite_register(ts, &restrict_01, RESTRICT_01));

                /* register GCC-compatible specific test cases */
        #if (defined __GNUC__ || defined __clang__)
                sol_try (sol_tsuite_register(ts, &likely_01, LIKELY_01));
                sol_try (sol_tsuite_register(ts, &likely_02, LIKELY_02));
                sol_try (sol_tsuite_register(ts, &unlikely_02, UNLIKELY_02));
                sol_try (sol_tsuite_register(ts, &unlikely_03, UNLIKELY_03));
        #endif

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

