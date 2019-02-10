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


#if (defined __GNUC__) || (defined __clang__)
#       define sol_hot __attribute__((hot))
#else
#       define sol_hot
#endif


#if (defined __GNUC__) || (defined __clang__)
#       define sol_cold __attribute__((cold))
#else
#       define sol_cold
#endif


#if (defined __GNUC__) || (defined __clang__)
#       define sol_likely(p) (__builtin_expect(!!(p), 1))
#else
#       define sol_likely(p) (p)
#endif


#if (defined __GNUC__) || (defined __clang__)
#       define sol_unlikely(p) (__builtin_expect(!!(p), 0))
#else
#       define sol_unlikely(p) (p)
#endif


#endif /* !defined __SOL_COMPILER_HINTS_MODULE */


/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

