/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/hint.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the compiler hints module.
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




#if !defined __SOL_COMPILER_HINTS_MODULE
#define __SOL_COMPILER_HINTS_MODULE




#include "./env.h"




/*
 *      sol_hot - hot code hint
 *
 *      The sol_hot symbolic constant provides a compiler hint that the code of
 *      the function it is associated with is frequently called. Using this hint
 *      helps to provide compile-time optimisations to the associated code. This
 *      hint is available on GCC-compatible compilation environments, and
 *      degrades gracefully to a safe no-op on other environments.
 */
#if (SOL_ENV_CC_GNUC == sol_env_cc() || SOL_ENV_CC_CLANG == sol_env_cc())
#       define sol_hot __attribute__((hot))
#else
#       define sol_hot
#endif




/*
 *      sol_cold - cold code hint
 *
 *      The sol_cold symbolic constant provides a compiler hint that the code of
 *      the function it is associated with is rarely called. Using this hint
 *      helps to provide compile-time optimisations to the associated code. This
 *      hint is available on GCC-compatible compilation environments, and
 *      degrades gracefully to a safe no-op on other environments.
 */
#if (SOL_ENV_CC_GNUC == sol_env_cc() || SOL_ENV_CC_CLANG == sol_env_cc())
#       define sol_cold __attribute__((cold))
#else
#       define sol_cold
#endif




/*
 *      sol_likely() - hint that predicate is likely to be true
 *        - p: predicate to evaluate
 *
 *      The sol_likely() macro provides a branch prediction hint to the
 *      compiler, indicating that a predicate @p is likely to be true. This
 *      macro is modelled after the likely() macro in the Linux kernel, and
 *      relies on a GCC-specific extension. However, this macro degrades
 *      gracefully to a safe no-op on non-GCC compatible compilation platforms.
 *
 *      @p is expected to be an integral predicate expression that evaluates to
 *      a Boolean value.
 *
 *      Return:
 *        - 0 if @p evaluates to false
 *        - 1 if @p evaluates to true
 */
#if (SOL_ENV_CC_GNUC == sol_env_cc() || SOL_ENV_CC_CLANG == sol_env_cc())
#       define sol_likely(p) (__builtin_expect(!!(p), 1))
#else
#       define sol_likely(p) (p)
#endif




/*
 *      sol_unlikely() - hint that predicate is unlikely to be true
 *        - p: predicate to evaluate
 *
 *      The sol_unlikely() macro provides a branch prediction hint to the
 *      compiler, indicating that a predicate @p is unlikely to be true. This
 *      macro is modelled after the unlikely() macro in the Linux kernel, and
 *      relies on a GCC-specific extension. However, this macro degrades
 *      gracefully to a safe no-op on non-GCC compatible compilation platforms.
 *
 *      @p is expected to be an integral predicate expression that evaluates to
 *      a Boolean value.
 *
 *      Return:
 *        - 0 if @p evaluates to false
 *        - 1 if @p evaluates to true
 */
#if (SOL_ENV_CC_GNUC == sol_env_cc() || SOL_ENV_CC_CLANG == sol_env_cc())
#       define sol_unlikely(p) (__builtin_expect(!!(p), 0))
#else
#       define sol_unlikely(p) (p)
#endif




/*
 *      sol_likely - hint that function should be inlined
 *
 *      The sol_inline symbolic constant provides a mechanism to portably hint
 *      to the compiler that a given function should be considered for inlining.
 *      This symbol expands to the inline keyword when C99 and above is used,
 *      and gracefully degrades on earlier versions.
 *
 *      If inlining is essential in dialects predating C99, then the only way
 *      out is to declare the inline code as a macro, optionally wrapped in a
 *      do-while(0) loop.
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define sol_inline inline
#else
#       define sol_inline
#endif




/*
 *      sol_restrict - hint that a pointer is restricted
 *
 *      The sol_restrict symbolic constant provides a mechanism to portably hint
 *      to the compiler that a given pointer should be considered as restricted.
 *      This symbol expands to the restrict keyword when C99 and above is used,
 *      and gracefully degrades on earlier versions.
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define sol_restrict restrict
#else
#       define sol_restrict
#endif




#endif /* !defined __SOL_COMPILER_HINTS_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

