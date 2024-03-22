# CMakeList.txt : CMake project for bind-tut, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.27)

#TODO: is there a better way other than env vars?
set(ENV{pybind11_DIR} "C:\\\\Users\\bruce\\.pyenv\\pyenv-win\\versions\\3.9.13\\Lib\\site-packages\\pybind11\\share\\cmake\\pybind11")

if (DEFINED ENV{pybind11_DIR})
  message(STATUS "Found env var: pybind11_DIR")
else()
  message(FATAL_ERROR "'pybind11_DIR' must be set in environment variables.")
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("bind11-tut")

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

# pybind11 method:
pybind11_add_module(example "bind-tut.cpp")
