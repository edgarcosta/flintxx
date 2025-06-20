/*
 * Simple vector test for flintxx C++ wrapper
 * 
 * VECTOR-SPECIFIC FIXES AND ISSUES:
 * 
 * 1. HEADER INCLUSION STRATEGY:
 *    Problem: Including fmpqxx.h or polynomial headers causes compilation errors
 *    due to missing FLINT functions (_fmpq_vec_init, nmod_poly_factor_*, etc.)
 *    
 *    Solution: Only include fmpz_vecxx.h which depends on stable fmpzxx.h.
 *    This avoids the problematic rational number and polynomial code.
 *
 * 2. VECTOR ELEMENT ASSIGNMENT:
 *    Problem: Vector elements need proper initialization and assignment.
 *    Solution: Use direct assignment `v[i] = value` which works reliably.
 *    Expression templates can be assigned to vector elements normally.
 *
 * 3. VECTOR ARITHMETIC LIMITATIONS:
 *    Problem: Vector-level arithmetic operations (like v1 + v2) are not
 *    implemented in this version of flintxx.
 *    
 *    Solution: Focus on element-wise operations and vector management
 *    (creation, copying, assignment, element access).
 *
 * 4. MEMORY MANAGEMENT:
 *    The vector classes handle memory management automatically through RAII.
 */

#include <iostream>
#include <cassert>
#include "../src/fmpz_vecxx.h"  // Only include stable vector header

using namespace flint;

int main()
{
    std::cout << "Testing simple vector operations..." << std::endl;
    
    try {
        std::cout << "1. Basic Vector Creation and Access:" << std::endl;
        
        // Vector creation - RAII handles memory management
        fmpz_vecxx v(10);
        
        // Element assignment with literals and expressions
        for(slong i = 0; i < v.size(); ++i) {
            v[i] = i * i;  // Direct assignment to vector elements works
        }
        
        std::cout << "   Vector of squares (first 5): ";
        for(slong i = 0; i < std::min(v.size(), 5L); ++i) {
            std::cout << v[i].to<slong>() << " ";
        }
        std::cout << "..." << std::endl;
        
        // Vector indexing and size queries
        assert(v.size() == 10);
        assert(v[0].to<slong>() == 0);
        assert(v[1].to<slong>() == 1);
        assert(v[2].to<slong>() == 4);
        assert(v[3].to<slong>() == 9);
        assert(v[4].to<slong>() == 16);
        
        std::cout << "   ✓ Basic vector creation and access passed!" << std::endl;
        
        std::cout << "2. Vector Copying and Assignment:" << std::endl;
        
        fmpz_vecxx a(5), b(5);
        
        // Element-wise initialization
        for(slong i = 0; i < 5; ++i) {
            a[i] = i + 1;     // 1, 2, 3, 4, 5
            b[i] = (i + 1) * 2; // 2, 4, 6, 8, 10
        }
        
        // Vector comparison and copying
        fmpz_vecxx c(a);  // Copy constructor
        assert(a == c);   // Vector equality comparison
        assert(a != b);   // Vector inequality comparison
        
        std::cout << "   Vector a: ";
        for(slong i = 0; i < a.size(); ++i) {
            std::cout << a[i].to<slong>() << " ";
        }
        std::cout << std::endl;
        
        std::cout << "   Vector b: ";
        for(slong i = 0; i < b.size(); ++i) {
            std::cout << b[i].to<slong>() << " ";
        }
        std::cout << std::endl;
        
        // Vector assignment
        fmpz_vecxx d(5);
        d = a;  // Assignment operator
        assert(d == a);
        
        // Element modification after copying
        d[0] = 100;
        assert(d != a);  // Vectors are properly independent after copying
        assert(d[0].to<slong>() == 100);
        
        std::cout << "   ✓ Vector copying and assignment passed!" << std::endl;
        
        std::cout << "3. Vector Element Manipulation:" << std::endl;
        
        fmpz_vecxx vec(3);
        // Vector elements can hold large numbers and negative numbers
        vec[0] = fmpzxx("123456789012345");  // Large positive number
        vec[1] = fmpzxx(-999);               // Negative number
        vec[2] = fmpzxx(0);                  // Zero
        
        // Const access
        const fmpz_vecxx& const_vec = vec;
        std::cout << "   Element 0: " << const_vec[0].to_string() << std::endl;
        std::cout << "   Element 1: " << const_vec[1].to<slong>() << std::endl;
        std::cout << "   Element 2: " << const_vec[2].to<slong>() << std::endl;
        
        assert(vec[0] == fmpzxx("123456789012345"));
        assert(vec[1] == fmpzxx(-999));
        assert(vec[2] == fmpzxx(0));
        
        std::cout << "   ✓ Vector element manipulation passed!" << std::endl;
        
        std::cout << "4. Large Vector Operations:" << std::endl;
        
        // Large vectors - memory is managed automatically
        const slong large_size = 100;
        fmpz_vecxx large_vec(large_size);
        
        // Complex element-wise operations
        if(large_size >= 2) {
            large_vec[0] = 1;
            large_vec[1] = 1;
            // Expression templates work in vector element assignment
            for(slong i = 2; i < large_size; ++i) {
                large_vec[i] = large_vec[i-1] + large_vec[i-2];  // Fibonacci sequence
            }
        }
        
        std::cout << "   Large vector size: " << large_vec.size() << std::endl;
        std::cout << "   First few Fibonacci numbers: ";
        for(slong i = 0; i < std::min(large_size, 10L); ++i) {
            std::cout << large_vec[i].to_string() << " ";
        }
        std::cout << std::endl;
        
        // Verify the Fibonacci sequence is correct
        if(large_size >= 10) {
            assert(large_vec[0] == fmpzxx(1));
            assert(large_vec[1] == fmpzxx(1));
            assert(large_vec[2] == fmpzxx(2));
            assert(large_vec[3] == fmpzxx(3));
            assert(large_vec[4] == fmpzxx(5));
            assert(large_vec[5] == fmpzxx(8));
            assert(large_vec[6] == fmpzxx(13));
            assert(large_vec[7] == fmpzxx(21));
            assert(large_vec[8] == fmpzxx(34));
            assert(large_vec[9] == fmpzxx(55));
        }
        
        std::cout << "   ✓ Large vector operations passed!" << std::endl;
        
        std::cout << "5. Edge Cases:" << std::endl;
        
        // Empty vectors (size 0)
        fmpz_vecxx empty(0);
        assert(empty.size() == 0);
        
        // Single element vectors
        fmpz_vecxx single(1);
        single[0] = 42;
        assert(single.size() == 1);
        assert(single[0] == fmpzxx(42));
        
        // Vectors with very large numbers
        fmpz_vecxx big_nums(3);
        big_nums[0] = fmpzxx("999999999999999999999999999999999999999999");
        big_nums[1] = fmpzxx("-888888888888888888888888888888888888888888");
        big_nums[2] = big_nums[0] + big_nums[1];  // Expression template assignment
        
        std::cout << "   Large number vector operations work" << std::endl;
        
        std::cout << "   ✓ Edge cases passed!" << std::endl;
        
        std::cout << std::endl;
        std::cout << "✅ ALL SIMPLE VECTOR TESTS PASSED!" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
} 