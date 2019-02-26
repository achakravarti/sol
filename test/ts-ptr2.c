/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-ptr2.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the pointer module while mocking a
 *      freestanding environment on a hosted environment.
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




        /* proceed only if we're on a hosted environment */
#if (SOL_ENV_HOSTED_NONE != sol_env_host())




        /* mock a freestanding environment on the current hosted environment;
         * include the stdlib.h header file to mock the malloc() and free()
         * functions for the mocked freestanding environment */
#define __SOL_ENV_HOST_BKP sol_env_host()
#undef sol_env_host
#define sol_env_host() SOL_ENV_HOSTED_NONE
#include <stdlib.h>




/*
 *      __sol_tests_ptr2() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tests_ptr2(sol_tlog *log,
                                 int      *pass,
                                 int      *fail,
                                 int      *total)
{
SOL_TRY:
                /* run pointer module test cases in the simulated freestanding
                 * environment */
        sol_try (__sol_tests_ptr(log, pass, fail, total));

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw();
}




        /* reset to original hosted environment */
#undef sol_env_host
#define sol_env_host() __SOL_ENV_HOST_BKP
#undef __SOL_ENV_HOST_BKP




#endif /* SOL_ENV_HOSTED_NONE != sol_env_host() */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

