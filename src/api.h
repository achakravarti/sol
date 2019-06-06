/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/api.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the modules that make up the Sol Library.
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
#if !defined __SOL_LIBRARY_API_INCLUDED
#define __SOL_LIBRARY_API_INCLUDED




#include "../inc/env.h" /* TODO: remove later */
#include "../inc/hint.h" /* TODO: remove later */




#if (sol_env_host() != SOL_ENV_HOST_NONE)
#       include <stdio.h>
#       include <stdlib.h>
#       include <time.h>
#       include <math.h>
#endif

/*
 *      SOL_LIBC_FILE_DEFINED - stdio.h FILE defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (!defined SOL_LIBC_FILE_DEFINED)
#               error "[!] Sol libc error: FILE not defined"
#       endif
#else
#       define SOL_LIBC_FILE_DEFINED
#endif




/*
 *      SOL_LIBC_TIME_T_DEFINED - time.h time_t defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (!defined SOL_LIBC_TIME_T_DEFINED)
#               error "[!] Sol libc error: time_t not defined"
#       endif
#else
#       define SOL_LIBC_TIME_T_DEFINED
#endif




/*
 *      SOL_LIBC_FOPEN_DEFINED - stdio.h fopen() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_FOPEN_DEFINED)
                extern FILE *fopen(const char*, const char*);
#       else
#               error "[!] Sol libc error: fopen() not defined"
#       endif
#else
#       define SOL_LIBC_FOPEN_DEFINED
#endif




/*
 *      SOL_LIBC_FCLOSE_DEFINED - stdio.h fclose() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_FCLOSE_DEFINED)
                extern int fclose(FILE*);
#       else
#               error "[!] Sol libc error: fclose() not defined"
#       endif
#else
#       define SOL_LIBC_FCLOSE_DEFINED
#endif




/*
 *      SOL_LIBC_FPRINTF_DEFINED - stdio.h fprintf() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_FPRINTF_DEFINED)
                extern int fprintf(FILE*, const char*, ...);
#       else
#               error "[!] Sol libc error: fprintf() not defined"
#       endif
#else
#       define SOL_LIBC_FPRINTF_DEFINED
#endif




/*
 *      SOL_LIBC_FGETS_DEFINED - stdio.h fgets() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_FGETS_DEFINED)
                extern char *fgets(char *s, int size, FILE *stream);
#       else
#               error "[!] Sol libc error: fgets() not defined"
#       endif
#else
#       define SOL_LIBC_FGETS_DEFINED
#endif




/*
 *      SOL_LIBC_MALLOC_DEFINED - stdlib.h malloc() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_MALLOC_DEFINED)
                extern void *malloc(size_t);
#       else
#               error "[!] Sol libc error: malloc() not defined"
#       endif
#else
#       define SOL_LIBC_FPRINTF_DEFINED
#endif




/*
 *      SOL_LIBC_FREE_DEFINED - stdlib.h free() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_MALLOC_DEFINED)
                extern void free(void*);
#       else
#               error "[!] Sol libc error: free() not defined"
#       endif
#else
#       define SOL_LIBC_FPRINTF_DEFINED
#endif




/*
 *      SOL_LIBC_TIME_DEFINED - time.h time() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_TIME_DEFINED)
                extern time_t time(time_t*);
#       else
#               error "[!] Sol libc error: time() not defined"
#       endif
#else
#       define SOL_LIBC_TIME_DEFINED
#endif




/*
 *      SOL_LIBC_CTIME_DEFINED - time.h ctime() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (defined SOL_LIBC_CTIME_DEFINED)
                extern char *ctime(const time_t*);
#       else
#               error "[!] Sol libc error: ctime() not defined"
#       endif
#else
#       define SOL_LIBC_CTIME_DEFINED
#endif




/*
 *      SOL_LIBC_FABS_DEFINED - math.h fabs() defined
 */
#if (sol_env_host() == SOL_ENV_HOST_NONE)
#       if (!defined SOL_LIBC_FABS_DEFINED)
#               error "[!] Sol libc error: fabs() not defined"
#       endif
#else
#       define SOL_LIBC_FABS_DEFINED
#endif




