/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/src/error.c
 *
 * Description:
 *      This file is part of the internal implementation of the Sol Library.
 *      It implements the exception handling module.
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
#include "../inc/prim.h"
#include "../inc/error.h"




/*
 *      BFR_LEN - length of string buffer
 */
#define BFR_LEN (19)




/*
 *      BFR_HND - handle to string buffer
 */
static sol_tls char bfr_hnd[BFR_LEN];




/*
 *      sol_erno_str() - declared in sol/inc/error.h
 */
extern const char *sol_erno_str(sol_erno erno)
{
        const int RADIX = 16;
        register sol_index i = 0;

                /* prefix with '0x' to indicate hex code */
        bfr_hnd[i] = '0';
        bfr_hnd[++i] = 'x';

                /* convert erno to hex string representation with padding zeros
                 * as required; this code has been adapted from that posted by
                 * user Lundin on StackOverflow */
        for (++i; i < BFR_LEN; i++) {
                bfr_hnd[BFR_LEN - i] = (erno % RADIX) + '0';
                erno /= RADIX;
        }

                /* close buffer and return it */
        bfr_hnd[i] = '\0';
        return bfr_hnd;
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

