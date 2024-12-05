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

class vector {
public:
    int *vec;
    int length;

    vector(int len) {
        this->vec = new int[len];
        this->length = len;
    }
};

void Mat_Vec_Col_Loop(matrix *A, vector *x, int i_row, int j_low, int j_high, std::atomic<int> *ret) {
    if (j_low == j_high) 
        ret->fetch_add(A->mat[i_row*A->cols + j_low] * x->vec[j_low]);

    else {
        int j_mid = (j_low + j_high) / 2;
        std::thread t1(Mat_Vec_Col_Loop, A, x, i_row, j_low, j_mid, ret);
        Mat_Vec_Col_Loop(A, x, i_row, j_mid + 1, j_high, ret);
        t1.join();
    }

}



void Mat_Vec_Row_Loop(matrix *A, vector *x, int i_low, int i_high, vector *b) {
    if (i_low == i_high) {
        std::atomic<int> ret(0);  // Initialize atomic variable
        Mat_Vec_Col_Loop(A, x, i_low, 0, A->cols - 1, &ret);
        b->vec[i_low] = ret.load(); // Convert atomic<int> back to int
    }
    else {
        int i_mid = (i_low + i_high) / 2;
        std::thread t1(Mat_Vec_Row_Loop, A, x, i_low, i_mid, b);
        Mat_Vec_Row_Loop(A, x, i_mid + 1, i_high, b);
        t1.join();
    }
}

vector* Mat_Vec_Mul(matrix *A, vector *x) {
    int m = A->rows;
    int n = A->cols;
    vector *b = new vector(m);
    Mat_Vec_Row_Loop(A, x, 0, m-1, b);
    return b;
}


int main() {
    int m = 4; int n = 9;
    matrix A = matrix(m, n);
    vector x = vector(n);

    for (int i = 0; i < A.rows * A.cols; ++i) 
        A.mat[i] = i;

    for (int i = 0; i < x.length; ++i)
        x.vec[i] = i;

    vector *b = Mat_Vec_Mul(&A, &x);

    for (int i = 0; i < b->length; ++i) 
      std::cout << b->vec[i] << ' ';
    std::cout << '\n';

    delete [] A.mat; delete [] x.vec;
    delete [] b->vec; delete b;

    return 0;
}