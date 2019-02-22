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




#include "../inc/env.h"
#include "../inc/ptr.h"
#if (sol_env_host() != SOL_ENV_HOST_NONE)
#       include <stdlib.h>
#endif




extern sol_erno sol_ptr_new(sol_ptr **ptr,
                            const size_t sz)
{
SOL_TRY:
        #if (SOL_ENV_HOST_NONE == sol_env_host())
        #       error "[!] sol_ptr_new() error: malloc() not available"
        #endif

        sol_assert (ptr && !*ptr, SOL_ERNO_NULL);
        sol_assert (sz, SOL_ERNO_NULL);

        sol_assert ((*ptr = malloc(sz)), SOL_ERNO_NULL);

SOL_CATCH:
        sol_throw();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

