
        /* include required header files */
#include "api.h"




        /* define the float_lt() utility function; this function returns true if
         * @lhs < @rhs, and false otherwise; this function uses Donald Knuth's
         * algorithm for the same as answered by user mch in the question posted
         * on https://stackoverflow.com/questions/17333 */
extern SOL_BOOL sol_f64_lt(const sol_f64 lhs, const sol_f64 rhs)
{
        return (rhs - lhs) > SOL_F64_EPSILON;
}




        /* define the float_eq() utility function; this function returns true if
         * @lhs == @rhs, and false otherwise; this function uses Donald Knuth's
         * algorithm for the same as answered by user mch in the question posted
         * on https://stackoverflow.com/questions/17333 */
extern SOL_BOOL sol_f64_eq(const sol_f64 lhs, const sol_f64 rhs)
{
        return fabs(lhs - rhs) < SOL_F64_EPSILON;
}




        /* define the float_gt() utility function; this function returns true if
         * @lhs > @rhs, and false otherwise; this function uses Donald Knuth's
         * algorithm for the same as answered by user mch in the question posted
         * on https://stackoverflow.com/questions/17333 */
extern SOL_BOOL sol_f64_gt(const sol_f64 lhs, const sol_f64 rhs)
{
        return (lhs - rhs) > SOL_F64_EPSILON;
}




