#include <array>
#include <utility>
#include <iostream>
#include <complex>
#include <stdexcept>

#include "include/dv_complex.h"
#include "include/dv_abs.h"
#include "include/dv_sqrt.h"

struct Mbrot
{
  // Number of pixels per unit space
  static constexpr std::size_t res = 16;
  // Stride (Number of pixels across the entire image in either direction)
  // 4*res+1, since we will span [-2, 2] in both the real (x) and complex (y) directions
  static constexpr std::size_t str = 4*Mbrot::res+1;
  // Total number of pixels in the image
  static constexpr std::size_t pix = Mbrot::str*Mbrot::str;
  // Return the column number given an index into the flat array.
  static constexpr std::size_t
  Col(const std::size_t &i)
    {
    if (i >= Mbrot::pix) { throw std::out_of_range("Index out of range."); }
    return i % Mbrot::str;
    }
  // Return the row number given an index into the flat array.
  static constexpr std::size_t
  Row(const std::size_t &i)
    {
    if (i >= Mbrot::pix) { throw std::out_of_range("Index out of range."); }
    return i / Mbrot::str;
    }
  // Return the position in the complex plane given an index into the flat array.
  static constexpr std::complex<double>
  Pos(const std::size_t &i)
    {
    if (i >= Mbrot::pix) { throw std::out_of_range("Index out of range."); }
    return std::complex<double>(
      (double(Mbrot::Col(i))-double(Mbrot::str/2))/double(Mbrot::res),
      (double(Mbrot::Row(i))-double(Mbrot::str/2))/double(Mbrot::res)
                               );
    }

  // Determine whether a given position in the complex plane is in the Mandelbrot set.
  static constexpr bool
  IsInSet(std::complex<double> c)
    {
    return Mbrot::is_inside_impl(c, c, Mbrot::its);
    }
  // Type of the array to be returned.
  using TArray = std::array<bool, Mbrot::pix>;

private:
  // std::integer_sequence instantiation, necessary.
  using TSequence = std::make_index_sequence<Mbrot::pix>;
  // Return the array.
  template<std::size_t ...i>
  static constexpr TArray
  get_array_impl(std::index_sequence<i...> s)
    {
    if (!std::is_same<std::index_sequence<i...>, TSequence>::value)
      { throw std::out_of_range("Incorrect sequence passed."); }
    return TArray{{ Mbrot::IsInSet(Mbrot::Pos(i))... }};
    }

public:
  // Return the array.
  static constexpr TArray
  GetArray()
    {
    constexpr auto s = Mbrot::TSequence();
    return Mbrot::get_array_impl(s);
    }

private:
  // Maximum number of iterations to determine convergence
  static constexpr std::size_t its = 8;
  // Private implementation of the recursive function determining membership in the Mandelbrot set.
  static constexpr bool
  is_inside_impl(std::complex<double> c,
                 std::complex<double> z,
                 std::size_t it)
    {
    return (0 == it || dv::abs(z) > 2) ?
      dv::abs(z) < 2 : is_inside_impl(c, dv::add(dv::mul(z,z), c), it - 1);
    }
};

int main()
{

  constexpr auto a = Mbrot::GetArray();

  for (unsigned int i = 0; i < Mbrot::pix; ++i)
    {
    std::cout << (a.at(i) ? " *" : "  ");
    if (Mbrot::str - 1 == i % Mbrot::str) std::cout << std::endl;
    }

  return EXIT_SUCCESS;

}

