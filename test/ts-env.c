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




        /* include required header files */
#include "./suite.h"




/*
 *      test_cc1() - sol_env_cc() unit test #1
 */
static sol_erno test_cc1(void)
{
        #define DESC_CC1 "sol_env_cc() determines the C compiler being used" \
                         " for compilation"
        auto SOL_ENV_CC cc;

SOL_TRY:
                /* set up test scenario */
        cc = sol_env_cc();

                /* check test condition */
        sol_assert (SOL_ENV_CC_GNUC == cc || SOL_ENV_CC_CLANG == cc,
                    SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_stdc1() - sol_env_stdc() unit test #1
 */
static sol_erno test_stdc1(void)
{
        #define DESC_STDC1 "sol_env_stdc() determines the standard C version" \
                           " being used for compilation"
        auto SOL_ENV_STDC stdc;

SOL_TRY:
                /* set up test scenario */
        stdc = sol_env_stdc();

                /* check test condition */
        sol_assert (SOL_ENV_STDC_C89 == stdc || SOL_ENV_STDC_C90 == stdc
                    || SOL_ENV_STDC_C94 == stdc || SOL_ENV_STDC_C99 == stdc
                    || SOL_ENV_STDC_C11 == stdc || SOL_ENV_STDC_C18 == stdc,
                    SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_host1() - sol_env_host() unit test #1
 */
static sol_erno test_host1(void)
{
        #define DESC_HOST1 "sol_env_host() determines the host environment" \
                           " being used for compilation"
        auto SOL_ENV_HOST host;

SOL_TRY:
                /* set up test scenario */
        host = sol_env_host();

                /* check test condition */
        sol_assert (SOL_ENV_HOST_NONE == host || SOL_ENV_HOST_ANDROID == host
                    || SOL_ENV_HOST_LINUX == host || SOL_ENV_HOST_CYGWIN == host
                    || SOL_ENV_HOST_BSD == host || SOL_ENV_HOST_HPUX == host
                    || SOL_ENV_HOST_AIX == host || SOL_ENV_HOST_IOS == host
                    || SOL_ENV_HOST_OSX == host || SOL_ENV_HOST_SOLARIS == host,
                    SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_arch1() - sol_env_arch() unit test #1
 */
static sol_erno test_arch1(void)
{
        #define DESC_ARCH1 "sol_env_arch() determines the CPU architecture" \
                           " being used for compilation"
        auto SOL_ENV_ARCH arch;

SOL_TRY:
                /* set up test scenario */
        arch = sol_env_arch();

                /* check test condition */
        sol_assert (SOL_ENV_ARCH_X86 == arch || SOL_ENV_ARCH_AMD64 == arch
                    || SOL_ENV_ARCH_IA64 == arch || SOL_ENV_ARCH_ARM == arch
                    || SOL_ENV_ARCH_ARM64 == arch,
                    SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      test_wordsz1() - sol_env_wordsz() unit test #1
 */
static sol_erno test_wordsz1(void)
{
        #define DESC_WORDSZ1 "sol_env_arch() determines the native word size" \
                             " of the CPU being used for compilation"

SOL_TRY:
                /* check test condition */
        sol_assert (32 == sol_env_wordsz() || 64 == sol_env_wordsz(),
                    SOL_ERNO_TEST);

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      __sol_tests_env() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tests_env(sol_tlog *log,
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
        sol_try (sol_tsuite_register(ts, &test_cc1, DESC_CC1));
        sol_try (sol_tsuite_register(ts, &test_stdc1, DESC_STDC1));
        sol_try (sol_tsuite_register(ts, &test_host1, DESC_HOST1));
        sol_try (sol_tsuite_register(ts, &test_arch1, DESC_ARCH1));
        sol_try (sol_tsuite_register(ts, &test_wordsz1, DESC_WORDSZ1));

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

