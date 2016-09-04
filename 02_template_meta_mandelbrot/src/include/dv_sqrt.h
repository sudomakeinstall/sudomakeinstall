#ifndef dv_sqrt_h
#define dv_sqrt_h

#include <limits>   

namespace dv
{

namespace Detail
{
  double constexpr sqrtNewtonRaphson(double x, double curr, double prev)
  {
    return curr == prev
      ? curr
      : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
  }
}

/*
 * * Constexpr version of the square root
 * * Return value:
 * *   - For a finite and non-negative value of "x", returns an approximation for the square root of "x"
 * *   - Otherwise, returns NaN
 * */
double constexpr sqrt(double x)
{
    return x >= 0 && x < std::numeric_limits<double>::infinity()
        ? Detail::sqrtNewtonRaphson(x, x, 0)
        : std::numeric_limits<double>::quiet_NaN();
}

}

#endif
