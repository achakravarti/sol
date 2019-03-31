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
#       include <inttypes.h>
#endif




        /*
         * SOL_BOOL - a Boolean value
         *   - SOL_BOOL_FALSE: Boolean value 'False'
         *   - SOL_BOOL_TRUE: Boolean value 'True'
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
         * SOL_BOOL_FMT - format specifier for SOL_BOOL
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_BOOL_FMT PRId32
#else
#       define SOL_BOOL_FMT "d"
#endif




        /*
         * sol_w8 - 8-bit word
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint8_t sol_w8;
#else
        typedef unsigned char sol_w8;
#endif

        /*
         * SOL_W8_NULL: sol_w8 null value
         */
#define SOL_W8_NULL ((sol_w8) 0x0)

        /*
         * SOL_W8_MIN - minimum value of sol_w8
         */
#define SOL_W8_MIN ((sol_w8) 0x0)

        /*
         * SOL_W8_MAX - maximum value of sol_w8
         */
#define SOL_W8_MAX ((sol_w8) 0xFF)

        /*
         * SOL_W8_FMT - format specifier for sol_w8
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_W8_FMT PRIu32
#else
#       define SOL_W8_FMT "u"
#endif




        /*
         * sol_w16 - 16-bit word
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint16_t sol_w16;
#else
        typedef unsigned short int sol_w16;
#endif

        /*
         * SOL_W16_NULL: sol_w16 null value
         */
#define SOL_W16_NULL ((sol_w16) 0x0)

        /*
         * SOL_W16_MIN - minimum value of sol_w16
         */
#define SOL_W16_MIN ((sol_w16) 0x0)

        /*
         * SOL_W16_MAX - maximum value of sol_w16
         */
#define SOL_W16_MAX ((sol_w16) 0xFFFF)

        /*
         * SOL_W16_FMT - format specifier for sol_w16
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_W16_FMT PRIu32
#else
#       define SOL_W16_FMT "u"
#endif




        /*
         * sol_w32 - 32-bit word
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint32_t sol_w32;
#else
        typedef unsigned int sol_w32;
#endif

        /*
         * SOL_W32_NULL: sol_w32 null value
         */
#define SOL_W32_NULL ((sol_w32) 0x0)

        /*
         * SOL_W32_MIN - minimum value of sol_w32
         */
#define SOL_W32_MIN ((sol_w32) 0x0)

        /*
         * SOL_W32_MAX - maximum value of sol_w32
         */
#define SOL_W32_MAX ((sol_w32) 0xFFFFFFFF)

        /*
         * SOL_W32_FMT - format specifier for sol_w32
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_W32_FMT PRIu32
#else
#       define SOL_W32_FMT "u"
#endif




        /*
         * sol_w64 - 64-bit word
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint64_t sol_w64;
#elif (sol_env_wordsz() == 64)
        typedef unsigned long sol_w64;
#else
#       error sol_w64: 64-bit types not supported in current environment
#endif

        /*
         * SOL_W64_NULL: sol_w64 null value
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_W64_NULL ((sol_w64) 0x0)
#else
#       error SOL_W64_NULL: 64-bit types not supported in current environment
#endif

        /*
         * SOL_W64_MIN - minimum value of sol_w64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_W64_MIN ((sol_w64) 0x0)
#else
#       error SOL_W64_MIN: 64-bit types not supported in current environment
#endif

        /*
         * SOL_W64_MAX - maximum value of sol_w64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_W32_MAX ((sol_w32) 0xFFFFFFFFFFFFFFFF)
#else
#       error SOL_W64_MAX: 64-bit types not supported in current environment
#endif

        /*
         * SOL_W64_FMT - format specifier for sol_w64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_W64_FMT PRIu64
#elif (sol_env_wordsz() == 64)
#       define SOL_W64_FMT "lu"
#else
#       error SOL_W64_FMT: 64-bit types not supported in current environment
#endif




        /*
         * sol_word - native size word
         */
#if (sol_env_wordsz() == 64)
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
                typedef uint_fast64_t sol_word;