#include <float.h>
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
#       define SOL_W64_MAX ((sol_w32) 0xFFFFFFFFFFFFFFFF)
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

#define SOL_F64_EPSILON DBL_EPSILON

        /*
         * sol_f64_lt() - compares two sol_f64 for less than
         */
extern SOL_BOOL sol_f64_lt(const sol_f64 lhs, const sol_f64 rhs);

        /*
         * sol_f64_eq() - compares two sol_f64 for equality
         */
extern SOL_BOOL sol_f64_eq(const sol_f64 lhs, const sol_f64 rhs);

        /*
         * sol_f64_gt() - compares two sol_f64 for greater than
         */
extern SOL_BOOL sol_f64_gt(const sol_f64 lhs, const sol_f64 rhs);




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

#define SOL_F32_EPSILON FLT_EPSILON

#define sol_f32_lt(lhs, rhs) \
        sol_f64_lt((lhs), (rhs))

#define sol_f32_eq(lhs, rhs) \
        sol_f64_eq((lhs), (rhs))

#define sol_f32_gt(lhs, rhs) \
        sol_f64_gt((lhs), (rhs))




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

#if (sol_env_wordsz() == 64)
#       define SOL_FLOAT_EPSILON SOL_F64_EPSILON
#else
#       define SOL_FLOAT_EPSILON SOL_F32_EPSILON
#endif

#define sol_float_lt(lhs, rhs) \
        sol_f64_lt((lhs), (rhs))

#define sol_float_eq(lhs, rhs) \
        sol_f64_eq((lhs), (rhs))

#define sol_float_gt(lhs, rhs) \
        sol_f64_gt((lhs), (rhs))




/*
 *      sol_erno - generic error code
 *
 *      The sol_erno concrete data type is used to hold error codes. Error codes
 *      may be defined by client code as unsigned integers, with the exception
 *      of the error codes defined below. This type aligns itself to the native
 *      word size of its compilation environment. Any function returning this
 *      type can take advantage of the exception handling features provided by
 *      this module.
 */
typedef sol_word sol_erno;




/*
 *      SOL_ERNO_NULL - no error
 *
 *      The SOL_ERNO_NULL symbolic constant indicates that no error has
 *      occurred. This error code is reserved by the Sol Library, and should
 *      **not** be redefined by client code. Functions that take advantage of
 *      the try-catch mechanism implemented by this module (through the SOL_TRY
 *      and SOL_CATCH labels) return this symbolic constant by default if they
 *      don't encounter any errors during execution.
 */
#define SOL_ERNO_NULL ((sol_erno) 0x0)




/*
 *      SOL_ERNO_PTR - invalid pointer
 *
 *      The SOL_ERNO_PTR symbolic constant indicates that an invalid pointer has
 *      been passed to an interface function or macro. This error code is
 *      reserved by the Sol Library, and should **not** be redefined by client
 *      code.
 */
#define SOL_ERNO_PTR ((sol_erno) 0x1)




/*
 *      SOL_ERNO_STR - invalid string
 *
 *      The SOL_ERNO_STR symbolic constant indicates that an invalid string has
 *      been passed to an interface function or macro. An invalid string is not
 *      necessarily a null string, and will depend on the context. Note that
 *      this error code should not be used to indicate null string pointers, and
 *      should be indicated by SOL_ERNO_PTR instead. This error code is reserved
 *      by the Sol Library, and should **not** be redefined by client code.
 */
#define SOL_ERNO_STR ((sol_erno) 0x2)




/*
 *      SOL_ERNO_RANGE - range error
 *
 *      The SOL_ERNO_RANGE symbolic constant indicates that a value that is
 *      outside its acceptable range has been passed to an interface function or
 *      macro. This error code is reserved by the Sol Library, and should
 *      **not** be redefined by client code.
 */
#define SOL_ERNO_RANGE ((sol_erno) 0x3)




/*
 *      SOL_ERNO_TEST - unit test failure
 *
 *      The SOL_ERNO_TEST symbolic constant indicates that a unit test failed.
 *      Note that this error code does not indicate an exception with the
 *      exception handling system, but rather that the condition that a unit
 *      test is checking has not been fulfilled. This error code is reserved by
 *      the Sol Library, and should **not** be redefined by client code.
 */
