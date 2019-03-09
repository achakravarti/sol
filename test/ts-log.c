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
 *      mock_sleep() - mocks the sleep() function
 *        - scale: sleep duration scale
 */
static void mock_sleep(int scale)
{
        const long TICK = 100000000;
        auto int i;
        auto int j;

        for (i = 0; i < scale; i++) {
                for (j = 0; j < TICK; j++); /* NOLINT */
        }
}




/*
 *      str_find() - searches for a substring
 *        - what: substring to search
 *        - where: string to search in
 *
 *      Return:
 *        - 0 if @what is not found in @where
 *        - 1 if @what is found in where
 */
static const int str_find(const char *needle, const char *haystack)
{
        const char *nitr = needle;
        const char *hitr = haystack;
        const char *hmark;
        register int found = 0;

                /* ensure both @needle and @haystack are valid strings */
        if (!(nitr && hitr && *nitr && *hitr)) {
                return 0;
        }

                /* loop through @haystack until @needle is found within it */
        while (!found && *hitr) {
                        /* locate position in @haystack that matches the first
                         * character of @needle */
                if (*hitr != *nitr) {
                        hitr++;
                        continue;
                }

                        /* mark current position of @haystack iterator, and
                         * assume @needle is present in @haystack */
                hmark = hitr;
                found = 1;

                        /* iterate through @haystack (from current position) and
                         * @needle (from beginning) until our assumption that
                         * @needle is present in @haystack is proven false */
                while (*nitr) {
                        if (!*hitr || (*hitr++ != *nitr++)) {
                                found = 0;
                                break;
                        }
                }

                        /* continue looping after resetting @haystack iterator
                         * to its last marked position and @needle iterator to
                         * the beginning of @needle. */
                hitr = hmark;
                nitr = needle;
                hitr++;
        }

                /* wind up */
        return found;
}




/*
 *      log_hasstr() - check log entry for string
 *        - path: path to log file
 *        - str: string to check
 *        - line: line in which to check
 *
 *      Return:
 *        - 0 if @str is not found
 *        - 1 if @str is found
 */
static int log_hasstr(const char *path, const char *str, int line)
{
        const int LEN = 256;
        auto FILE *log = SOL_PTR_NULL;
        auto int rc = 0;
        auto char bfr[LEN];
        register int i;

                /* open log file at @path and check whether @str exists as a
                 * substring in the given @line; @path is assumed to be a valid
                 * string */
        if ((log = fopen(path, "r"))) { /* NOLINT */
                for (i = 0; i < line; i++) {
                        rc = fgets(bfr, LEN, log) ? str_find(str, bfr) : 0;
                }

                fclose(log);
        }

                /* wind up */
        return rc;
}




/*
 *      log_hasctm() - check log entry for current timestamp
 *        - path: path to log file
 *        - line: line in which to check
 *
 *      Return:
 *        - 0 if current timestamp not found
 *        - 1 if current timestamp found
 */
static int log_hasctm(const char *path, int line)
{
        const int NEWLN = 24;
        auto time_t tm;
        auto char *ctm;

                /* get current timestamp and trim away trailing newline */
        (void) time(&tm);
        ctm = ctime(&tm);
        ctm[NEWLN] = '\0';

                /* check if current timestamp is in the log file at @path */
        return log_hasstr(path, ctm, line);
}




/*
 *      open_test1() - sol_log_open() unit test #1
 */
