#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <algorithm>

using namespace std;

//w c максимальным числом итераций
double wmax = -1;
int itermax = -1;
//w c минимальным числом итераций
double wmin = -1;
int itermin = -1;

void print_matrix(double **matrix, int n) // вывод матрицы
{
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            cout << matrix[i][k] << " ";
        }
        cout << "\n";
    }
    
}

void print_vector(double *vector, int n) // вывод вектора
{
    for (int i = 0; i < n; i++) {
        cout << vector[i] << " ";
    }
        cout << "\n";
}

double **create_matrix(int n) //выделение памяти для матрицы
{
    double **newmatrix = (double **)calloc(n, sizeof(*newmatrix));
    for (int i = 0; i < n; i++) {
        newmatrix[i] = (double *)calloc(n, sizeof(**newmatrix));
    }
    return newmatrix;
}

double **duplicate_matrix(double **matrix, int n) // копирование матрицы 
{
    double **newmatrix = create_matrix(n);
    for (int i = 0; i < n; i++) { 
        for (int k = 0; k < n; k++) {
            newmatrix[i][k] = matrix[i][k];
        }
        
    }
    return newmatrix;
}

double *duplicate_vector(double *vector, int n)  // копирование вектора
{
    double *newvector = (double *)calloc(n, sizeof(*vector));
    for (int i = 0; i < n; i++) { 
        newvector[i] = vector[i];
    }
    return newvector;
}

void free_matrix(double **matrix, int n) // освобождение памяти
{
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

double *top_relax(double **matrix, double *vector, int n, double w) 
{
    // метод Верхней релаксации
    int iter_count = 0;
    double epsilon = 0.000001; // граничное значение для сходимости
    double *result_vector = (double *)calloc(n, sizeof(*result_vector)); // создаем первый вектор результата, инициализированный нулями
    double *iter_vector = (double *)calloc(n, sizeof(*iter_vector)); // вектор, получаемый на итерации
    double *nev_vector = (double *)calloc(n, sizeof(*nev_vector)); // вектор невязки
    double iter_elem; // элемент итерационной поледовательности
    double nev = 0; // норма невязки
    do {
        // Вычисляется i-ый шаг в котором по формулам (*) и (**) из алгоритма решения вычисляются:
        // Новый вектор-результат, вектор невязки и норма невязки
        // Цикл заканчивается, когда метод вектор-результат достигнет определенной точности,
        // т е норма невязки будет < epsilon
        nev = 0;
        iter_count++;
        for (int i = 0; i < n; i++) {
            iter_elem = vector[i];
            for (int j = 0; j <= i - 1; j++) {
                iter_elem -= matrix[i][j] * iter_vector[j];
            }
            for (int j = i; j < n; j++) {
                iter_elem -= matrix[i][j] * result_vector[j];
            }
            iter_elem *= w / matrix[i][i];
            iter_vector[i] = result_vector[i] + iter_elem;
        }
        for (int i = 0; i < n; i++) {
            nev_vector[i] = 0;
            for (int j = 0; j < n; j++) {
                nev_vector[i] += matrix[i][j] * iter_vector[j];
            }
            nev_vector[i] -= vector[i];
            nev += nev_vector[i] * nev_vector[i];
        }
        nev = sqrt(nev);
        for (int i = 0; i < n; i++) result_vector[i] = iter_vector[i];
    } while (nev > epsilon); 
    // нахождение wmax и wmin
    if (iter_count > itermax || itermax < 0) {
        itermax = iter_count;
        wmax = w;
    }
    if (iter_count < itermin || itermin < 0) {
        itermin = iter_count;
        wmin = w;
    }
    // освобождение памяти
    free(nev_vector);
    free(iter_vector);
    return result_vector; 
}

int main(void)
{
    int mod; // Метод ввода матрицы
    double n; // Порядок матрицы
    double w; // параметр w в методе верхней релаксации
    double elem; // Элемент матрицы
    double **matrix; // Исходная матрица
    double *vector; // Исходный вектор
    cout << "Пожалуйста выберите метод ввода матрицы:(1) - из файла, (2) - рекурентной формулой\n";
    cin >> mod;
    if (mod == 1) {
        char filename[PATH_MAX] = {};
        // Ввод матрицы и вектора из файла
        cout << "Введите имя файла, в котором содержится матрица\n";
        cin >> filename;
        ifstream in;
        in.open(filename);
        in >> n;
        matrix = create_matrix(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                in >> elem;
                matrix[i][k] = elem;
            }
        }
        vector = (double *)calloc(n, sizeof(*vector));
        for (int i = 0; i < n; i++) {
            in >> elem;
            vector[i] = elem;
        }
        in.close();
    } else if (mod == 2) {
        // Генерерация данных по формуле
        // Пример 1 Варинант 5 => n = 30; m = 20;
        n = 30;
        double m = 20;        
        matrix = create_matrix(n);
        vector = (double *)calloc(n, sizeof(*vector));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (i == k) {
                    matrix[i][k] = n + m * m + (k + 1) / m + (i + 1)/ double(n);
                } else {
                    matrix[i][k] = (i + k + 2) / (m + n);
                }
            }
            vector[i] = m * (i + 1) + n;
        }
    } else {
        // Ввод неправильного режима ввода
        cout << "Введите верный режим ввода марицы (1 или 2)\n";
        exit(0);
    }
    cout << "Исходная матрица\n";
    print_matrix(matrix, n);
    // Вычисление и сопряженной матрицы А*
    double **matrix_s = duplicate_matrix(matrix, n);
    for(int i = 0; i < n; i++) {
        for (int k = 0; k < i; k++) {
            swap(matrix_s[i][k], matrix_s[k][i]); 
        }
    }
    // помножение исходной матрицы А и вектора b на A*
    double **newmatrix = create_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                newmatrix[i][k] += matrix_s[i][j] * matrix[j][k];
            }
        }
    }
    double *newvector = (double *)calloc(1, sizeof(*newvector));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            newvector[i] += matrix_s[i][k] * vector[k];
        }
    }
    free(vector);
    free_matrix(matrix, n);
    free_matrix(matrix_s, n);
    vector = newvector;
    matrix = newmatrix;
    // метод верхней релаксации
    double **work_matrix;
    double *work_vector;
    double *answer;
    for (w = 0.05; w < 2; w+=0.05) {
        // копирование исходной матрицы и ветора
        work_matrix = duplicate_matrix(matrix, n);
        work_vector = duplicate_vector(vector, n);
        answer = top_relax(work_matrix, work_vector, n, w);
        // освобождение памяти
        free_matrix(work_matrix, n);
        free(work_vector);
        free(answer);
    }
    cout << "w - самое близкое к оптимальному: " << wmin << "\n";
    cout << "Ответ:";
    work_matrix = duplicate_matrix(matrix, n);
    work_vector = duplicate_vector(vector, n);
    answer = top_relax(work_matrix, work_vector, n, wmin);
    print_vector(answer, n);
    // Освобождение памяти
    free_matrix(work_matrix, n);
    free(work_vector);
    free(answer);
    
    cout << "w - самое далекое от оптимального: " << wmax << "\n"; 
    cout << "Ответ:";
    work_matrix = duplicate_matrix(matrix, n);
    work_vector = duplicate_vector(vector, n);
    answer = top_relax(work_matrix, work_vector, n, wmax);
    print_vector(answer, n);
    // Освобождение памяти
    free_matrix(work_matrix, n);
    free(work_vector);
    free(answer);
    free_matrix(matrix, n);
    free(vector);
    return 0;
}