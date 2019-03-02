/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/config.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      configuration identifiers of the Sol Library.
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
#if (!defined __SOL_CONFIGURATION_IDENTIFIERS)
#define __SOL_CONFIGURATION_IDENTIFIERS




        /* include required header files */
#include "./env.h"




/*
 *      SOL_CONFIG_ERRORLOG - path to error log file
 */
#define SOL_CONFIG_ERRORLOG "bld/error.log"




/*
 *      SOL_CONFIG_TRACELOG - path to trace log file
 */
#define SOL_CONFIG_TRACELOG "bld/trace.log"




/*
 *      SOL_CONFIG_DEBUGLOG - path to debug log file
 */
#define SOL_CONFIG_DEBUGLOG "bld/debug.log"




/*
 *      sol_config_file - file structure
 */
#if (SOL_ENV_HOST_NONE == sol_env_host())
        typedef struct sol_config_file sol_config_file;
#else
#       include <stdio.h>
        typedef FILE sol_config_file;
#endif





#if (SOL_ENV_HOST_NONE == sol_env_host())
        extern sol_config_file *sol_config_fopen(const char *filename,
                                                 const char *mode);
#else
#       include <stdio.h>
#       define sol_config_fopen fopen
#endif




#if (SOL_ENV_HOST_NONE == sol_env_host())
        extern int *sol_config_fclose(sol_config_file *stream);
#else
#       include <stdio.h>
#       define sol_config_fclose fclose
#endif




#endif /* !defined __SOL_CONFIGURATION_IDENTIFIERS */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

