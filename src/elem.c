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




struct __sol_elem {
        sol_ptr *data;
        sol_elem_meta *meta;
        sol_size nref;
};




struct __sol_elem_meta {
        sol_index id;                    /* element ID             */
        sol_size sz;                     /* element size           */
        sol_size nref;                   /* reference count        */
        sol_elem_delegate_dispose *disp; /* dispose delegate       */
        sol_elem_delegate_eq *eq;        /* == comparison delegate */
        sol_elem_delegate_lt *lt;        /* < comparison delegate  */
        sol_elem_delegate_gt *gt;        /* > comparison delegate  */
};




extern sol_erno sol_elem_new(sol_elem **elem,
                             const sol_elem_meta *meta,
                             const sol_ptr *data)
{
        auto sol_elem *hnd;

SOL_TRY:
        sol_assert (meta && data, SOL_ERNO_PTR);
        sol_assert (sizeof (*data) == meta->sz, SOL_ERNO_STATE);

        sol_try (sol_ptr_new((sol_ptr **) elem, meta->sz));
        hnd = *elem;
        hnd->nref = (sol_size) 1;

        hnd->meta = hnd->data = SOL_PTR_NULL;
        sol_try (sol_elem_meta_copy(&hnd->meta, meta));
        sol_try (sol_ptr_copy(&hnd->data, data, meta->sz));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_copy(sol_elem **elem,
                              const sol_elem *src)
{
        auto sol_elem *hnd;

SOL_TRY:
        sol_assert (elem && src, SOL_ERNO_PTR);
        sol_assert (!(hnd = *elem), SOL_ERNO_STATE);

        hnd = (sol_elem *) src;
        hnd->nref++;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void sol_elem_free(sol_elem **elem)
{
        auto sol_elem *hnd;

        if (sol_likely (elem && (hnd = *elem))) {
                if (!(--hnd->nref)) {
                        hnd->meta->disp(&hnd->data);
                        sol_ptr_free((sol_ptr **) elem);
                }

                else {
                        hnd = SOL_PTR_NULL;
                }
        }
}




extern sol_erno sol_elem_lt(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *lt)
{
SOL_TRY:
        sol_assert (lhs && rhs && lt, SOL_ERNO_PTR);
        sol_assert (lhs->meta->id == rhs->meta->id, SOL_ERNO_STATE);

        sol_try (lhs->meta->lt(lhs->data, rhs->data, lt));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_eq(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *eq)
{
SOL_TRY:
        sol_assert (lhs && rhs && eq, SOL_ERNO_PTR);
        sol_assert (lhs->meta->id == rhs->meta->id, SOL_ERNO_STATE);

        sol_try (lhs->meta->eq(lhs->data, rhs->data, eq));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_gt(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *gt)
{
SOL_TRY:
        sol_assert (lhs && rhs && gt, SOL_ERNO_PTR);
        sol_assert (lhs->meta->id == rhs->meta->id, SOL_ERNO_STATE);

        sol_try (lhs->meta->gt(lhs->data, rhs->data, gt));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_id(const sol_elem *elem, sol_index *id)
{
SOL_TRY:
        sol_assert (elem && id, SOL_ERNO_PTR);

        *id = elem->meta->id;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_sz(const sol_elem *elem, sol_size *sz)
{
SOL_TRY:
        sol_assert (elem && sz, SOL_ERNO_PTR);

        *sz = elem->meta->sz;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_data(const sol_elem *elem, sol_ptr **data)
{
SOL_TRY:
        sol_assert (elem, SOL_ERNO_PTR);

        sol_try (sol_ptr_copy(data, elem->data, elem->meta->sz));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




static sol_erno meta_init(sol_elem_meta **meta,
                           const sol_index id,
                           const sol_size sz,
                           sol_elem_delegate_dispose *disp,
                           sol_elem_delegate_eq *eq,
                           sol_elem_delegate_lt *lt,
                           sol_elem_delegate_gt *gt)
{
        auto sol_elem_meta *hnd;

SOL_TRY:
        sol_assert (sz, SOL_ERNO_RANGE);

        sol_try (sol_ptr_new((sol_ptr **) meta, sizeof (**meta)));
        hnd = *meta;
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




extern sol_erno sol_elem_meta_new(sol_elem_meta **meta,
                                   const sol_index id,
                                   const sol_size sz)
{
        return meta_init(meta,
                         id,
                         sz,
                         SOL_PTR_NULL,
                         SOL_PTR_NULL,
                         SOL_PTR_NULL,
                         SOL_PTR_NULL);
}




extern sol_erno sol_elem_meta_new2(sol_elem_meta **meta,
                                   const sol_index id,
                                   const sol_size sz,
                                   sol_elem_delegate_dispose *disp)
{
SOL_TRY:
        sol_assert (disp, SOL_ERNO_PTR);

        sol_try (meta_init(meta,
                           id,
                           sz,
                           disp,
                           SOL_PTR_NULL,
                           SOL_PTR_NULL,
                           SOL_PTR_NULL));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_meta_new3(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq)
{
SOL_TRY:
        sol_assert (disp && eq, SOL_ERNO_PTR);

        sol_try (meta_init(meta, id, sz, disp, eq, SOL_PTR_NULL, SOL_PTR_NULL));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_meta_new4(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq,
                                    sol_elem_delegate_lt *lt,
                                    sol_elem_delegate_gt *gt)
{
SOL_TRY:
        sol_assert (disp && eq && lt && gt, SOL_ERNO_PTR);

        sol_try (meta_init(meta, id, sz, disp, eq, lt, gt));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_elem_meta_copy(sol_elem_meta **meta,
                                   const sol_elem_meta *src)
{
SOL_TRY:
        sol_assert (meta && src, SOL_ERNO_PTR);
        sol_assert (!*meta, SOL_ERNO_STATE);

        *meta = (sol_elem_meta *) src;
        (*meta)->nref++;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void sol_elem_meta_free(sol_elem_meta **meta)
{
        auto sol_elem_meta *hnd;

        if (sol_likely (meta && (hnd = *meta))) {
                if (!(--hnd->nref))
                        sol_ptr_free ((sol_ptr **) meta);
                else
                        hnd = SOL_PTR_NULL;
        }
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

