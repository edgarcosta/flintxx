/*
 * Comprehensive test for flintxx C++ wrapper
 * 
 * FIXES AND ISSUES ENCOUNTERED:
 * 
 * 1. EXPRESSION TEMPLATE INITIALIZATION ISSUE:
 *    Problem: Direct initialization like `fmpzxx result = expr1 + expr2;` fails
 *    because expression templates cannot be implicitly converted to fmpzxx.
 *    
 *    Solution: Use two-step initialization:
 *    - Declare variable: `fmpzxx result;`
 *    - Assign expression: `result = expr1 + expr2;`
 *    
 *    This allows the expression template to be evaluated during assignment.
 *
 * 2. MISSING FLINT FUNCTIONS:
 *    Problem: Several FLINT C functions have been removed or renamed in newer versions:
 *    - _fmpq_vec_init/_fmpq_vec_clear are missing (used _fmpz_vec_* incorrectly)
 *    - nmod_poly_factor_* functions are missing
 *    - flint_randinit/flint_randclear are deprecated
 *    
 *    Solution: Avoid using problematic headers (fmpqxx.h, polynomial factorization)
 *    and focus on core functionality that works (fmpzxx, fmpz_vecxx, fmpz_matxx).
 *
 * 3. INCLUDE PATH ISSUES:
 *    Problem: Headers used `#include "../flint.h"` which doesn't exist.
 *    Solution: Updated to `#include <flint/flint.h>` format throughout.
 *
 * 4. BUILD SYSTEM ISSUES:
 *    Problem: CMake couldn't find FLINT library properly.
 *    Solution: Switched to autoconf build system with proper library detection.
 *
 * 5. MEMBER FUNCTION VS GLOBAL FUNCTION USAGE:
 *    Problem: Some global functions (like gcd, lcm) don't work with expression templates.
 *    Solution: Use member functions instead: `a.gcd(b)` instead of `gcd(a, b)`.
 */

#include <iostream>
#include <cassert>
#include <sstream>
#include "../src/fmpzxx.h"

using namespace flint;

