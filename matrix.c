#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 10

void printmatr(double matr[MAX][MAX], int strok, int stolb) {
    for (int i = 0; i < strok; i++) {
        for (int j = 0; j < stolb; j++) {
            printf("%10.4lf ", matr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int readfile(char *filename, double matr[MAX][MAX], int *strok, int *stolb) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Ошибка открытия файла!\n");
        return 0;
    }

    *strok = 0;
    *stolb = 0;

    while (!feof(f)) {
        int j = 0;
        while (fscanf(f, "%lf", &matr[*strok][j]) == 1) {
            j++;
            if (fgetc(f) == '\n') break;
        }
        if (j > 0) {
            *stolb = j;
            (*strok)++;
        }
    }

    fclose(f);
    return 1;
}

void treug(double matr[MAX][MAX], int strok, int stolb) {
    for (int k = 0; k < strok; k++) {
        for (int i = k + 1; i < strok; i++) {
            double kof = matr[i][k] / matr[k][k];
            for (int j = k; j < stolb; j++) {
                matr[i][j] -= kof * matr[k][j];
            }
        }
    }
}

void diagon(double matr[MAX][MAX], int strok, int stolb) {
    for (int k = 0; k < strok; k++) {
        for (int i = 0; i < strok; i++) {
            if (i != k) {
                double kof = matr[i][k] / matr[k][k];
                for (int j = k; j < stolb; j++) {
                    matr[i][j] -= kof * matr[k][j];
                }
            }
        }
    }
}

void perestanovka(double matr[MAX][MAX], int strok, int stolb) {
    for (int k = 0; k < strok; k++) {

        int maxx = k;
        for (int i = k + 1; i < strok; i++) {
            if (fabs(matr[i][k]) > fabs(matr[maxx][k])) {
                maxx = i;
            }
        }

        if (maxx != k) {
            for (int j = 0; j < stolb; j++) {
                double temp = matr[k][j];
                matr[k][j] = matr[maxx][j];
                matr[maxx][j] = temp;
            }
        }

        for (int i = k + 1; i < strok; i++) {
            double kof = matr[i][k] / matr[k][k];
            for (int j = k; j < stolb; j++) {
                matr[i][j] -= kof * matr[k][j];
            }
        }
    }
}

void naxodim(double matr[MAX][MAX], int strok, double x[MAX]) {
    for (int i = strok - 1; i >= 0; i--) {
        double s = 0;
        for (int j = i + 1; j < strok; j++) {
            s += matr[i][j] * x[j];
        }
        x[i] = (matr[i][strok] - s) / matr[i][i];
    }
}

int main() {

    while (1) {

        double matr[MAX][MAX];
        double x[MAX];
        int strok, stolb;

        if (!readfile("matrix.txt", matr, &strok, &stolb)) {
            return 1;
        }

        printf("Матрица из файла:\n\n");
        printmatr(matr, strok, stolb);

        printf("Выберите метод решения:\n");
        printf("1 - Треугольная матрица\n");
        printf("2 - Диагональная матрица\n");
        printf("3 - Выбор главного элемента\n\n");

        int vibor;
        printf("Ваш выбор: ");
        scanf("%d", &vibor);
        printf("\n");

        if (vibor == 1) {
            treug(matr, strok, stolb);
        }
        else if (vibor == 2) {
            diagon(matr, strok, stolb);
        }
        else if (vibor == 3) {
            perestanovka(matr, strok, stolb);
        }
        else {
            printf("Неверный выбор!\n");
            continue;
        }

        printf("Матрица после преобразования:\n\n");
        printmatr(matr, strok, stolb);

        naxodim(matr, strok, x);

        printf("Иксы равны:\n\n");
        for (int i = 0; i < strok; i++) {
            printf("x%d = %.6lf\n", i + 1, x[i]);
        }

        char povtor[10];
        printf("\nРешить другим методом? (Да/Нет): ");
        scanf("%s", povtor);

        if (strcmp(povtor, "Да") != 0 && strcmp(povtor, "да") != 0) {
            break;
        }

        printf("\n\n");
    }

    return 0;
}
