#include <iostream>


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



void Mat_Add(matrix *C, matrix *P1, matrix *P2, matrix *P3, matrix *P4, matrix *P5, matrix *P6, matrix *P7, int i_top, int i_down, int j_left, int j_right) {
    int n = C->rows;
    int n1 = P1->rows;
    for (int i = i_top; i <= i_down; ++i) 
        for (int j = j_left; j <= j_right; ++j) {
            C->mat[i*n + j] = P5->mat[i*n1 + j] + P4->mat[i*n1 + j] - P2->mat[i*n1 + j] + P6->mat[i*n1 + j];
            C->mat[i*n + (j + n1)] = P1->mat[i*n1 + j] + P2->mat[i*n1 + j];
            C->mat[(i + n1)*n + j] = P3->mat[i*n1 + j] + P4->mat[i*n1 + j];
            C->mat[(i + n1)*n + (j + n1)] = P5->mat[i*n1 + j] + P1->mat[i*n1 + j] - P3->mat[i*n1 + j] - P7->mat[i*n1 + j];
        }
}



void Create_S(matrix *S1, matrix *S2, matrix *S3, matrix *S4, matrix *S5, matrix *S6, matrix *S7, matrix *S8, matrix *S9, matrix *S10, matrix *A, matrix *B, int i_top_a, int i_down_a, int j_left_a, int j_right_a, int i_top_b, int i_down_b, int j_left_b, int j_right_b, int i1, int i2, int j1, int j2) {
    int n1 = S1->rows;
    int n_a = A->rows;
    int n_b = B->rows;
    for (int i = i1; i <= i2; ++i) {
        for (int j = j1; j <= j2; ++j) {
            S1->mat[i*n1 + j] = B->mat[(i_top_b + i)*n_b + (j_left_b + j + n1)] - B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j + n1)];

            S2->mat[i*n1 + j] = A->mat[(i_top_a + i)*n_a + (j_left_a + j)] + A->mat[(i_top_a + i)*n_a + (j_left_a + j + n1)];

            S3->mat[i*n1 + j] = A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j)] + A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j + n1)];

            S4->mat[i*n1 + j] = B->mat[(i_top_b + i  + n1)*n_b + (j_left_b + j)] - B->mat[(i_top_b + i)*n_b + (j_left_b + j)];

            S5->mat[i*n1 + j] = A->mat[(i_top_a + i)*n_a + (j_left_a + j)] + A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j + n1)];

            S6->mat[i*n1 + j] = B->mat[(i_top_b + i)*n_b + (j_left_b + j)] + B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j + n1)];

            S7->mat[i*n1 + j] = A->mat[(i_top_a + i)*n_a + (j_left_a + j + n1)] - A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j + n1)];

            S8->mat[i*n1 + j] = B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j)] + B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j + n1)];

            S9->mat[i*n1 + j] = A->mat[(i_top_a + i)*n_a + (j_left_a + j)] - A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j)];

            S10->mat[i*n1 + j] = B->mat[(i_top_b + i)*n_b + (j_left_b + j)] + B->mat[(i_top_b + i)*n_b + (j_left_b + j + n1)];
        }
    }
}

void Strassen(matrix *A, matrix *B, int i_top_a, int i_down_a, int j_left_a, int j_right_a, int i_top_b, int i_down_b, int j_left_b, int j_right_b, matrix *C) {
    int n = C->rows;
    if (n == 1)
        C->mat[0] = A->mat[i_top_a * A->cols + j_left_a] * B->mat[i_top_b * B->cols + j_left_b];

    else {
        matrix S1 = matrix(n/2, n/2);
        matrix S2 = matrix(n/2, n/2);
        matrix S3 = matrix(n/2, n/2);
        matrix S4 = matrix(n/2, n/2);
        matrix S5 = matrix(n/2, n/2);
        matrix S6 = matrix(n/2, n/2);
        matrix S7 = matrix(n/2, n/2);
        matrix S8 = matrix(n/2, n/2);
        matrix S9 = matrix(n/2, n/2);
        matrix S10 = matrix(n/2, n/2);

        Create_S(&S1, &S2, &S3, &S4, &S5, &S6, &S7, &S8, &S9, &S10, A, B, i_top_a, i_down_a, j_left_a, j_right_a, i_top_b, i_down_b, j_left_b, j_right_b, 0, n/2 - 1, 0, n/2 - 1);

        matrix P1 = matrix(n/2, n/2);
        matrix P2 = matrix(n/2, n/2);
        matrix P3 = matrix(n/2, n/2);
        matrix P4 = matrix(n/2, n/2);
        matrix P5 = matrix(n/2, n/2);
        matrix P6 = matrix(n/2, n/2);
        matrix P7 = matrix(n/2, n/2);


        int n1 = n/2;
        Strassen(A, &S1, i_top_a, i_top_a + (n/2 - 1), j_left_a, j_left_a + (n/2 - 1), 0, n1 - 1, 0, n1 - 1, &P1);
        Strassen(&S2, B, 0, n1 - 1, 0, n1 - 1, i_top_b + n/2, i_down_b, j_left_b + n/2, j_right_b, &P2);
        Strassen(&S3, B, 0, n1 - 1, 0, n1 - 1, i_top_b, i_top_b + (n/2 - 1), j_left_b, j_left_b + (n/2 - 1), &P3);       
        Strassen(A, &S4, i_top_a + n/2, i_down_a, j_left_a + n/2, j_right_a, 0, n1 - 1, 0, n1 - 1, &P4);     
        Strassen(&S5, &S6, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, &P5);
        Strassen(&S7, &S8, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, &P6);
        Strassen(&S9, &S10, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, &P7);


        Mat_Add(C, &P1, &P2, &P3, &P4, &P5, &P6, &P7, 0, n/2 - 1, 0, n/2 - 1);


        delete [] S1.mat; delete [] S2.mat; delete [] S3.mat; delete [] S4.mat; delete [] S5.mat; delete [] S6.mat; delete [] S7.mat; delete [] S8.mat; delete [] S9.mat; delete [] S10.mat;
        delete [] P1.mat; delete [] P2.mat; delete [] P3.mat; delete [] P4.mat; delete [] P5.mat; delete [] P6.mat; delete [] P7.mat;
    }
}

matrix* Mat_Mul(matrix *A, matrix *B) {
    int n = A->rows;
    matrix *C = new matrix(n, n);
    Strassen(A, B, 0, n-1, 0, n-1, 0, n-1, 0, n-1, C);
    return C;
}

int main() {
    int m = 4; int n = 4;
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