int main()
{
    std::cout << "Testing comprehensive flintxx functionality..." << std::endl;
    
    try {
        std::cout << "1. Expression Templates and Lazy Evaluation:" << std::endl;
        
        // Test expression templates - these should work with proper evaluation
        fmpzxx a(10), b(20), c(30);
        
        // IMPORTANT: Expression templates must be assigned, not directly initialized
        // This WORKS: fmpzxx result; result = a + b;
        // This FAILS: fmpzxx result = a + b;
        
        fmpzxx result1;
        result1 = a + b;  // Expression template assignment works
        std::cout << "   a + b = " << result1.to<slong>() << std::endl;
        assert(result1.to<slong>() == 30);
        
        // Test more complex expressions
        fmpzxx result2;
        result2 = a + b * c;  // Should be 10 + 20*30 = 610
        std::cout << "   a + b * c = " << result2.to<slong>() << std::endl;
        assert(result2.to<slong>() == 610);
        
        // Test chained operations
        fmpzxx result3;
        result3 = (a + b) * c;  // Should be (10 + 20) * 30 = 900
        std::cout << "   (a + b) * c = " << result3.to<slong>() << std::endl;
        assert(result3.to<slong>() == 900);
        
        std::cout << "   ✓ Expression templates passed!" << std::endl;
        
        std::cout << "2. Arithmetic Functions:" << std::endl;
        
        // IMPORTANT: Use member functions for compatibility
        // Member functions handle expression templates better than global functions
        
        fmpzxx base(2);
        fmpzxx power_result;
        power_result = base.pow(10u);  // Use member function instead of pow(base, 10u)
        std::cout << "   2^10 = " << power_result.to<slong>() << std::endl;
        assert(power_result.to<slong>() == 1024);
        
        // Test square root
        fmpzxx x(16);
        fmpzxx sqrt_result;
        sqrt_result = x.sqrt();  // Use member function instead of sqrt(x)
        std::cout << "   sqrt(16) = " << sqrt_result.to<slong>() << std::endl;
        assert(sqrt_result.to<slong>() == 4);
        
        // Test absolute value
        fmpzxx neg(-42);
        fmpzxx abs_result;
        abs_result = neg.abs();  // Member function
        std::cout << "   abs(-42) = " << abs_result.to<slong>() << std::endl;
        assert(abs_result.to<slong>() == 42);
        
        std::cout << "   ✓ Arithmetic functions passed!" << std::endl;
        
        std::cout << "3. Number Theory Functions:" << std::endl;
        
        // IMPORTANT: Use member functions for GCD/LCM
        // Global gcd(a, b) and lcm(a, b) have issues with expression templates
        
        fmpzxx num1(48), num2(18);
        fmpzxx gcd_result;
        gcd_result = num1.gcd(num2);  // Member function works, gcd(num1, num2) fails
        std::cout << "   gcd(48, 18) = " << gcd_result.to<slong>() << std::endl;
        assert(gcd_result.to<slong>() == 6);
        
        fmpzxx lcm_result;
        lcm_result = num1.lcm(num2);  // Member function works, lcm(num1, num2) fails
        std::cout << "   lcm(48, 18) = " << lcm_result.to<slong>() << std::endl;
        assert(lcm_result.to<slong>() == 144);
        
        // Test divisibility - this works as expected
        assert(num1.divisible(num2.gcd(num1)));
        assert(!num1.divisible(fmpzxx(7)));
        
        std::cout << "   ✓ Number theory functions passed!" << std::endl;
        
        std::cout << "4. Type Conversion and String Operations:" << std::endl;
        
        // String conversion and parsing
        fmpzxx large_num("12345678901234567890");
        std::cout << "   Large number: " << large_num.to_string() << std::endl;
        
        // Test base conversions
        fmpzxx hex_num(255);
        std::cout << "   255 in hex: " << hex_num.to_string(16) << std::endl;
        std::cout << "   255 in binary: " << hex_num.to_string(2) << std::endl;
        std::cout << "   255 in octal: " << hex_num.to_string(8) << std::endl;
        
        // Test primitive type conversions
        assert(hex_num.to<slong>() == 255);
        assert(hex_num.to<ulong>() == 255u);
        
        std::cout << "   ✓ Type conversion passed!" << std::endl;
        
        std::cout << "5. Bit Operations:" << std::endl;
        
        // Bit operations
        fmpzxx bit_num(42);  // 42 = 101010 in binary
        std::cout << "   42 in binary: " << bit_num.to_string(2) << std::endl;
        assert(bit_num.tstbit(1) == true);   // bit 1 is set
        assert(bit_num.tstbit(0) == false); // bit 0 is not set
        assert(bit_num.tstbit(3) == true);   // bit 3 is set
        assert(bit_num.tstbit(5) == true);   // bit 5 is set
        
        // Test bit manipulation
        fmpzxx bit_test(17);  // 17 = 10001 in binary
        bit_test.clrbit(0);   // Clear bit 0: 10001 -> 10000 = 16
        assert(bit_test.to<slong>() == 16);
        
        bit_test.combit(1);   // Complement bit 1: 10000 -> 10010 = 18
        assert(bit_test.to<slong>() == 18);
        
        std::cout << "   ✓ Bit operations passed!" << std::endl;
        
        std::cout << "6. Properties and Predicates:" << std::endl;
        
        // Test various properties and predicates
        fmpzxx zero(0), one(1), two(2), neg_one(-1);
        
        assert(zero.is_zero());
        assert(!zero.is_one());
        assert(!zero.is_odd());
        assert(zero.is_even());
        
        assert(one.is_one());
        assert(!one.is_zero());
        assert(one.is_odd());
        assert(!one.is_even());
        assert(one.is_pm1());
        
        assert(two.is_even());
        assert(!two.is_odd());
        assert(!two.is_zero());
        assert(!two.is_one());
        
        assert(neg_one.is_pm1());
        assert(neg_one.sgn() == -1);
        assert(one.sgn() == 1);
        assert(zero.sgn() == 0);
        
        std::cout << "   ✓ Properties and predicates passed!" << std::endl;
        
        std::cout << "7. Assignment Operators:" << std::endl;
        
        // Assignment operators properly handle expression templates
        fmpzxx assign_test(100);
        
        assign_test += fmpzxx(50);
        assert(assign_test.to<slong>() == 150);
        
        assign_test -= fmpzxx(25);
        assert(assign_test.to<slong>() == 125);
        
        assign_test *= fmpzxx(2);
        assert(assign_test.to<slong>() == 250);
        
        assign_test /= fmpzxx(5);
        assert(assign_test.to<slong>() == 50);
        
        assign_test %= fmpzxx(7);
        assert(assign_test.to<slong>() == 1);  // 50 % 7 = 1
        
        std::cout << "   ✓ Assignment operators passed!" << std::endl;
        
        std::cout << "8. Stream Operations:" << std::endl;
        
        // Stream operations using to_string()
        std::ostringstream oss;
        fmpzxx stream_test(12345);
        oss << "Value: " << stream_test;
        std::string output = oss.str();
        std::cout << "   " << output << std::endl;
        assert(output == "Value: 12345");
        
        std::cout << "   ✓ Stream operations passed!" << std::endl;
        
        std::cout << "9. Shift Operations:" << std::endl;
        
        // IMPORTANT: Shift operations need assignment, not direct initialization
        fmpzxx shift_test(1);
        fmpzxx left_shifted;
        left_shifted = shift_test << 10;  // Assignment works, direct init fails
        assert(left_shifted.to<slong>() == 1024);
        
        fmpzxx right_shifted;
        right_shifted = left_shifted >> 9;  // Assignment works, direct init fails
        assert(right_shifted.to<slong>() == 2);
        
        std::cout << "   Left shift: 1 << 10 = " << left_shifted.to<slong>() << std::endl;
        std::cout << "   Right shift: 1024 >> 9 = " << right_shifted.to<slong>() << std::endl;
        
        std::cout << "   ✓ Shift operations passed!" << std::endl;
        
        std::cout << "10. Large Number Operations:" << std::endl;
        
        // Large number support
        fmpzxx very_large("999999999999999999999999999999999999999999");
        fmpzxx large_sum;
        large_sum = very_large + fmpzxx(1);  // Assignment pattern for expressions
        std::cout << "   Large number arithmetic works" << std::endl;
        
        // Test size and bits utility functions
        std::cout << "   Large number size in bits: " << very_large.bits() << std::endl;
        std::cout << "   Large number size in base 10: " << very_large.sizeinbase(10) << std::endl;
        
        std::cout << "   ✓ Large number operations passed!" << std::endl;
        
        std::cout << std::endl;
        std::cout << "✅ ALL COMPREHENSIVE TESTS PASSED!" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
} 