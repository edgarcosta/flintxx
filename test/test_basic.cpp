/*
 * Basic test for flintxx C++ wrapper
 * 
 * BASIC FUNCTIONALITY:
 * 
 * 1. CORE fmpzxx OPERATIONS:
 *    - Construction from integers, strings
 *    - Basic arithmetic (+, -, *, /, %)
 *    - Assignment operators (+=, -=, *=, /=, %=)
 *    - Comparison operators (<, >, ==, !=, <=, >=)
 *    - String conversion and output
 *    - Member functions (sgn, is_odd, is_even, etc.)
 *
 * 2. WHAT TO AVOID:
 *    - Direct initialization from expression templates
 *    - Global functions that don't work with expression templates
 *    - Headers with missing FLINT functions (fmpqxx.h, polynomial factorization)
 *
 * 3. BEST PRACTICES:
 *    - Use assignment instead of direct initialization for expressions
 *    - Prefer member functions over global functions
 *    - Stick to core integer functionality
 */

#include <iostream>
#include <cassert>
#include <string>
#include "../src/fmpzxx.h"  // Core integer functionality

using namespace flint;

int main()
{
    std::cout << "Testing basic flintxx functionality..." << std::endl;
    
    try {
        // Basic construction
        fmpzxx a(42);
        fmpzxx b(17);
        
        std::cout << "Created fmpzxx a = " << a.to<slong>() << std::endl;
        std::cout << "Created fmpzxx b = " << b.to<slong>() << std::endl;
        
        // Comparison operators
        assert(a > b);
        assert(b < a);
        assert(a != b);
        assert(a == fmpzxx(42));
        assert(b == fmpzxx(17));
        
        // Comparisons with built-in types
        assert(a == 42);
        assert(b == 17);
        assert(a > 30);
        assert(b < 20);
        
        std::cout << "✓ Comparison tests passed!" << std::endl;
        
        // Assignment arithmetic operators
        fmpzxx c(10);
        
        c += fmpzxx(5);  // Assignment operators handle expression evaluation
        assert(c == 15);
        
        c -= fmpzxx(3);
        assert(c == 12);
        
        c *= fmpzxx(2);
        assert(c == 24);
        
        c /= fmpzxx(4);
        assert(c == 6);
        
        c %= fmpzxx(4);
        assert(c == 2);
        
        std::cout << "✓ Assignment arithmetic tests passed!" << std::endl;
        
        // String conversion and large numbers
        fmpzxx big_number("123456789012345678901234567890");
        std::cout << "Big number: " << big_number.to_string() << std::endl;
        
        // String parsing and output
        assert(big_number.to_string() == "123456789012345678901234567890");
        
        std::cout << "✓ String conversion tests passed!" << std::endl;
        
        // Member functions
        fmpzxx zero(0);
        fmpzxx one(1);
        fmpzxx negative(-5);
        fmpzxx even(8);
        fmpzxx odd(9);
        
        // Test predicates
        assert(zero.is_zero());
        assert(one.is_one());
        assert(!zero.is_one());
        assert(!one.is_zero());
        
        assert(negative.sgn() == -1);
        assert(one.sgn() == 1);
        assert(zero.sgn() == 0);
        
        assert(even.is_even());
        assert(!even.is_odd());
        assert(odd.is_odd());
        assert(!odd.is_even());
        
        std::cout << "✓ Member function tests passed!" << std::endl;
        
        std::cout << "All basic tests passed! ✓" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
} 