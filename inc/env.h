/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/env.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the environment module.
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




#if !defined __SOL_ENVIRONMENT_MODULE
#define __SOL_ENVIRONMENT_MODULE




typedef enum __SOL_ENV_COMPILER {
        SOL_ENV_COMPILER_GNUC,
        SOL_ENV_COMPILER_CLANG
} SOL_ENV_COMPILER;




typedef enum __SOL_ENV_CSTD {
        SOL_ENV_CSTD_C89,
        SOL_ENV_CSTD_C90,
        SOL_ENV_CSTD_C94,
        SOL_ENV_CSTD_C11,
        SOL_ENV_CSTD_C18
} SOL_ENV_CSTD;




#endif /* __SOL_ENVIRONMENT_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

