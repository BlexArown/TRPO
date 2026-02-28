#include <stdio.h>

double cblas_ddot(int n, const double *x, int incx,
                  const double *y, int incy)
{
    printf("Fake ddot используется\n");
    return 0.0;  // Неправильный результат
}
