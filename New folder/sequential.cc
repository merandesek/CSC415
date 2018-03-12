#include <unistd.h>
#include <iostream.h>
#include <iomanip>
#include <chrono>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

void sequential(int *A, int *x, int *b, int m, int n){
   
   // Going through row A 
    for (int i = 0; i < m; i++) {
        int temp = 0;
        // Going through columns in A and rows in x
        // multiplies A[ij] * x[j] = b[i]
        // A[i * j + n] accesses the i,jth element
        for (int j = 0; j < n; j++)
            temp += (A[i + j *n] * x[j]);
        b[i] = temp;
    }
}

void print_mat(int *A, int *x, int *b, int m, int n){
    
    bool is_less;
    
    if (m < n)
        is_less = true;
        
    std::cout << std::right << std::setw(7) << "A";
    std::cout << std::right << std::setw(7*n) << "x";
    std::cout << std::right << std::setw(7) << " = b" << std::endl;
    
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) 
            std::cout << std::right << std::setw(7) << A[i + j *n];
    
        if(i < n) {
            std::cout << std::right << std::setw(7) << x[i];
            std::cout << std::right << std::setw(7) << b[i] << std::endl;
        }
        else
            std::cout << std::right << std::setw(14) << b[i] << std::endl;
    }
    
    if (is_less){
        int width = 7*(n + 1);
            for(int k = m; k < n; k++)
                std::cout << std::right << std::setw(width) << x[k] << std::endl;
        }
}
     
void initial(int *A, int *x, int m, int n){

    srand (time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            A[i + j *n] = rand() % 10 + 1;
    }
        
    for (int k = 0; k < n; k++)
        x[k] = rand() % 10 + 1;
}

bool check_matrix(int *b1, int *b2, int m, int n){
	
	for(int i = 0; i < m; i++){
		if(b1[i] != b2[i])
			return false;
	}
	return true;
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
	int b1[m*1];
	//int b2[m*1];
	
	initial(A, x, m, n);

	auto start = std::chrono::high_resolution_clock::now();
	sequential(A, x, b1, m, n);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << std::fixed << std::setprecision(4);

    print_mat(A, x, b1, m, n);
	std::cout << "\n Sequential running time: " << diff.count() << " sec\t" << std::endl;

	
	// test(A, x, b2, m, n, false);
	// print_mat(A, x, b2, m, n);
		
	// check_matrix(b1, b2, m, n);
    
    return 0;
    
}

