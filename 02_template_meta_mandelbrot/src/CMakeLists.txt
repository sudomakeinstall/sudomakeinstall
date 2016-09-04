# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 2.4)

# This project is designed to be built outside the Insight source tree.
project(dv-template-meta-mandelbrot)

#set(CMAKE_CXX_FLAGS "-std=c++14 -ftemplate-depth=1024 -fconstexpr-depth=1024")
set(CMAKE_CXX_FLAGS "-std=c++14")

add_executable(dv-template-meta-mandelbrot dv-template-meta-mandelbrot.cxx )

