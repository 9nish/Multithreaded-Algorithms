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

    class vector {
    public:
        int *vec;
        int length;

        vector(int len) {
            this->vec = new int[len];
            this->length = len;
        }
    };


    vector* Mat_Vec_Mul(matrix *A, vector *x) {
        vector *b = new vector(A->rows);
        for (int i = 0; i < A->rows; ++i) {
            b->vec[i] = 0;
            for (int j = 0; j < A->cols; ++j)
                b->vec[i] +=  A->mat[i*A->cols + j] * x->vec[j];
        }
        return b;
    }


    int main() {
        int m = 10; int n = 500;
        matrix A = matrix(m, n);
        vector x = vector(n);

        for (int i = 0; i < A.rows * A.cols; ++i) 
            A.mat[i] = i;

        for (int i = 0; i < x.length; ++i)
            x.vec[i] = i;


        vector *b = Mat_Vec_Mul(&A, &x);

        for (int i = 0; i < b->length; ++i) 
        std::cout << b->vec[i] << " ";
        std::cout << "\n";
        
        delete [] A.mat; delete [] x.vec;
        delete [] b->vec; delete b;

        return 0;
    }