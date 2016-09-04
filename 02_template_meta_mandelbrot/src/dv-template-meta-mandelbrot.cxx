#include <array>
#include <utility>
#include <iostream>
#include <complex>

#include "include/dv_complex.h"
#include "include/dv_abs.h"
#include "include/dv_sqrt.h"

struct Mbrot
{
  static constexpr std::size_t its = 8;
  static constexpr std::size_t res = 5;
  static constexpr std::size_t str = 4*Mbrot::res+1;
  static constexpr std::size_t pix = Mbrot::str*Mbrot::str;

  static constexpr std::size_t
  Col(const std::size_t &i) { return i % Mbrot::str; }

  static constexpr std::size_t
  Row(const std::size_t &i) { return i / Mbrot::str; }

  static constexpr std::complex<double>
  Pos(const std::size_t &i)
    {
    return std::complex<double>(
      (double(Mbrot::Col(i))-double(Mbrot::str/2))/double(Mbrot::res),
      (double(Mbrot::Row(i))-double(Mbrot::str/2))/double(Mbrot::res)
                               );
    }
  static constexpr bool
  IsInside(std::complex<double> p)
    {
    return Mbrot::is_inside_impl(p, p, Mbrot::its);
    }

  using Sequence = std::make_index_sequence<Mbrot::pix>;
  using Array = std::array<bool, Mbrot::pix>;

  template<std::size_t ...i>
  static constexpr Array
  GetArray(std::index_sequence<i...>)
    {
    return Array{{ Mbrot::IsInside(Mbrot::Pos(i))... }};
    }

  private:
  static constexpr bool
  is_inside_impl(std::complex<double> initial,
                 std::complex<double> final,
                 std::size_t it)
    {
    return (0 == it || dv::abs(final) > 2) ?
      dv::abs(final) < 2 : is_inside_impl(initial, dv::add(dv::mul(final,final), initial), it - 1);
    }
};

int main()
{

  constexpr auto s = Mbrot::Sequence();
  constexpr auto a = Mbrot::GetArray(s);

  for (unsigned int i = 0; i < Mbrot::pix; ++i)
    {
    std::cout << (a.at(i) ? " *" : "  ");
    if (Mbrot::str - 1 == i % Mbrot::str) std::cout << std::endl;
    }

  return EXIT_SUCCESS;

}
