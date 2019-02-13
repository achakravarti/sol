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




#if (!defined __SOL_ENVIRONMENT_MODULE)
#define __SOL_ENVIRONMENT_MODULE




/*
 *      SOL_ENV_CC - enumerates supported C compilers
 *        - SOL_ENV_CC_GNUC : GNU C or GNU C compatible compiler
 *        - SOL_ENV_CC_CLANG: CLang front-end of LLVM compiler
 *
 *      The SOL_ENV_CC type enumerates the C compilers that are supported by the
 *      Sol Library. The constants enumerated by this type are returned by the
 *      sol_env_cc() macro (defined below) in order to indicate the C compiler
 *      being used at compile-time.
 *
 *      Currently, only GNU C and CLang compilers are supported directly, and
 *      GNU C compatible compilers indirectly. This is expected to be adequate
 *      as far as portability is concerned, as GNU C is the most widely ported C
 *      compiler. However, in future, support for other compilers, including
 *      MSVC, *may* be introduced if there is adequate reason to do so.
 */
typedef enum __SOL_ENV_CC {
        SOL_ENV_CC_GNUC,
        SOL_ENV_CC_CLANG
} SOL_ENV_CC;




/*
 *      SOL_ENV_STDC - enumerates supported C language standards
 *        - SOL_ENV_STDC_C89: C89 standard
 *        - SOL_ENV_STDC_C90: C90 standard
 *        - SOL_ENV_STDC_C94: C94 standard
 *        - SOL_ENV_STDC_C99: C99 standard
 *        - SOL_ENV_STDC_C11: C11 standard
 *        - SOL_ENV_STDC_C18: C18 standard
 *
 *      The SOL_ENV_STDC type enumerates the C language standards that are
 *      supported by the Sol Library. The constants enumerated by this type are
 *      used by the sol_env_stdc() macro (defined below) in order to indicate
 *      the compile-time C standard being used.
 *
 *      The Sol Library is designed to be backward-compatible with the C89
 *      standard, while taking advantage of some of the new features introduced
 *      by the modern standards. Backward-compatiblity with the C89 standard
 *      ensures maximum portability; dialects predating the C89 standard are not
 *      considered, as they are fairly archaic and limited only to deprecated
 *      compilers.
 */
typedef enum __SOL_ENV_STDC {
        SOL_ENV_STDC_C89,
        SOL_ENV_STDC_C90,
        SOL_ENV_STDC_C94,
        SOL_ENV_STDC_C99,
        SOL_ENV_STDC_C11,
        SOL_ENV_STDC_C18
} SOL_ENV_STDC;




/*
 *      SOL_ENV_HOST - enumerates supported host platforms
 *        - SOL_ENV_HOST_ANDROID: Android
 *        - SOL_ENV_HOST_LINUX  : All other flavours of Linux
 *        - SOL_ENV_HOST_CYGWIN : Cygwin on Microsoft Windows
 *        - SOL_ENV_HOST_BSD    : All BSD variants
 *        - SOL_ENV_HOST_HPUX   : HP-UX
 *        - SOL_ENV_HOST_AIX    : IBM AIX
 *        - SOL_ENV_HOST_IOS    : Apple iOS
 *        - SOL_ENV_HOST_OSX    : Apple OSX
 *        - SOL_ENV_HOST_SOLARIS: Oracle Solaris / Open Indiana
 *
 *      The SOL_ENV_HOST type enumerates the host platforms that are supported
 *      by the Sol Library. The constants enumerated by this type are returned
 *      by the sol_env_host() macro (defined below) in order to indicate the
 *      compile-time host platform.
 *
 *      The Sol Library has been designed to support both freestanding and POSIX
 *      compliant hosted platforms; however, as of now, only the Linux platform
 *      has been tested, and support for the others being assumed based on these
 *      tests.
 */
