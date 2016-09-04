#ifndef dv_complex_h
#define dv_complex_h

#include <complex>

namespace dv
{

constexpr
std::complex<double>
mul(std::complex<double> c1, std::complex<double> c2)
{
  return std::complex<double>(c1.real() * c2.real() - c1.imag() * c2.imag(),
                              c1.real() * c2.imag() + c1.imag() * c2.real());
}

constexpr
std::complex<double>
add(std::complex<double> c1, std::complex<double> c2)
{
  return std::complex<double>(c1.real() + c2.real(),
                              c1.imag() + c2.imag());
}

}

#endif