#define SOL_ERNO_TEST ((sol_erno)0x4)




/*
 *      SOL_ERNO_HEAP - heap memory failure
 */
#define SOL_ERNO_HEAP ((sol_erno)0x5)




/*
 *      SOL_ERNO_FILE - file error
 */
#define SOL_ERNO_FILE ((sol_erno)0x6)




/*
 *      SOL_ERNO_STATE - invalid state
 */
#define SOL_ERNO_STATE ((sol_erno)0x7)




/*
 *      SOL_TRY - start of try block
 *
 *      The SOL_TRY label identifies the starting point of the try block within
 *      a function that returns a sol_erno value. The try block contains the
 *      normal flow of code that may throw exceptions. It must be placed at the
 *      beginning of the function body, right after declaring any required local
 *      variables and constants, and terminated by a SOL_CATCH block.
 *
 *      The code that may throw exceptions within this block must be tested
 *      through the sol_assert() and sol_try() macros defined below. In case an
 *      exception occurs, then control is passed to the adjacent SOL_CATCH
 *      block without executing the remaining code in the try block.
 *
 *      If no error occurs, then control automatically moves to the SOL_FINALLY
 *      block placed after the SOL_CATCH block; this allows for the necessary
 *      cleanup code to be performed.
 */
#define SOL_TRY                                       \
        register sol_erno __sol_erno = SOL_ERNO_NULL; \
        goto __SOL_TRY;                               \
        __SOL_TRY




/*
 *      SOL_CATCH - start of catch block
 *
 *      The SOL_CATCH label identifies the starting point of a catch block
 *      within a function that returns a sol_erno value. The catch block
 *      contains the error handling code, and must be placed immediately at the
 *      end of a SOL_TRY block.
 *
 *      The SOL_CATCH block must be terminated by an adjacent SOL_FINALLY block.
 *      This allows all necessary cleanup code to be performed after the
 *      exception handling code has been executed. At no point should the
 *      sol_assert() and sol_try() macros be used in the SOL_CATCH block, as
 *      this would potentially lead to an infinite loop.
 */
#define SOL_CATCH           \
        goto __SOL_FINALLY; \
        __SOL_CATCH




/*
 *      SOL_FINALLY - start of finally block
 *
 *      The SOL_FINALLY label identifies the starting point of a finally block
 *      within a function that returns a sol_erno value. The finally block
 *      contains the cleanup code that is common to both the try and catch
 *      blocks, and must be placed immediately at the end of a SOL_TRY block.
 *
 *      The SOL_FINALLY block must be terminated by returning the current error
 *      code provided by the sol_erno_get() macro defined below. At no point
 *      should the sol_assert() and sol_try() macros be used in the SOL_FINALLY
 *      block as this could potentially lead to an infinite loop.
 */
#define SOL_FINALLY __SOL_FINALLY




/*
 *      sol_erno_get() - gets current error code
 *
 *      The sol_erno_get() macro returns the current sol_erno error code within
 *      the context of the function in which it is called. This macro is meant
 *      to be used primarily within SOL_CATCH blocks, but if required, may also
 *      be used within SOL_TRY and SOL_FINALLY blocks.
 *
 *      Return:
 *        - SOL_ERNO if no error has occured
 *        - The current error code if an error has occured
 */
#define /* sol_erno */ sol_erno_get(/* void */) \
        ((const sol_erno) __sol_erno)




/*
 *      sol_erno_str() - stringifies error code
 *        - erno: error code
 *
 *      The sol_erno_str() function generates the string representation of a
 *      sol_erno error code @erno. This function represents @erno in hexadecimal
 *      notation prefixed with a "0x".
 *
 *      Return:
 *        - string representation of @erno
 */
extern const char *sol_erno_str(sol_erno erno);




/*
 *      sol_erno_set() - sets current error code
 *        - erno: error code
 *
 *      The sol_erno_set() macro sets the current sol_erno error code @erno
 *      within the context of the function in which it is called. Like its
 *      sister macro sol_erno_get(), this macro is meant to be used within
 *      SOL_CATCH blocks, but may also be used within SOL_TRY and SOL_FINALLY
 *      blocks as required.
 */
