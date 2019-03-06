/******************************************************************************
 *                           SOL LIBRARY v0.1.0+41
 *
 * File: sol/inc/log.h
 *
 * Description:
 *      This file is part of the API of the Sol Library. It declares the
 *      interface of the logging module.
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
#if (!defined __SOL_LOGGING_MODULE)
#define __SOL_LOGGING_MODULE




        /* include required header files */
#include "./env.h"
#include "./error.h"




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
 *        - SOL_ERNO_PTR if log file is already open
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
 *        - SOL_ERNO_PTR if log file is already open
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




#endif /* !defined __SOL_LOGGING_MODULE */




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

