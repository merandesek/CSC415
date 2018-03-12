#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cassert>
#include <immintrin.h>

void test(int *A, int *x) {

    auto *arr_A = new int[16];
    auto *arr_x = new int[8];
    
    for(int i = 0; i < 16; i++){
        arr_A[i] = i;
    }

	__m256i reg_A = _mm256_loadu_si256((__m256i*)arr_A);
    __m256i reg_x = _mm256_loadu_si256((__m256i*)arr_x + 8);

    for (int i = 0; i < 8; i++)
        std::cout << arr_x[i] << "  ";
    
    std::cout << std::endl;
    
    delete[] arr_A;
}

void loading(int *A, int *x, int m, int n){
    
	__m256i reg_A, reg_x;
	__m256 reg_mult;

    int *ptr_A = (int *) &reg_A;
    int *ptr_x = (int *) &reg_x;
    
    *A = ptr_A[0];
    *x = ptr_x[0];

    int m_iter = m / 8;
	int n_iter = n / 8;
	
	if (n_iter > 0) {

    	// loads each
        for(int i = 0, offset_A = 8; i < m_iter; i++, offset_A += 8){
            for (int j = 0, offset_x = 8; j < n_iter; j++) {
            	
            	// in form of float
            	reg_A = _mm256_loadu_si256((__m256i*)A + offset_x);
    		    reg_x = _mm256_loadu_si256((__m256i*)x + offset_x);
    		    
    		    // convert to int
    		    __m256 tempA = _mm256_cvtepi32_ps(reg_A);
    		    __m256 tempx = _mm256_cvtepi32_ps(reg_x);
    	
    		    reg_mult = _mm256_mul_ps(tempA, tempx);
    		    
            }
        }
	}
}
	

int main(int argc, char *argv[]) {
    
    srand (time(NULL));

	int m = atoi(argv[2]); // rand() % 10 + 1; 
    int n = atoi(argv[3]); // rand() % 10 + 1;
  
    std::cout << "# of Rows --> m: " << m << std::endl;
    std::cout << "# of Cols -- > n: " << n << std::endl << std::endl;

   /* 
        Note: size_N is the number of row in x, and the number of columns in A
        must be equal in order to execute
        
        General --> Matrix(rows, columns)
        
        Note: A = (m x n)     x = n x 1       b = m x 1
    
   */
	
	int A[m*n];
	int x[n*1];
	
	loading(A, x, m, n);

	test(A, x);
	
    return 0;
}