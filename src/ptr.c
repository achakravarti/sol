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




#include "../inc/ptr.h"
#include "../inc/env.h"
#if (SOL_ENV_HOST_NONE != sol_env_host())
#       include <stdlib.h>
#endif




extern sol_erno sol_ptr_new(sol_ptr **ptr,
                            const size_t sz)
{
SOL_TRY:
        sol_assert (ptr && !*ptr, SOL_ERNO_PTR);
        sol_assert (sz, SOL_ERNO_SZ);

        sol_assert ((*ptr = malloc(sz)), SOL_ERNO_HEAP);

SOL_CATCH:
        sol_throw();
}



extern sol_erno sol_ptr_copy(sol_ptr **ptr,
                             const sol_ptr *src,
                             const size_t sz)
{
}




extern void sol_ptr_free(sol_ptr **ptr)
{
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

