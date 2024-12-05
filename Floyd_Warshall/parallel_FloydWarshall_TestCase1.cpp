#include <iostream>
#include <thread>
#include <cmath>

class matrix {
public:
    double *mat;
    int rows;
    int cols;

    matrix(int row, int col) {
        this->rows = row;
        this->cols = col;
        this->mat = new double[row * col];
    }
};

void Column_In_Charge(int i, int j1, int j2, int k, matrix *D, matrix *P) {
    if (j1 == j2) {
        int n = D->rows;
        if ((D->mat[i*n + k] + D->mat[k*n + j1]) < D->mat[i*n + j1]) {
            D->mat[i*n + j1] = D->mat[i*n + k] + D->mat[k*n + j1];
            P->mat[i*n + j1] = P->mat[k*n + j1];
        } 
    }

    else {
        int j_mid  = (j1 + j2) / 2;
        std::thread t1(Column_In_Charge, i, j1, j_mid, k, D, P);
        Column_In_Charge(i, j_mid + 1, j2, k, D, P);
        t1.join();
    }
}

void Row_In_Charge(int i1, int i2, int k, matrix *D, matrix *P) {
    if (i1 == i2)
        Column_In_Charge(i1, 0, D->rows - 1, k, D, P);
    else {
        int i_mid = (i1 + i2) / 2;
        std::thread t1(Row_In_Charge, i1, i_mid, k, D, P);
        Row_In_Charge(i_mid + 1, i2, k, D, P);
        t1.join();
    }      
}

void Column_Initialize(int i, int j1, int j2, matrix *W, matrix *D, matrix *P) {
    if (j1 == j2) {
        int n = D->cols;
        D->mat[i*n + j1] = W->mat[i*n + j1];
        (i == j1 || D->mat[i*n + j1] == INFINITY)? P->mat[i*n + j1] = -1 : P->mat[i*n + j1] = i;
    }
    else {
        int j_mid  = (j1 + j2) / 2;
        std::thread t1(Column_Initialize, i, j1, j_mid, W, D, P);
        Column_Initialize(i, j_mid + 1, j2, W, D, P);
        t1.join(); 
    }
}

void Row_Initialize(int i1, int i2, matrix *W, matrix *D, matrix *P) {
    if (i1 == i2)
        Column_Initialize(i1, 0, W->rows - 1, W, D, P);
    else {
        int i_mid = (i1 + i2) / 2;
        std::thread t1(Row_Initialize, i1, i_mid, W, D, P);
        Row_Initialize(i_mid + 1, i2, W, D, P);
        t1.join();
    }    
}

std::pair<matrix*, matrix*> Floyd_Warshall(matrix *W) {
    int n = W->rows;
    matrix *D = new matrix(n, n);
    matrix *P = new matrix(n, n);
    Row_Initialize(0, n - 1, W, D, P);
    for (int k = 0; k < n; ++k) 
        Row_In_Charge(0, n - 1, k, D, P);
    return std::make_pair(D, P);
}


void Print_Shortest_Path(int i, int j, matrix *P) {
    if (i == j)
        std::cout << i << " ";
    else if (P->mat[i*P->cols + j] == -1)
        std::cout << "No path exists from " << i << " to " << j;
    else {
        Print_Shortest_Path(i, P->mat[i*P->cols + j], P);
        std::cout << j << " ";
    }
}

void Print_All_Pairs_Shortest_Paths(matrix *P, matrix *D) {
    int n = P->rows;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << "(" << i << " --> " << j << ") :" << " d = " << D->mat[i*n + j] << "\t\t" << "Path : ";
            Print_Shortest_Path(i, j, P);
            std::cout << "\n";
        }         
    }  
}


int main() {
    int n = 5;
    /* W represents the Adjacency Matrix */
    /* This test case 1 of the Adjacency Matrix */
    matrix W(n, n);
    W.mat[0] = 0; 
    W.mat[1] = 3; 
    W.mat[2] = 8; 
    W.mat[3] = INFINITY;
    W.mat[4] = -4;
    W.mat[5] = INFINITY;
    W.mat[6] = 0;
    W.mat[7] = INFINITY;
    W.mat[8] = 1;
    W.mat[9] = 7;
    W.mat[10] = INFINITY;
    W.mat[11] = 4;
    W.mat[12] = 0;
    W.mat[13] = INFINITY;
    W.mat[14] = INFINITY;
    W.mat[15] = 2;
    W.mat[16] = INFINITY;
    W.mat[17] = -5;
    W.mat[18] = 0;
    W.mat[19] = INFINITY;
    W.mat[20] = INFINITY;
    W.mat[21] = INFINITY;
    W.mat[22] = INFINITY;
    W.mat[23] = 6;
    W.mat[24] = 0;


    matrix *D; matrix *P; 
    std::tie(D, P) = Floyd_Warshall(&W);

    Print_All_Pairs_Shortest_Paths(P, D);

    delete[] W.mat;
    delete[] D->mat; delete[] P->mat;
    delete[] D;  delete[] P;

    return 0;
}