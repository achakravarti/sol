/******************************************************************************
 *                           SOL LIBRARY v1.0.0+41
 *
 * File: sol/test/ts-log.c
 *
 * Description:
 *      This file is part of the internal quality checking of the Sol Library.
 *      It implements the test suite for the logging module.
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
#include "../inc/libc.h"
#include "../inc/ptr.h"
#include "./suite.h"




/*
 *      str_find() - searches for a substring
 *        - what: substring to search
 *        - where: string to search in
 *
 *      Return:
 *        - 0 if @what is not found in @where
 *        - 1 if @what is found in where
 */
static int str_find(const char *what,
                    const char *where)
{
        const char *i = where;
        const char *j = what;

                /* ensure @what and @where are not empty */
        if (!(i && j && *i && *j)) {
                return 0;
        }

                /* iterate through each character in @where; when the first
                 * character of @what is found, check whether @what exists as a
                 * substring of @where */
        while (*i) {
                if (*i == *j) {
                        while (*j) {
                                if (*i++ != *j++) {
                                        return 0;
                                }
                        }

                        return 1;
                }

                i++;
        }

                /* if we're here, then @what hasn't been found in @where */
        return 0;
}




/*
 *      log_hasstr() - check log entry for string
 *        - path: path to log file
 *        - str: string to check
 *
 *      Return:
 *        - 0 if @str is not found
 *        - 1 if @str is found
 */
static int log_hasstr(const char *path,
                      const char *str)
{
        const int LEN = 256;
        auto FILE *log = SOL_PTR_NULL;
        auto int rc = 0;
        auto char bfr[LEN];

                /* open log file at @path and read check whether @str exists as
                 * a substring in the first line; @path is assumed to be a valid
                 * string */
        if ((log = fopen(path, "r"))) { /* NOLINT */
                rc = fgets(bfr, LEN, log) ? str_find(str, bfr) : 0;
                fclose(log);
        }

                /* wind up */
        return rc;
}




/*
 *      log_hasctm() - check log entry for current timestamp
 *        - path: path to log file
 *
 *      Return:
 *        - 0 if current timestamp not found
 *        - 1 if current timestamp found
 */
static int log_hasctm(const char *path)
{
        const int NEWLN = 24;
        auto time_t tm;
        auto char *ctm;

                /* get current timestamp and trim away trailing newline */
        (void) time(&tm);
        ctm = ctime(&tm);
        ctm[NEWLN] = '\0';

                /* check if current timestamp is in the log file at @path */
        return log_hasstr(path, ctm);
}




/*
 *      test_open1() - sol_log_open() unit test #1
 */
static sol_erno test_open1(void)
{
        #define DESC_OPEN1 "sol_log_open() throws SOL_ERNO_STR is @path is" \
                           " a null pointer"

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_log_close();
        return sol_erno_get();
}




/*
 *      test_open2() - sol_log_open() unit test #2
 */
static sol_erno test_open2(void)
{
        #define DESC_OPEN2 "sol_log_open() throws SOL_ERNO_STR is @path is" \
                           " a null string"

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(""));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_log_close();
        return sol_erno_get();
}




/*
 *      test_open3() - sol_log_open() unit test #3
 */
static sol_erno test_open3(void)
{
        #define DESC_OPEN3 "sol_log_open() should create the log file" \
                           " specified by @path"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_trace("Hello!");
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[T]"), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "Hello"), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      __sol_tests_log() - declared in sol/test/suite.h
 */
extern sol_erno __sol_tests_log(sol_tlog *log,
                                int *pass,
                                int *fail,
                                int *total)
{
        auto sol_tsuite __ts, *ts = &__ts;

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* initialise test suite */
        sol_try (sol_tsuite_init2(ts, log));

                /* register test cases */
        sol_try (sol_tsuite_register(ts, &test_open1, DESC_OPEN1));
        sol_try (sol_tsuite_register(ts, &test_open2, DESC_OPEN2));
        sol_try (sol_tsuite_register(ts, &test_open3, DESC_OPEN3));

                /* execute test cases */
        sol_try (sol_tsuite_exec(ts));

                /* report test counts */
        sol_try (sol_tsuite_pass(ts, pass));
        sol_try (sol_tsuite_fail(ts, fail));
        sol_try (sol_tsuite_total(ts, total));

SOL_CATCH:
SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(ts);
        return sol_erno_get();
}




/******************************************************************************
 *                                    EOF
 *          Built on hyperion [Tue Jan 29 02:37:24 UTC 2019]
 ******************************************************************************/

