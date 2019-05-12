/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/ptr.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the pointer module.
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




        /* create header guard */
#if (!defined __SOL_POINTER_MODULE)
#define __SOL_POINTER_MODULE




        /* include required header files */
#include "error.h"
#include "prim.h"




/*
 *      sol_ptr - generic pointer to any type
 *
 *      The sol_ptr type is an abstract type representing a generic pointer to
 *      data type, including itself. This type can be declared only as a pointer
 *      in order to make it explicitly obvious that a pointer is being used.
 *
 *      The interface functions associated with this type depend on externally
 *      defined malloc() and free() functions in freestanding environments, and
 *      automatically make use of the malloc() and free() functions supplied by
 *      the standard library in hosted environments.
 */
typedef void sol_ptr;




/*
 *      SOL_PTR_NULL - generic null pointer
 *
 *      The SOL_PTR_NULL symbolic constant represents the generic null ponter.
 *      Using this symbolic constant instead of the standard NULL symbol is
 *      preferred because it removes dependence on the standard library and
 *      preserves the Sol namespace.
 */
#define SOL_PTR_NULL ((sol_ptr*)0)




/*
 *      sol_ptr_new() - initialises a new generic pointer
 *        - ptr: contextual pointer instance
 *        - sz : size in bytes of pointer buffer
 *
 *      The sol_ptr_new() interface function creates a new instance of a generic
 *      pointer @ptr in the heap memory with a buffer of size @sz bytes. This
 *      function requires an externally defined malloc() function to be present
 *      in freestanding environments; in hosted environments, it automatically
 *      uses the malloc() supplied by the standard library.
 *
 *      @ptr must be a valid pointer to a **null** pointer; this restriction
 *      helps to prevent subtle memory leaks caused by reallocating @ptr without
 *      having first freed the heap memory already allocated to it. @sz must be
 *      greater than zero. An appropriate exception is thrown if either of these
 *      conditions is not met.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer has been passed
 *        - SOL_ERNO_RANGE if an invalid size has been passed
 *        - SOL_ERNO_HEAP if heap memory failure occurs
 */
extern sol_erno sol_ptr_new(sol_ptr **ptr,
                            sol_size sz);




/*
 *      sol_ptr_copy() - copies an existing generic pointer
 *        - ptr: contextual pointer instance
 *        - src: source pointer instance
 *        - len: length in bytes of @src to copy
 *
 *      The sol_ptr_copy() interface function creates a new instance of a
 *      generic pointer @ptr in the heap memory, and copies @len bytes of data
 *      on to it from an existing buffer pointed by @src. Just as in the case of
 *      sol_ptr_new(), this function requires an externally defined malloc()
 *      function to be present in freestanding environments, while automatically
 *      selecting the malloc() supplied by the standard library in hosted
 *      environments.
 *
 *      Both @ptr and @src are required to be valid pointers; just as in the
 *      case of sol_ptr_new(), @ptr is also required to point to a null pointer
 *      to prevent accidental memory leaks. @len is required to be greater than
 *      zero. An appropriate exception is thrown if either of these conditions
 *      is not met. Additionally, @len is assumed to be not greater than the
 *      length of the buffer pointed by @src; no exception is thrown if this
 *      condition is not met, and the resulting behaviour is undefined.
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_PTR if an invalid pointer has been passed
 *        - SOL_ERNO_RANGE if an invalid size has been passed
 *        - SOL_ERNO_HEAP if heap memory failure occurs
 */
extern sol_erno sol_ptr_copy(sol_ptr **ptr,
                             const sol_ptr *src,
                             sol_size len);




/*
 *      sol_ptr_free() - frees an existing generic pointer
 *        - ptr: contextual pointer instance
 *
 *      The sol_ptr_free() interface function frees a generic pointer @ptr by
 *      releasing the heap memory allocated to it by a previous call to either
 *      sol_ptr_new() or sol_ptr_copy(). This function requires an externally
 *      defined free() function to be present in freestanding environments, and
 *      automatically uses the free() function provided by the standard library
 *      in hosted environments. @ptr is guaranteed to be null after this
 *      operation, thereby preventing the onset of dangling pointers.
 *
 *      @ptr is expected to be a valid handle to a **non-null** pointer, but in
 *      case this condition is not met, then a safe no-op occurs.
 */
extern void sol_ptr_free(sol_ptr **ptr);




#endif /* !defined __SOL_POINTER_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

