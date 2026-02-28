#include <stdio.h>
#include <cblas.h>

int main() {

    int n = 3;
    double A[9] = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    double B[9] = {
        9,8,7,
        6,5,4,
        3,2,1
    };

    double C[9] = {0};

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n,
                1.0, A, n,
                B, n,
                0.0, C, n);

    for(int i=0;i<9;i++)
        printf("%lf ", C[i]);
    printf("\n");
    return 0;
}
