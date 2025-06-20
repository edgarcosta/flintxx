#include <iostream>
#include <cassert>
#include "../src/fmpz_polyxx.h"

using namespace flint;

int main()
{
    std::cout << "Testing polynomial functionality..." << std::endl;
    
    try {
        // Test basic polynomial construction
        fmpz_polyxx p;
        std::cout << "Created empty polynomial: " << p.to_string() << std::endl;
        
        // Test setting coefficients
        p.set_coeff(0, fmpzxx(1));  // constant term
        p.set_coeff(1, fmpzxx(2));  // x term
        p.set_coeff(2, fmpzxx(3));  // x^2 term
        
        std::cout << "Polynomial p = " << p.to_string() << std::endl;
        
        // Test degree
        assert(p.degree() == 2);
        std::cout << "✓ Degree test passed!" << std::endl;
        
        // Test coefficient access
        assert(p.get_coeff(0).to<slong>() == 1);
        assert(p.get_coeff(1).to<slong>() == 2);
        assert(p.get_coeff(2).to<slong>() == 3);
        std::cout << "✓ Coefficient access tests passed!" << std::endl;
        
        // Test evaluation
        fmpzxx result = p.evaluate(fmpzxx(2));  // p(2) = 1 + 2*2 + 3*4 = 17
        std::cout << "p(2) = " << result.to<slong>() << std::endl;
        assert(result.to<slong>() == 17);
        std::cout << "✓ Evaluation test passed!" << std::endl;
        
        // Test string construction
        fmpz_polyxx q("3  1 2 3");  // 1 + 2*x + 3*x^2
        assert(q.degree() == 2);
        assert(q.get_coeff(0).to<slong>() == 1);
        assert(q.get_coeff(1).to<slong>() == 2);
        assert(q.get_coeff(2).to<slong>() == 3);
        std::cout << "✓ String construction test passed!" << std::endl;
        
        std::cout << "All polynomial tests passed! ✓" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
} 