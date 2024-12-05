#include <iostream>
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



void Print_Shortest_Path(int i, int j, const matrix &P) {
    if (i == j)
        std::cout << i << " ";
    else if (P.mat[i*P.cols + j] == -1)
        std::cout << "No path exists from " << i << " to " << j;
    else {
        Print_Shortest_Path(i, P.mat[i*P.cols + j], P);
        std::cout << j << " ";
    }
}

void Print_All_Pairs_Shortest_Paths(const matrix &P, const matrix &D) {
    int n = P.rows;
    for (int i = 0; i < n; ++i) {
        //std::cout << "Vertex " << i << "\n\t";
        for (int j = 0; j < n; ++j) {
            std::cout << "(" << i << " --> " << j << ") :" << " d = " << D.mat[i*n + j] << "\t\t" << "Path : ";
            Print_Shortest_Path(i, j, P);
            std::cout << "\n";
        }         
    }  
}


void Floyd_Warshall(matrix *W) {
    int n = W->rows;
    matrix P(n, n);
    matrix D(n, n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            D.mat[i*n + j] = W->mat[i*n + j];
            (i == j || D.mat[i*n + j] == INFINITY)? P.mat[i*n + j] = -1 : P.mat[i*n + j] = i;
        }
    }
    

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((D.mat[i*n + k] + D.mat[k*n + j]) < D.mat[i*n + j]) {
                    D.mat[i*n + j] = D.mat[i*n + k] + D.mat[k*n + j];
                    P.mat[i*n + j] = P.mat[k*n + j];
                } 
            }
        }
    }

    Print_All_Pairs_Shortest_Paths(P, D);     
}


int main() {
    int n = 5;
    matrix W(5, 5);
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

    Floyd_Warshall(&W);
    return 0;
}
