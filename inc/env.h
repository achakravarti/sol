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




        /* define header guard */
#if (!defined __SOL_ENVIRONMENT_MODULE)
#define __SOL_ENVIRONMENT_MODULE




/*
 * Interface: compiler
 *
 * Synopsis:
 *      #include sol/inc/env.h"
 *
 *      SOL_ENV_CC;
 *      SOL_ENV_CC_GNUC;
 *      SOL_ENV_CC_CLANG;
 *      SOL_ENV_CC sol_env_cc(void);
 *
 * Description:
 *      The compiler interface of the Environment Module of the Sol Library
 *      provides a mechanism for client code to determine at compile time the
 *      compiler being used.
 *
 *      The SOL_ENV_CC family of symbolic constants enumerate the compilers
 *      recognised and supported by the Sol Library. Currently, only GNU C and
 *      CLang compilers are supported directly, and GNU C compatible compilers
 *      indirectly. This is expected to be adequate as far as portability is
 *      concerned, as GNU C is the most widely ported C compiler. However, in
 *      future, support for other compilers, including MSVC, **may** be
 *      introduced if there is adequate reason to do so.
 *
 *      Accordingly, the supported compilers are represented by the SOL_ENV_CC
 *      family of symbolic constants as follows:
 *        - SOL_ENV_CC_GNUC: GNU C or GNU C compatible compiler
 *        - SOL_ENV_CC_CLANG: CLang front-end of LLVM compiler
 *
 *      The sol_env_cc() macro determines at compile-time the C compiler that is
 *      being used. This macro returns one of the SOL_ENV_CC family of constants
 *      as appropriate.
 *
 * Notes:
 *      The SOL_ENV_CC family of symbolic constants are defined as such, and not
 *      as an enumeration, so that they may be used to perform relevant
 *      pre-compilation checks at file scope outside any function body.
 *
 *      In case a compiler other than those recognised and supported by the Sol
 *      Library is used, then the sol_env_cc() macro raises a compiler error.
 */

#define SOL_ENV_CC int
#define SOL_ENV_CC_GNUC (0)
#define SOL_ENV_CC_CLANG (1)

#if (defined __GNUC__)
#       define sol_env_cc() SOL_ENV_CC_GNUC
#elif (defined __clang__)
#       define sol_env_cc() SOL_ENV_CC_CLANG
#else
#       error sol_env_cc(): unsupported C compiler
#endif




        /*
         * SOL_ENV_STDC - enumerates supported C language standards
         *   - SOL_ENV_STDC_C89: C89 standard
         *   - SOL_ENV_STDC_C90: C90 standard
         *   - SOL_ENV_STDC_C94: C94 standard
         *   - SOL_ENV_STDC_C99: C99 standard
         *   - SOL_ENV_STDC_C11: C11 standard
         *   - SOL_ENV_STDC_C18: C18 standard
         *
         * The SOL_ENV_STDC type enumerates the C language standards that are
         * supported by the Sol Library. The constants enumerated by this type
         * are used by the sol_env_stdc() macro (defined below) in order to
         * indicate the compile-time C standard being used.
         *
         * The Sol Library is designed to be backward-compatible with the C89
         * standard, while taking advantage of some of the new features
         * introduced by the modern standards. Backward-compatiblity with the
         * C89 standard ensures maximum portability; dialects predating the C89
         * standard are not considered, as they are fairly archaic and limited
         * only to deprecated compilers.
         */
