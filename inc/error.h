/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/error.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the exception handling module.
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
#if !defined __SOL_EXCEPTION_HANDLING_MODULE
#define __SOL_EXCEPTION_HANDLING_MODULE




        /* include required header files */
#include "hint.h"
#include "prim.h"




/*
 *      sol_erno - generic error code
 *
 *      The sol_erno concrete data type is used to hold error codes. Error codes
 *      may be defined by client code as unsigned integers, with the exception
 *      of the error codes defined below. This type aligns itself to the native
 *      word size of its compilation environment. Any function returning this
 *      type can take advantage of the exception handling features provided by
 *      this module.
 */
typedef sol_word sol_erno;




/*
 *      SOL_ERNO_NULL - no error
 *
 *      The SOL_ERNO_NULL symbolic constant indicates that no error has
 *      occurred. This error code is reserved by the Sol Library, and should
 *      **not** be redefined by client code. Functions that take advantage of
 *      the try-catch mechanism implemented by this module (through the SOL_TRY
 *      and SOL_CATCH labels) return this symbolic constant by default if they
 *      don't encounter any errors during execution.
 */
#define SOL_ERNO_NULL ((sol_erno) 0x0)




/*
 *      SOL_ERNO_PTR - invalid pointer
 *
 *      The SOL_ERNO_PTR symbolic constant indicates that an invalid pointer has
 *      been passed to an interface function or macro. This error code is
 *      reserved by the Sol Library, and should **not** be redefined by client
 *      code.
 */
#define SOL_ERNO_PTR ((sol_erno) 0x1)




/*
 *      SOL_ERNO_STR - invalid string
 *
 *      The SOL_ERNO_STR symbolic constant indicates that an invalid string has
 *      been passed to an interface function or macro. An invalid string is not
 *      necessarily a null string, and will depend on the context. Note that
 *      this error code should not be used to indicate null string pointers, and
 *      should be indicated by SOL_ERNO_PTR instead. This error code is reserved
 *      by the Sol Library, and should **not** be redefined by client code.
 */
#define SOL_ERNO_STR ((sol_erno) 0x2)




/*
 *      SOL_ERNO_RANGE - range error
 *
 *      The SOL_ERNO_RANGE symbolic constant indicates that a value that is
 *      outside its acceptable range has been passed to an interface function or
 *      macro. This error code is reserved by the Sol Library, and should
 *      **not** be redefined by client code.
 */
#define SOL_ERNO_RANGE ((sol_erno) 0x3)




/*
 *      SOL_ERNO_TEST - unit test failure
 *
 *      The SOL_ERNO_TEST symbolic constant indicates that a unit test failed.
 *      Note that this error code does not indicate an exception with the
 *      exception handling system, but rather that the condition that a unit
 *      test is checking has not been fulfilled. This error code is reserved by
 *      the Sol Library, and should **not** be redefined by client code.
 */
#define SOL_ERNO_TEST ((sol_erno)0x4)




/*
 *      SOL_ERNO_HEAP - heap memory failure
 */
#define SOL_ERNO_HEAP ((sol_erno)0x5)




/*
 *      SOL_ERNO_FILE - file error
 */
#define SOL_ERNO_FILE ((sol_erno)0x6)




/*
 *      SOL_ERNO_STATE - invalid state
 */
#define SOL_ERNO_STATE ((sol_erno)0x7)




/*
 *      SOL_TRY - start of try block
 *
 *      The SOL_TRY label identifies the starting point of the try block within
 *      a function that returns a sol_erno value. The try block contains the
 *      normal flow of code that may throw exceptions. It must be placed at the
 *      beginning of the function body, right after declaring any required local
 *      variables and constants, and terminated by a SOL_CATCH block.
 *
 *      The code that may throw exceptions within this block must be tested
 *      through the sol_assert() and sol_try() macros defined below. In case an
 *      exception occurs, then control is passed to the adjacent SOL_CATCH
 *      block without executing the remaining code in the try block.
 *
 *      If no error occurs, then control automatically moves to the SOL_FINALLY
 *      block placed after the SOL_CATCH block; this allows for the necessary
 *      cleanup code to be performed.
 */
#define SOL_TRY                                       \
        register sol_erno __sol_erno = SOL_ERNO_NULL; \
        goto __SOL_TRY;                               \
        __SOL_TRY




