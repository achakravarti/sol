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




