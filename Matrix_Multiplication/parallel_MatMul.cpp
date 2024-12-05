#include <iostream>
#include <thread>
#include <atomic>

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

void Mat_Mul_Dot_Prod(matrix *A, matrix *B, int i, int j, int k_low, int k_high, std::atomic<int> *ret) {
    if (k_low == k_high) 
        ret->fetch_add(A->mat[i*A->cols + k_low] * B->mat[k_low*B->cols + j]);
    else {
        int k_mid = (k_low + k_high) / 2;
        std::thread t1(Mat_Mul_Dot_Prod, A, B, i, j, k_low, k_mid, ret);
        Mat_Mul_Dot_Prod(A, B, i, j, k_mid+1, k_high, ret);
        t1.join();
    }
}


void Mat_Mul_Col_Loop(matrix *A, matrix *B, int i, int j_low, int j_high, matrix *C) {
    if (j_low == j_high) {
        std::atomic<int> ret(0);
        Mat_Mul_Dot_Prod(A, B, i, j_low, 0, A->cols-1, &ret);
        C->mat[i*C->cols + j_low] = ret.load();
    }
    else {
        int j_mid = (j_low + j_high) / 2;
        std::thread t1(Mat_Mul_Col_Loop, A, B, i, j_low, j_mid, C);
        Mat_Mul_Col_Loop(A, B, i, j_mid + 1, j_high, C);
        t1.join();
    }
}

void Mat_Mul_Row_Loop(matrix *A, matrix *B, int i_low, int i_high, matrix *C) {
    if (i_low == i_high) 
        Mat_Mul_Col_Loop(A, B, i_low, 0, B->cols - 1, C);
    else {
        int i_mid = (i_low + i_high) / 2;
        std::thread t1(Mat_Mul_Row_Loop, A, B, i_low, i_mid, C);
        Mat_Mul_Row_Loop(A, B, i_mid + 1, i_high, C);
        t1.join();
    }
}

matrix* Mat_Mul(matrix *A, matrix *B) {
    int m = A->rows;
    int n = B->cols;
    matrix *C = new matrix(m, n);
    Mat_Mul_Row_Loop(A, B, 0, m-1, C);
    return C;
}

int main() {
    int m = 4; int n = 3; int p = 6;
    matrix A = matrix(m, n);
    matrix B = matrix(n, p);
    for (int i = 0; i < A.rows * A.cols; ++i) 
        A.mat[i] = i;
    for (int i = 0; i < B.rows * B.cols; ++i)
        B.mat[i] = i;

    matrix *C = Mat_Mul(&A, &B);

    for (int i = 0; i < C->rows;  ++i) {
        for (int j = 0; j < C->cols; ++j) 
            std::cout << C->mat[i*C->cols + j] << ' ';
        std::cout << '\n';
    }

    delete [] A.mat; delete [] B.mat;
    delete [] C->mat; delete C;

    return 0;
}

