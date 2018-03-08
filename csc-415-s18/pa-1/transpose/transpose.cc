#include <iostream>
#include <chrono>

// input matrix A (row-major order) of dimensions m x n
// output matrix AT (row-major order) of dimensions n x m
void transpose(const int *A, unsigned int m, unsigned int n, int *AT) {
    unsigned int i, j;

    for (i = 0 ; i < m ; i++ ) {
        for (j = 0 ; j < n ; j++ ) {
            AT[i+j*m] = A[j+i*n];
        }
    }
}

void transpose_block(const int *A, unsigned int m, unsigned int n, unsigned int block_size, int *AT) {

	// Note: was referencing http://csapp.cs.cmu.edu/2e/waside/waside-blocking.pdf for understanding of loop cache blocking
	// PDF "Using Blocking to Increase Temporal Locality"

	// Recall: m = row = i;
	// Recall: n = column = j;
	// Goal: If A is an m × n matrix then AT is an n × m matrix.

	// if the size of the array is not equal we cannot transpose it correctly
	if (m != n)
		return;

	unsigned int row, column, counter;

	bool isMultiple;

	unsigned int remainder = n % block_size;

	unsigned int iternations = n / block_size;

	int end_with_remainder = block_size * iternations;
	unsigned int additional_transpose = remainder;



	// determines if they are multiples each other
	if (remainder != 0) {

		isMultiple = false;
		printf("Matrix dimensions are not multiples of the block-size but we can still transpose...");

	}

	//	Note this works if multiple block sizes
	while(counter < iternations) {


		for (row = 0; row < end_with_remainder; row += block_size) {

			for (column = 0; column < end_with_remainder; column += block_size) {

				//	This is where it starts checking per block size;
				//	Transpose [row, column] --> [column, row]
				for (int i = row; i < row + block_size; i++) {
					for (int j = column; j < column + block_size; j++) {
						AT[i + j*n] = A[j + i*n];
					}
				}
			}

		counter++;

		}
	}

	if(counter >= iternations){

		int final_end = end_with_remainder + additional_transpose;

		for (row = end_with_remainder; row < final_end; row++ ) {
			for (column = end_with_remainder ; column < final_end ; column++ ) {
				AT[row + column*n] = A[column + row*n];
			}
		}
	}

}

bool check_transpose(const int *A, const int *AT, unsigned int m, unsigned int n) {
    unsigned int i, j;

    for ( i = 0 ; i < m ; i++ ) {
        for ( j = 0 ; j < n ; j++ ) {
            if ( AT[j+i*n] != A[i+j*m] ) {
                return false;
            }
        }
    }

    return true;
}


int main() {
    unsigned int n = 5000;

    int *A = new int [n * n];
    int *AT = new int [n * n];
	int size = 45;

    std::srand(std::time(nullptr));
    for (unsigned int i = 0 ; i < n*n ; i++) {
        A[i] = std::rand();
    }

    auto start = std::chrono::high_resolution_clock::now();
    //transpose(A, n, n, AT);
	transpose_block(A, n, n, size, AT);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time of `transpose`: " << diff.count() << " sec\n";

    if (! check_transpose(A, AT, n, n)) {
        std::cout << "Incorrect !";
    }

    delete [] A;
    delete [] AT;
}
