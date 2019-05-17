/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/src/elem.c
 *
 * Description:
 *      This file is part of the internal implementation of the Sol Library.
 *      It implements the element and element delegate interfaces.
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
#include "../inc/dsa.h"




struct __sol_elem_delegate {
        sol_elem_delegate_dispose *disp;
        sol_elem_delegate_eq *eq;
        sol_elem_delegate_lt *lt;
        sol_elem_delegate_gt *gt;
        sol_size nref;
};




extern sol_erno sol_elem_delegate_new(sol_elem_delegate **dlg,
                                      sol_elem_delegate_dispose *disp)
{
        return sol_elem_delegate_new3(dlg,
                                      disp,
                                      SOL_PTR_NULL,
                                      SOL_PTR_NULL,
                                      SOL_PTR_NULL);
}




extern sol_erno sol_elem_delegate_new2(sol_elem_delegate **dlg,
                                       sol_elem_delegate_dispose *disp,
                                       sol_elem_delegate_eq *eq)
{
        return sol_elem_delegate_new3(dlg,
                                      disp,
                                      eq,
                                      SOL_PTR_NULL,
                                      SOL_PTR_NULL);
}




extern sol_erno sol_elem_delegate_new3(sol_elem_delegate **dlg,
                                       sol_elem_delegate_dispose *disp,
                                       sol_elem_delegate_eq *eq,
                                       sol_elem_delegate_lt *lt,
                                       sol_elem_delegate_gt *gt)
{
        auto sol_elem_delegate *hnd;

SOL_TRY:
        sol_assert (disp && eq && lt && gt, SOL_ERNO_PTR);

        sol_try (sol_ptr_new((sol_ptr **) dlg, sizeof (**dlg)));
        hnd = *dlg;
        hnd->nref = (sol_size) 1;

        hnd->disp = disp;
        hnd->eq = eq;
        hnd->lt = lt;
        hnd->gt = gt;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_delegate_copy(sol_elem_delegate **dlg,
                                       const sol_elem_delegate *src)
{
SOL_TRY:
        sol_assert (dlg && src, SOL_ERNO_PTR);

        sol_elem_delegate_free(dlg);

        *dlg = (sol_elem_delegate *) src;
        (*dlg)->nref++;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void sol_elem_delegate_free(sol_elem_delegate **dlg)
{
        auto sol_elem_delegate *hnd;

        if (sol_likely (dlg && *dlg)) {
                if ((hnd = *dlg) && !(--hnd->nref))
                        sol_ptr_free((sol_ptr **) dlg);
        }
}




extern sol_erno sol_elem_delegate_execdispose(const sol_elem_delegate *dlg,
                                              sol_elem **elem)
{
SOL_TRY:
        sol_assert (dlg, SOL_ERNO_PTR);

        dlg->disp(elem);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_delegate_calleq(const sol_elem_delegate *dlg,
                                         const sol_elem *lhs,
                                         const sol_elem *rhs,
                                         SOL_BOOL *eq)
{
SOL_TRY:
        sol_assert (dlg, SOL_ERNO_PTR);

        dlg->eq(lhs, rhs, eq);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

