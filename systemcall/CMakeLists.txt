
cmake_minimum_required(VERSION 3.15)
project(msvctest)
set(APPNAME "msvctest")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 17)


add_executable(${APPNAME} main.cc)

set_property(TARGET ${APPNAME} PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(${APPNAME} Ws2_32.lib)