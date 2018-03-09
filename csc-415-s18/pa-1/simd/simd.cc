#include <iostream>
#include <chrono>
#include <unistd.h>
#include <immintrin.h>

void sequential(const int *A, const int *x, const int m_rows, unsigned int size_N){
   
   int b[size_N];
   
    for(int i = 0; i < size_N; i++) {
        
        for(int j = 0; j < size_N; j++) {
            int temp = (A[j+i]) * (x[j]);
            b[i] += temp;
	    
	    std::cout << "i: " << i << std::endl;
	    std::cout << "j: " << j << std::endl;
	    
	    std::cout << "A[i+j]: " << A[j] << std::endl;
	    std::cout << "x[j]: " << x[j] << std::endl;
	    std::cout << "temp: " << temp  << std::endl;
	    std::cout << "b[i]: " << b[i]  << std::endl;
	    std::cout << "\n";
		}
	}

}

int main() {
    
    int A[] = {1,2,1,5,0,3,0,4,-1,-2,0,0};
    int x[] = {1,3,2,1};
    
    int m_rows = 3;
    int size_N = 4;
    
    sequential(A,x, m_rows, size_N);
	
	
	/* unsigned int size_N = rand() % 100;

	unsigned int m_row = rand() % 100;
	unsigned int m_column = size_N;
	
	unsigned total_inN = m_row * m_column;
	
	float x[size_N];
	for (unsigned int i = 0; i < size_N ; i++) {
		x[i] = rand() % 100;
	}
	
	float A[total_inN];
	for (unsigned int j = 0; j < m_column ; j++) {
		A[j] = rand() % 100;
    } */
	
}
    