#define /* void */ sol_erno_set(/* const sol_erno */ erno) \
        (__sol_erno = (erno))




/*
 *      sol_assert() - verifies precondition
 *        - p: precondition predicate being asserted
 *        - e: error code to be thrown if assertion fails
 *
 *      The sol_assert() macro verifies whether a precondition, expressed as a
 *      predicate @p, is true before any further processing takes place. This
 *      macro can only be called within a SOL_TRY block. If the assertion fails,
 *      then a sol_erno error code @e is thrown and control jumps to the
 *      adjacent SOL_CATCH block.
 *
 *      This macro should **never** be called within a SOL_CATCH block as it may
 *      potentially lead to an infinite loop.
 */
#define /* void */ sol_assert(p, /* sol_erno */ e) \
        do {                                       \
                if (sol_unlikely (!(p))) {         \
                        __sol_erno = (e);          \
                        goto __SOL_CATCH;          \
                }                                  \
        } while (0)




/*
 *      sol_try() - validates postcondition
 *        - p: postcondition being evaluated
 *
 *      The sol_try() macro validates whether a postcondition @p, expressed as a
 *      function returning a sol_erno value, has not failed. The function is
 *      deemed to have run successfully if it has not thrown any exception as
 *      flagged by the returned error code. This macro can only be called within
 *      a SOL_TRY block. If the validation fails, then control will jump to the
 *      adjacent SOL_CATCH block.
 *
 *      As with the sol_assert() macro, this macro should **never** be called
 *      within a SOL_CATCH block as it may potentially lead to an infinite loop.
 */
#define /* void */ sol_try(p)                            \
        do {                                             \
                if (sol_unlikely ((__sol_erno = (p)))) { \
                        goto __SOL_CATCH;                \
                }                                        \
        } while (0)


/*
 *      sol_ptr - generic pointer to any type
 *
 *      The sol_ptr type is an abstract type representing a generic pointer to
 *      data type, including itself. This type can be declared only as a pointer
 *      in order to make it explicitly obvious that a pointer is being used.
 *
 *      The interface functions associated with this type depend on externally
 *      defined malloc() and free() functions in freestanding environments, and
 *      automatically make use of the malloc() and free() functions supplied by
 *      the standard library in hosted environments.
 */
typedef void sol_ptr;




/*
 *      SOL_PTR_NULL - generic null pointer
 *
 *      The SOL_PTR_NULL symbolic constant represents the generic null ponter.
 *      Using this symbolic constant instead of the standard NULL symbol is
 *      preferred because it removes dependence on the standard library and
 *      preserves the Sol namespace.
 */
#define SOL_PTR_NULL ((sol_ptr*)0)




/*
 *      sol_ptr_new() - initialises a new generic pointer
 *        - ptr: contextual pointer instance
 *        - sz : size in bytes of pointer buffer
 *
 *      The sol_ptr_new() interface function creates a new instance of a generic
 *      pointer @ptr in the heap memory with a buffer of size @sz bytes. This
 *      function requires an externally defined malloc() function to be present
 *      in freestanding environments; in hosted environments, it automatically
 *      uses the malloc() supplied by the standard library.
 *
 *      @ptr must be a valid pointer to a **null** pointer; this restriction
 *      helps to prevent subtle memory leaks caused by reallocating @ptr without
 *      having first freed the heap memory already allocated to it. @sz must be
 *      greater than zero. An appropriate exception is thrown if either of these
 *      conditions is not met.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer has been passed
 *        - SOL_ERNO_RANGE if an invalid size has been passed
 *        - SOL_ERNO_HEAP if heap memory failure occurs
 */
extern sol_erno sol_ptr_new(sol_ptr **ptr,
                            sol_size sz);




