
cmake_minimum_required(VERSION 3.5)


message("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME} ")
message("CMAKE_HOST_UNIX: ${CMAKE_HOST_UNIX} ")
message("CMAKE_HOST_WIN32: ${CMAKE_HOST_WIN32} ")

message("UNIX: ${UNIX} ")
message("WIN32: ${WIN32} ")


project(HardWareInfo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SRC_LIST main.cpp InstructionSet.cc)

if(WIN32)
    add_executable(HardWareInfo ${SRC_LIST})
elseif(UNIX)
    add_executable(CpuId cpuid_linux.cc)
else()
    message("current platform unknown")
endif()
