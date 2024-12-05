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


void Mat_Add_Col(matrix *C, matrix *P1, matrix *P2, matrix *P3, matrix *P4, matrix *P5, matrix *P6, matrix *P7, int i, int j_left, int j_right) {
    if (j_left <= j_right) {
        int j_mid = (j_left + j_right) / 2;
        std::thread t1(Mat_Add_Col, C, P1, P2, P3, P4, P5, P6, P7, i, j_left, j_mid - 1);
        std::thread t2(Mat_Add_Col, C, P1, P2, P3, P4, P5, P6, P7, i, j_mid + 1, j_right);

        int n = C->rows;
        int n1 = P1->rows;
        C->mat[i*n + j_mid] = P5->mat[i*n1 + j_mid] + P4->mat[i*n1 + j_mid] - P2->mat[i*n1 + j_mid] + P6->mat[i*n1 + j_mid];
        C->mat[i*n + (j_mid + n1)] = P1->mat[i*n1 + j_mid] + P2->mat[i*n1 + j_mid];
        C->mat[(i + n1)*n + j_mid] = P3->mat[i*n1 + j_mid] + P4->mat[i*n1 + j_mid];
        C->mat[(i + n1)*n + (j_mid + n1)] = P5->mat[i*n1 + j_mid] + P1->mat[i*n1 + j_mid] - P3->mat[i*n1 + j_mid] - P7->mat[i*n1 + j_mid];

        t1.join();
        t2.join();
    }
}

void Mat_Add(matrix *C, matrix *P1, matrix *P2, matrix *P3, matrix *P4, matrix *P5, matrix *P6, matrix *P7, int i_top, int i_down, int j_left, int j_right) {
    if (i_top <= i_down) {
        int i_mid = (i_top + i_down) / 2;
        std::thread t1(Mat_Add, C, P1, P2, P3, P4, P5, P6, P7, i_top, i_mid - 1, j_left, j_right);
        std::thread t2(Mat_Add, C, P1, P2, P3, P4, P5, P6, P7, i_mid + 1, i_down, j_left, j_right);

        Mat_Add_Col(C, P1, P2, P3, P4, P5, P6, P7, i_mid, j_left, j_right);
        t1.join();
        t2.join();
    }
}


void Create_S_Col(matrix *S1, matrix *S2, matrix *S3, matrix *S4, matrix *S5, matrix *S6, matrix *S7, matrix *S8, matrix *S9, matrix *S10, matrix *A, matrix *B, int i_top_a, int i_down_a, int j_left_a, int j_right_a, int i_top_b, int i_down_b, int j_left_b, int j_right_b, int i, int j_left, int j_right) {
    if (j_left <= j_right) {
        int j_mid = (j_left + j_right) / 2;
        std::thread t1(Create_S_Col, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, A, B, i_top_a, i_down_a, j_left_a, j_right_a, i_top_b, i_down_b, j_left_b, j_right_b, i, j_left, j_mid - 1);
        std::thread t2(Create_S_Col, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, A, B, i_top_a, i_down_a, j_left_a, j_right_a, i_top_b, i_down_b, j_left_b, j_right_b, i, j_mid + 1, j_right);

        int n1 = S1->rows;
        int n_a = A->rows;
        int n_b = B->rows;


        S1->mat[i*n1 + j_mid] = B->mat[(i_top_b + i)*n_b + (j_left_b + j_mid + n1)] - B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j_mid + n1)];

        S2->mat[i*n1 + j_mid] = A->mat[(i_top_a + i)*n_a + (j_left_a + j_mid)] + A->mat[(i_top_a + i)*n_a + (j_left_a + j_mid + n1)];

        S3->mat[i*n1 + j_mid] = A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j_mid)] + A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j_mid + n1)];

        S4->mat[i*n1 + j_mid] = B->mat[(i_top_b + i  + n1)*n_b + (j_left_b + j_mid)] - B->mat[(i_top_b + i)*n_b + (j_left_b + j_mid)];

        S5->mat[i*n1 + j_mid] = A->mat[(i_top_a + i)*n_a + (j_left_a + j_mid)] + A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j_mid + n1)];

        S6->mat[i*n1 + j_mid] = B->mat[(i_top_b + i)*n_b + (j_left_b + j_mid)] + B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j_mid + n1)];

        S7->mat[i*n1 + j_mid] = A->mat[(i_top_a + i)*n_a + (j_left_a + j_mid + n1)] - A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j_mid + n1)];

        S8->mat[i*n1 + j_mid] = B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j_mid)] + B->mat[(i_top_b + i + n1)*n_b + (j_left_b + j_mid + n1)];

        S9->mat[i*n1 + j_mid] = A->mat[(i_top_a + i)*n_a + (j_left_a + j_mid)] - A->mat[(i_top_a + i + n1)*n_a + (j_left_a + j_mid)];

        S10->mat[i*n1 + j_mid] = B->mat[(i_top_b + i)*n_b + (j_left_b + j_mid)] + B->mat[(i_top_b + i)*n_b + (j_left_b + j_mid + n1)];

        t1.join();
        t2.join();
    }
}


void Create_S(matrix *S1, matrix *S2, matrix *S3, matrix *S4, matrix *S5, matrix *S6, matrix *S7, matrix *S8, matrix *S9, matrix *S10, matrix *A, matrix *B, int i_top_a, int i_down_a, int j_left_a, int j_right_a, int i_top_b, int i_down_b, int j_left_b, int j_right_b, int i1, int i2, int j1, int j2) {
    if (i1 <= i2) {
        int i_mid = (i1 + i2) / 2;
        std::thread t1(Create_S, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, A, B, i_top_a, i_down_a, j_left_a, j_right_a, i_top_b, i_down_b, j_left_b, j_right_b, i1, i_mid - 1, j1, j2);
        std::thread t2(Create_S, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, A, B, i_top_a, i_down_a, j_left_a, j_right_a, i_top_b, i_down_b, j_left_b, j_right_b, i_mid + 1, i2, j1, j2);

        Create_S_Col(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, A, B, i_top_a, i_down_a, j_left_a, j_right_a, i_top_b, i_down_b, j_left_b, j_right_b, i_mid, j1, j2);

        t1.join();
        t2.join();
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
        std::thread t_P1(Strassen, A, &S1, i_top_a, i_top_a + (n/2 - 1), j_left_a, j_left_a + (n/2 - 1), 0, n1 - 1, 0, n1 - 1, &P1);
        std::thread t_P2(Strassen, &S2, B, 0, n1 - 1, 0, n1 - 1, i_top_b + n/2, i_down_b, j_left_b + n/2, j_right_b, &P2);
        std::thread t_P3(Strassen, &S3, B, 0, n1 - 1, 0, n1 - 1, i_top_b, i_top_b + (n/2 - 1), j_left_b, j_left_b + (n/2 - 1), &P3);       
        std::thread t_P4(Strassen, A, &S4, i_top_a + n/2, i_down_a, j_left_a + n/2, j_right_a, 0, n1 - 1, 0, n1 - 1, &P4);     
        std::thread t_P5(Strassen, &S5, &S6, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, &P5);
        std::thread t_P6(Strassen, &S7, &S8, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, &P6);
        Strassen(&S9, &S10, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, 0, n1 - 1, &P7);

        t_P1.join();
        t_P2.join();
        t_P3.join();
        t_P4.join();    
        t_P5.join();
        t_P6.join();


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
            std::cout << C->mat[i*C->cols + j] << "     ";
        std::cout << "\n";
    }


    delete [] A.mat; delete [] B.mat;
    delete [] C->mat; delete C;

    return 0;
}