/*
 *      sol_ptr_copy() - copies an existing generic pointer
 *        - ptr: contextual pointer instance
 *        - src: source pointer instance
 *        - len: length in bytes of @src to copy
 *
 *      The sol_ptr_copy() interface function creates a new instance of a
 *      generic pointer @ptr in the heap memory, and copies @len bytes of data
 *      on to it from an existing buffer pointed by @src. Just as in the case of
 *      sol_ptr_new(), this function requires an externally defined malloc()
 *      function to be present in freestanding environments, while automatically
 *      selecting the malloc() supplied by the standard library in hosted
 *      environments.
 *
 *      Both @ptr and @src are required to be valid pointers; just as in the
 *      case of sol_ptr_new(), @ptr is also required to point to a null pointer
 *      to prevent accidental memory leaks. @len is required to be greater than
 *      zero. An appropriate exception is thrown if either of these conditions
 *      is not met. Additionally, @len is assumed to be not greater than the
 *      length of the buffer pointed by @src; no exception is thrown if this
 *      condition is not met, and the resulting behaviour is undefined.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer has been passed
 *        - SOL_ERNO_RANGE if an invalid size has been passed
 *        - SOL_ERNO_HEAP if heap memory failure occurs
 */
extern sol_erno sol_ptr_copy(sol_ptr **ptr,
                             const sol_ptr *src,
                             sol_size len);




/*
 *      sol_ptr_free() - frees an existing generic pointer
 *        - ptr: contextual pointer instance
 *
 *      The sol_ptr_free() interface function frees a generic pointer @ptr by
 *      releasing the heap memory allocated to it by a previous call to either
 *      sol_ptr_new() or sol_ptr_copy(). This function requires an externally
 *      defined free() function to be present in freestanding environments, and
 *      automatically uses the free() function provided by the standard library
 *      in hosted environments. @ptr is guaranteed to be null after this
 *      operation, thereby preventing the onset of dangling pointers.
 *
 *      @ptr is expected to be a valid handle to a **non-null** pointer, but in
 *      case this condition is not met, then a safe no-op occurs.
 */
extern void sol_ptr_free(sol_ptr **ptr);



typedef struct __sol_elem sol_elem;

typedef struct __sol_elem_meta sol_elem_meta;

typedef void (sol_elem_delegate_dispose)(sol_ptr **data);

typedef sol_erno (sol_elem_delegate_lt)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *lt);

typedef sol_erno (sol_elem_delegate_eq)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *eq);

typedef sol_erno (sol_elem_delegate_gt)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *gt);

extern sol_erno sol_elem_new(sol_elem **elem,
                             const sol_elem_meta *meta,
                             const sol_ptr *data);

extern sol_erno sol_elem_copy(sol_elem **elem, const sol_elem *src);

extern void sol_elem_free(sol_elem **elem);

extern sol_erno sol_elem_lt(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *lt);

extern sol_erno sol_elem_eq(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *eq);

extern sol_erno sol_elem_gt(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *gt);

extern sol_erno sol_elem_id(const sol_elem *elem, sol_index *id);

extern sol_erno sol_elem_sz(const sol_elem *elem, sol_size *sz);

extern sol_erno sol_elem_data(const sol_elem *elem, sol_ptr **data);

extern sol_erno sol_elem_meta_new(sol_elem_meta **meta,
                                   const sol_index id,
                                   const sol_size sz);

extern sol_erno sol_elem_meta_new2(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp);

extern sol_erno sol_elem_meta_new3(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq);

extern sol_erno sol_elem_meta_new4(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq,
                                    sol_elem_delegate_lt *lt,
                                    sol_elem_delegate_gt *gt);

extern sol_erno sol_elem_meta_copy(sol_elem_meta **meta,
                                    const sol_elem_meta *src);

extern void sol_elem_meta_free(sol_elem_meta **meta);




/* Module: List */
typedef struct __sol_list sol_list;

extern sol_erno sol_list_new(sol_list **list, const sol_elem_meta *meta);

extern sol_erno sol_list_copy(sol_list **list, const sol_list *src);

extern void sol_list_free(sol_list **list);

extern sol_erno sol_list_len(const sol_list *list, sol_size *len);

extern sol_erno sol_list_elem(const sol_list *list, sol_elem **elem);

extern sol_erno sol_list_setelem(sol_list **list, const sol_elem *elem);

extern sol_erno sol_list_start(sol_list **list);

extern sol_erno sol_list_next(sol_list **list);

extern sol_erno sol_list_end(sol_list **list);

extern sol_erno sol_list_push(sol_list **list, const sol_elem *elem);

extern sol_erno sol_list_pop(sol_list **list);




