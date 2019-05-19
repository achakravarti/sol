/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/dsa.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the data structures and algorithms module.
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
#if (!defined __SOL_DATA_STRUCTURES_AND_ALGORITHMS_MODULE)
#define __SOL_DATA_STRUCTURES_AND_ALGORITHMS_MODULE




        /* include required header files */
#include "ptr.h"




typedef struct __sol_elem sol_elem;

typedef void (sol_elem_delegate_dispose)(sol_ptr **elem);


typedef sol_erno (sol_elem_delegate_lt)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *lt);

typedef sol_erno (sol_elem_delegate_eq)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *eq);

typedef sol_erno (sol_elem_delegate_gt)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *gt);

typedef struct __sol_elem_meta sol_elem_meta;

extern sol_erno sol_elem_new(sol_elem **elem,
                             const sol_elem_meta *meta,
                             const sol_ptr *data);

extern sol_erno sol_elem_copy(sol_elem **elem, const sol_elem *src);

extern void sol_elem_free(sol_elem **elem);

extern sol_erno sol_elem_lt(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *lt);

extern sol_erno sol_elem_eq(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *eq);

extern sol_erno sol_elem_gt(const sol_elem *lhs,
                            const sol_elem *rhs,
                            SOL_BOOL *gt);

extern sol_erno sol_elem_id(const sol_elem *elem, sol_index *id);

extern sol_erno sol_elem_sz(const sol_elem *elem, sol_size *sz);

extern sol_erno sol_elem_data(const sol_elem *elem, sol_ptr **data);

extern sol_erno sol_elem_setdata(sol_elem *elem, const sol_ptr *data);

extern sol_erno sol_elem_meta_new(sol_elem_meta **meta,
                                   const sol_index id,
                                   const sol_size sz);

extern sol_erno sol_elem_meta_new2(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp);

extern sol_erno sol_elem_meta_new3(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq);

extern sol_erno sol_elem_meta_new4(sol_elem_meta **meta,
                                    const sol_index id,
                                    const sol_size sz,
                                    sol_elem_delegate_dispose *free,
                                    sol_elem_delegate_eq *eq,
                                    sol_elem_delegate_lt *lt,
                                    sol_elem_delegate_gt *gt);

extern sol_erno sol_elem_meta_copy(sol_elem_meta **meta,
                                    const sol_elem_meta *src);

extern void sol_elem_meta_free(sol_elem_meta **meta);




typedef struct __sol_list sol_list;

extern sol_erno sol_list_new(sol_list **list, const sol_elem_meta *meta);

extern sol_erno sol_list_copy(sol_list **list, const sol_list *src);

extern void sol_list_free(sol_list **list);

extern sol_erno sol_list_len(const sol_list *list, sol_size *len);

extern sol_erno sol_list_elem(const sol_list *list, sol_elem **elem);

extern sol_erno sol_list_setelem(sol_list **list, const sol_elem *elem);

extern sol_erno sol_list_start(sol_list **list);

extern sol_erno sol_list_next(sol_list **list);

extern sol_erno sol_list_end(sol_list **list);

extern sol_erno sol_list_push(sol_list **list, const sol_elem *elem);

extern sol_erno sol_list_pop(sol_list *list);




#endif /* (!defined __SOL_DATA_STRUCTURES_AND_ALGORITHMS_MODULE) */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

