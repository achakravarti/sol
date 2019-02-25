/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-env.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the environment module.
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




#include "../inc/env.h"
#include "./suite.h"




/*
 *      cc_01() - sol_env_cc() unit test #1
 */
static sol_erno cc_01(void)
{
        #define CC_01 "sol_env_cc() is able to determine the C compiler being" \
                      " used for compilation"

SOL_TRY:
                /* check test condition */
        sol_assert (sol_env_cc() >= 0, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      stdc_01() - sol_env_stdc() unit test #1
 */
static sol_erno stdc_01(void)
{
        #define STDC_01 "sol_env_stdc() is able to determine the standard" \
                        " C version being used for compilation"

SOL_TRY:
                /* check test condition */
        sol_assert (sol_env_stdc() >= 0, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      host_01() - sol_env_host() unit test #1
 */
static sol_erno host_01(void)
{
        #define HOST_01 "sol_env_host() is able to determine the host" \
                        " environment being used for compilation"

SOL_TRY:
                /* check test condition */
        sol_assert (sol_env_host() >= 0, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      arch_01() - sol_env_arch() unit test #1
 */
static sol_erno arch_01(void)
{
        #define ARCH_01 "sol_env_arch() is able to determine the CPU" \
                        " architecture being used for compilation"

SOL_TRY:
                /* check test condition */
        sol_assert (sol_env_arch() >= 0, SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      wordsz_01() - sol_env_wordsz() unit test #1
 */
static sol_erno wordsz_01(void)
{
        #define WORDSZ_01 "sol_env_arch() is able to determine the native"   \
                          " word size of the CPU being used for compilation"

SOL_TRY:
                /* check test condition */
        sol_assert (32 == sol_env_wordsz() || 64 == sol_env_wordsz(),
                    SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      __sol_tests_env() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tests_env(sol_tlog *log,
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
        sol_try (sol_tsuite_register(ts, &cc_01, CC_01));
        sol_try (sol_tsuite_register(ts, &stdc_01, STDC_01));
        sol_try (sol_tsuite_register(ts, &host_01, HOST_01));
        sol_try (sol_tsuite_register(ts, &arch_01, ARCH_01));
        sol_try (sol_tsuite_register(ts, &wordsz_01, WORDSZ_01));

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
        sol_throw();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

