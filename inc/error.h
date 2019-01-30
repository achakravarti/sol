/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/error.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the exception handling module.
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





#if !defined __SOL_EXCEPTION_HANDLING_MODULE
#define __SOL_EXCEPTION_HANDLING_MODULE




#include <stddef.h>




typedef size_t sol_erno;




#define SOL_ERNO_NULL ((sol_erno) 0x0)




#define SOL_TRY                                       \
        register sol_erno __sol_erno = SOL_ERNO_NULL; \
        __SOL_TRY




#define SOL_CATCH             \
        return SOL_ERNO_NULL; \
        __SOL_CATCH




#define /* sol_erno */ sol_throw(/* void */) \
        return __sol_erno




#define /* const sol_erno */ sol_erno_now(/* void */) \
        ((const sol_erno) __sol_erno)




#define /* void */ sol_assert(p, /* sol_erno */ e) \
        do {                                       \
                if (!(p)) {                        \
                        __sol_erno = (e);          \
                        goto __SOL_CATCH:          \
                }                                  \
        } while (0)




#define /* void */ sol_try(p) \
        do { \
                if ((__sol_erno = (p))) \
                        goto __SOL_CATCH; \
        } while (0)




#endif /* !defined __SOL_EXCEPTION_HANDLING_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

