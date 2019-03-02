/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/src/log.c
 *
 * Description:
 *      This file is part of the internal implementation of the Sol Library.
 *      It implements the logging module.
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
#include "../inc/log.h"
#include "../inc/ptr.h"
#include <stdio.h>




static  FILE *log_hnd = SOL_PTR_NULL;




extern sol_erno sol_log_open(const char *path)
{
SOL_TRY:
        sol_assert (!log_hnd, SOL_ERNO_PTR);
        sol_assert (path && *path, SOL_ERNO_STR);

        log_hnd = fopen(path, "w"); /* NOLINT */
        sol_assert (log_hnd, SOL_ERNO_FILE);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_log_open2(const char *path,
                              const int flush)
{
SOL_TRY:
        sol_assert (!log_hnd, SOL_ERNO_PTR);
        sol_assert (path && *path, SOL_ERNO_STR);

        log_hnd = fopen(path, flush ? "w" : "a+");
        sol_assert (log_hnd, SOL_ERNO_FILE);

SOL_CATCH:
SOL_FINALLY:
        return sol_erno_get();
}




extern void sol_log_close(void)
{
        if (log_hnd) {
                (void) fclose(log_hnd);
                log_hnd = SOL_PTR_NULL;
        }
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

