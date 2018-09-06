#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <algorithm>

using namespace std;

double f(double x, double y) // фунцкция из примера
{
    return (x - x * x) * y;
}

double f1(double x, double u, double v) // функция из примера
{
    return pow(M_E, -u * u - v * v) + 2 * x;
}

double f2(double x, double u, double v) // функция из примера
{
    return 2 * u * u + v;
}

double **vectors; // массив генерируемых итерациионно значений x, y1, ...
double h;// шаг
int iter_count;// число итераций

void RK_2(int num) { // метод Рунге-Кутта второго порядка
    double *k1 = (double *)malloc((num + 1) * sizeof(double));
    double *k2 = (double *)malloc((num + 1) * sizeof(double));
    if (num == 1) { // 1 уравнение
        for (int i = 1; i <= iter_count; i++) {
            vectors[0][i] = vectors[0][i - 1] + h;
            for (int k = 1; k < num + 1; k++) {
                k1[k] = f(vectors[0][i - 1], vectors[k][i - 1]);
                k2[k] = f(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k1[k]);
            }
            for (int k = 1; k < num + 1; k++) {
                double delta_y = h * k2[k];
                vectors[k][i] = vectors[k][i - 1] + delta_y;
            }
        }
    } else if (num == 2) { // 2 уравнения
        double *l1 = (double *)malloc((num + 1) * sizeof(double));
        double *l2 = (double *)malloc((num + 1) * sizeof(double));
        for (int i = 1; i <= iter_count; i++) {
            vectors[0][i] = vectors[0][i - 1] + h;
            for (int k = 1; k < num; k++) {
                k1[k] = f1(vectors[0][i - 1], vectors[k][i - 1], vectors[k + 1][i - 1]);
                l1[k] = f2(vectors[0][i - 1], vectors[k][i - 1], vectors[k + 1][i - 1]);
                k2[k] = f1(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k1[k], vectors[k + 1][i - 1] + h / 2 * l1[k]);
                l2[k] = f2(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k1[k], vectors[k + 1][i - 1] + h / 2 * l1[k]);
            }
            for (int k = 1; k < num; k++) {
                double delta_y = h / 2 * (k1[k] + k2[k]);
                vectors[k][i] = vectors[k][i - 1] + delta_y;
                delta_y = h / 2 * (l1[k] + l2[k]);
                vectors[k + 1][i] = vectors[k + 1][i - 1] + delta_y;
            }
        free(l1);
        free(l2);
        }
    }
    free(k1);
    free(k2);
}