#define SOL_ENV_STDC int
#define SOL_ENV_STDC_C89 (0)
#define SOL_ENV_STDC_C90 (1)
#define SOL_ENV_STDC_C94 (2)
#define SOL_ENV_STDC_C99 (3)
#define SOL_ENV_STDC_C11 (4)
#define SOL_ENV_STDC_C18 (5)

        /*
         * sol_env_stdc() - determines compile-time C language standard
         *
         * The sol_env_stdc() macro determines at compile-time the C language
         * standard that is being used. This macro returns one of the constants
         * enumerated by the SOL_ENV_STDC type as appropriate. A compile-time
         * error is raised in case an unsupported standard is detected.
         *
         * Return:
         *   - SOL_ENV_STDC_C89 if C89 standard detected
         *   - SOL_ENV_STDC_C90 if C90 standard detected
         *   - SOL_ENV_STDC_C94 if C94 standard detected
         *   - SOL_ENV_STDC_C99 if C99 standard detected
         *   - SOL_ENV_STDC_C11 if C11 standard detected
         *   - SOL_ENV_STDC_C18 if C18 standard detected
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
#       error sol_env_stdc(): unsupported C language standard
#endif




        /*
         * SOL_ENV_HOST - enumerates supported host platforms
         *   - SOL_ENV_HOST_NONE: Freestanding environment
         *   - SOL_ENV_HOST_ANDROID: Android
         *   - SOL_ENV_HOST_LINUX: All other flavours of Linux
         *   - SOL_ENV_HOST_CYGWIN: Cygwin on Microsoft Windows
         *   - SOL_ENV_HOST_BSD: All BSD variants
         *   - SOL_ENV_HOST_HPUX: HP-UX
         *   - SOL_ENV_HOST_AIX: IBM AIX
         *   - SOL_ENV_HOST_IOS: Apple iOS
         *   - SOL_ENV_HOST_OSX: Apple OSX
         *   - SOL_ENV_HOST_SOLARIS: Oracle Solaris / Open Indiana
         *
         * The SOL_ENV_HOST type enumerates the host platforms that are
         * supported by the Sol Library. The constants enumerated by this type
         * are returned by the sol_env_host() macro (defined below) in order to
         * indicate the compile-time host platform.
         *
         * The Sol Library has been designed to support both freestanding and
         * POSIX compliant hosted platforms; however, as of now, only the Linux
         * platform has been tested, and support for the others being assumed
         * based on these tests.
         */
#define SOL_ENV_HOST int
#define SOL_ENV_HOST_NONE (0)
#define SOL_ENV_HOST_ANDROID (1)
#define SOL_ENV_HOST_LINUX (2)
#define SOL_ENV_HOST_CYGWIN (3)
#define SOL_ENV_HOST_BSD (4)
#define SOL_ENV_HOST_HPUX (5)
#define SOL_ENV_HOST_AIX (6)
#define SOL_ENV_HOST_IOS (7)
#define SOL_ENV_HOST_OSX (8)
#define SOL_ENV_HOST_SOLARIS (9)

        /*
         * sol_env_host() - determines compile-time host platform
         *
         * The sol_env_host() macro determines at compile-time the host platform
         * that is being used. This macro returns one of the constants
         * enumerated by the SOL_ENV_HOST type as appropriate. A compile-time
         * error is raised in case an unsupported host is detected.
         *
         * Return:
         *   - SOL_ENV_HOST_NONE if freestanding environment detected
         *   - SOL_ENV_HOST_ANDROID if Android detected
         *   - SOL_ENV_HOST_LINUX if other Linux flavour detected
         *   - SOL_ENV_HOST_CYGWIN if Cygwin on Microsoft Windows detected
         *   - SOL_ENV_HOST_BSD if a BSD variant detected
         *   - SOL_ENV_HOST_HPUX if HP-UX detected
         *   - SOL_ENV_HOST_AIX if IBM AIX detected
         *   - SOL_ENV_HOST_IOS if Apple iOS detected
         *   - SOL_ENV_HOST_OSX if Apple OSX detected
         *   - SOL_ENV_HOST_SOLARIS if Oracle Solaris / Open Indiana detected
         */
#if (defined __CYGWIN__)
#       define sol_env_host() (SOL_ENV_HOST_CYGWIN)
#elif (defined __ANDROID__)
#       define sol_env_host() (SOL_ENV_HOST_ANDROID)
#elif (defined __linux__)
#       define sol_env_host() (SOL_ENV_HOST_LINUX)
#elif (defined __hpux)
#       define sol_env_host() (SOL_ENV_HOST_HPUX)
#elif (defined _AIX)
#       define sol_env_host() (SOL_ENV_HOST_AIX)
#elif (defined __sun && defined __SVR4)
#       define sol_env_host() (SOL_ENV_HOST_SOLARIS)
#elif (defined __unix__)
#       include <sys/param.h>
#       if (defined BSD)
#               define sol_env_host() (SOL_ENV_HOST_BSD)
#       endif
#elif (defined __APPLE__ && defined __MACH__)
#       include <TargetConditionals.h>
#       if (TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1)
#               define sol_env_host() (SOL_ENV_HOST_IOS)
#       elif (TARGET_OS_MAC == 1)
#               define sol_env_host() (SOL_ENV_HOST_OSX)
#       endif
#elif (defined __STDC_HOSTED__)
#       if (__STDC_HOSTED__ == 0)
#               define sol_env_host() (SOL_ENV_HOST_NONE)
#       endif
#else
#       error sol_env_host(): unsupported host platform
#endif




        /*
         * SOL_ENV_ARCH - enumerates supported CPU architectures
         *   - SOL_ENV_ARCH_X68: 32-bit x86 processor
         *   - SOL_ENV_ARCH_AMD64: 64-bit x86_64 processor
         *   - SOL_ENV_ARCH_IA64: 64-bit Itanium processor
         *   - SOL_ENV_ARCH_ARM: 32-bit ARM processor
         *   - SOL_ENV_ARCH_ARM64: 64-bit ARM64 processor
         *
         * The SOL_ENV_ARCH type enumerates the CPU architectures supported by
         * the Sol Library. The constants enumerated by this type are returned
         * by the sol_env_arch() macro (defined below) in order to indicate the
         * processor architecture at compile-time.
         *
         * The Sol Library currently supports the 32-bit ARM and x86 processor
         * families, and the 64-bit ARM64, x86_64 and Itanium family of
         * processors. The Sol Library has been tested on the x86_64
         * architecture, and support for the others is assumed based on these
         * tests.
         */
