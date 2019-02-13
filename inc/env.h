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
        SOL_ENV_COMPILER_UNKNOWN,
        SOL_ENV_COMPILER_GNUC,
        SOL_ENV_COMPILER_CLANG
} SOL_ENV_COMPILER;




typedef enum __SOL_ENV_STDC {
        SOL_ENV_STDC_UNKNOWN,
        SOL_ENV_STDC_C89,
        SOL_ENV_STDC_C90,
        SOL_ENV_STDC_C94,
        SOL_ENV_STDC_C99,
        SOL_ENV_STDC_C11,
        SOL_ENV_STDC_C18
} SOL_ENV_STDC;




typedef enum __SOL_ENV_HOST {
        SOL_ENV_HOST_UNKNOWN,
        SOL_ENV_HOST_ANDROID,
        SOL_ENV_HOST_LINUX,
        SOL_ENV_HOST_CYGWIN,
        SOL_ENV_HOST_BSD,
        SOL_ENV_HOST_HPUX,
        SOL_ENV_HOST_AIX,
        SOL_ENV_HOST_IOS,
        SOL_ENV_HOST_OSX,
        SOL_ENV_HOST_SOLARIS
} SOL_ENV_HOST;




typedef enum __SOL_ENV_ARCH {
        SOL_ENV_ARCH_UNKNOWN,
        SOL_ENV_ARCH_X86,
        SOL_ENV_ARCH_AMD64,
        SOL_ENV_ARCH_IA64
} SOL_ENV_ARCH;




#if (defined __GNUC__)
#       define sol_env_compiler() SOL_ENV_COMPILER_GNUC
#elif (defined __clang__)
#       define sol_env_compiler() SOL_ENV_COMPILER_CLANG
#else
#       define sol_env_compiler() SOL_ENV_COMPILER_UNKNOWN
#endif




#if (defined __STDC__)
#       if (defined __STDC_VERSION__)
#               if (__STDC_VERSION__ >= 201710L)
#                       define sol_env_stdc() SOL_ENV_STDC_C18
#               elif (__STDC_VERSION__ >= 201112L)
#                       define sol_env_stdc() SOL_ENV_STDC_C11
#               elif (__STDC_VERSION__ >= 199901L)
#                       define sol_env_stdc() SOL_ENV_STDC_C99
#               elif (__STDC_VERSION__ >= 199409L)
#                       define sol_env_stdc() SOL_ENV_STDC_C94
#               else
#                       define sol_env_stdc() SOL_ENV_STDC_C90
#               endif
#       else
#               define sol_env_stdc() SOL_ENV_STDC_C89
#       endif
#else
#       define sol_env_stdc() SOL_ENV_STDC_UNKNOWN
#endif




#if (defined __CYGWIN__)
#       define sol_env_host() SOL_ENV_HOST_CYGWIN
#elif (defined __ANDROID__)
#       define sol_env_host() SOL_ENV_HOST_ANDROID
#elif (defined __linux__)
#       define sol_env_host() SOL_ENV_HOST_LINUX
#elif (defined __hpux)
#       define sol_env_host() SOL_ENV_HOST_HPUX
#elif (defined _AIX)
#       define sol_env_host() SOL_ENV_HOST_AIX
#elif (defined __sun && defined __SVR4)
#       define sol_env_host() SOL_ENV_HOST_SOLARIS
#elif (defined __unix__)
#       include <sys/param.h>
#       if (defined BSD)
#               define sol_env_host() SOL_ENV_HOST_BSD
#       endif
#elif (defined __APPLE__ && defined __MACH__)
#       include <TargetConditionals.h>
#       if (1 == TARGET_IPHONE_SIMULATOR || 1 == TARGET_OS_IPHONE)
#               define sol_env_host() SOL_ENV_HOST_IOS
#       elif (1 == TARGET_OS_MAC)
#               define sol_env_host() SOL_ENV_HOST_OSX
#       endif
#else
#       define sol_env_host() SOL_ENV_HOST_UNKNOWN
#endif




#if (defined __amd64__ || defined __amd64                          \
     || defined __x86_64__  || defined __x86_64)
#       define sol_env_arch() SOL_ENV_ARCH_AMD64
#elif (defined __ia64__ || defined __IA64__ || defined _IA64)
#       define sol_env_arch() SOL_ENV_ARCH_IA64
#elif (defined i386 || defined __i386 || defined __i386__          \
       || defined __i486__ || defined __i586__ || defined __i686__)
#       define sol_env_arch() SOL_ENV_ARCH_X86
#else
#       define sol_env_arch() SOL_ENV_ARCH_UNKNOWN
#endif




#if (SOL_ENV_ARCH_X86 == sol_env_arch())
#       define sol_env_wordsz() 32
#elif (SOL_ENV_ARCH_AMD64 == sol_env_arch())
#       define sol_env_wordsz() 64
#elif (SOL_ENV_ARCH_IA64 == sol_env_arch())
#       define sol_env_wordsz() 64
#else
#       error "sol_env_wordsz() error: unknown compiler!"
#endif




#endif /* __SOL_ENVIRONMENT_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

