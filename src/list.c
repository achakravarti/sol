/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/src/list.c
 *
 * Description:
 *      This file is part of the internal implementation of the Sol Library.
 *      It implements the list interface.
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
#include "api.h"




struct list_node {
        sol_elem *elem;
        struct list_node *next;
};




struct __sol_list {
        struct list_node *head;
        struct list_node *tail;
        struct list_node *curr;
        sol_size len;
        sol_size nref;
};




static sol_erno list_fork(sol_list **list)
{
        register sol_index i;
        register sol_list *src;
        auto struct list_node *mark;

SOL_TRY:
        sol_assert ((src = *list), SOL_ERNO_STATE);

        if (src->nref == (sol_size) 1)
                return SOL_ERNO_NULL;

        src->nref--;
        mark = src->curr;

        *list = SOL_PTR_NULL;
        sol_try (sol_list_new(list));

        for (i = (sol_index) 0; i < src->len; i++) {
                src->curr = src->curr->next;
                sol_try (sol_list_push(list, src->curr->elem));
        }

        src->curr = mark;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}



extern sol_erno sol_list_new(sol_list **list)
{
        auto sol_list *hnd; /* handle to @list */

SOL_TRY:
                /* allocate heap for new list */
        sol_try (sol_ptr_new((sol_ptr **) list, sizeof (**list)));
        hnd = *list;

                /* init fields */
        hnd->head = hnd->tail = hnd->curr = SOL_PTR_NULL;
        hnd->len = (sol_size) 0;
        hnd->nref = (sol_size) 1;

SOL_CATCH:
                /* log any exception that might have occurred */
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
                /* return current error code */
        return sol_erno_get();
}




extern sol_erno sol_list_copy(sol_list **list, const sol_list *src)
{
        auto sol_list *hnd;

SOL_TRY:
        sol_assert (list && src, SOL_ERNO_PTR);
        sol_assert (!(hnd = *list), SOL_ERNO_STATE);

        hnd = (sol_list *) src;
        hnd->nref++;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void sol_list_free(sol_list **list)
{
        auto sol_list *hnd;
        auto struct list_node *node;

        if (sol_likely (list && (hnd = *list))) {
                if (!(--hnd->nref)) {
                        hnd->curr = hnd->head;

                        while ((node = hnd->curr)) {
                                hnd->curr = hnd->curr->next;
                                sol_elem_free(&node->elem);
                        }

                        sol_ptr_free((sol_ptr **) list);
                }

                else {
                        *list = SOL_PTR_NULL;
                }
        }
}




extern sol_erno sol_list_len(const sol_list *list, sol_size *len)
{
SOL_TRY:
        sol_assert (list && len, SOL_ERNO_PTR);

        *len = list->len;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_elem(const sol_list *list, sol_elem **elem)
{
SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);
        sol_assert (list->curr, SOL_ERNO_STATE);

        sol_try (sol_elem_copy(elem, list->curr->elem));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_setelem(sol_list **list, const sol_elem *elem)
{
        auto sol_list *hnd; /* handle to @list        */
        auto sol_index sid; /* source element ID      */
        auto sol_index did; /* destination element ID */

SOL_TRY:
                /* check preconditions */
        sol_assert (list && (hnd = *list), SOL_ERNO_PTR);
        sol_assert (hnd->curr, SOL_ERNO_STATE);
        sol_try (sol_elem_id(elem, &sid));
        sol_try (sol_elem_id(hnd->curr->elem, &did));
        sol_assert (sid == did, SOL_ERNO_STATE);

        sol_try (list_fork(list));
        hnd = *list;

        sol_try (sol_elem_copy(&hnd->curr->elem, elem));

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_start(sol_list **list)
{
        auto sol_list *hnd;

SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);

        sol_try (list_fork(list));
        hnd = *list;

        hnd->curr = hnd->head;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_next(sol_list **list)
{
        auto sol_list *hnd;

SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);

        sol_try (list_fork(list));
        hnd = *list;

        hnd->curr = hnd->curr->next;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_end(sol_list **list)
{
        auto sol_list *hnd;

SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);

        sol_try (list_fork(list));
        hnd = *list;

        hnd->curr = hnd->tail;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_push(sol_list **list, const sol_elem *elem)
{
        auto struct list_node *node = SOL_PTR_NULL;
        auto sol_list *hnd;
        auto sol_index sid;
        auto sol_index did;

SOL_TRY:
        sol_assert (list && (hnd = *list) && elem, SOL_ERNO_PTR);

        if (sol_likely (hnd->len)) {
                sol_try (sol_elem_id(elem, &sid));
                sol_try (sol_elem_id(hnd->curr->elem, &did));
                sol_assert (sid == did, SOL_ERNO_STATE);
        }

        sol_try (list_fork(list));
        hnd = *list;

        sol_try (sol_ptr_new((sol_ptr**)&node, sizeof (*node)));
        node->elem = SOL_PTR_NULL;
        node->next = SOL_PTR_NULL;

        sol_try (sol_elem_copy(&node->elem, elem));

        if (!hnd->head)
                hnd->head = node;

        if (hnd->tail)
                hnd->tail->next = node;

        hnd->tail = node;
        hnd->len++;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_pop(sol_list **list)
{
        register sol_index i;
        auto sol_list *hnd;

SOL_TRY:
        sol_assert (list, SOL_ERNO_PTR);

        sol_try (list_fork(list));
        hnd = *list;

        if (sol_likely (hnd->tail)) {
                sol_elem_free(&hnd->tail->elem);
                sol_ptr_free((sol_ptr**) &hnd->tail);

                hnd->curr = hnd->head;
                hnd->len--;

                for (i = (sol_index) 0; i < hnd->len; i++)
                        hnd->curr = hnd->curr->next;

                hnd->curr->next = SOL_PTR_NULL;
                hnd->tail = hnd->curr;
        }

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

