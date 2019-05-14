#include "ptr.h"

typedef sol_ptr sol_elem;

typedef void (sol_elem_delegate_free)(sol_elem **elem);

typedef sol_erno (sol_elem_delegate_lt)(const sol_elem *lhs,
                                        const sol_elem *rhs,
                                        const SOL_BOOL *lt);

typedef sol_erno (sol_elem_delegate_eq)(const sol_elem *lhs,
                                        const sol_elem *rhs,
                                        const SOL_BOOL *eq);

typedef sol_erno (sol_elem_delegate_gt)(const sol_elem *lhs,
                                        const sol_elem *rhs,
                                        const SOL_BOOL *gt);

typedef struct __sol_list sol_list;

extern sol_erno sol_list_ctor(sol_list **list);

extern sol_erno sol_list_ctor2(sol_list **list,
                               sol_elem_delegate_free *free);

extern void sol_list_free(sol_list **list);

extern sol_erno sol_list_len(const sol_list *list, sol_size *len);

extern sol_erno sol_list_elem(const sol_list *list, sol_elem **elem);

extern sol_erno sol_list_setelem(sol_list *list, const sol_elem *elem);

extern sol_erno sol_list_start(sol_list *list);

extern sol_erno sol_list_next(sol_list *list);

extern sol_erno sol_list_end(sol_list *list);

extern sol_erno sol_list_push(sol_list *list, const sol_elem *elem);

extern sol_erno sol_list_pop(sol_list *list);

