#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <algorithm>

using namespace std;

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

void gauss(double **matrix, double *vector, int n)
{
    // метод Гаусса
    int flag; // флаг, который хранит, нужно ли переставлять строки в матрице
    double dev; // сохраняемый элемент матрицы, для упрощения вычислений
    double **invert = create_matrix(n); // обратная матрица, которая параллельно вычисляется.
    double det = 1; // детерминант, который параллельно вычисляется
    double normmatr = 0; // норма исходной матрицы 
    double norminv = 0; // норма обратной матрицы
    for(int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) 
            normmatr += matrix[i][k] * matrix[i][k];
    normmatr = sqrt(normmatr);
    for (int i = 0; i < n; i++) invert[i][i] = 1; // сначала обратная матрица - единичная
    cout << "Исходная матрица\n";
    print_matrix(matrix, n); //вывод исходной матрицы
    for (int i = 0; i < n - 1; i++) { // проход прямым ходом метода Гаусса
        flag = 0;
        for (int k = i; k < n; k++) { // поиск первого ненулевого элемента в i-ом столбце 
            if (fabs(matrix[k][i]) < 0.000001) { // считаем ноль с опредленной точностью
                flag = 1;
                if (k == n - 1) { // обработка ошибки при вырожденности матрицы
                    cout << "матрица вырождена!\n";
                    exit(0);
                }
            } else { // если, найденный первый ненулевой элемент не i-ый, 
                //то нужно поменять его строку местами с i-ым
                // это учитывается и в обратной матрице
                if (flag) {
                    swap(matrix[k], matrix[i]);
                    swap(invert[k], invert[i]);
                    swap(vector[k], vector[i]);
                    det *= -1; // перестановка строк отражается на знаке определителя
                }
                break;
            }
        }
        // Преобразовывание матрицы: обнуление всех элементов i-го столбца после i-той строки
        // с помощью линейных преобразований строк расширенной матрицы
        // также преобразуется и обратная матрица
        for (int k = i + 1; k < n; k++) {
            dev = 1.0 / matrix[i][i] * matrix[k][i];
            for (int j = i; j < n; j++) {
                matrix[k][j] -= matrix[i][j] * dev; 
                invert[k][j] -= invert[i][j] * dev; 
            }
            vector[k] -= vector[i] * dev;
        }
    }
    // проход обратным ходом метода Гаусса
    // вычисление значения вектора ответа по полученной треугольной матрице
    for (int i = n - 1; i >= 0; i--) {
        for (int k = n - 1; k > i; k--) {
            vector[i] -= matrix[i][k] * vector[k];
        }
        vector[i] = vector[i] / matrix[i][i];
    }
    cout << "Метода Гаусса - ответ:\n";
    print_vector(vector, n);
    
    
    // Вычисление определителя, Обратной матрицы и Числа обусловленности
    cout << "Определитель:\n";
    for(int i = 0; i < n; i++) { // Оставшаяся после метода Гаусса 
       // треугольная матрица упрощает вычисление определителя 
       // ее определить - произведение элементов на диагонали
        det *= matrix[i][i];
    }
    cout << det << "\n";
    cout << "Обратная:\n";
    // Преобразовывание оставшейся после метода Гаусса треугольной матрицы 
    // в единичную линейными преобразованиями. Параллельное преобразование и обратной.
    for (int i = n - 1; i > 0; i--) {
        dev = matrix[i][i];
        for (int k = n - 1; k >= 0; k--) {
            matrix[i][k] /= dev;
            invert[i][k] /= dev;
        }
        dev = matrix[i - 1][i];
        for (int k = n - 1; k >= 0; k--) {
             invert[i - 1][k] -= invert[i][k] * dev;
             matrix[i - 1][k] -= matrix[i][k] * dev;
        }
    }
    dev = matrix[0][0];
    for (int k = n - 1; k >= 0; k--) {
        matrix[0][k] /= dev;
        invert[0][k] /= dev;
    }
    print_matrix(invert, n);
    cout << "Число обусловленности:\n";
    // Вычисление нормы обратной матрицы.
    for(int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) 
            norminv += invert[i][k] * invert[i][k];
    norminv = sqrt(norminv);
    // Число обусловленности есть произведение нормы исходной матрицы и нормы обратной к ней
    cout << norminv * normmatr << "\n";
}