/*
 *      SOL_CATCH - start of catch block
 *
 *      The SOL_CATCH label identifies the starting point of a catch block
 *      within a function that returns a sol_erno value. The catch block
 *      contains the error handling code, and must be placed immediately at the
 *      end of a SOL_TRY block.
 *
 *      The SOL_CATCH block must be terminated by an adjacent SOL_FINALLY block.
 *      This allows all necessary cleanup code to be performed after the
 *      exception handling code has been executed. At no point should the
 *      sol_assert() and sol_try() macros be used in the SOL_CATCH block, as
 *      this would potentially lead to an infinite loop.
 */
#define SOL_CATCH           \
        goto __SOL_FINALLY; \
        __SOL_CATCH




/*
 *      SOL_FINALLY - start of finally block
 *
 *      The SOL_FINALLY label identifies the starting point of a finally block
 *      within a function that returns a sol_erno value. The finally block
 *      contains the cleanup code that is common to both the try and catch
 *      blocks, and must be placed immediately at the end of a SOL_TRY block.
 *
 *      The SOL_FINALLY block must be terminated by returning the current error
 *      code provided by the sol_erno_get() macro defined below. At no point
 *      should the sol_assert() and sol_try() macros be used in the SOL_FINALLY
 *      block as this could potentially lead to an infinite loop.
 */
#define SOL_FINALLY __SOL_FINALLY




/*
 *      sol_erno_get() - gets current error code
 *
 *      The sol_erno_get() macro returns the current sol_erno error code within
 *      the context of the function in which it is called. This macro is meant
 *      to be used primarily within SOL_CATCH blocks, but if required, may also
 *      be used within SOL_TRY and SOL_FINALLY blocks.
 *
 *      Return:
 *        - SOL_ERNO if no error has occured
 *        - The current error code if an error has occured
 */
#define /* sol_erno */ sol_erno_get(/* void */) \
        ((const sol_erno) __sol_erno)




/*
 *      sol_erno_str() - stringifies error code
 *        - erno: error code
 *
 *      The sol_erno_str() function generates the string representation of a
 *      sol_erno error code @erno. This function represents @erno in hexadecimal
 *      notation prefixed with a "0x".
 *
 *      Return:
 *        - string representation of @erno
 */
extern const char *sol_erno_str(sol_erno erno);




/*
 *      sol_erno_set() - sets current error code
 *        - erno: error code
 *
 *      The sol_erno_set() macro sets the current sol_erno error code @erno
 *      within the context of the function in which it is called. Like its
 *      sister macro sol_erno_get(), this macro is meant to be used within
 *      SOL_CATCH blocks, but may also be used within SOL_TRY and SOL_FINALLY
 *      blocks as required.
 */
#define /* void */ sol_erno_set(/* const sol_erno */ erno) \
        (__sol_erno = (erno))




/*
 *      sol_assert() - verifies precondition
 *        - p: precondition predicate being asserted
 *        - e: error code to be thrown if assertion fails
 *
 *      The sol_assert() macro verifies whether a precondition, expressed as a
 *      predicate @p, is true before any further processing takes place. This
 *      macro can only be called within a SOL_TRY block. If the assertion fails,
 *      then a sol_erno error code @e is thrown and control jumps to the
 *      adjacent SOL_CATCH block.
 *
 *      This macro should **never** be called within a SOL_CATCH block as it may
 *      potentially lead to an infinite loop.
 */
#define /* void */ sol_assert(p, /* sol_erno */ e) \
        do {                                       \
                if (sol_unlikely (!(p))) {         \
                        __sol_erno = (e);          \
                        goto __SOL_CATCH;          \
                }                                  \
        } while (0)




/*
 *      sol_try() - validates postcondition
 *        - p: postcondition being evaluated
 *
 *      The sol_try() macro validates whether a postcondition @p, expressed as a
 *      function returning a sol_erno value, has not failed. The function is
 *      deemed to have run successfully if it has not thrown any exception as
 *      flagged by the returned error code. This macro can only be called within
 *      a SOL_TRY block. If the validation fails, then control will jump to the
 *      adjacent SOL_CATCH block.
 *
 *      As with the sol_assert() macro, this macro should **never** be called
 *      within a SOL_CATCH block as it may potentially lead to an infinite loop.
 */
#define /* void */ sol_try(p)                            \
        do {                                             \
                if (sol_unlikely ((__sol_erno = (p)))) { \
                        goto __SOL_CATCH;                \
                }                                        \
        } while (0)




#endif /* !defined __SOL_EXCEPTION_HANDLING_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

