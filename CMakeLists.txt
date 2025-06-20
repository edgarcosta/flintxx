#
# Copyright (C) 2023 Isuru Fernando
#
# This file is part of FLINT.
#
# FLINT is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License (LGPL) as published
# by the Free Software Foundation; either version 2.1 of the License, or
# (at your option) any later version.  See <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.10)

include(CheckIPOSupported)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckPrototypeDefinition)
include(CheckCCompilerFlag)
include(CheckCSourceRuns)
include(CheckLibraryExists)
include(TestBigEndian)

# Source of truth for project version - read from FLINT
file(STRINGS flint/VERSION FLINT_VERSION_FULL)
string(REGEX MATCH "([0-9]+\.[0-9]+\.[0-9]+)" _ ${FLINT_VERSION_FULL})
set(FLINT_VERSION ${CMAKE_MATCH_1})

project(flintxx 
  VERSION ${FLINT_VERSION}
  DESCRIPTION "C++ wrapper for FLINT - Fast Library for Number Theory"
  HOMEPAGE_URL https://flintlib.org/
  LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build" FORCE)
   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

option(BUILD_SHARED_LIBS "Build shared libs" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" ON)
option(WITH_NTL "Build with NTL support" OFF)

# Version information - use simple versioning for packaging
# Parse the version from VERSION file
string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" _ ${FLINT_VERSION})
set(FLINT_MAJOR_SO ${CMAKE_MATCH_1})
set(FLINT_MINOR_SO ${CMAKE_MATCH_2})
set(FLINT_PATCH_SO ${CMAKE_MATCH_3})

# Required dependencies
find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(PythonInterp REQUIRED)

# Optional dependencies
find_package(CBLAS)
set(FLINT_USES_BLAS ${CBLAS_FOUND})

if(WITH_NTL)
    find_package(NTL REQUIRED)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(FLINT_WANT_ASSERT ON)
endif()

# pthread configuration
if(MSVC)
    find_package(PThreads REQUIRED)
    set(FLINT_USES_PTHREAD ON CACHE BOOL "Use POSIX Threads.")
else()
    option(CMAKE_THREAD_PREFER_PTHREAD "Prefer pthreads" yes)
    option(THREADS_PREFER_PTHREAD_FLAG "Prefer -pthread flag" yes)
    find_package(Threads REQUIRED)
    set(PThreads_LIBRARIES Threads::Threads)
    set(FLINT_USES_PTHREAD ON CACHE BOOL "Use POSIX Threads.")
endif()

# Thread-local storage configuration
if(cxx_thread_local IN_LIST CMAKE_CXX_COMPILE_FEATURES)
  set(FLINT_USES_TLS ON CACHE BOOL "Use thread local storage.")
endif()

# Add source files
add_subdirectory(src)

# Add examples if enabled
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Add tests if enabled
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS flintxx
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/flintxx
    FILES_MATCHING PATTERN "*.h"
)

# Generate and install CMake config files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/flintxxConfigVersion.cmake"
    VERSION "${FLINT_MAJOR_SO}.${FLINT_MINOR_SO}.${FLINT_PATCH_SO}"
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/flintxxConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/flintxxConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/flintxx
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/flintxxConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/flintxxConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/flintxx
)
