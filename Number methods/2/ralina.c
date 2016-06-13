// изменяемые параметры
#define n 1        // количество уравнений в системе (или 1, если уравнение одно)
#define len 1      // длина отрезка [x0; x0 + len]
#define k 10       // кол-во шагов
#define alpha 0.5
// заполнется для каждого теста
void f(double *y_tmp, double x, double *y)
{
    y_tmp[0] = y[0] * y[0] - 2.0 / (x * x);    // пример
}

// заполнется для каждого теста
void real_solve(double **solve, double x0)
{
    double x_i = x0, h = (double)len / k;    // пример
    for (int i = 0; i < k + 1; i++) {
        solve[0][i] = -2.0 / x_i;
        x_i += h;
    }
}

void print_solve(double **solve, double x0, double h)
{
    for (int i = 0; i < k + 1; i++) {
        for(int j = 0; j < n; j++) {
            printf("   у%d(%lf)  =   %lf\n", j + 1, x0 + i * h, solve[j][i]);
        }
    }

}

void r_kutta2(double **solve, double x0, double *y0)
{
    double x_i = x0, h = (double)len / k;
    double *y_i = calloc(n, sizeof(*y_i));    // y_i
    double *y_tmp = calloc(n, sizeof(*y_tmp));   // ~y_i+1
    // первый вектор совпадает с начальными условиями
    for (int i = 0; i < n; i++) {
        y_i[i] = y0[i];
    }

    double *f_i = calloc(n, sizeof(*solve));   // f(x_i, y_i)
    double *f_tmp = calloc(n, sizeof(*solve)); // для промежуточных вычислений

    // вычисляем y_i+1
    for (int i = 1; i < k + 1; i++) {
        // для конкретного x находим вектор значений ф-ции f(x_i, y_i)
        f(f_i, x_i, y_i);

        // вычисляем ~y_i+1
        for (int j = 0; j < n; j++) {
            y_tmp[j] = y_i[j] + (h / (2 * alpha)) * f_i[j];
        }

        f(f_tmp, x_i + h / (2 * alpha), y_tmp);

        // получаем y_i+1
        for (int j = 0; j < n; j++) {
            y_i[j] = y_i[j] + ((1 - alpha) * f_i[j] + alpha * f_tmp[j]) * h;
            solve[j][i] = y_i[j];
        }

        x_i += h;
    }

    free(y_i);
    free(y_tmp);
    free(f_i);
    free(f_tmp);
}

void r_kutta4(double **solve, double x0, double *y0)
{
    double x_i = x0, h = (double)len / k;
    double *y_i = calloc(n, sizeof(*y_i));
    double *y_tmp = calloc(n, sizeof(*y_tmp));

    // первый вектор совпадает с начальными условиями
    for (int i = 0; i < n; i++) {
        y_i[i] = y0[i];
    }

    double *k1 = calloc(n, sizeof(*solve));
    double *k2 = calloc(n, sizeof(*solve));
    double *k3 = calloc(n, sizeof(*solve));
    double *k4 = calloc(n, sizeof(*solve));

    // вычисляем y_i+1
    for (int i = 1; i <= k; i++)
    {
        f(k1, x_i, y_i);

        // готовим второй параметр для k2
        for (int j = 0; j < n; j++) {
            y_tmp[j] = y_i[j] + (h / 2) * k1[j];
        }
        f(k2, x_i + h / 2, y_tmp);

        // готовим второй параметр для k3
        for (int j = 0; j < n; j++) {
            y_tmp[j] = y_i[j] + (h / 2) * k2[j];
        }
        f(k3, x_i + h / 2, y_tmp);

        // готовим второй параметр для k4
        for (int j = 0; j < n; j++) {
            y_tmp[j] = y_i[j] + h * k3[j];
        }
        f(k4, x_i + h, y_tmp);

        // вячисляем y_i+1
        for (int j = 0; j < n; j++) {
            y_i[j] = y_i[j] + (h / 6) * (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]);
            solve[j][i] = y_i[j];
        }

        x_i += h;
    }

    free(k1);
    free(k2);
    free(k3);
    free(k4);
    free(y_i);
    free(y_tmp);
}

int
main(void)
{
    // Считываем начальные условия
    double *y0 = calloc(n, sizeof(*y0));
    printf("Введите начальные условия (x0 и вектор y0)\n");
    double x0;
    scanf("%lf", &x0);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &y0[i]);
    }

    // находим решения по методу Рунге-Кутты второго и четвертого порядка точности

    // выделяем память для ответов уравнений системы для каждого х_i
    // и заполняю для x_i = x0
    double **solve = calloc(n, sizeof(*solve));
    for (int i = 0; i < n; i++) {
        solve[i] = calloc(k + 1, sizeof(**solve));
        solve[i][0] = y0[i];
    }

    double h = (double)len / k;    // шаг

    r_kutta2(solve, x0, y0);
    printf("\nРешение методом Рунге-Кутта второго порядка точности:\n");
    print_solve(solve, x0, h);

    r_kutta4(solve, x0, y0);
    printf("\nРешение методом Рунге-Кутта четвертого порядка точности:\n");
    print_solve(solve, x0, h);

    real_solve(solve, x0);
    printf("\nТочное решение:\n");
    print_solve(solve, x0, h);

    free(y0);
    free(solve);
    return 0;

}
