#include "../src/api.h"
#include "suite.h"




        /* str_len() determines the length of a string @str */
static sol_inline sol_size str_len(const char *str)
{
        const char *itr;

        itr = str;
        while (*itr++);

        return (sol_size) (itr - str);
}




        /* str_new() creates a new heap allocated string @str from a stack
         * allocated string @src */
static sol_erno str_new(char **str, const char *src)
{
        const char *sitr;    /* iterator for @src */
        register char *ditr; /* iterator for @str */

SOL_TRY:
                /* copy @src to @str */
        sol_try (sol_ptr_new((sol_ptr **) str, str_len(src)));

                /* init iterators */
        sitr = src;
        ditr = *str;

                /* copy each character from @src to @str */
        while (*sitr)
                *ditr++ = *sitr++;

                /* terminate @str */
        *ditr = '\0';

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* return current error code */
        return sol_erno_get();
}




        /* str_dispose() releases the heap memory allocated to a heap allocated
         * string @str */
static sol_inline void str_dispose(sol_ptr **str)
{
        sol_ptr_free(str);
}




        /* str_eq() checks whether a string @lhs is lexicographically equal to
         * another string @rhs, saving the comparison result to @eq. */
static sol_erno str_eq(const sol_ptr *lhs, const sol_ptr *rhs, SOL_BOOL *eq)
{
        register char *litr; /* iterator for @lhs */
        register char *ritr; /* iterator for @rhs */

                /* init iterators */
        litr = (char *) lhs;
        ritr = (char *) rhs;

                /* loop through each character in @lhs and @rhs, checking for
                 * equality */
        do {
                *eq = (*litr == *ritr);
        } while (*eq && *litr++ && *ritr++);

                /* no error is expected to occur */
        return SOL_ERNO_NULL;
}




        /* str_lt() checks whether a string @lhs is lexicographically less than
         * another string @rhs, saving the comparison result to @lt. */
static sol_erno str_lt(const sol_ptr *lhs, const sol_ptr *rhs, SOL_BOOL *lt)
{
        register char *litr; /* iterator for @lhs */
        register char *ritr; /* iterator for @rhs */

                /* init iterators */
        litr = (char *) lhs;
        ritr = (char *) rhs;

                /* loop through each character in @lhs and @rhs, checking
                 * whether @lhs < @rhs */
        do {
                *lt = (*litr < *ritr);
        } while (*lt && *litr++ && *ritr++);

                /* no error is expected to occur */
        return SOL_ERNO_NULL;
}




        /* str_gt() checks whether a string @lhs is lexicographically greater
         * than another string @rhs, saving the comparison result to @gt. */
static sol_erno str_gt(const sol_ptr *lhs, const sol_ptr *rhs, SOL_BOOL *lt)
{
        register char *litr; /* iterator for @lhs */
        register char *ritr; /* iterator for @rhs */

                /* init iterators */
        litr = (char *) lhs;
        ritr = (char *) rhs;

                /* loop through each character in @lhs and @rhs, checking
                 * whether @lhs > @rhs */
        do {
                *lt = (*litr > *ritr);
        } while (*lt && *litr++ && *ritr++);

                /* no error is expected to occur */
        return SOL_ERNO_NULL;
}




        /* meta_new() initialises the element metadata @meta used for testing
         * the sol_list interface. */
static sol_inline sol_erno meta_new(sol_elem_meta **meta)
{
        const sol_index ID = (sol_index) 5;
        const sol_size SZ = sizeof (char *);

        return sol_elem_meta_new4(meta,
                                  ID,
                                  SZ,
                                  str_dispose,
                                  str_eq,
                                  str_lt,
                                  str_gt);
}




        /* elem_new() initialises an element @elem with a payload string @str */
static sol_erno elem_new(sol_elem **elem, const char *str)
{
        auto sol_elem_meta *meta; /* metadata of @elem */
        auto char *hstr;          /* heap copy of @str */

SOL_TRY:
                /* init @elem metadata */
        meta = SOL_PTR_NULL;
        sol_try (meta_new(&meta));

                /* init heap copy of @str */
        hstr = SOL_PTR_NULL;
        sol_try (str_new(&hstr, str));

                /* init @elem with heap copy of @str */
        sol_try (sol_elem_new(elem, meta, (sol_ptr *) hstr));

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* return current error code */
        return sol_erno_get();
}




        /* new_test1() defines the test case described by NEW_TEST1 */
