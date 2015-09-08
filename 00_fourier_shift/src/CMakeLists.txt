cmake_minimum_required(VERSION 2.8.12)
 
project(dv-fourier-shift)

set(ITK_DIR "~/Developer/ITK/bin")
set(CMAKE_CXX_FLAGS "-std=c++11" CACHE STRING "cxx compiler flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Werror" CACHE STRING "cxx debug compiler flags" FORCE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "build type" FORCE)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(dv-fourier-shift dv-fourier-shift.cxx)
target_link_libraries(dv-fourier-shift ${ITK_LIBRARIES})
