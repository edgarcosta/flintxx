#include <iostream>
#include <cassert>
#include "../src/fmpzxx.h"

using namespace flint;

int main()
{
    std::cout << "Testing expression template system..." << std::endl;
    
    try {
        // Test that expressions can be evaluated
        fmpzxx a(10);
        fmpzxx b(20);
        fmpzxx c(30);
        
        // Test simple expression evaluation
        auto expr1 = a + b;
        fmpzxx result1 = expr1.evaluate();
        std::cout << "10 + 20 = " << result1.to<slong>() << std::endl;
        assert(result1.to<slong>() == 30);
        
        // Test chained expressions with assignment operators
        fmpzxx x(5);
        x += fmpzxx(3);
        assert(x.to<slong>() == 8);
        
        x *= fmpzxx(2);
        assert(x.to<slong>() == 16);
        
        x /= fmpzxx(4);
        assert(x.to<slong>() == 4);
        
        std::cout << "✓ Assignment expression tests passed!" << std::endl;
        
        // Test comparison operations
        assert(a < b);
        assert(b > a);
        assert(a != b);
        assert(a == fmpzxx(10));
        
        std::cout << "✓ Comparison expression tests passed!" << std::endl;
        
        // Test that expressions are lazy (don't evaluate until needed)
        auto lazy_expr = a + b + c;  // This creates an expression tree
        fmpzxx result2 = lazy_expr.evaluate();  // This triggers evaluation
        std::cout << "10 + 20 + 30 = " << result2.to<slong>() << std::endl;
        assert(result2.to<slong>() == 60);
        
        std::cout << "✓ Lazy evaluation tests passed!" << std::endl;
        
        // Test with built-in types
        fmpzxx d(5);
        d += 10;  // Adding slong
        assert(d.to<slong>() == 15);
        
        d *= 2u;  // Multiplying by unsigned
        assert(d.to<slong>() == 30);
        
        std::cout << "✓ Built-in type interaction tests passed!" << std::endl;
        
        std::cout << "All expression tests passed! ✓" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
} 