static sol_erno open_test1(void)
{
        #define OPEN_TEST1 "sol_log_open() throws SOL_ERNO_STR if @path is" \
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
 *      open_test2() - sol_log_open() unit test #2
 */
static sol_erno open_test2(void)
{
        #define OPEN_TEST2 "sol_log_open() throws SOL_ERNO_STR if @path is" \
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
 *      open_test3() - sol_log_open() unit test #3
 */
static sol_erno open_test3(void)
{
        #define OPEN_TEST3 "sol_log_open() creates the log file specified" \
                           " by @path"
        const char *PATH = "bld/dummy.test.log";
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_trace("Hello!");
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[T]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "Hello!", line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      open_test4() - sol_log_open() unit test #4
 */
static sol_erno open_test4(void)
{
        #define OPEN_TEST4 "sol_log_open() throws SOL_ERNO_STATE if called" \
                           " when a log file is already open"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_try (sol_log_open(PATH));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_log_close();
        return sol_erno_get();
}




/*
 *      open2_test1() - sol_log_open2() unit test #1
 */
static sol_erno open2_test1(void)
{
        #define OPEN2_TEST1 "sol_log_open2() throws SOL_ERNO_STR if @path is" \
                            " a null pointer"

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open2(SOL_PTR_NULL, 0));

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
 *      open2_test2() - sol_log_open2() unit test #2
 */
static sol_erno open2_test2(void)
{
        #define OPEN2_TEST2 "sol_log_open2() throws SOL_ERNO_STR if @path is" \
                            " a null string"

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open2("", 0));

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
 *      open2_test3() - sol_log_open2() unit test #3
 */
static sol_erno open2_test3(void)
{
        #define OPEN2_TEST3 "sol_log_open2() creates the log file specified" \
                            " by @path when @flush is false"
        const char *PATH = "bld/dummy.test.log";
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open2(PATH, 0));
        sol_log_trace("Hello!");
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[T]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "Hello!", line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      open2_test4() - sol_log_open2() unit test #4
 */
static sol_erno open2_test4(void)
{
        #define OPEN2_TEST4 "sol_log_open2() creates the log file specified" \
                            " by @path when @flush is true"
        const char *PATH = "bld/dummy.test.log";
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open2(PATH, 1));
        sol_log_trace("Hello!");
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[T]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "Hello!", line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      open2_test5() - sol_log_open2() unit test #5
 */
static sol_erno open2_test5(void)
{
        #define OPEN2_TEST5 "sol_log_open2() overwrites the entries in the" \
                            " log file at @path when @flush is true"
        const char *PATH = "bld/dummy.test.log";
        const int line = 1;
        const int sleep = 10;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open2(PATH, 1));
        sol_log_trace("Hello!");
        sol_log_close();
        mock_sleep(10);
        sol_try (sol_log_open2(PATH, 1));
        sol_log_debug("Goodbye!");
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[D]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "Goodbye!", line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      open2_test6() - sol_log_open2() unit test #6
 */
static sol_erno open2_test6(void)
{
        #define OPEN2_TEST6 "sol_log_open2() preserves the entries in the" \
                            " log file at @path when @flush is false"
        const char *PATH = "bld/dummy.test.log";
        const int line = 2;
        const int sleep = 10;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open2(PATH, 1));
        sol_log_trace("Hello!");
        sol_log_close();
        mock_sleep(sleep);
        sol_try (sol_log_open2(PATH, 0));
        sol_log_debug("Goodbye!");
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[D]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "Goodbye!", line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      trace_test1() - sol_log_trace() unit test #1
 */
static sol_erno trace_test1(void)
{
        #define TRACE_TEST1 "sol_log_trace() writes a time-stamped trace" \
                            " message correctly"
        const char *PATH = "bld/dummy.test.log";
        const char *msg = "This is a sample trace message.";
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_trace(msg);
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[T]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, msg, line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      trace_test2() - sol_log_trace() unit test #2
 */
static sol_erno trace_test2(void)
{
        #define TRACE_TEST2 "sol_log_trace() performs a safe no-op if called" \
                            " when no log file is open"

                /* set up test scenario */
        sol_log_trace("Dummy");
        return SOL_ERNO_NULL;
}




/*
 *      trace_test3() - sol_log_trace() unit test #3
 */
static sol_erno trace_test3(void)
{
        #define TRACE_TEST3 "sol_log_trace() performs a safe no-op if passed" \
                            " a null pointer for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_trace(SOL_PTR_NULL);
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      trace_test4() - sol_log_trace() unit test #4
 */
static sol_erno trace_test4(void)
{
        #define TRACE_TEST4 "sol_log_trace() performs a safe no-op if passed" \
                            " a null string for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_trace("");
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      debug_test1() - sol_log_debug() unit test #1
 */
static sol_erno debug_test1(void)
{
        #define DEBUG_TEST1 "sol_log_debug() writes a time-stamped debug" \
                            " message correctly"
        const char *PATH = "bld/dummy.test.log";
        const char *msg = "This is a sample debug message.";
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_debug(msg);
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[D]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, msg, line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      debug_test2() - sol_log_debug() unit test #2
 */
static sol_erno debug_test2(void)
{
        #define DEBUG_TEST2 "sol_log_debug() performs a safe no-op if called" \
                            " when no log file is open"

                /* set up test scenario */
        sol_log_debug("Dummy");
        return SOL_ERNO_NULL;
}




/*
 *      debug_test3() - sol_log_debug() unit test #3
 */
static sol_erno debug_test3(void)
{
        #define DEBUG_TEST3 "sol_log_debug() performs a safe no-op if passed" \
                            " a null pointer for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_debug(SOL_PTR_NULL);
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      debug_test4() - sol_log_debug() unit test #4
 */
static sol_erno debug_test4(void)
{
        #define DEBUG_TEST4 "sol_log_debug() performs a safe no-op if passed" \
                            " a null string for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_debug("");
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      warn_test1() - sol_log_warn() unit test #1
 */
static sol_erno warn_test1(void)
{
        #define WARN_TEST1 "sol_log_warn() writes a time-stamped warning" \
                           " message correctly"
        const char *PATH = "bld/dummy.test.log";
        const char *msg = "This is a sample warning message.";
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_warn(msg);
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[W]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, msg, line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      warn_test2() - sol_log_warn() unit test #2
 */
static sol_erno warn_test2(void)
{
        #define WARN_TEST2 "sol_log_warn() performs a safe no-op if called" \
                           " when no log file is open"

                /* set up test scenario */
        sol_log_warn("Dummy");
        return SOL_ERNO_NULL;
}




/*
 *      warn_test3() - sol_log_warn() unit test #3
 */
static sol_erno warn_test3(void)
{
        #define WARN_TEST3 "sol_log_warn() performs a safe no-op if passed" \
                           " a null pointer for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_warn(SOL_PTR_NULL);
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      warn_test3() - sol_log_warn() unit test #3
 */
static sol_erno warn_test4(void)
{
        #define WARN_TEST4 "sol_log_warn() performs a safe no-op if passed" \
                           " a null string for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_warn("");
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      error_test1() - sol_log_error() unit test #1
 */
static sol_erno error_test1(void)
{
        #define ERROR_TEST1 "sol_log_error() writes a time-stamped error" \
                            " message correctly"
        const char *PATH = "bld/dummy.test.log";
        const char *msg = "This is a sample error message.";
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_error(msg);
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[E]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, msg, line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      error_test2() - sol_log_error() unit test #2
 */
static sol_erno error_test2(void)
{
        #define ERROR_TEST2 "sol_log_error() performs a safe no-op if called" \
                            " when no log file is open"

                /* set up test scenario */
        sol_log_error("Dummy");
        return SOL_ERNO_NULL;
}




/*
 *      error_test3() - sol_log_error() unit test #3
 */
static sol_erno error_test3(void)
{
        #define ERROR_TEST3 "sol_log_error() performs a safe no-op if passed" \
                            " a null pointer for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_error(SOL_PTR_NULL);
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      error_test4() - sol_log_error() unit test #4
 */
static sol_erno error_test4(void)
{
        #define ERROR_TEST4 "sol_log_error() performs a safe no-op if passed" \
                            " a null string for @msg"
        const char *PATH = "bld/dummy.test.log";

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_error("");
        sol_log_close();

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      erno_test1() - sol_log_erno() unit test #1
 */
static sol_erno erno_test1(void)
{
        #define ERNO_TEST1 "sol_log_erno() writes a time-stamped error code" \
                           " message correctly"
        const char *PATH = "bld/dummy.test.log";
        const char *msg = sol_erno_str(SOL_ERNO_STR);
        const int line = 1;

SOL_TRY:
                /* set up test scenario */
        sol_try (sol_log_open(PATH));
        sol_log_erno(SOL_ERNO_STR);
        sol_log_close();

                /* check test condition */
        sol_assert (log_hasctm(PATH, line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, "[E]", line), SOL_ERNO_TEST);
        sol_assert (log_hasstr(PATH, msg, line), SOL_ERNO_TEST);

SOL_CATCH:
                /* nothing to do in case of an exception */

SOL_FINALLY:
                /* wind up */
        return sol_erno_get();
}




/*
 *      erno_test2() - sol_log_erno() unit test #2
 */
static sol_erno erno_test2(void)
{
        #define ERNO_TEST2 "sol_log_erno() performs a safe no-op if called" \
                           " when no log file is open"

                /* set up test scenario */
        sol_log_erno(SOL_ERNO_STR);
        return SOL_ERNO_NULL;
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
        sol_try (sol_tsuite_register(ts, &open_test1, OPEN_TEST1));
        sol_try (sol_tsuite_register(ts, &open_test2, OPEN_TEST2));
        sol_try (sol_tsuite_register(ts, &open_test3, OPEN_TEST3));
        sol_try (sol_tsuite_register(ts, &open_test4, OPEN_TEST4));
        sol_try (sol_tsuite_register(ts, &open2_test1, OPEN2_TEST1));
        sol_try (sol_tsuite_register(ts, &open2_test2, OPEN2_TEST2));
        sol_try (sol_tsuite_register(ts, &open2_test3, OPEN2_TEST3));
        sol_try (sol_tsuite_register(ts, &open2_test4, OPEN2_TEST4));
        sol_try (sol_tsuite_register(ts, &open2_test5, OPEN2_TEST5));
        sol_try (sol_tsuite_register(ts, &open2_test6, OPEN2_TEST6));
        sol_try (sol_tsuite_register(ts, &trace_test1, TRACE_TEST1));
        sol_try (sol_tsuite_register(ts, &trace_test2, TRACE_TEST2));
        sol_try (sol_tsuite_register(ts, &trace_test3, TRACE_TEST3));
        sol_try (sol_tsuite_register(ts, &trace_test4, TRACE_TEST4));
        sol_try (sol_tsuite_register(ts, &debug_test1, DEBUG_TEST1));
        sol_try (sol_tsuite_register(ts, &debug_test2, DEBUG_TEST2));
        sol_try (sol_tsuite_register(ts, &debug_test3, DEBUG_TEST3));
        sol_try (sol_tsuite_register(ts, &debug_test4, DEBUG_TEST4));
        sol_try (sol_tsuite_register(ts, &warn_test1, WARN_TEST1));
        sol_try (sol_tsuite_register(ts, &warn_test2, WARN_TEST2));
        sol_try (sol_tsuite_register(ts, &warn_test3, WARN_TEST3));
        sol_try (sol_tsuite_register(ts, &warn_test4, WARN_TEST4));
        sol_try (sol_tsuite_register(ts, &error_test1, ERROR_TEST1));
        sol_try (sol_tsuite_register(ts, &error_test2, ERROR_TEST2));
        sol_try (sol_tsuite_register(ts, &error_test3, ERROR_TEST3));
        sol_try (sol_tsuite_register(ts, &error_test4, ERROR_TEST4));
        sol_try (sol_tsuite_register(ts, &erno_test1, ERNO_TEST1));
        sol_try (sol_tsuite_register(ts, &erno_test2, ERNO_TEST2));

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

