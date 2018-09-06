#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <algorithm>

using namespace std;

int iter_count; // количество итераций
//k1 * y(l) + k2 * y'(l) = a
//l1 * y(r) + l2 * y'(r) = b
double k1 = 2, k2 = -1, a = 1, l1 = 1, l2 = 0, b = 3; // параметры системы (из примера)
double l = 1.3, r = 1.6; // параметры системы (из примера)
double h;// шаг

double p(double x) // из примера
{
    return 1.5;
}

double q(double x) // из примера
{
    return -x;
}

double f(double x) // из примера
{
    return 0.5;
}


void progonka(double *arr_x, double *arr_y) // метод прогонки
{
    double *arr_p = (double *)malloc((iter_count + 1) * sizeof(double));
    double *arr_q = (double *)malloc((iter_count + 1) * sizeof(double));
    double *arr_r = (double *)malloc((iter_count + 1) * sizeof(double));
    double *arr_f = (double *)malloc((iter_count + 1) * sizeof(double));
    double *arr_alpha = (double *)malloc((iter_count + 1) * sizeof(double));
    double *arr_betta = (double *)malloc((iter_count + 1) * sizeof(double));
    // прямой проход
    // вычисление коефицентов
    for (int i = 0; i <= iter_count; i++) {
        arr_x[i] = l + h * i;
        arr_p[i] = 1 - p(arr_x[i]) * h / 2;
        arr_q[i] = 1 + p(arr_x[i]) * h / 2;
        arr_r[i] = 2 - q(arr_x[i]) * h * h;
        arr_f[i] = h * h * f(arr_x[i]);
    }
    // вычисление альфа и бетта
    arr_alpha[1] = k2 / (k2 - k1 * h);
    arr_betta[1] = - (a * h) / (k2 - k1 * h);
    for (int i = 1; i < iter_count; i++) {
        arr_alpha[i + 1] = arr_q[i] / (arr_r[i] - arr_alpha[i] * arr_p[i]);
        arr_betta[i + 1] = (arr_p[i] * arr_betta[i] - arr_f[i]) / (arr_r[i] - arr_alpha[i] * arr_p[i]);
    }
    // обратный проход
    arr_y[iter_count] = (l2 * arr_betta[iter_count] + b * h) / (l2 + h * l1 - l2 * arr_alpha[iter_count]);
    for (int i = iter_count - 1; i >= 0; i--) {
        arr_y[i] = arr_alpha[i + 1] * arr_y[i + 1] + arr_betta[i + 1];
    }
}


int main()
{
    cout << "Пожалуйста введите количество итераций\n";
    cin >> iter_count;
    h = (r - l) / iter_count;
    double *arr_x = (double *)malloc((iter_count + 1) * sizeof(double));
    double *arr_rez = (double *)malloc((iter_count + 1) * sizeof(double));
    progonka(arr_x, arr_rez);
    cout << "x: " ;
    for (int i = 0; i < iter_count + 1; i++) {
        cout << arr_x[i] << " ";
    }
    cout << "\n";
    cout << "y: " ;
    for (int i = 0; i < iter_count + 1; i++) {
        cout << arr_rez[i] << " ";
    }
    cout << "\n";
    return 0;
}