#       else
                typedef sol_w64 sol_word;
#       endif
#else
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
                typedef uint_fast32_t sol_word;
#       else
                typedef sol_w32 sol_word;
#       endif
#endif

        /*
         * SOL_WORD_NULL - sol_word null value
         */
#define SOL_WORD_NULL ((sol_word) 0x0)

        /*
         * SOL_WORD_MIN - minimum value of sol_word
         */
#define SOL_WORD_MIN ((sol_word) 0x0)

        /*
         * SOL_WORD_MAX - maximum value of sol_word
         */
#if (sol_env_wordsz() == 64)
#       define SOL_WORD_MAX SOL_W64_MAX
#else
#       define SOL_WORD_MAX SOL_W32_MAX
#endif

        /*
         * SOL_WORD_FMT - format specifier for sol_word
         */
#if (sol_env_wordsz() == 64)
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#               define SOL_WORD_FMT PRIuFAST64
#       else
#               define SOL_WORD_FMT SOL_W64_FMT
#       endif
#else
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#               define SOL_WORD_FMT PRIuFAST32
#       else
#               define SOL_WORD_FMT SOL_W32_FMT
#       endif
#endif




        /*
         * sol_size - size value
         */
typedef sol_word sol_size;

        /*
         * SOL_SIZE_MIN - minimum value of sol_size
         */
#define SOL_SIZE_MIN SOL_WORD_MIN

        /*
         * SOL_SIZE_MAX - maximum value of sol_size
         */
#define SOL_SIZE_MAX SOL_WORD_MAX

        /*
         * SOL_SIZE_FMT - format specifier for sol_size
         */
#define SOL_SIZE_FMT SOL_WORD_FMT




        /*
         * sol_index - index value
         */
typedef sol_word sol_index;

        /*
         * SOL_INDEX_MIN - minimum value of sol_index
         */
#define SOL_INDEX_MIN SOL_WORD_MIN

        /*
         * SOL_INDEX_MAX - maximum value of sol_index
         */
#define SOL_INDEX_MAX SOL_WORD_MAX

        /*
         * SOL_INDEX_FMT - format specifier for sol_index
         */
#define SOL_INDEX_FMT SOL_WORD_FMT




        /*
         * sol_i8 - 8-bit signed integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef int8_t sol_i8;
#else
        typedef signed char sol_i8;
#endif

        /*
         * SOL_I8_MIN - minimum value of sol_i8
         */
#define SOL_I8_MIN ((sol_i8) -127)

        /*
         * SOL_I8_MAX - maximum value of sol_i8
         */
#define SOL_I8_MAX ((sol_i8) 127)

        /*
         * SOL_I8_FMT - format specifier for sol_i8
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_I8_FMT PRId32
#else
#       define SOL_I8_FMT "d"
#endif




        /*
         * sol_i16 - 16-bit signed integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef int16_t sol_i16;
#else
        typedef signed short int sol_i16;
#endif

        /*
         * SOL_I16_MIN - minimum value of sol_i16
         */
#define SOL_I16_MIN ((sol_i16) -32767)

        /*
         * SOL_I16_MAX - maximum value of sol_i16
         */
#define SOL_I16_MAX ((sol_i16) 32767)

        /*
         * SOL_I16_FMT - format specifier for sol_i16
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_I16_FMT PRId32
#else
#       define SOL_I16_FMT "d"
#endif




        /*
         * sol_i32 - 32-bit signed integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef int32_t sol_i32;
#else
        typedef signed int sol_i32;
#endif

        /*
         * SOL_I32_MIN - minimum value of sol_i32
         */
#define SOL_I32_MIN ((sol_i32) -2147483647)

        /*
         * SOL_I32_MAX - maximum value of sol_i32
         */
