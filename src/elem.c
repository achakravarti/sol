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




struct __sol_elem_class {
        sol_index id;
        sol_size sz;
        sol_size nref;
        sol_elem_delegate_dispose *disp;
        sol_elem_delegate_eq *eq;
        sol_elem_delegate_lt *lt;
        sol_elem_delegate_gt *gt;
};




static sol_erno class_init(sol_elem_class **cls,
                           const sol_index id,
                           const sol_size sz,
                           sol_elem_delegate_dispose *disp,
                           sol_elem_delegate_eq *eq,
                           sol_elem_delegate_lt *lt,
                           sol_elem_delegate_gt *gt)
{
        auto sol_elem_class *hnd;

SOL_TRY:
        sol_assert (sz, SOL_ERNO_RANGE);

        sol_try (sol_ptr_new((sol_ptr **) cls, sizeof (**cls)));
        hnd = *cls;
        hnd->nref = (sol_size) 1;

        hnd->id = id;
        hnd->sz = sz;
        hnd->disp = disp;
        hnd->eq = eq;
        hnd->lt = lt;
        hnd->gt = gt;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_class_new(sol_elem_class **cls,
                                   const sol_index id,
                                   const sol_size sz)
{
        return class_init(cls,
                          id,
                          sz,
                          SOL_PTR_NULL,
                          SOL_PTR_NULL,
                          SOL_PTR_NULL,
                          SOL_PTR_NULL);
}




extern sol_erno sol_elem_class_new2(sol_elem_class **cls,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp)
{
        return class_init(cls,
                          id,
                          sz,
                          disp,
                          SOL_PTR_NULL,
                          SOL_PTR_NULL,
                          SOL_PTR_NULL);
}




extern sol_erno sol_elem_class_new3(sol_elem_class **cls,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq)
{
        return class_init(cls, id, sz, disp, eq, SOL_PTR_NULL, SOL_PTR_NULL);
}




extern sol_erno sol_elem_class_new4(sol_elem_class **cls,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq,
                                    sol_elem_delegate_lt *lt,
                                    sol_elem_delegate_gt *gt)
{
SOL_TRY:
        sol_assert (disp && eq && lt && gt, SOL_ERNO_PTR);

        sol_try (class_init(cls, id, sz, disp, eq, lt, gt));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_class_copy(sol_elem_class **cls,
                                    const sol_elem_class *src)
{
        auto sol_elem_class *hnd;

SOL_TRY:
        sol_assert (cls && src, SOL_ERNO_PTR);
        sol_assert (!(hnd = *cls), SOL_ERNO_STATE);

        hnd = (sol_elem_class *) src;
        hnd->nref++;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void sol_elem_class_free(sol_elem_class **cls)
{
        auto sol_elem_class *hnd;

        if (sol_likely (cls && (hnd = *cls))) {
                if (!(--hnd->nref))
                        sol_ptr_free ((sol_ptr **) cls);
                else
                        hnd = SOL_PTR_NULL;
        }
}




extern void sol_elem_class_dispose(const sol_elem_class *cls,
                                   sol_elem **elem)
{
        if (sol_likely (cls && cls->disp))
                cls->disp(elem);
}




extern sol_erno sol_elem_class_eq(const sol_elem_class *cls,
                                  const sol_elem *lhs,
                                  const sol_elem *rhs,
                                  SOL_BOOL *eq)
{
SOL_TRY:
        sol_assert (cls, SOL_ERNO_PTR);

        cls->eq(lhs, rhs, eq);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_class_lt(const sol_elem_class *cls,
                                  const sol_elem *lhs,
                                  const sol_elem *rhs,
                                  SOL_BOOL *lt)
{
SOL_TRY:
        sol_assert (cls, SOL_ERNO_PTR);

        cls->lt(lhs, rhs, lt);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_class_gt(const sol_elem_class *cls,
                                  const sol_elem *lhs,
                                  const sol_elem *rhs,
                                  SOL_BOOL *gt)
{
SOL_TRY:
        sol_assert (cls, SOL_ERNO_PTR);

        cls->gt(lhs, rhs, gt);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

