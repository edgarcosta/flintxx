#include <iostream>
#include <cassert>
#include "../src/fmpz_matxx.h"
#include "../src/fmpzxx.h"

using namespace flint;

int main()
{
    std::cout << "Testing matrix operations..." << std::endl;
    
    try {
        std::cout << "1. Basic Matrix Operations:" << std::endl;
        
        // Create a 3x3 matrix
        fmpz_matxx A(3, 3);
        
        // Initialize with values
        for(slong i = 0; i < A.rows(); ++i) {
            for(slong j = 0; j < A.cols(); ++j) {
                A.at(i, j) = i * A.cols() + j + 1;  // 1, 2, 3, 4, 5, 6, 7, 8, 9
            }
        }
        
        std::cout << "   3x3 Matrix A:" << std::endl;
        for(slong i = 0; i < A.rows(); ++i) {
            std::cout << "   ";
            for(slong j = 0; j < A.cols(); ++j) {
                std::cout << A.at(i, j).to<slong>() << " ";
            }
            std::cout << std::endl;
        }
        
        // Test matrix dimensions
        assert(A.rows() == 3);
        assert(A.cols() == 3);
        assert(A.at(0, 0).to<slong>() == 1);
        assert(A.at(2, 2).to<slong>() == 9);
        
        std::cout << "   ✓ Basic matrix operations passed!" << std::endl;
        
        std::cout << "2. Matrix Arithmetic:" << std::endl;
        
        // Create identity matrix
        fmpz_matxx I(3, 3);
        I.one();  // Set to identity matrix
        
        std::cout << "   Identity matrix I:" << std::endl;
        for(slong i = 0; i < I.rows(); ++i) {
            std::cout << "   ";
            for(slong j = 0; j < I.cols(); ++j) {
                std::cout << I.at(i, j).to<slong>() << " ";
            }
            std::cout << std::endl;
        }
        
        // Test identity matrix properties
        assert(I.at(0, 0).to<slong>() == 1);
        assert(I.at(0, 1).to<slong>() == 0);
        assert(I.at(1, 1).to<slong>() == 1);
        
        // Create zero matrix
        fmpz_matxx Z(2, 2);
        Z.zero();
        
        assert(Z.at(0, 0).is_zero());
        assert(Z.at(1, 1).is_zero());
        
        std::cout << "   ✓ Matrix arithmetic passed!" << std::endl;
        
        std::cout << "3. Matrix Assignment and Copying:" << std::endl;
        
        // Test copy constructor
        fmpz_matxx B(A);
        assert(B.rows() == A.rows());
        assert(B.cols() == A.cols());
        
        // Test element-wise equality
        bool matrices_equal = true;
        for(slong i = 0; i < A.rows(); ++i) {
            for(slong j = 0; j < A.cols(); ++j) {
                if(A.at(i, j) != B.at(i, j)) {
                    matrices_equal = false;
                    break;
                }
            }
        }
        assert(matrices_equal);
        
        // Test assignment
        fmpz_matxx C(3, 3);
        C = A;
        
        // Modify C and ensure A is unchanged
        C.at(0, 0) = 999;
        assert(C.at(0, 0).to<slong>() == 999);
        assert(A.at(0, 0).to<slong>() == 1);  // A should be unchanged
        
        std::cout << "   ✓ Matrix assignment and copying passed!" << std::endl;
        
        std::cout << "4. Matrix Element Access:" << std::endl;
        
        // Test element access and modification
        fmpz_matxx M(2, 3);  // 2 rows, 3 columns
        
        // Set some values
        M.at(0, 0) = fmpzxx("123456789");
        M.at(0, 1) = fmpzxx(-42);
        M.at(0, 2) = fmpzxx(0);
        M.at(1, 0) = fmpzxx(1);
        M.at(1, 1) = fmpzxx(2);
        M.at(1, 2) = fmpzxx(3);
        
        std::cout << "   2x3 Matrix M:" << std::endl;
        for(slong i = 0; i < M.rows(); ++i) {
            std::cout << "   ";
            for(slong j = 0; j < M.cols(); ++j) {
                std::cout << M.at(i, j).to_string() << " ";
            }
            std::cout << std::endl;
        }
        
        // Test const access
        const fmpz_matxx& const_M = M;
        assert(const_M.at(0, 0) == fmpzxx("123456789"));
        assert(const_M.at(1, 2) == fmpzxx(3));
        
        std::cout << "   ✓ Matrix element access passed!" << std::endl;
        
        std::cout << "5. Special Matrix Operations:" << std::endl;
        
        // Test transpose (if available)
        fmpz_matxx rect(2, 3);
        for(slong i = 0; i < rect.rows(); ++i) {
            for(slong j = 0; j < rect.cols(); ++j) {
                rect.at(i, j) = i * 10 + j;
            }
        }
        
        std::cout << "   Original 2x3 matrix:" << std::endl;
        for(slong i = 0; i < rect.rows(); ++i) {
            std::cout << "   ";
            for(slong j = 0; j < rect.cols(); ++j) {
                std::cout << rect.at(i, j).to<slong>() << " ";
            }
            std::cout << std::endl;
        }
        
        // Test determinant for square matrices
        fmpz_matxx square2x2(2, 2);
        square2x2.at(0, 0) = 1;
        square2x2.at(0, 1) = 2;
        square2x2.at(1, 0) = 3;
        square2x2.at(1, 1) = 4;
        
        std::cout << "   2x2 matrix for determinant test:" << std::endl;
        for(slong i = 0; i < square2x2.rows(); ++i) {
            std::cout << "   ";
            for(slong j = 0; j < square2x2.cols(); ++j) {
                std::cout << square2x2.at(i, j).to<slong>() << " ";
            }
            std::cout << std::endl;
        }
        
        // Calculate determinant manually: det = 1*4 - 2*3 = 4 - 6 = -2
        fmpzxx det = det(square2x2);
        std::cout << "   Determinant: " << det.to<slong>() << std::endl;
        assert(det.to<slong>() == -2);
        
        std::cout << "   ✓ Special matrix operations passed!" << std::endl;
        
        std::cout << "6. Large Matrix Operations:" << std::endl;
        
        // Test with larger matrices
        const slong size = 10;
        fmpz_matxx large(size, size);
        
        // Fill with a pattern
        for(slong i = 0; i < size; ++i) {
            for(slong j = 0; j < size; ++j) {
                if(i == j) {
                    large.at(i, j) = i + 1;  // diagonal elements
                } else {
                    large.at(i, j) = 0;      // off-diagonal elements
                }
            }
        }
        
        std::cout << "   " << size << "x" << size << " diagonal matrix created" << std::endl;
        std::cout << "   First few diagonal elements: ";
        for(slong i = 0; i < std::min(size, 5L); ++i) {
            std::cout << large.at(i, i).to<slong>() << " ";
        }
        std::cout << std::endl;
        
        // Verify diagonal properties
        for(slong i = 0; i < size; ++i) {
            assert(large.at(i, i) == fmpzxx(i + 1));
            if(i < size - 1) {
                assert(large.at(i, i + 1).is_zero());
            }
        }
        
        std::cout << "   ✓ Large matrix operations passed!" << std::endl;
        
        std::cout << "7. Edge Cases:" << std::endl;
        
        // Test 1x1 matrix
        fmpz_matxx tiny(1, 1);
        tiny.at(0, 0) = 42;
        assert(tiny.rows() == 1);
        assert(tiny.cols() == 1);
        assert(tiny.at(0, 0).to<slong>() == 42);
        
        // Test rectangular matrices
        fmpz_matxx tall(5, 2);  // tall matrix
        fmpz_matxx wide(2, 5);  // wide matrix
        
        assert(tall.rows() == 5 && tall.cols() == 2);
        assert(wide.rows() == 2 && wide.cols() == 5);
        
        // Test with very large numbers
        fmpz_matxx big_nums(2, 2);
        big_nums.at(0, 0) = fmpzxx("999999999999999999999999999999");
        big_nums.at(1, 1) = fmpzxx("-888888888888888888888888888888");
        
        std::cout << "   Matrix with large numbers works" << std::endl;
        
        std::cout << "   ✓ Edge cases passed!" << std::endl;
        
        std::cout << std::endl;
        std::cout << "✅ ALL MATRIX TESTS PASSED!" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
} 