#define SOL_I32_MAX ((sol_i32) 2147483647)

        /*
         * SOL_I32_FMT - format specifier for sol_i32
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_I32_FMT PRId32
#else
#       define SOL_I32_FMT "d"
#endif




        /*
         * sol_i64 - 64-bit signed integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef int64_t sol_i64;
#elif (sol_env_wordsz() == 64)
        typedef signed long sol_i64;
#else
#       error sol_i64: 64-bit types not supported in current environment
#endif

        /*
         * SOL_I64_MIN - minimum value of sol_i64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_I64_MIN ((sol_i64) -9223372036854775807)
#else
#       error SOL_I64_MIN: 64-bit types not supported in current environment
#endif

        /*
         * SOL_I64_MAX - maximum value of sol_i64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_I64_MAX ((sol_i64) 9223372036854775807)
#else
#       error SOL_I64_MAX: 64-bit types not supported in current environment
#endif

        /*
         * SOL_I64_FMT - format specifier for sol_i64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_I64_FMT PRId64
#elif (sol_env_wordsz() == 64)
#       define SOL_I64_FMT "ld"
#else
#       error SOL_I64_FMT: 64-bt types not supported in current environment
#endif




        /*
         * sol_int - native size signed integer
         */
#if (sol_env_wordsz() == 64)
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
                typedef int_fast64_t sol_int;
#       else
                typedef sol_i64 sol_int;
#       endif
#else
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
                typedef int_fast32_t sol_int;
#       else
                typedef sol_i32 sol_int;
#       endif
#endif

        /*
         * SOL_INT_MIN - minimum value of sol_int
         */
#if (sol_env_wordsz() == 64)
#       define SOL_INT_MIN SOL_I64_MIN
#else
#       define SOL_INT_MIN SOL_I32_MIN
#endif

        /*
         * SOL_INT_MAX - maximum value of sol_int
         */
#if (sol_env_wordsz() == 64)
#       define SOL_INT_MAX SOL_I64_MAX
#else
#       define SOL_INT_MAX SOL_I32_MAX
#endif

        /*
         * SOL_INT_FMT - format specifier for sol_int
         */
#if (sol_env_wordsz() == 64)
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#               define SOL_INT_FMT PRIdFAST64
#       else
#               define SOL_INT_FMT SOL_I64_FMT
#       endif
#else
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#               define SOL_INT_FMT PRIdFAST32
#       else
#               define SOL_INT_FMT SOL_I32_FMT
#       endif
#endif




        /*
         * sol_u8 - 8-bit unsigned integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint8_t sol_u8;
#else
        typedef unsigned char sol_u8;
#endif

        /*
         * SOL_U8_MIN - minimum value of sol_u8
         */
#define SOL_U8_MIN ((sol_u8) 0)

        /*
         * SOL_U8_MAX - maximum value of sol_u8
         */
#define SOL_U8_MAX ((sol_u8) 255)

        /*
         * SOL_U8_FMT - format specifier for sol_u8
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_U8_FMT PRIu32
#else
#       define SOL_U8_FMT "u"
#endif




        /*
         * sol_u16 - 16-bit signed integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint16_t sol_u16;
#else
        typedef unsigned short int sol_u16;
#endif

        /*
         * SOL_U16_MIN - minimum value of sol_u16
         */
#define SOL_U16_MIN ((sol_u16) 0)

        /*
         * SOL_U16_MAX - maximum value of sol_u16
         */
#define SOL_U16_MAX ((sol_u16) 65535)

        /*
         * SOL_U16_FMT - format specifier for sol_u16
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_U16_FMT PRIu32
#else
#       define SOL_U16_FMT "u"
#endif




        /*
         * sol_u32 - 32-bit unsigned integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint32_t sol_u32;
#else
        typedef unsigned int sol_u32;
#endif

        /*
         * SOL_U32_MIN - minimum value of sol_u32
         */
#define SOL_U32_MIN ((sol_u32) 0)

        /*
         * SOL_U32_MAX - maximum value of sol_u32
         */