void gauss_full_pivot(double **matrix, double *vector, int n) 
{
    // метод Гаусса с выделением главного элемента
    double max_elem = 0; // главный элемент
    int max_index = 0; // индекс главного элемента
    double dev; // сохраняемый элемент матрицы, для упрощения вычислений
    double *swap_vector = (double *)calloc(n, sizeof(*swap_vector));// вектор перестановок столбцов в матрице 
    for(int i = 0; i < n; i++) swap_vector[i] = i;
    for (int i = 0; i < n - 1; i++) { // проход прямым ходом метода Гаусса
        for (int k = i; k < n; k++) { // поиск индекса максимального по модулю элемента в i строке 
            if (fabs(max_elem) < fabs(matrix[i][k])) {
                max_elem = matrix[i][k];
                max_index = k;
            }
        }
        // меняются местами столбцы - выбирается главный элемент
        // учитывается это и в векторе перестановок
        for (int k = 0; k < n; k++) {
            swap(matrix[k][max_index], matrix[k][i]);
        }
        swap(swap_vector[i], swap_vector[max_index]);
        // Преобразовывание матрицы: обнуление всех элементов i-го столбца после i-той строки
        // с помощью линейных преобразований строк расширенной матрицы
        for (int k = i + 1; k < n; k++) {
            dev = 1.0 / matrix[i][i] * matrix[k][i];
            for (int j = i; j < n; j++) {
                matrix[k][j] -= matrix[i][j] * dev; 
            }
            vector[k] -= vector[i] * dev;
        }
    }
    // проход обратным ходом метода Гаусса
    // вычисление значения вектора ответа по полученной треугольной матрице
    for (int i = n - 1; i >= 0; i--) {
        for (int k = n - 1; k > i; k--) {
            vector[i] -= matrix[i][k] * vector[k];
        }
        vector[i] = vector[i] / matrix[i][i];
    }
    // преобразовывание ответа с помощью накопленного вектора перестановок
    // сортировка вектора перестановок и вектора ответов
    for(int i = 0; i < n - 1; i++) {
        for(int k = i; k < n; k++) {
            if (swap_vector[i] > swap_vector[k]) {
                swap(swap_vector[i], swap_vector[k]);
                swap(vector[i], vector[k]);
            }
        }
    }
    
    cout << "Метода Гаусса c выбором главного элемента - ответ:\n";
    print_vector(vector, n);
}

int main(void)
{
    int mod; // Метод ввода матрицы
    double n; // Порядок матрицы
    double elem; // Элемент матрицы
    double **matrix; // Исходная матрица
    double *vector; // Исходный вектор
    cout << "Пожалуйста выберите метод ввода матрицы:(1) - из файла, (2) - рекурентной формулой\n";
    cin >> mod;
    if (mod == 1) {
        // Ввод матрицы и вектора из файла
        char filename[PATH_MAX] = {};
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
        // Пример 1 Варинант 5
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
    // Копирование матрицы и вектора
    double **work_matrix = duplicate_matrix(matrix, n);
    double *work_vector = duplicate_vector(vector, n);
    
    // метод Гаусса, определитель, число обусловленности, обратная матрица
    gauss(work_matrix, work_vector, n);
    // освобождение выделенной памяти    
    free_matrix(work_matrix, n);
    free(work_vector);
    
    // метод Гаусса с выбором главного элемента
    gauss_full_pivot(matrix, vector, n);
    // освобождение выделенной памяти    
    free_matrix(matrix, n);
    free(vector);
    return 0;
}