#define SOL_ENV_ARCH int
#define SOL_ENV_ARCH_X86 (0)
#define SOL_ENV_ARCH_AMD64 (1)
#define SOL_ENV_ARCH_IA64 (2)
#define SOL_ENV_ARCH_ARM (3)
#define SOL_ENV_ARCH_ARM64 (4)

        /*
         * sol_env_arch() - determines compile-time CPU architecture
         *
         * The sol_env_arch() macro determines at compile-time the processor
         * architecture that is being used. This macro returns one of the
         * constants enumerated by the SOL_ENV_ARCH type as appropriate. A
         * compile-time error is raised in case an unsupported architecture is
         * detected.
         *
         * Return:
         *   - SOL_ENV_ARCH_X68 if 32-bit x86 processor detected
         *   - SOL_ENV_ARCH_AMD64 if 64-bit x86_64 processor detected
         *   - SOL_ENV_ARCH_IA64 if 64-bit Itanium processor detected
         *   - SOL_ENV_ARCH_ARM if 32-bit ARM processor detected
         *   - SOL_ENV_ARCH_ARM64 if 64-bit ARM64 processor detected
         */
#if (defined __amd64__ || defined __amd64                           \
     || defined __x86_64__  || defined __x86_64)
#       define sol_env_arch() SOL_ENV_ARCH_AMD64
#elif (defined __ia64__ || defined __IA64__ || defined _IA64)
#       define sol_env_arch() SOL_ENV_ARCH_IA64
#elif (defined i386 || defined __i386 || defined __i386__           \
       || defined __i486__ || defined __i586__ || defined __i686__)
#       define sol_env_arch() SOL_ENV_ARCH_X86
#elif (defined __arm__ || defined __thumb__)
#       define sol_env_arch() SOL_ENV_ARCH_ARM
#elif (defined __aarch64__)
#       define sol_env_arch() SOL_ENV_ARCH_ARM64
#else
#       error sol_env_arch(): unsupported architecture
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
#elif (SOL_ENV_ARCH_ARM == sol_env_arch())
#       define sol_env_wordsz() 32
#elif (SOL_ENV_ARCH_AMD64 == sol_env_arch())
#       define sol_env_wordsz() 64
#elif (SOL_ENV_ARCH_IA64 == sol_env_arch())
#       define sol_env_wordsz() 64
#elif (SOL_ENV_ARCH_ARM64 == sol_env_arch())
#       define sol_env_wordsz() 64
#else
#       error "[!] sol_env_wordsz() error: unsupported architecture"
#endif




/*
 * Interface: introspection
 *
 * Synopsis:
 *      #include "sol/inc/env.h"
 *
 *      const char* sol_env_file(void);
 *      const char* sol_env_func(void);
 *      int sol_env_line(void);
 *
 * Description:
 *      The introspection interface of the Environment Module of the Sol Library
 *      provides a mechanism for client code to determine at compile time the
 *      current point of execution.
 *
 *      The sol_env_file() macro returns the name of the source file where the
 *      current point of execution resides. The sol_env_func() macro returns the
 *      name of the function where the current point of execution resides. The
 *      sol_env_line() macro returns the line number where the current point of
 *      execution resides.
 *
 * Notes:
 *      The sol_env_func() macro is available only if C99 and above is used for
 *      compilation; in case C89 or C90 is used, then sol_env_func() returns a
 *      string set to "<unknown>" and issues a compiler warning.
 */

#define sol_env_file() __FILE__

#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define sol_env_func() __func__
#elif (sol_env_cc() == SOL_ENV_CC_GNUC || sol_env_cc() == SOL_ENV_CC_CLANG)
#       define sol_env_func() __FUNCTION__
#else
#       define sol_env_func() "<unknown>"
#       warning sol_env_func(): unable to determine function name
#endif

#define sol_env_line() __LINE__




#endif /* (!defined __SOL_ENVIRONMENT_MODULE) */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