#define SOL_U32_MAX ((sol_u32) 4294967295)

        /*
         * SOL_U32_FMT - format specifier for sol_u32
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_U32_FMT PRIu32
#else
#       define SOL_U32_FMT "u"
#endif




        /*
         * sol_u64 - 64-bit unsigned integer
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
        typedef uint64_t sol_u64;
#elif (sol_env_wordsz() == 64)
        typedef signed long sol_u64;
#else
#       error sol_u64: 64-bit types not supported in current environment
#endif

        /*
         * SOL_U64_MIN - minimum value of sol_u64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_U64_MIN ((sol_u64) 0)
#else
#       error SOL_U64_MIN: 64-bit types not supported in current environment
#endif

        /*
         * SOL_U64_MAX - maximum value of sol_u64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99 || sol_env_wordsz() == 64)
#       define SOL_U64_MAX ((sol_u64) 18446744073709551615)
#else
#       error SOL_U64_MAX: 64-bit types not supported in current environment
#endif

        /*
         * SOL_U64_FMT - format specifier for sol_u64
         */
#if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#       define SOL_U64_FMT PRIu64
#elif (sol_env_wordsz() == 64)
#       define SOL_U64_FMT "lu"
#else
#       error SOL_U64_FMT: 64-bit types not supported in current environment
#endif




        /*
         * sol_uint - native size unsigned integer
         */
#if (sol_env_wordsz() == 64)
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
                typedef uint_fast64_t sol_uint;
#       else
                typedef sol_u64 sol_uint;
#       endif
#else
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
                typedef uint_fast32_t sol_uint;
#       else
                typedef sol_u32 sol_uint;
#       endif
#endif

        /*
         * SOL_UINT_MIN - minimum value of sol_uint
         */
#define SOL_UINT_MIN ((sol_uint) 0x0)

        /*
         * SOL_UINT_MAX - maximum value of sol_uint
         */
#if (sol_env_wordsz() == 64)
#       define SOL_UINT_MAX SOL_U64_MAX
#else
#       define SOL_UINT_MAX SOL_U32_MAX
#endif

        /*
         * SOL_UINT_FMT - format specifier for sol_uint
         */
#if (sol_env_wordsz() == 64)
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#               define SOL_UINT_FMT PRIuFAST64
#       else
#               define SOL_UINT_FMT SOL_U64_FMT
#       endif
#else
#       if (sol_env_stdc() >= SOL_ENV_STDC_C99)
#               define SOL_UINT_FMT PRIuFAST32
#       else
#               define SOL_UINT_FMT SOL_U32_FMT
#       endif
#endif




        /*
         * sol_f32 - 32-bit floating point number
         */
typedef float sol_f32;

        /*
         * SOL_F32_MIN - minimum value of sol_f32
         */
#define SOL_F32_MIN ((sol_f32) -1e+37)

        /*
         * SOL_F32_MAX - maximum value of sol_f32
         */
#define SOL_F32_MAX ((sol_f32) 1e+37)

        /*
         * SOL_F32_FMT - format specifier for sol_f32
         */
#define SOL_F32_FMT "f"




        /*
         * sol_f64 - 64-bit floating point number
         */
typedef double sol_f64;

        /*
         * SOL_F64_MIN - minimum value of sol_f64
         */
#define SOL_F64_MIN ((sol_f64) -1e+37)

        /*
         * SOL_F64_MAX - maximum value of sol_f64
         */
#define SOL_F64_MAX ((sol_f64) 1e+37)

        /*
         * SOL_F64_FMT - format specifier for sol_f64
         */
#define SOL_F64_FMT "f"




        /*
         * sol_float - native size floating point number
         */
#if (sol_env_wordsz() == 64)
        typedef double sol_float;
#else
        typedef float sol_float;
#endif

        /*
         * SOL_FLOAT_MIN - minimum value of sol_float
         */
#define SOL_FLOAT_MIN ((sol_float) -1e+37)

        /*
         * SOL_FLOAT_MAX - maximum value of sol_float
         */
#define SOL_FLOAT_MAX ((sol_float) 1e+37)

        /*
         * SOL_FLOAT_FMT - format specifier for sol_f64
         */
#define SOL_FLOAT_FMT "f"




#endif /* (!defined __SOL_PRIMITIVES_MODULE) */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