/*
 *      sol_log_open() - opens log file
 *        - path: log file path
 *
 *      The sol_log_open() interface function opens the log file located at
 *      @path, and sets it as the default log file where the log entries will be
 *      written by the logging module. This function flushes out the contents of
 *      the log file at @path if it exists, and creates it if it does not exist.
 *
 *      @path is required to be a valid non-null string, or else an exception is
 *      thrown. An error is also raised in case the log file at @path has
 *      already been opened by an earlier call to either sol_log_open() or
 *      sol_log_open2().
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_STATE if log file is already open
 *        - SOL_ERNO_STR if @path is invalid
 *        - SOL_ERNO_FILE if log file can't be opened
 */
extern sol_erno sol_log_open(const char *path);




/*
 *      sol_log_open2() - opens log file
 *        - path: log file path
 *        - flush: flag to indicate whether log file should be flushed
 *
 *      The sol_log_open2() interface function is the overloaded form of the
 *      sol_log_open() function declared above. This function, like its original
 *      form, opens the log file located @path, and sets it as the default log
 *      file where the log entries will be written by the logging module. In
 *      addition, this function allows a flag @flush to explicitly specify
 *      whether or not the contents of the log file should be flushed on
 *      opening in case file already exists. If the file does not exist, then
 *      this function creates it.
 *
 *      @path is required to be a valid non-null string, or else an exception is
 *      thrown. An error is also raised in case the log file at @path has
 *      already been opened by an earlier call to either sol_log_open() or
 *      sol_log_open2().
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_STATE if log file is already open
 *        - SOL_ERNO_STR if @path is invalid
 *        - SOL_ERNO_FILE if log file can't be opened
 */
extern sol_erno sol_log_open2(const char *path,
                              int flush);




/*
 *      sol_log_close() - closes log file
 *
 *      The sol_log_close() interface function closes the log file that has been
 *      opened by an earlier call to either sol_log_open() or sol_log_open2().
 *      Calling this function when no log file is currently open results in a
 *      safe no-op.
 *
 *      This function must be called when the logging module is no longer
 *      required in order to prevent a resource leak.
 */
extern void sol_log_close(void);




/*
 *      sol_log_trace() - logs a trace message
 *        - msg: message
 *
 *      The sol_log_trace() interface macro records a trace message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_trace(/* const char* */ msg) \
        __sol_log_write("T",                            \
                        sol_env_func(),                 \
                        sol_env_file(),                 \
                        sol_env_line(),                 \
                        (msg))




/*
 *      sol_log_debug() - logs a debug message
 *        - msg: message
 *
 *      The sol_log_debug() interface macro records a debug message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_debug(/* const char* */ msg) \
        __sol_log_write("D",                            \
                        sol_env_func(),                 \
                        sol_env_file(),                 \
                        sol_env_line(),                 \
                        (msg))




/*
 *      sol_log_warn() - logs a warning message
 *        - msg: message
 *
 *      The sol_log_warn() interface macro records a warning message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_warn(/* const char* */ msg) \
        __sol_log_write("W",                           \
                        sol_env_func(),                \
                        sol_env_file(),                \
                        sol_env_line(),                \
                        (msg))




/*
 *      sol_log_error() - logs an error message
 *        - msg: message
 *
 *      The sol_log_error() interface macro records an error message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_error(/* const char* */ msg) \
        __sol_log_write("E",                            \
                        sol_env_func(),                 \
                        sol_env_file(),                 \
                        sol_env_line(),                 \
                        (msg))




/*
 *      sol_log_erno() - log an error code
 *        - erno: error code
 *
 *      The sol_log_erno() interface macro records an error code @erno to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_erno(/* sol_erno */ erno) \
        __sol_log_write("E",                         \
                        sol_env_func(),              \
                        sol_env_file(),              \
                        sol_env_line(),              \
                        sol_erno_str((erno)))




/*
 *      __sol_log_write() - writes a log entry
 *
 *      The __sol_log_write() function is **not** a part of the interface of the
 *      logging module, and must **not** be called directly. This function is a
 *      utility function that helps in writing log entries to the log file, and
 *      has been declared in this file so that it can be called by the logging
 *      macros defined above.
 */
