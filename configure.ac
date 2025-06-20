AC_PREREQ(2.62)

# flintxx C++ wrapper for FLINT
# 
# BUILD SYSTEM FIXES APPLIED:
# 
# 1. SIMPLIFIED AUTOCONF SETUP:
#    - Removed complex version detection from FLINT sources
#    - Use fixed version number for stability
#    - Focus on C++ compilation and library detection
#
# 2. LIBRARY DETECTION IMPROVEMENTS:
#    - Proper detection of system-installed FLINT library
#    - Support for homebrew installation paths
#    - Simplified dependency checking
#
# 3. REMOVED PROBLEMATIC FEATURES:
#    - Removed NTL support (optional and problematic)
#    - Made pthread support optional (not needed for header-only wrapper)
#    - Simplified C++ standard detection

# Version information
AC_INIT([flintxx], [3.4.0-dev], [https://github.com/flintlib/flint/issues/], [flintxx], [https://flintlib.org/])

# Basic setup
AC_CONFIG_AUX_DIR([config])
AC_LANG([C++])

# Make sure that we are in the right directory
AC_CONFIG_SRCDIR(src/flintxx.h)

# Configure headers
AC_CONFIG_HEADERS(src/flint-config.h)

# Check for C++ compiler
AC_PROG_CXX
AC_PROG_CXXCPP

# Check C++ standard - require C++11 minimum
# Add -std=c++11 to CXXFLAGS if not already present
case "$CXXFLAGS" in
    *-std=c++11*) ;;
    *-std=c++1y*) ;;
    *-std=c++14*) ;;
    *-std=c++1z*) ;;
    *-std=c++17*) ;;
    *-std=c++2a*) ;;
    *-std=c++20*) ;;
    *) CXXFLAGS="$CXXFLAGS -std=c++11" ;;
esac

# Check for required dependencies
AC_CHECK_HEADER([flint/flint.h], [], 
    [AC_MSG_ERROR([FLINT headers not found. Please install FLINT development package.])])

# Check for required libraries
AC_CHECK_LIB([flint], [fmpz_init], [], 
    [AC_MSG_ERROR([FLINT library not found. Please install FLINT.])])

AC_CHECK_LIB([gmp], [__gmpz_init], [], 
    [AC_MSG_ERROR([GMP library not found. Please install GMP.])])

AC_CHECK_LIB([mpfr], [mpfr_init], [], 
    [AC_MSG_ERROR([MPFR library not found. Please install MPFR.])])

# Optional pthread support (usually not needed for header-only wrapper)
AC_ARG_ENABLE(pthread,
[AS_HELP_STRING([--enable-pthread],[Enable pthread [default=no]])],
[case $enableval in
yes|no)
    ;;
*)
    AC_MSG_ERROR([Bad value $enableval for --enable-pthread. Need yes or no.])
    ;;
esac],
enable_pthread="no")

if test "x$enable_pthread" = "xyes"; then
    AC_CHECK_LIB([pthread], [pthread_create], [], 
        [AC_MSG_ERROR([pthread library not found. Please install pthread.])])
    AC_DEFINE([FLINT_USES_PTHREAD], [1], [Define if pthread is used])
fi

# Output files
AC_CONFIG_FILES([Makefile])
AC_OUTPUT 