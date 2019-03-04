/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/src/ptr.c
 *
 * Description:
 *      This file is part of the internal implementation of the Sol Library.
 *      It implements the pointer module.
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
#include "../inc/env.h"
#include "../inc/log.h"
#include "../inc/ptr.h"




        /* the implementation of the pointer module uses the standard malloc()
         * and free() functions; in hosted environments, these are provided by
         * the standard stdlib.h header file, and in freestanding environments
         * by the client code (until an allocator is implemented in future) */
#if (SOL_ENV_HOST_NONE == sol_env_host())
        extern void *malloc(size_t);
        extern void free(void*);
#else
#       include <stdlib.h>
#endif




/*
 *      copy_byte() - copies a buffer on to another byte-wise
 *        - ptr: destination buffer
 *        - src: source buffer
 *        - len: length in bytes to copy
 */
static sol_inline void copy_byte(sol_ptr **ptr,
                                 const sol_ptr *src,
                                 const size_t len)
{
                /* @ptr, @src and @len are valid, as they have already been
                 * checked by the calling function sol_ptr_copy() */
        register char *bdst = (char*) *ptr;
        register char *bsrc = (char*) src;
        register size_t itr = len;

                /* copy @src to @ptr byte-by-byte for @len bytes */
        for (; itr; itr--, *bdst++ = *bsrc++); /* NOLINT */
}




/*
 *      sol_ptr_new() - declared in sol/inc/ptr.h
 */
extern sol_erno sol_ptr_new(sol_ptr **ptr,
                            const size_t sz)
{
SOL_TRY:
                /* check preconditions */
        sol_assert (ptr && !*ptr, SOL_ERNO_PTR);
        sol_assert (sz, SOL_ERNO_RANGE);

                /* allocate heap memory of size @sz to @ptr */
        sol_assert ((*ptr = malloc(sz)), SOL_ERNO_HEAP);

SOL_CATCH:
                /* log current error */
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      sol_ptr_copy() - declared in sol/inc/ptr.h
 */
extern sol_erno sol_ptr_copy(sol_ptr **ptr,
                             const sol_ptr *src,
                             const size_t len)
{
SOL_TRY:
                /* check preconditions */
        sol_assert (ptr && !*ptr && src, SOL_ERNO_PTR);
        sol_assert (len, SOL_ERNO_RANGE);

                /* copy contents of @src to @ptr after allocating it */
        sol_assert ((*ptr = malloc(len)), SOL_ERNO_HEAP);
        copy_byte(ptr, src, len);

SOL_CATCH:
                /* log current error */
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      sol_ptr_free() - declared in sol/inc/ptr.h
 */
extern void sol_ptr_free(sol_ptr **ptr)
{
                /* free heap memory allocated to @ptr if it's valid */
        if (sol_likely (ptr && *ptr)) {
                free(*ptr);
                *ptr = SOL_PTR_NULL;
        }
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

