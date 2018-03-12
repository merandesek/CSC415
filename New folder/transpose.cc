#include <iostream>
#include <chrono>

// input matrix A (row-major order) of dimensions m x n
// output matrix AT (row-major order) of dimensions n x m
void transpose(const int *A, int m, int n, int *AT) {
    int i, j;

    for (i = 0 ; i < m ; i++ ) {
        for (j = 0 ; j < n ; j++ ) {
            AT[i+j*m] = A[j+i*n];
        }
    }
}

void transpose_block(const int *A, int m, int n, int block_size, int *AT) {

	// Note: was referencing http://csapp.cs.cmu.edu/2e/waside/waside-blocking.pdf for understanding of loop cache blocking
	// PDF "Using Blocking to Increase Temporal Locality"

	// Recall: m = row = i;
	// Recall: n = column = j;
	// Goal: If A is an m × n matrix then AT is an n × m matrix.

	// if the size of the array is not equal we cannot transpose it correctly

	int row = 0;
	int column;
	int iternations = n / block_size;
	int end_with_remainder = block_size * iternations;

	//	Note this works if multiple block sizes
    if(row < end_with_remainder){
		for (row = 0; row < end_with_remainder; row += block_size) {
			for (column = 0; column < end_with_remainder; column += block_size) {
				//	This is where it starts checking per block size;
				//	Transpose [row, column] --> [column, row]
				for (int i = row; i < row + block_size; i++) {
					for (int j = column; j < column + block_size; j++) {
						AT[i + j*n] = A[j + i*m];
					}
				}
			}
	    }
    }

	// If there are not multiples
    else {
        for (row = 0 ; row < m ; row++) {
            for (column = 0 ; column < n  ; column++ )
                AT[row + column*n] = A[column + row*m];
    	}
	}
}

bool check_transpose(const int *A, const int *AT, int m, int n) {
    int i, j;

    for ( i = 0 ; i < m ; i++ ) {
        for ( j = 0 ; j < n ; j++ ) {
            if ( AT[j+i*n] != A[i+j*m] )
                return false;
        }
    }
    return true;
}

void testTransposeBlock(int n, int *A, int *AT) {

    int test_case[] = {2, 50, 100, 250, 500, 1000, 2500};
    int size = sizeof(test_case)/sizeof(test_case[0]);

    for (int i = 0; i < size; i++) {

        int block_size = test_case[i];
        std::cout << "Block Size: " << block_size << " x " << block_size << "\n";

    	int remainder = n % block_size;

    	// determines if they are multiples each other
    	if (remainder != 0) {
    		std::cout << "Matrix dimensions are not multiples of the ";
    		std::cout << "block-size but we can still block transpose...\n";

    	}

        auto start = std::chrono::high_resolution_clock::now();
    	transpose_block(A, n, n, block_size, AT);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Time of Transpose Block: " << diff.count() << " sec\n\n";

    }
}

int main(int argc, char *argv[]) {

    int n = atoi(argv[2]);

    int *A = new int [n * n];
    int *AT = new int [n * n];

    std::cout << "Matrix Size: " << n << " x " << n << "\n\n";

    auto start = std::chrono::high_resolution_clock::now();
    transpose(A, n, n, AT);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time of `transpose`: " << diff.count() << " sec\n";

    testTransposeBlock(n, A, AT);

    if (! check_transpose(A, AT, n, n)) {
        std::cout << "Incorrect!";
    }

    delete [] A;
    delete [] AT;
}