extern void __sol_log_write(const char *type,
                            const char *func,
                            const char *file,
                            int line,
                            const char *msg);




/*
 *      SOL_TSUITE_MAXTCASE - maximum number of test cases in a test suite
 *
 *      The SOL_TSUITE_MAXTCASE symbolic constant defines the maxiumum number of
 *      test cases that can be registered in one test suite. The cap limit of
 *      128 test cases is expected to be more than adequate for most situations.
 */
#define SOL_TSUITE_MAXTCASE 128




/*
 *      SOL_TCASE_MAXDESCLEN - maximum length of test case description
 *
 *      The SOL_TCASE_MAXDESCLEN symbolic constant defines the maximum length of
 *      the description for a test case. The limit of 128 characters (including
 *      the terminating null character) should be adequate for most situations.
 */
#define SOL_TCASE_MAXDESCLEN 128




/*
 *      sol_tcase - test case callback
 *
 *      The sol_tcase callback function defines a test case that may be executed
 *      as part of a test suite abstracted by the sol_tsuite type defined below.
 *      The test case callback is defined by client code, and needs to be
 *      registered with a test suite through the sol_tsuite_register() function
 *      in order to be executed. The test case callback is required to return an
 *      error code indicating whether or not it passed.
 *
 *      Return:
 *        - SOL_ERNO_NULL if the test case passes
 *        - A context-sensitive error code if the test case fails
 */
typedef sol_erno (sol_tcase)(void);




/*
 *      sol_tlog - test suite logging callback
 *        - desc: unit test description
 *        - erno: error code returned by a test case
 *
 *      The sol_tlog callback function defines the logging mechanism that is to
 *      be used by a sol_tsuite test suite to log the results of its registered
 *      test cases when they are executed through sol_tsuite_exec().
 *
 *      The sol_tlog callback is defined by client code, and plugged into a test
 *      suite through the sol_tsuite_init2() function. If this callback function
 *      is available to a test suite, it will be passed the description @desc of
 *      each test case executed, along with the error code @erno returned by the
 *      test case.
 */
typedef void (sol_tlog)(const char *desc,
                        sol_erno erno);




/*
 *      sol_tsuite - test suite
 *
 *      The sol_tsuite type abstracts a test suite. A test suite is a collection
 *      of related test cases, each of which is defined by a sol_tcase callback
 *      function.
 *
 *      Although the sol_tsuite type is defined as a transparent type so that it
 *      has no dependence on heap memory interfaces (which may not be available
 *      in freestanding environments), it should be treated as an opaque type,
 *      and used only through its interface functions declared below.
 */
typedef struct __sol_tsuite {
        sol_uint total;
        sol_uint fail;
        char desc[SOL_TSUITE_MAXTCASE][SOL_TCASE_MAXDESCLEN];
        sol_tcase *tcase[SOL_TSUITE_MAXTCASE];
        sol_tlog *tlog;
} sol_tsuite;




/*
 *      sol_tsuite_init() - initialises test suite
 *        - tsuite: contextual test suite
 *
 *      The sol_tsuite_init() interface function initialises a test suite
 *      @tsuite to its default state. This function **must** be called before
 *      calling any of the other interface functions of sol_tsuite, other than
 *      the overloaded sol_tsuite_init2() function.
 *
 *      This function initialises @tsuite without hooking up a logging callback
 *      function, and so is suitable for use in freestanding environments, or in
 *      situations where logging of the unit tests is not required. If logging
 *      of the test cases is required, then the overloaded version
 *      sol_tsuite_init2() should be used instead.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed
 */
extern sol_erno sol_tsuite_init(sol_tsuite *tsuite);




