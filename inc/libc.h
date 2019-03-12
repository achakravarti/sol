/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/libc.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the libc compatibility module.
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
#if (!defined __SOL_LIBC_COMPATIBILITY_MODULE)
#define __SOL_LIBC_COMPATIBILITY_MODULE




        /* include required header files */
#include "./env.h"
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



#endif /* !defined __SOL_LIBC_COMPATIBILITY_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

