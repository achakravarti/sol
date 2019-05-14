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
#include "../inc/log.h"
#include "../inc/dsa.h"




struct list_node {
        sol_elem *elem;
        struct list_node *next;
};




struct __sol_list {
        sol_elem_delegate *free;
        struct list_node *head;
        struct list_node *tail;
        struct list_node *curr;
        sol_size len;
};




static sol_inline void delegate_free(sol_elem **elem)
{
        (void) elem;
}




extern sol_erno sol_list_ctor(sol_list **list)
{
        return sol_list_ctor2(list, &delegate_free);
}




extern sol_erno sol_list_ctor2(sol_list **list,
                               sol_elem_delegate_free *free)
{
        auto sol_list *hnd;

SOL_TRY:
        sol_assert (free, SOL_ERNO_PTR);

        sol_try (sol_ptr_new((sol_ptr **) list, sizeof (**list)));
        hnd = *list;

        hnd->free = free;
        hnd->head = hnd->tail = hnd->curr = SOL_PTR_NULL;
        hnd->len = (sol_size) 0;

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern void sol_list_free(sol_list **list)
{
}




extern sol_erno sol_list_len(const sol_list *list, sol_size *len)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_elem(const sol_list *list, sol_elem **elem)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_setelem(sol_list *list, const sol_elem *elem)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_start(sol_list *list)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_next(sol_list *list)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_end(sol_list *list)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_push(sol_list *list, const sol_elem *elem)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




extern sol_erno sol_list_pop(sol_list *list)
{
SOL_TRY:
        sol_assert (SOL_BOOL_TRUE, SOL_ERNO_PTR);

SOL_CATCH:
        sol_log_erno(sol_erno_get());

SOL_FINALLY:
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