void RK_4(int num) { // Метод Рунге-Кутта четвертого порядка
    double *k1 = (double *)malloc((num + 1) * sizeof(double));
    double *k2 = (double *)malloc((num + 1) * sizeof(double));
    double *k3 = (double *)malloc((num + 1) * sizeof(double));
    double *k4 = (double *)malloc((num + 1) * sizeof(double));
    if (num == 1) { // 1 уравнение
        for (int i = 1; i <= iter_count; i++) {
            vectors[0][i] = vectors[0][i - 1] + h;
            for (int k = 1; k < num + 1; k++) {
                k1[k] = f(vectors[0][i - 1], vectors[k][i - 1]);
                k2[k] = f(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k1[k]);
                k3[k] = f(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k2[k]);
                k4[k] = f(vectors[0][i - 1] + h, vectors[k][i - 1] + h * k3[k]);
            }
            for (int k = 1; k < num + 1; k++) {
                double delta_y = h / 6 * (k1[k] + 2 * k2[k] + 2 * k3[k] + k4[k]);
                vectors[k][i] = vectors[k][i - 1] + delta_y;
            }
        }

    } else if (num == 2) { // 2 уравнения
        double *l1 = (double *)malloc((num + 1) * sizeof(double));
        double *l2 = (double *)malloc((num + 1) * sizeof(double));
        double *l3 = (double *)malloc((num + 1) * sizeof(double));
        double *l4 = (double *)malloc((num + 1) * sizeof(double));
        for (int i = 1; i <= iter_count; i++) {
            vectors[0][i] = vectors[0][i - 1] + h;
            for (int k = 1; k < num; k++) {
                k1[k] = f1(vectors[0][i - 1], vectors[k][i - 1], vectors[k + 1][i - 1]);
                l1[k] = f2(vectors[0][i - 1], vectors[k][i - 1], vectors[k + 1][i - 1]);
                k2[k] = f1(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k1[k], vectors[k + 1][i - 1] + h / 2 * l1[k]);
                l2[k] = f2(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k1[k], vectors[k + 1][i - 1] + h / 2 * l1[k]);
                k3[k] = f1(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k2[k], vectors[k + 1][i - 1] + h / 2 * l2[k]);
                l3[k] = f2(vectors[0][i - 1] + h / 2, vectors[k][i - 1] + h / 2 * k2[k], vectors[k + 1][i - 1] + h / 2 * l2[k]);
                k4[k] = f1(vectors[0][i - 1] + h, vectors[k][i - 1] + h * k3[k], vectors[k + 1][i - 1] + h * l3[k]);
                l4[k] = f2(vectors[0][i - 1] + h, vectors[k][i - 1] + h * k3[k], vectors[k + 1][i - 1] + h * l3[k]);
            }
            for (int k = 1; k < num; k++) {
                double delta_y = h / 6  * (k1[k] + 2 * k2[k] + 2 * k3[k] + k4[k]);
                vectors[k][i] = vectors[k][i - 1] + delta_y;
                delta_y = h / 6 * (l1[k] + 2 * l2[k]+ 2 * l3[k] + l4[k]);
                vectors[k + 1][i] = vectors[k + 1][i - 1] + delta_y;
            }
        }
        free(l1);
        free(l2);
        free(l3);
        free(l4);
    }
    free(k1);
    free(k2);
    free(k3);
    free(k4);
}

void print(int n) // вывод ответа
{
    cout << "i: ";
    for (int i = 0; i < iter_count + 1; i++) {
        cout << i << " ";
    }
    cout << "\n";
    cout << "x: " ;
    for (int i = 0; i < iter_count + 1; i++) {
        cout << vectors[0][i] <<     " ";
    }
    cout << "\n";
    for (int k = 1; k < n + 1; k++ ){
        cout << "y[" << k << "]:" ;
        for (int i = 0; i < iter_count + 1; i++) {
            cout << vectors[k][i] << " ";
        }
        cout << "\n";
    }
}


int main()
{
    int mod; // количество уравнений
    int method; // порядок в методе Рунге-Кутта
    double left, right; // границы вычисления
    cout << "Пожалуйста выберите тип входных данных:(1) - одно уравнение, (2) - система из двух уравнений\n";
    cin >> mod;
    cout << "Пожалуйста выберите порядок метода Рунге-Кутта:(2) - второй, (4) - четвертый\n";
    cin >> method;
    cout << "Пожалуйста введите отрезок, на котором будет искаться решение в формате \"a b\"\n";
    cin >> left >> right;
    cout << "Пожалуйста введите количество итераций\n";
    cin >> iter_count;
    h = (right - left) / iter_count;
    vectors = (double **)malloc((mod + 1) * sizeof(double *));
    for (int i = 0; i <= mod; i++) {
        vectors[i] = (double *)malloc((iter_count + 1) * sizeof(double));
    }
    cout << "Введите начаньные условия\n";
    for (int i = 0; i < mod + 1; i++) {
        cin >> vectors[i][0];
    }
    if (method == 2) {
        RK_2(mod);
        print(mod);
    } else if (method == 4) {
        RK_4(mod);
        print(mod);
    } else {
        cout << "Введите правильный метод";
        exit(0);
    }
    return 0;
}
