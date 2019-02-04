/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/runner.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test runner to execute all the module test suites.
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
 *      BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAt
 *      YOU HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
 ******************************************************************************/




#include "./suite.h"




/*
 *      main() - main entry point of test runner
 */
int main( void )
{
                /* execute test suites */
        (void) __sol_tsuite_error ();

                /* everything's OK */
        return 0;
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

