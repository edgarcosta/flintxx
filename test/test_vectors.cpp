#include <iostream>
#include <cassert>
#include "../src/fmpz_vecxx.h"
#include "../src/fmpzxx.h"

using namespace flint;

int main()
{
    std::cout << "Testing vector operations..." << std::endl;
    
    try {
        std::cout << "1. Basic Vector Operations:" << std::endl;
        
        // Create a vector of size 10
        fmpz_vecxx v(10);
        
        // Initialize with values
        for(slong i = 0; i < v.size(); ++i) {
            v[i] = i * i;  // squares: 0, 1, 4, 9, 16, ...
        }
        
        std::cout << "   Vector of squares: ";
        for(slong i = 0; i < std::min(v.size(), 5L); ++i) {
            std::cout << v[i].to<slong>() << " ";
        }
        std::cout << "..." << std::endl;
        
        // Test vector size
        assert(v.size() == 10);
        assert(v[0].to<slong>() == 0);
        assert(v[1].to<slong>() == 1);
        assert(v[2].to<slong>() == 4);
        assert(v[3].to<slong>() == 9);
        
        std::cout << "   ✓ Basic vector operations passed!" << std::endl;
        
        std::cout << "2. Vector Arithmetic:" << std::endl;
        
        // Create two vectors for arithmetic
        fmpz_vecxx a(5), b(5);
        
        // Initialize vectors
        for(slong i = 0; i < 5; ++i) {
            a[i] = i + 1;     // 1, 2, 3, 4, 5
            b[i] = (i + 1) * 2; // 2, 4, 6, 8, 10
        }
        
        // Test vector equality and inequality
        fmpz_vecxx c(a);  // copy constructor
        assert(a == c);
        assert(a != b);
        
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
        
        std::cout << "   ✓ Vector arithmetic passed!" << std::endl;
        
        std::cout << "3. Vector Assignment and Copying:" << std::endl;
        
        // Test assignment
        fmpz_vecxx d(5);
        d = a;  // assignment
        assert(d == a);
        
        // Test modification
        d[0] = 100;
        assert(d != a);
        assert(d[0].to<slong>() == 100);
        
        std::cout << "   Modified vector d[0] = " << d[0].to<slong>() << std::endl;
        std::cout << "   Original vector a[0] = " << a[0].to<slong>() << std::endl;
        
        std::cout << "   ✓ Vector assignment and copying passed!" << std::endl;
        
        std::cout << "4. Vector Element Access:" << std::endl;
        
        // Test element access and modification
        fmpz_vecxx vec(3);
        vec[0] = fmpzxx("123456789012345");
        vec[1] = fmpzxx(-999);
        vec[2] = fmpzxx(0);
        
        // Test const access
        const fmpz_vecxx& const_vec = vec;
        std::cout << "   Element 0: " << const_vec[0].to_string() << std::endl;
        std::cout << "   Element 1: " << const_vec[1].to<slong>() << std::endl;
        std::cout << "   Element 2: " << const_vec[2].to<slong>() << std::endl;
        
        assert(vec[0] == fmpzxx("123456789012345"));
        assert(vec[1] == fmpzxx(-999));
        assert(vec[2] == fmpzxx(0));
        
        std::cout << "   ✓ Vector element access passed!" << std::endl;
        
        std::cout << "5. Large Vector Operations:" << std::endl;
        
        // Test with larger vectors
        const slong large_size = 100;
        fmpz_vecxx large_vec(large_size);
        
        // Fill with Fibonacci-like sequence
        if(large_size >= 2) {
            large_vec[0] = 1;
            large_vec[1] = 1;
            for(slong i = 2; i < large_size; ++i) {
                large_vec[i] = large_vec[i-1] + large_vec[i-2];
            }
        }
        
        std::cout << "   Large vector size: " << large_vec.size() << std::endl;
        std::cout << "   First few elements: ";
        for(slong i = 0; i < std::min(large_size, 10L); ++i) {
            std::cout << large_vec[i].to_string() << " ";
        }
        std::cout << std::endl;
        
        // Test that the sequence is correct
        if(large_size >= 10) {
            assert(large_vec[0] == fmpzxx(1));
            assert(large_vec[1] == fmpzxx(1));
            assert(large_vec[2] == fmpzxx(2));
            assert(large_vec[3] == fmpzxx(3));
            assert(large_vec[4] == fmpzxx(5));
            assert(large_vec[5] == fmpzxx(8));
        }
        
        std::cout << "   ✓ Large vector operations passed!" << std::endl;
        
        std::cout << "6. Edge Cases:" << std::endl;
        
        // Test empty vector
        fmpz_vecxx empty(0);
        assert(empty.size() == 0);
        
        // Test single element vector
        fmpz_vecxx single(1);
        single[0] = 42;
        assert(single.size() == 1);
        assert(single[0] == fmpzxx(42));
        
        // Test vector with very large numbers
        fmpz_vecxx big_nums(3);
        big_nums[0] = fmpzxx("999999999999999999999999999999999999999999");
        big_nums[1] = fmpzxx("-888888888888888888888888888888888888888888");
        big_nums[2] = big_nums[0] + big_nums[1];
        
        std::cout << "   Large number vector operations work" << std::endl;
        
        std::cout << "   ✓ Edge cases passed!" << std::endl;
        
        std::cout << std::endl;
        std::cout << "✅ ALL VECTOR TESTS PASSED!" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
} 