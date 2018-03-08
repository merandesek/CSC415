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

    int remainder = m % block_size;
    int numTransposition = m / block_size;

    if (remainder != 0)
        additional_transpose = partition;

    int start_n = 0;
    int start_m = 0;

    int i, j;

    for (int counter = 0; i < numTransposition; counter++) {

        for (i = start_n; i < block_size, i++) {

          int tempN = A[i*m];

            if (j < block_size) {
              AT[i*m] = A[j*n];
              A[i*n] = temp;
              j++;
            }

            if (i == block_size && j == block_size) {
      i = start_n + 1;
      j = start_m + 1;
  }

counter++;

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

    std::srand(std::time(nullptr));
    for (unsigned int i = 0 ; i < n*n ; i++) {
        A[i] = std::rand();
    }

    auto start = std::chrono::high_resolution_clock::now();
    transpose(A, n, n, AT);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time of `transpose`: " << diff.count() << " sec\n";

    if (! check_transpose(A, AT, n, n)) {
        std::cout << "Incorrect !";
    }

    delete [] A;
    delete [] AT;
}
