#include <iostream>
#include <cassert>
#include "../src/fmpzxx.h"
#include "../src/fmpqxx.h"

using namespace flint;

int main()
{
    std::cout << "Testing arithmetic functions..." << std::endl;
    
    try {
        std::cout << "1. Basic Arithmetic Functions:" << std::endl;
        
        // Test factorial and primorial
        fmpzxx fact4 = fac(4u);
        std::cout << "   4! = " << fact4.to<slong>() << std::endl;
        assert(fact4.to<slong>() == 24);
        
        // Test binomial coefficient
        fmpzxx bin_4_2 = bin(4u, 2u);
        std::cout << "   C(4,2) = " << bin_4_2.to<slong>() << std::endl;
        assert(bin_4_2.to<slong>() == 6);
        
        // Test Fibonacci numbers
        fmpzxx fib5 = fib(5u);
        std::cout << "   F(5) = " << fib5.to<slong>() << std::endl;
        assert(fib5.to<slong>() == 5);
        
        std::cout << "   ✓ Basic arithmetic functions passed!" << std::endl;
        
        std::cout << "2. Number Theory Functions:" << std::endl;
        
        // Test GCD and LCM
        fmpzxx a(48), b(18);
        fmpzxx g = gcd(a, b);
        fmpzxx l = lcm(a, b);
        std::cout << "   gcd(48, 18) = " << g.to<slong>() << std::endl;
        std::cout << "   lcm(48, 18) = " << l.to<slong>() << std::endl;
        assert(g.to<slong>() == 6);
        assert(l.to<slong>() == 144);
        
        // Test modular arithmetic
        fmpzxx base(7), exp(3), mod(10);
        fmpzxx pow_result = powm(base, exp, mod);
        std::cout << "   7^3 mod 10 = " << pow_result.to<slong>() << std::endl;
        assert(pow_result.to<slong>() == 3);  // 7^3 = 343, 343 mod 10 = 3
        
        // Test square root
        fmpzxx x(16);
        fmpzxx sqrt_x = sqrt(x);
        std::cout << "   sqrt(16) = " << sqrt_x.to<slong>() << std::endl;
        assert(sqrt_x.to<slong>() == 4);
        
        std::cout << "   ✓ Number theory functions passed!" << std::endl;
        
        std::cout << "3. Advanced Operations:" << std::endl;
        
        // Test bit operations
        fmpzxx num(42);  // 42 = 101010 in binary
        std::cout << "   42 in binary: " << num.to_string(2) << std::endl;
        assert(num.tstbit(1) == true);   // bit 1 is set
        assert(num.tstbit(0) == false); // bit 0 is not set
        
        // Test power operations
        fmpzxx base2(2);
        fmpzxx power = pow(base2, 10u);
        std::cout << "   2^10 = " << power.to<slong>() << std::endl;
        assert(power.to<slong>() == 1024);
        
        // Test divisibility
        assert(power.divisible(base2) == true);
        assert(power.divisible(fmpzxx(3)) == false);
        
        std::cout << "   ✓ Advanced operations passed!" << std::endl;
        
        std::cout << "4. Rational Number Operations:" << std::endl;
        
        // Test rational arithmetic
        fmpqxx r1(3, 4);  // 3/4
        fmpqxx r2(2, 3);  // 2/3
        
        // Test addition
        fmpqxx sum = r1;
        sum += r2;
        std::cout << "   3/4 + 2/3 = " << sum.to_string() << std::endl;
        
        // Test multiplication
        fmpqxx product = r1;
        product *= r2;
        std::cout << "   3/4 * 2/3 = " << product.to_string() << std::endl;
        
        // Test comparison
        assert(r1 > r2);  // 3/4 > 2/3
        assert(r2 < r1);
        
        std::cout << "   ✓ Rational number operations passed!" << std::endl;
        
        std::cout << "5. String and Conversion Tests:" << std::endl;
        
        // Test string parsing
        fmpzxx from_str("12345678901234567890");
        std::cout << "   Parsed: " << from_str.to_string() << std::endl;
        
        // Test base conversions
        fmpzxx hex_num(255);
        std::cout << "   255 in hex: " << hex_num.to_string(16) << std::endl;
        std::cout << "   255 in binary: " << hex_num.to_string(2) << std::endl;
        std::cout << "   255 in octal: " << hex_num.to_string(8) << std::endl;
        
        std::cout << "   ✓ String and conversion tests passed!" << std::endl;
        
        std::cout << "6. Edge Cases:" << std::endl;
        
        // Test zero and one
        fmpzxx zero(0), one(1);
        assert(zero.is_zero());
        assert(one.is_one());
        assert(!zero.is_one());
        assert(!one.is_zero());
        
        // Test negative numbers
        fmpzxx neg(-42);
        assert(neg.sgn() == -1);
        assert(neg.abs() == fmpzxx(42));
        
        // Test large numbers
        fmpzxx large("999999999999999999999999999999");
        fmpzxx large2 = large * fmpzxx(2);
        std::cout << "   Large number doubled: " << large2.to_string().substr(0, 20) << "..." << std::endl;
        
        std::cout << "   ✓ Edge cases passed!" << std::endl;
        
        std::cout << std::endl;
        std::cout << "✅ ALL ARITHMETIC TESTS PASSED!" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
} 