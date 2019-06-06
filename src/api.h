/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/api.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the modules that make up the Sol Library.
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
#if !defined __SOL_LIBRARY_API_INCLUDED
#define __SOL_LIBRARY_API_INCLUDED




#include "../inc/env.h" /* TODO: remove later */
#include "../inc/prim.h" /* TODO: remove later */
#include "../inc/error.h" /* TODO: remove later */

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



typedef struct __sol_elem sol_elem;

typedef struct __sol_elem_meta sol_elem_meta;

typedef void (sol_elem_delegate_dispose)(sol_ptr **data);

typedef sol_erno (sol_elem_delegate_lt)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *lt);

typedef sol_erno (sol_elem_delegate_eq)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *eq);

typedef sol_erno (sol_elem_delegate_gt)(const sol_ptr *lhs,
                                        const sol_ptr *rhs,
                                        SOL_BOOL *gt);

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
                                    sol_elem_delegate_dispose *disp,
                                    sol_elem_delegate_eq *eq,
                                    sol_elem_delegate_lt *lt,
                                    sol_elem_delegate_gt *gt);

extern sol_erno sol_elem_meta_copy(sol_elem_meta **meta,
                                    const sol_elem_meta *src);

extern void sol_elem_meta_free(sol_elem_meta **meta);




/* Module: List */
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

extern sol_erno sol_list_pop(sol_list **list);




/*
 *      sol_log_open() - opens log file
 *        - path: log file path
 *
 *      The sol_log_open() interface function opens the log file located at
 *      @path, and sets it as the default log file where the log entries will be
 *      written by the logging module. This function flushes out the contents of
 *      the log file at @path if it exists, and creates it if it does not exist.
 *
 *      @path is required to be a valid non-null string, or else an exception is
 *      thrown. An error is also raised in case the log file at @path has
 *      already been opened by an earlier call to either sol_log_open() or
 *      sol_log_open2().
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_STATE if log file is already open
 *        - SOL_ERNO_STR if @path is invalid
 *        - SOL_ERNO_FILE if log file can't be opened
 */
extern sol_erno sol_log_open(const char *path);




/*
 *      sol_log_open2() - opens log file
 *        - path: log file path
 *        - flush: flag to indicate whether log file should be flushed
 *
 *      The sol_log_open2() interface function is the overloaded form of the
 *      sol_log_open() function declared above. This function, like its original
 *      form, opens the log file located @path, and sets it as the default log
 *      file where the log entries will be written by the logging module. In
 *      addition, this function allows a flag @flush to explicitly specify
 *      whether or not the contents of the log file should be flushed on
 *      opening in case file already exists. If the file does not exist, then
 *      this function creates it.
 *
 *      @path is required to be a valid non-null string, or else an exception is
 *      thrown. An error is also raised in case the log file at @path has
 *      already been opened by an earlier call to either sol_log_open() or
 *      sol_log_open2().
 *
 *      Return:
 *        - SOL_ERNO_NULL if no error occurs
 *        - SOL_ERNO_STATE if log file is already open
 *        - SOL_ERNO_STR if @path is invalid
 *        - SOL_ERNO_FILE if log file can't be opened
 */
extern sol_erno sol_log_open2(const char *path,
                              int flush);




/*
 *      sol_log_close() - closes log file
 *
 *      The sol_log_close() interface function closes the log file that has been
 *      opened by an earlier call to either sol_log_open() or sol_log_open2().
 *      Calling this function when no log file is currently open results in a
 *      safe no-op.
 *
 *      This function must be called when the logging module is no longer
 *      required in order to prevent a resource leak.
 */
extern void sol_log_close(void);




/*
 *      sol_log_trace() - logs a trace message
 *        - msg: message
 *
 *      The sol_log_trace() interface macro records a trace message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_trace(/* const char* */ msg) \
        __sol_log_write("T",                            \
                        sol_env_func(),                 \
                        sol_env_file(),                 \
                        sol_env_line(),                 \
                        (msg))




/*
 *      sol_log_debug() - logs a debug message
 *        - msg: message
 *
 *      The sol_log_debug() interface macro records a debug message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_debug(/* const char* */ msg) \
        __sol_log_write("D",                            \
                        sol_env_func(),                 \
                        sol_env_file(),                 \
                        sol_env_line(),                 \
                        (msg))




/*
 *      sol_log_warn() - logs a warning message
 *        - msg: message
 *
 *      The sol_log_warn() interface macro records a warning message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_warn(/* const char* */ msg) \
        __sol_log_write("W",                           \
                        sol_env_func(),                \
                        sol_env_file(),                \
                        sol_env_line(),                \
                        (msg))




/*
 *      sol_log_error() - logs an error message
 *        - msg: message
 *
 *      The sol_log_error() interface macro records an error message @msg to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_error(/* const char* */ msg) \
        __sol_log_write("E",                            \
                        sol_env_func(),                 \
                        sol_env_file(),                 \
                        sol_env_line(),                 \
                        (msg))




/*
 *      sol_log_erno() - log an error code
 *        - erno: error code
 *
 *      The sol_log_erno() interface macro records an error code @erno to the
 *      currently open log file. The current local timestamp and code location
 *      are automatically prefixed to @msg. It is safe to call this macro even
 *      if no log file is currently open.
 */
#define /* void */ sol_log_erno(/* sol_erno */ erno) \
        __sol_log_write("E",                         \
                        sol_env_func(),              \
                        sol_env_file(),              \
                        sol_env_line(),              \
                        sol_erno_str((erno)))




/*
 *      __sol_log_write() - writes a log entry
 *
 *      The __sol_log_write() function is **not** a part of the interface of the
 *      logging module, and must **not** be called directly. This function is a
 *      utility function that helps in writing log entries to the log file, and
 *      has been declared in this file so that it can be called by the logging
 *      macros defined above.
 */
extern void __sol_log_write(const char *type,
                            const char *func,
                            const char *file,
                            int line,
                            const char *msg);




        /* close header guard __SOL_LIBRARY_API_INCLUDED */
#endif




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

