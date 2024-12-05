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


void Mat_Add_Col(matrix *C, matrix *C11_1, matrix *C11_2, matrix *C12_1, matrix *C12_2, matrix *C21_1, matrix *C21_2, matrix *C22_1, matrix *C22_2, int i, int j_left, int j_right) {
    if (j_left <= j_right) {
        int j_mid = (j_left + j_right) / 2;
        std::thread t1(Mat_Add_Col, C, C11_1, C11_2, C12_1, C12_2, C21_1, C21_2, C22_1, C22_2, i, j_left, j_mid - 1);
        std::thread t2(Mat_Add_Col, C, C11_1, C11_2, C12_1, C12_2, C21_1, C21_2, C22_1, C22_2, i, j_mid + 1, j_right);

        int n1 = C11_1->rows;
        int n = 2*n1;
        C->mat[i*n + j_mid] = C11_1->mat[i*n1 + j_mid] + C11_2->mat[i*n1 + j_mid];
        C->mat[i*n + (j_mid+n1)] = C12_1->mat[i*n1 + j_mid] + C12_2->mat[i*n1 + j_mid];
        C->mat[(i+n1)*n + j_mid] = C21_1->mat[i*n1 + j_mid] + C21_2->mat[i*n1 + j_mid];
        C->mat[(i+n1)*n + (j_mid+n1)] = C22_1->mat[i*n1 + j_mid] + C22_2->mat[i*n1 + j_mid];

        t1.join();
        t2.join();
    }
}

void Mat_Add(matrix *C, matrix *C11_1, matrix *C11_2, matrix *C12_1, matrix *C12_2, matrix *C21_1, matrix *C21_2, matrix *C22_1, matrix *C22_2, int i_top, int i_down, int j_left, int j_right) {
    if (i_top <= i_down) {
        int i_mid = (i_top + i_down) / 2;

        std::thread t1(Mat_Add, C, C11_1, C11_2, C12_1, C12_2, C21_1, C21_2, C22_1, C22_2, i_top, i_mid - 1, j_left, j_right);
        std::thread t2(Mat_Add, C, C11_1, C11_2, C12_1, C12_2, C21_1, C21_2, C22_1, C22_2, i_mid + 1, i_down, j_left, j_right);        
        Mat_Add_Col(C, C11_1, C11_2, C12_1, C12_2, C21_1, C21_2, C22_1, C22_2, i_mid, j_left, j_right);

        t1.join();
        t2.join();
    }
}


void Mat_Mul_Recur(matrix *A, matrix *B, int i_top_a, int i_down_a, int j_left_a, int j_right_a, int i_top_b, int i_down_b, int j_left_b, int j_right_b, matrix *C) {
    int n = C->rows;
    if (n == 1)
        C->mat[0] = A->mat[i_top_a * A->cols + j_left_a] * B->mat[i_top_b * B->cols + j_left_b];

    else {
        matrix C11_1 = matrix(n/2, n/2);
        matrix C11_2 = matrix(n/2, n/2);
        matrix C12_1 = matrix(n/2, n/2);
        matrix C12_2 = matrix(n/2, n/2);
        matrix C21_1 = matrix(n/2, n/2);
        matrix C21_2 = matrix(n/2, n/2);
        matrix C22_1 = matrix(n/2, n/2);
        matrix C22_2 = matrix(n/2, n/2);



        std::thread t11_1(Mat_Mul_Recur, A, B, i_top_a, i_top_a + (n/2 - 1), j_left_a, j_left_a + (n/2 - 1), i_top_b, i_top_b + (n/2 - 1), j_left_b, j_left_b + (n/2 - 1), &C11_1);
        std::thread t11_2(Mat_Mul_Recur, A, B, i_top_a, i_top_a + (n/2 - 1), j_left_a + n/2, j_right_a, i_top_b + n/2, i_down_b, j_left_b, j_left_b + (n/2 - 1), &C11_2);

        std::thread t12_1(Mat_Mul_Recur, A, B, i_top_a, i_top_a + (n/2 - 1), j_left_a, j_left_a + (n/2 - 1), i_top_b, i_top_b + (n/2 - 1), j_left_b + n/2, j_right_b, &C12_1);
        std::thread t12_2(Mat_Mul_Recur, A, B, i_top_a, i_top_a + (n/2 - 1), j_left_a + n/2, j_right_a, i_top_b + n/2, i_down_b, j_left_b + n/2, j_right_b, &C12_2);

        std::thread t21_1(Mat_Mul_Recur, A, B, i_top_a + n/2, i_down_a, j_left_a, j_left_a + (n/2 - 1), i_top_b, i_top_b + (n/2 - 1), j_left_b, j_left_b + (n/2 - 1), &C21_1);
        std::thread t21_2(Mat_Mul_Recur, A, B, i_top_a + n/2, i_down_a, j_left_a + n/2, j_right_a, i_top_b + n/2, i_down_b, j_left_b, j_left_b + (n/2 - 1), &C21_2);

        std::thread t22_1(Mat_Mul_Recur, A, B, i_top_a + n/2, i_down_a, j_left_a, j_left_a + (n/2 - 1), i_top_b, i_top_b + (n/2 - 1), j_left_b + n/2, j_right_b, &C22_1);
        Mat_Mul_Recur(A, B, i_top_a + n/2, i_down_a, j_left_a + n/2, j_right_a, i_top_b + n/2, i_down_b, j_left_b + n/2, j_right_b, &C22_2);

        t11_1.join();
        t11_2.join();

        t12_1.join();
        t12_2.join();

        t21_1.join();
        t21_2.join();
        t22_1.join();

        int n1 = n/2;

        Mat_Add(C, &C11_1, &C11_2, &C12_1, &C12_2, &C21_1, &C21_2, &C22_1, &C22_2, 0, n1 - 1, 0, n1 - 1);

        delete [] C11_1.mat; delete [] C11_2.mat; delete [] C12_1.mat; delete [] C12_2.mat; delete [] C21_1.mat; delete [] C21_2.mat;
        delete [] C22_1.mat; delete [] C22_2.mat;
    }
}

matrix* Mat_Mul(matrix *A, matrix *B) {
    int n = A->rows;
    matrix *C = new matrix(n, n);
    Mat_Mul_Recur(A, B, 0, n-1, 0, n-1, 0, n-1, 0, n-1, C);
    return C;
}

int main() {
    int m = 4; int n = 4;    /*A and B must be square matrices of same size equal to a power of 2*/
    matrix A = matrix(m, n);
    matrix B = matrix(m, n);
    for (int i = 0; i < m*n; ++i) {
        A.mat[i] = i;
        B.mat[i] = i;
    }

    matrix *C = Mat_Mul(&A, &B);

    for (int i = 0; i < C->rows;  ++i) {
        for (int j = 0; j < C->cols; ++j) 
            std::cout << C->mat[i*C->cols + j] << "  ";
        std::cout << "\n";
    }

    delete [] A.mat; delete [] B.mat;
    delete [] C->mat; delete C;

    return 0;
}