typedef enum __SOL_ENV_HOST {
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




/*
 *      SOL_ENV_ARCH - enumerates supported CPU architectures
 *        - SOL_ENV_ARCH_X68  : 32-bit x86 processor
 *        - SOL_ENV_ARCH_AMD64: 64-bit x86_64 processor
 *        - SOL_ENV_ARCH_IA64 : 64-bit Itanium processor
 *
 *      The SOL_ENV_ARCH type enumerates the CPU architectures supported by the
 *      Sol Library. The constants enumerated by this type are returned by the
 *      sol_env_host() macro (defined below) in order to indicate the processor
 *      architecture at compile-time.
 *
 *      The Sol Library currently supports the 32-bit x86 family of processors,
 *      and the 64-bit x86_64 and Itanium family of processors. The Sol Library
 *      has been tested on the x86_64 architecture, and support for the others
 *      is assumed based on these tests.
 */
typedef enum __SOL_ENV_ARCH {
        SOL_ENV_ARCH_X86,
        SOL_ENV_ARCH_AMD64,
        SOL_ENV_ARCH_IA64
} SOL_ENV_ARCH;




/*
 *      sol_env_cc() - determines C compiler at compile-time
 *
 *      The sol_env_cc() macro determines at compile-time the C compiler that is
 *      being used. This macro returns one of the constants enumerated by the
 *      SOL_ENV_CC type as appropriate. A compile-time error is raised in case
 *      an unsupported compiler is detected.
 *
 *      Return:
 *        - SOL_ENV_CC_GNUC if GNU C or GNU C compatible compiler detected
 *        - SOL_ENV_CC_CLANG if CLang compiler detected
 */
#if (defined __GNUC__)
#       define sol_env_cc() SOL_ENV_CC_GNUC
#elif (defined __clang__)
#       define sol_env_cc() SOL_ENV_CC_CLANG
#else
#       error "[!] sol_env_cc() error: unsupported C compiler"
#endif




/*
 *      sol_env_stdc() - determines compile-time C language standard
 *
 *      The sol_env_stdc() macro determines at compile-time the C language
 *      standard that is being used. This macro returns one of the constants
 *      enumerated by the SOL_ENV_STDC type as appropriate. A compile-time error
 *      is raised in case an unsupported standard is detected.
 *
 *      Return:
 *        - SOL_ENV_STDC_C89 if C89 standard detected
 *        - SOL_ENV_STDC_C90 if C90 standard detected
 *        - SOL_ENV_STDC_C94 if C94 standard detected
 *        - SOL_ENV_STDC_C99 if C99 standard detected
 *        - SOL_ENV_STDC_C11 if C11 standard detected
 *        - SOL_ENV_STDC_C18 if C18 standard detected
 *
 */
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
#       error "[!] sol_env_stdc() error: unsupported C language standard"
#endif




/*
 *      sol_env_host() - determines compile-time host platform
 *
 *      The sol_env_host() macro determines at compile-time the host platform
 *      that is being used. This macro returns one of the constants enumerated
 *      by the SOL_ENV_HOST type as appropriate. A compile-time error is raised
 *      in case an unsupported host is detected.
 *
 *      Return:
 *        - SOL_ENV_HOST_ANDROID if Android detected
 *        - SOL_ENV_HOST_LINUX if other Linux flavour detected
 *        - SOL_ENV_HOST_CYGWIN if Cygwin on Microsoft Windows detected
 *        - SOL_ENV_HOST_BSD if a BSD variant detected
 *        - SOL_ENV_HOST_HPUX if HP-UX detected
 *        - SOL_ENV_HOST_AIX if IBM AIX detected
 *        - SOL_ENV_HOST_IOS if Apple iOS detected
 *        - SOL_ENV_HOST_OSX if Apple OSX detected
 *        - SOL_ENV_HOST_SOLARIS if Oracle Solaris / Open Indiana detected
 */
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
#       error "[!] sol_env_host() error: unsupported host platform"
#endif




/*
 *      sol_env_arch() - determines compile-time CPU architecture
 *
 *      The sol_env_arch() macro determines at compile-time the processor
 *      architecture that is being used. This macro returns one of the constants
 *      enumerated by the SOL_ENV_ARCH type as appropriate. A compile-time error
 *      is raised in case an unsupported architecture is detected.
 *
 *      Return:
 *        - SOL_ENV_ARCH_X68 if 32-bit x86 processor detected
 *        - SOL_ENV_ARCH_AMD64 if 64-bit x86_64 processor detected
 *        - SOL_ENV_ARCH_IA64 if 64-bit Itanium processor detected
 */
#if (defined __amd64__ || defined __amd64                          \
     || defined __x86_64__  || defined __x86_64)
#       define sol_env_arch() SOL_ENV_ARCH_AMD64
#elif (defined __ia64__ || defined __IA64__ || defined _IA64)
#       define sol_env_arch() SOL_ENV_ARCH_IA64
#elif (defined i386 || defined __i386 || defined __i386__          \
       || defined __i486__ || defined __i586__ || defined __i686__)
#       define sol_env_arch() SOL_ENV_ARCH_X86
#else
#       error "[!] sol_env_arch() error: unsupported architecture"
#endif




/*
 *      sol_env_wordsz() - determines compile-time native word size
 *
 *      The sol_env_wordsz() macro determines the native word size of the
 *      processor at compile-time. This macro supports only the architectures
 *      defined by the SOL_ENV_ARCH type, with a compile-time error being thrown
 *      for other processors.
 *
 *      Return:
 *        - 32 if 32-bit processor detected
 *        - 64 if 64-bit processor detected
 */
#if (SOL_ENV_ARCH_X86 == sol_env_arch())
#       define sol_env_wordsz() 32
#elif (SOL_ENV_ARCH_AMD64 == sol_env_arch())
#       define sol_env_wordsz() 64
#elif (SOL_ENV_ARCH_IA64 == sol_env_arch())
#       define sol_env_wordsz() 64
#else
#       error "[!] sol_env_wordsz() error: unsupported architecture"
#endif




#endif /* (!defined __SOL_ENVIRONMENT_MODULE) */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

