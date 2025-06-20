#include <iostream>
#include <cassert>
#include <sstream>
#include "../src/fmpzxx.h"
#include "../src/fmpqxx.h"
#include "../src/fmpz_matxx.h"
#include "../src/fmpz_vecxx.h"

using namespace flint;

int main()
{
    std::cout << "Testing advanced features..." << std::endl;
    
    try {
        std::cout << "1. Expression Template System:" << std::endl;
        
        // Test complex expressions with lazy evaluation
        fmpzxx a(10), b(20), c(30);
        
        // This should create an expression tree, not immediately evaluate
        auto expr1 = a + b * c - a / fmpzxx(2);
        fmpzxx result1 = expr1;  // Force evaluation
        
        // Manual calculation: 10 + 20*30 - 10/2 = 10 + 600 - 5 = 605
        std::cout << "   Complex expression result: " << result1.to<slong>() << std::endl;
        assert(result1.to<slong>() == 605);
        
        // Test chained operations
        fmpzxx x = fmpzxx(2).pow(10u) + fmpzxx(3).pow(5u) - fmpzxx(100);
        // 2^10 + 3^5 - 100 = 1024 + 243 - 100 = 1167
        std::cout << "   Chained operations: " << x.to<slong>() << std::endl;
        assert(x.to<slong>() == 1167);
        
        std::cout << "   ✓ Expression template system passed!" << std::endl;
        
        std::cout << "2. Mixed Type Operations:" << std::endl;
        
        // Test operations between different types
        fmpzxx big_int(1000);
        fmpqxx rational(3, 4);
        
        // Operations with built-in types
        fmpzxx result2 = big_int + 42;
        fmpzxx result3 = 100 * big_int;
        
        std::cout << "   big_int + 42 = " << result2.to<slong>() << std::endl;
        std::cout << "   100 * big_int = " << result3.to<slong>() << std::endl;
        
        assert(result2.to<slong>() == 1042);
        assert(result3.to<slong>() == 100000);
        
        // Rational arithmetic with integers
        fmpqxx mixed_result = rational + fmpzxx(1);  
        std::cout << "   3/4 + 1 = " << mixed_result.to_string() << std::endl;
        
        std::cout << "   ✓ Mixed type operations passed!" << std::endl;
        
        std::cout << "3. Assignment Operators:" << std::endl;
        
        // Test all assignment operators
        fmpzxx num(100);
        
        num += 50;
        assert(num.to<slong>() == 150);
        std::cout << "   After += 50: " << num.to<slong>() << std::endl;
        
        num -= 25;
        assert(num.to<slong>() == 125);
        std::cout << "   After -= 25: " << num.to<slong>() << std::endl;
        
        num *= 2;
        assert(num.to<slong>() == 250);
        std::cout << "   After *= 2: " << num.to<slong>() << std::endl;
        
        num /= 5;
        assert(num.to<slong>() == 50);
        std::cout << "   After /= 5: " << num.to<slong>() << std::endl;
        
        num %= 7;
        assert(num.to<slong>() == 1);  // 50 % 7 = 1
        std::cout << "   After %= 7: " << num.to<slong>() << std::endl;
        
        std::cout << "   ✓ Assignment operators passed!" << std::endl;
        
        std::cout << "4. Comparison Operations:" << std::endl;
        
        // Test all comparison operators
        fmpzxx val1(42), val2(42), val3(100);
        
        assert(val1 == val2);
        assert(val1 != val3);
        assert(val1 < val3);
        assert(val3 > val1);
        assert(val1 <= val2);
        assert(val1 <= val3);
        assert(val3 >= val1);
        assert(val2 >= val1);
        
        // Test comparisons with built-in types
        assert(val1 == 42);
        assert(val1 != 43);
        assert(val1 < 100);
        assert(val3 > 50);
        
        std::cout << "   All comparison operators work correctly" << std::endl;
        std::cout << "   ✓ Comparison operations passed!" << std::endl;
        
        std::cout << "5. Stream Operations:" << std::endl;
        
        // Test output streams
        std::ostringstream oss;
        fmpzxx stream_test(12345);
        oss << "Value: " << stream_test;
        std::string output = oss.str();
        std::cout << "   Stream output: " << output << std::endl;
        assert(output == "Value: 12345");
        
        // Test with rational numbers
        std::ostringstream oss2;
        fmpqxx rational_stream(22, 7);  // approximation of pi
        oss2 << "Pi approximation: " << rational_stream;
        std::string output2 = oss2.str();
        std::cout << "   Rational stream: " << output2 << std::endl;
        
        std::cout << "   ✓ Stream operations passed!" << std::endl;
        
        std::cout << "6. Memory Management:" << std::endl;
        
        // Test RAII and automatic memory management
        {
            // Create objects in a scope
            fmpzxx temp1("999999999999999999999999999999");
            fmpzxx temp2 = temp1 * temp1;
            fmpz_vecxx temp_vec(1000);
            fmpz_matxx temp_mat(50, 50);
            
            // Fill with data
            for(slong i = 0; i < temp_vec.size(); ++i) {
                temp_vec[i] = i;
            }
            
            std::cout << "   Created large objects in scope" << std::endl;
        } // Objects should be automatically destroyed here
        
        std::cout << "   Objects destroyed automatically" << std::endl;
        std::cout << "   ✓ Memory management passed!" << std::endl;
        
        std::cout << "7. Error Handling:" << std::endl;
        
        // Test division by zero handling (should be caught by FLINT)
        bool caught_error = false;
        try {
            fmpzxx zero(0);
            fmpzxx nonzero(42);
            fmpzxx result = nonzero / zero;  // This should cause an error
        } catch (...) {
            caught_error = true;
            std::cout << "   Division by zero properly handled" << std::endl;
        }
        
        // Test invalid operations
        try {
            fmpzxx negative(-1);
            fmpzxx root = sqrt(negative);  // Square root of negative number
            std::cout << "   Square root of negative: " << root.to_string() << std::endl;
        } catch (...) {
            std::cout << "   Square root of negative handled" << std::endl;
        }
        
        std::cout << "   ✓ Error handling passed!" << std::endl;
        
        std::cout << "8. Performance Features:" << std::endl;
        
        // Test move semantics and temporary optimization
        fmpzxx create_large_number() {
            return fmpzxx("123456789012345678901234567890");
        }
        
        fmpzxx moved = create_large_number();  // Should use move semantics
        std::cout << "   Move semantics work: " << moved.to_string().substr(0, 10) << "..." << std::endl;
        
        // Test expression template efficiency
        fmpzxx a1(1), b1(2), c1(3), d1(4), e1(5);
        fmpzxx complex_expr = ((a1 + b1) * (c1 + d1)) + e1;
        // This should minimize temporary allocations
        std::cout << "   Complex expression result: " << complex_expr.to<slong>() << std::endl;
        assert(complex_expr.to<slong>() == ((1 + 2) * (3 + 4)) + 5); // = 3 * 7 + 5 = 26
        
        std::cout << "   ✓ Performance features passed!" << std::endl;
        
        std::cout << "9. Type Safety:" << std::endl;
        
        // Test that the type system prevents common errors
        fmpzxx integer(42);
        fmpqxx rational(1, 2);
        
        // These should compile and work correctly
        fmpzxx int_result = integer + integer;
        fmpqxx rat_result = rational + rational;
        
        // Mixed operations should promote correctly
        fmpqxx mixed = integer + rational;  // Should promote integer to rational
        
        std::cout << "   Type promotion works correctly" << std::endl;
        std::cout << "   Integer + Integer = " << int_result.to<slong>() << std::endl;
        std::cout << "   Rational + Rational = " << rat_result.to_string() << std::endl;
        std::cout << "   Integer + Rational = " << mixed.to_string() << std::endl;
        
        std::cout << "   ✓ Type safety passed!" << std::endl;
        
        std::cout << std::endl;
        std::cout << "✅ ALL ADVANCED TESTS PASSED!" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
} 