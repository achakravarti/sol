/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/log.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the logging module.
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




        /* create header guard */
#if (!defined __SOL_LOGGING_MODULE)
#define __SOL_LOGGING_MODULE




        /* include required header files */
#include "./error.h"




extern sol_erno sol_log_open(const char *path);




extern sol_erno sol_log_open2(const char *path,
                              const int flush);




extern void sol_log_close(void);




#endif /* !defined __SOL_LOGGING_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

