#ifndef dv_abs_h
#define dv_abs_h

#include "dv_sqrt.h"
#include <complex>

namespace dv
{

constexpr
double
abs(double v)
{
  return v < 0 ? -1 * v : v;
}

constexpr
double
abs(std::complex<double> c)
{
  return dv::sqrt(c.imag()*c.imag() + c.real()*c.real());
}

}

#endif
