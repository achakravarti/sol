/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/prim.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the primitives module.
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
#if (!defined __SOL_PRIMITIVES_MODULE)
#define __SOL_PRIMITIVES_MODULE




        /* include required header files; the stdbool.h and stdint.h header
         * files are used in case a C99 environment is available */
#include "./env.h"
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       include <stdbool.h>
#       include <stdint.h>
#endif




/*
 *      SOL_BOOL - a Boolean value
 *        - SOL_BOOL_FALSE: Boolean value 'False'
 *        - SOL_BOOL_TRUE: Boolean value 'True'
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef bool SOL_BOOL;
#       define SOL_BOOL_FALSE (false)
#       define SOL_BOOL_TRUE (true)
#else
        typedef int SOL_BOOL;
#       define SOL_BOOL_FALSE ((SOL_BOOL) 0)
#       define SOL_BOOL_TRUE ((SOL_BOOL) 1)
#endif




/*
 *      sol_w8 - 8-bit word
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint8_t sol_w8;
#else
        typedef unsigned char sol_w8;
#endif




/*
 *      SOL_W8_NULL: sol_w8 null value
 */
#define SOL_W8_NULL ((sol_w8) 0x0)




/*
 *      sol_w16 - 16-bit word
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint16_t sol_w16;
#else
        typedef unsigned short int sol_w16;
#endif




/*
 *      SOL_W16_NULL: sol_w16 null value
 */
#define SOL_W16_NULL ((sol_w16) 0x0)




/*
 *      sol_w32 - 32-bit word
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint32_t sol_w32;
#else
        typedef unsigned int sol_w32;
#endif




/*
 *      SOL_W32_NULL: sol_w32 null value
 */
#define SOL_W32_NULL ((sol_w32) 0x0)




/*
 *      sol_w64 - 64-bit word
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint64_t sol_w64;
#elif (sol_env_wordsz() == 64)
        typedef unsigned long sol_w64;
#else
#       error "sol_w64: 64-bit types not supported in current environment"
#endif




/*
 *      SOL_W64_NULL: sol_w64 null value
 */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_W64_NULL ((sol_w64) 0x0)
#else
#       error SOL_W64_NULL: "64-bit types not supported in current environment"
#endif




/*
 *      sol_word - native size word
 */
#if (sol_env_wordsz() == 64)
        typedef sol_w64 sol_word;
#else
        typedef sol_w32 sol_word;
#endif




/*
 *      SOL_WORD_NULL: sol_word null value
 */
#define SOL_WORD_NULL ((sol_word) 0x0)




#endif /* (!defined __SOL_PRIMITIVES_MODULE) */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