static sol_erno new_test1(void)
{
        #define NEW_TEST1 "sol_list_new() throws SOL_ERNO_PTR if passed a" \
                          " null pointer for @list"

SOL_TRY:
                /* set up test */
        sol_try (sol_list_new(SOL_PTR_NULL));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* return current error code */
        return sol_erno_get();
}




        /* new_test2() defines the test case described by NEW_TEST2 */
static sol_erno new_test2(void)
{
        #define NEW_TEST2 "sol_list_new() creates a new list instance"

        auto sol_list *list; /* test list */

SOL_TRY:
                /* set up test */
        list = SOL_PTR_NULL;
        sol_try (sol_list_new(&list));

                /* check test condition */
        sol_assert (list, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* wind up */
        sol_list_free(&list);

                /* return current error code */
        return sol_erno_get();
}




        /* new_test3() defines the test case described by NEW_TEST3 */
static sol_erno new_test3(void)
{
        #define NEW_TEST3 "sol_list_new() throws SOL_ERNO_STATE if passed a" \
                          " non-null pointer"

        auto sol_list *list; /* test list */

SOL_TRY:
                /* set up test condition */
        list = SOL_PTR_NULL;
        sol_try (sol_list_new(&list));
        sol_try (sol_list_new(&list));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_STATE
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* wind up */
        sol_list_free(&list);

                /* return current error code */
        return sol_erno_get();
}




        /* len_test1() defines the test case described by LEN_TEST1 */
static sol_erno len_test1(void)
{
        #define LEN_TEST1 "sol_list_len() returns 0 for a newly created @list"

        auto sol_list *list; /* test list       */
        auto sol_size len;   /* length of $list */

SOL_TRY:
                /* set up test */
        list = SOL_PTR_NULL;
        sol_try (sol_list_new(&list));

                /* check test condition */
        sol_try (sol_list_len(list, &len));
        sol_assert (!len, SOL_ERNO_TEST);

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* wind up */
        sol_list_free(&list);

                /* return current error code */
        return sol_erno_get();
}




        /* len_test2() defines the test case described by LEN_TEST2 */
static sol_erno len_test2(void)
{
        #define LEN_TEST2 "sol_list_len() throws SOL_ERNO_PTR if passed a" \
                          " null pointer for @list"

        auto sol_size len; /* dummy length */

SOL_TRY:
                /* set up test */
        sol_try (sol_list_len(SOL_PTR_NULL, &len));

SOL_CATCH:
                /* check test condition */
        sol_erno_set(sol_erno_get() == SOL_ERNO_PTR
                     ? SOL_ERNO_NULL
                     : SOL_ERNO_TEST);

SOL_FINALLY:
                /* return current error code */
        return sol_erno_get();
}




        /* __sol_tests_list() is declared in sol/test/suite.h */
extern sol_erno __sol_tests_list(sol_tlog *log,
                                 sol_uint *pass,
                                 sol_uint *fail,
                                 sol_uint *total)
{
        auto sol_tsuite ts;   /* sol_list test suite */
        auto sol_tsuite *hnd; /* handle to $ts       */

SOL_TRY:
                /* check preconditions */
        sol_assert (log && pass && fail && total, SOL_ERNO_PTR);

                /* init test suite */
        hnd = &ts;
        sol_try (sol_tsuite_init2(hnd, log));

                /* register sol_list_new() test cases */
        sol_try (sol_tsuite_register(hnd, new_test1, NEW_TEST1));
        sol_try (sol_tsuite_register(hnd, new_test2, NEW_TEST2));
        sol_try (sol_tsuite_register(hnd, new_test3, NEW_TEST3));

                /* register sol_list_len() test cases */
        sol_try (sol_tsuite_register(hnd, len_test1, LEN_TEST1));
        sol_try (sol_tsuite_register(hnd, len_test2, LEN_TEST2));

                /* execute test cases */
        sol_try (sol_tsuite_exec(hnd));

                /* report test counts */
        sol_try (sol_tsuite_pass(hnd, pass));
        sol_try (sol_tsuite_fail(hnd, fail));
        sol_try (sol_tsuite_total(hnd, total));

SOL_CATCH:
                /* pass by in case of exception */

SOL_FINALLY:
                /* wind up */
        sol_tsuite_term(hnd);

                /* return currrent error code */
        return sol_erno_get();
}


