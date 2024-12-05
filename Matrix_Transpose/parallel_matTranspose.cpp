#include <iostream>
#include <thread>

class matrix {
public:
    int *mat;
    int rows;
    int cols;

    matrix(int row, int col) {
        this->rows = row;
        this->cols = col;
        this->mat = new int[row * col];
    }
};


void Transpose_Col(matrix *A, int i, int j_low, int j_high) {
    if (j_low == j_high) {
        int temp = A->mat[j_low*A->cols + i];
        A->mat[j_low*A->cols + i] = A->mat[i*A->cols + j_low];
        A->mat[i*A->cols + j_low] = temp;
    }
    else {
        int j_mid = (j_low + j_high) / 2;
        std::thread t1(Transpose_Col, A, i, j_low, j_mid);
        Transpose_Col(A, i, j_mid+1, j_high);
        t1.join();
    }
}

void Transpose_Row(matrix *A, int i_low, int i_high) {
    if (i_low == i_high)
        Transpose_Col(A, i_low, i_low + 1, A->rows-1);
    else {
        int i_mid = (i_low + i_high) / 2;
        std::thread t1(Transpose_Row, A, i_low, i_mid);
        Transpose_Row(A, i_mid + 1, i_high);
        t1.join();
    }
}

void Transpose(matrix *A) {
    int n = A->rows;
    if (n > 1)
        Transpose_Row(A, 0, n - 2);
}

int main() {
    int m = 13; int n = 13;    /*A should be a square matrix with m = n >= 1*/
    matrix A = matrix(m, n);
    for (int i = 0; i < (A.rows * A.cols); ++i) 
        A.mat[i] = i;


    Transpose(&A);

    for (int i = 0; i < (A.rows * A.cols); ++i) 
      std::cout << A.mat[i] << ' ';
    std::cout << '\n';
    delete [] A.mat; 

    return 0;
}