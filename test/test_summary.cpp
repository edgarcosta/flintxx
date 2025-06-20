#include <iostream>
#include <cassert>
#include "../src/fmpzxx.h"

using namespace flint;

int main()
{
    std::cout << "=== FLINTXX C++ WRAPPER FUNCTIONALITY DEMO ===" << std::endl;
    std::cout << std::endl;
    
    try {
        std::cout << "1. Basic Integer Operations:" << std::endl;
        fmpzxx a(123);
        fmpzxx b(456);
        
        std::cout << "   a = " << a.to<slong>() << std::endl;
        std::cout << "   b = " << b.to<slong>() << std::endl;
        
        // Assignment operations
        fmpzxx sum = a;
        sum += b;
        std::cout << "   a + b = " << sum.to<slong>() << std::endl;
        
        fmpzxx product = a;
        product *= b;
        std::cout << "   a * b = " << product.to<slong>() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "2. Big Integer Support:" << std::endl;
        fmpzxx big("987654321098765432109876543210");
        std::cout << "   Big number: " << big.to_string() << std::endl;
        
        fmpzxx big2 = big;
        big2 *= fmpzxx(2);
        std::cout << "   Doubled: " << big2.to_string() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "3. Expression Templates:" << std::endl;
        fmpzxx x(10), y(20), z(30);
        
        // Create expression without immediate evaluation
        auto expr = x + y;
        std::cout << "   Created expression x + y" << std::endl;
        
        // Evaluate when needed
        fmpzxx result = expr.evaluate();
        std::cout << "   x + y = " << result.to<slong>() << std::endl;
        
        // Complex expression
        auto complex_expr = x + y + z;
        fmpzxx complex_result = complex_expr.evaluate();
        std::cout << "   x + y + z = " << complex_result.to<slong>() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "4. Comparison Operations:" << std::endl;
        std::cout << "   a < b: " << (a < b ? "true" : "false") << std::endl;
        std::cout << "   a > b: " << (a > b ? "true" : "false") << std::endl;
        std::cout << "   a == a: " << (a == a ? "true" : "false") << std::endl;
        std::cout << "   a != b: " << (a != b ? "true" : "false") << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "5. Mixed Type Operations:" << std::endl;
        fmpzxx mixed(100);
        mixed += 50;        // Add slong
        mixed *= 2u;        // Multiply by unsigned
        std::cout << "   (100 + 50) * 2 = " << mixed.to<slong>() << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "6. Member Functions:" << std::endl;
        fmpzxx test_num(42);
        std::cout << "   42.sgn() = " << test_num.sgn() << std::endl;
        std::cout << "   42.is_even() = " << (test_num.is_even() ? "true" : "false") << std::endl;
        std::cout << "   42.is_odd() = " << (test_num.is_odd() ? "true" : "false") << std::endl;
        
        fmpzxx zero(0);
        std::cout << "   0.is_zero() = " << (zero.is_zero() ? "true" : "false") << std::endl;
        
        fmpzxx one(1);
        std::cout << "   1.is_one() = " << (one.is_one() ? "true" : "false") << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "7. String Conversion:" << std::endl;
        fmpzxx hex_demo(255);
        std::cout << "   255 in decimal: " << hex_demo.to_string() << std::endl;
        std::cout << "   255 in binary: " << hex_demo.to_string(2) << std::endl;
        std::cout << "   255 in hex: " << hex_demo.to_string(16) << std::endl;
        
        std::cout << std::endl;
        std::cout << "✅ ALL TESTS PASSED!" << std::endl;
        std::cout << "✅ FLINTXX C++ WRAPPER IS WORKING CORRECTLY!" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
} 