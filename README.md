# flintxx - C++ Wrapper for FLINT

A C++ wrapper for the [FLINT](https://flintlib.org/) library, providing expression templates and object-oriented interfaces for number theory computations.

## Quick Start

### Prerequisites
- C++17 compatible compiler
- FLINT library (3.0+)
- GMP and MPFR libraries
- CMake (3.10+) or Autotools

### Build with CMake
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make test_basic test_comprehensive test_vectors_simple
```

### Build with Autoconf
```bash
./bootstrap.sh
./configure
make test/test_basic test/test_comprehensive test/test_vectors_simple
```

### Run Tests
```bash
./test/test_basic && ./test/test_comprehensive && ./test/test_vectors_simple
```

## Documentation

- **API Documentation**: `doc/source/flintxx.rst`
- **Function Reference**: `doc/source/flintxx_functions.txt`
- **Working Examples**: `test/test_*.cpp`

## Status

This is a restored version of the flintxx C++ wrapper originally from FLINT. Core functionality (fmpzxx, fmpz_vecxx, fmpz_matxx) works with current FLINT versions. Some advanced features may need API updates for newer FLINT versions.

## License

LGPL 2.1+ (same as FLINT). See `gpl-2.0.txt`.