/*
 *      sol_tsuite_init2() - initialises test suite
 *        - tsuite: contextual test suite
 *        - tlog: test logging callback
 *
 *     The sol_tsuite_init2() interface function is the overloaded form of the
 *     sol_tsuite_init() function declared above. This function, like its
 *     original form, intialises a test suite instance @tsuite, but additionally
 *     hooks up a callback function @tlog that is used to log the test case
 *     results. This function **must** be called before any of the other
 *     sol_tsuite interface functions are invoked on @tsuite, apart from
 *     sol_tsuite_init().
 *
 *     Both @tsuite and @tlog are required to be valid pointers; otherwise, an
 *     exception is thrown.
 *
 *     Return:
 *       - SOL_ERNO_NULL if no error occurs
 *       - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_init2(sol_tsuite *tsuite,
                                 sol_tlog *tlog);




/*
 *      sol_tsuite_term() - terminates a test suite
 *        - tsuite: contextual test suite
 *
 *      The sol_tsuite_term() interface function terminates a test suite
 *      instance @tsuite that was earlier initialised by a call to either
 *      sol_tsuite_init() or sol_tsuite_init2(). Although this function expects
 *      @tsuite to be a valid pointer, a safe no-op occurs if this condition is
 *      not satisfied.
 */
extern void sol_tsuite_term(sol_tsuite *tsuite);




/*
 *      sol_tsuite_register() - registers a test case
 *        - tsuite: contextual test suite
 *        - tcase: test case to register
 *        - desc: test case description
 *
 *     The sol_tsuite_register() interface function registers a test case @tcase
 *     described by @desc with a test suite @tsuite. A test case must first be
 *     registered as part of a test suite before it can be executed. This
 *     function allows a maximum of SOL_TSUITE_MAXTCASE test cases to be
 *     registered with @tsuite, and automatically truncates the length of @desc
 *     to SOL_TCASE_MAXDESCLEN characters if required.
 *
 *     @tsuite, @tcase, and @desc must all be valid pointers, and additionally
 *     @desc must be a non-null string; if any of these conditions is not met,
 *     then an exception is thrown.
 *
 *     Return:
 *       - SOL_ERNO_NULL if no error occurs
 *       - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 *       - SOL_ERNO_STR if @desc is a null string
 *       - SOL_ERNO_RANGE if the limit of registered test cases is exceeded
 */
extern sol_erno sol_tsuite_register(sol_tsuite *tsuite,
                                    sol_tcase *tcase,
                                    const char *desc);




/*
 *      sol_tsuite_pass() - count of passed test cases
 *        - tsuite: contextual test suite
 *        - pass: count of passed test cases
 *
 *      The sol_tsuite_pass() interface function returns the number of test
 *      cases @pass of a test suite @tsuite that have been successfully run
 *      through the sol_tsuite_exec() interface function.
 *
 *      Both @tsuite and @pass are required to be valid pointers, or else an
 *      exception is thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_pass(const sol_tsuite *tsuite,
                                sol_uint *pass);




/*
 *      sol_tsuite_fail() - count of failed test cases
 *        - tsuite: contextual test suite
 *        - fail: count of failed test cases
 *
 *      The sol_tsuite_fail() interface function returns the number of test
 *      cases @fail of a test suite @tsuite that have failed when executed
 *      through the sol_tsuite_exec() interface function.
 *
 *      Both @tsuite @fail are required to be valid pointers, or else an
 *      exception is thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_fail(const sol_tsuite *tsuite,
                                sol_uint *fail);




/*
 *      sol_tsuite_total() - count of total test cases
 *        - tsuite: contextual test suite
 *        - total: count of total test cases
 *
 *      The sol_tsuite_total() interface function returns the total number of
 *      test cases @total registered with a test suite @tsuite.
 *
 *      Both @tsuite and @total are required to be valid pointers, or else an
 *      exception is thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer is passed as an argument
 */
extern sol_erno sol_tsuite_total(const sol_tsuite *tsuite,
                                 sol_uint *total);




/*
 *      sol_tsuite_exec() - executes registered test cases
 *        - tsuite: contextual test suite
 *
 *      The sol_tsuite_exec() interface function sequentially executes all the
 *      test cases registered with a test suite @tsuite. If @tsuite had been
 *      hooked to a logging callback at the time of initialisation through
 *      sol_tsuite_init2(), then this function also logs the result of each test
 *      case executed.
 *
 *      @tsuite is required to be a valid pointer, or else an exception is
 *      thrown.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid argument is passed
 */
extern sol_erno sol_tsuite_exec(sol_tsuite *tsuite);





        /* close header guard __SOL_LIBRARY_API_INCLUDED */
#endif




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

