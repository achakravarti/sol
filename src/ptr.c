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




        /* include required header files; stdlib.h and string.h are available
         * in hosted environments */
#include "../inc/env.h"
#include "../inc/ptr.h"
#if (sol_env_host() != SOL_ENV_HOST_NONE)
#       include <stdlib.h>
#       include <string.h>
#endif




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
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      sol_ptr_copy() - declared in sol/inc/ptr.h
 */
extern sol_erno sol_ptr_copy(sol_ptr **ptr,
                             const sol_ptr *src,
                             const size_t sz)
{
SOL_TRY:
                /* check preconditions */
        sol_assert (ptr && !*ptr && src, SOL_ERNO_PTR);
        sol_assert (sz, SOL_ERNO_RANGE);

                /* copy contents of @src to @ptr after allocating it */
        sol_assert ((*ptr = malloc(sz)), SOL_ERNO_HEAP);
        sol_assert ((*ptr = memmove(*ptr, src, sz)), SOL_ERNO_HEAP);

SOL_CATCH:
                /* throw current exception, if any */
        sol_throw();
}




/*
 *      sol_ptr_free() - declared in sol/inc/ptr.h
 */
extern void sol_heap_free(sol_ptr **ptr)
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

