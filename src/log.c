/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/src/log.c
 *
 * Description:
 *      This file is part of the internal implementation of the Sol Library.
 *      It implements the logging module.
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
#include "../inc/hint.h"
#include "../inc/libc.h"
#include "../inc/log.h"
#include "../inc/ptr.h"




/*
 *      log_hnd - handle to log file
 */
static sol_tls FILE *log_hnd = SOL_PTR_NULL;




/*
 *      sol_log_open() - declared in sol/inc/log.h
 */
extern sol_erno sol_log_open(const char *path)
{
SOL_TRY:
                /* check preconditions */
        sol_assert (!log_hnd, SOL_ERNO_PTR);
        sol_assert (path && *path, SOL_ERNO_STR);

                /* open the log file using the standard fopen() function
                 * provided by the libc module */
        log_hnd = fopen(path, "w"); /* NOLINT */
        sol_assert (log_hnd, SOL_ERNO_FILE);

SOL_CATCH:
                /* nothing to do if an exception occurs */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      sol_log_open2() - declared in sol/inc/log.h
 */
extern sol_erno sol_log_open2(const char *path,
                              const int flush)
{
SOL_TRY:
                /* check preconditions */
        sol_assert (!log_hnd, SOL_ERNO_PTR);
        sol_assert (path && *path, SOL_ERNO_STR);

                /* open the log file, flushing it if required; we use the
                 * standard fopen() function provided by the libc module */
        log_hnd = fopen(path, flush ? "w" : "a+");
        sol_assert (log_hnd, SOL_ERNO_FILE);

SOL_CATCH:
                /* nothing to do if an exception occurs */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      sol_log_close() - declared in sol/inc/log.h
 */
extern void sol_log_close(void)
{
                /* close log file if it's open; we use the standard fclose()
                 * function provided by the libc module */
        if (log_hnd) {
                (void) fclose(log_hnd);
                log_hnd = SOL_PTR_NULL;
        }
}




/*
 *      __sol_log_write() - declared in sol/inc/log.h
 *        - type: log entry type - (T)race, (D)ebug, or (E)rror
 *        - func: function name of log entry source
 *        - file: file name of log entry source
 *        - line: line number of log entry source
 *        - msg: log message
 */
extern void __sol_log_write(const char *type,
                            const char *func,
                            const char *file,
                            int line,
                            const char *msg)
{
        const char *FMT = "[%s] [%s] [%s():%s:%d] %s\n";
        auto time_t tm;
        auto char *ctm;

                /* determine current local time */
        (void) time(&tm);
        ctm = ctime(&tm);

                /* write entry to log file if it's open; this check is necessary
                 * because the wrapper macros sol_log_trace(), sol_log_debug(),
                 * sol_log_error(), and sol_log_erno() may be called even if the
                 * log file hasn't been opened */
        if (log_hnd) {
                (void) fprintf(log_hnd, FMT, type, ctm, func, file, line, msg);
        }
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

