#ifndef __GAUSS_H__
#define __GAUSS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef struct Vector_t
{
    double *vector_data;
    int size;
} Vector_t;

typedef struct Matrix_t
{
    double **matrix_data;
    int sizex;
    int sizey;
} Matrix_t;

void vdestroy (Vector_t *vector_ptr)
{
    if (vector_ptr->vector_data != NULL) {
        free (vector_ptr->vector_data);    
    }
    vector_ptr->vector_data = NULL;
    vector_ptr->size = 0;
}

void vcreate (Vector_t *vector_ptr, int sizev)
{
    vector_ptr->size = sizev;
    vector_ptr->vector_data = calloc (sizev, sizeof (double));
    memset (vector_ptr->vector_data, 0, sizeof(vector_ptr->vector_data[0])*sizev);
}

Vector_t vduplicate (Vector_t vector)
{
    Vector_t new_one;
    vcreate (&new_one, vector.size);
    
    for (int i = 0; i < vector.size; i++) {
        new_one.vector_data[i] = vector.vector_data[i];
    }
    
    return new_one;
}

void vprint (Vector_t vector, const char *comment)
{
    printf ("Vector_t:\"%s\"\n", comment);
    printf ("size: %d\n", vector.size);
    printf ("elems: {");
    if (vector.size == 0) {
        printf ("empty}\n");
        return;
    }
    printf ("%.3g", vector.vector_data[0]);
    for (int i = 1; i < vector.size; i++) {
        printf (", %.3g", vector.vector_data[i]);
    }
    printf ("}\n");
    return;    
}

void mdestroy (Matrix_t* matrix_ptr)
{
    if (matrix_ptr->matrix_data != NULL) {
        for (int i = 0; i < matrix_ptr->sizey; i++) {
            if (matrix_ptr->matrix_data[i] != NULL) {
                free (matrix_ptr->matrix_data[i]);
            }
            matrix_ptr->matrix_data[i] = NULL;
        }
    
        free (matrix_ptr->matrix_data);
    }
    
    matrix_ptr->matrix_data = NULL;
    matrix_ptr->sizex = 0;
    matrix_ptr->sizey = 0;
}

void mcreate (Matrix_t *matrix_ptr, int xsz, int ysz)
{
    matrix_ptr->sizex = xsz;
    matrix_ptr->sizey = ysz;
    
    matrix_ptr->matrix_data = calloc (xsz, sizeof(double*));
    
    for (int i = 0; i < ysz; i++) {
        matrix_ptr->matrix_data[i] = calloc (xsz, sizeof(double));
        memset (matrix_ptr->matrix_data[i], 0, sizeof (matrix_ptr->matrix_data[i][0])*xsz);
    }
}

Matrix_t mduplicate (Matrix_t matrix)
{
    Matrix_t new_one;
    
    mcreate (&new_one, matrix.sizex, matrix.sizey);
    
    for (int i = 0; i < matrix.sizey; i++) {
        for (int j = 0; j < matrix.sizex; j++) {
            new_one.matrix_data[i][j] = matrix.matrix_data[i][j];
        }
    }
    
    return new_one;
}

void mprint (Matrix_t matrix, const char *comment)
{
    printf ("Matrix_t:\"%s\"\n", comment);
    printf ("size x: %d\n", matrix.sizex);
    printf ("size y: %d\n", matrix.sizey);
    printf ("elems: {\n");
    if (matrix.sizex == 0 || matrix.sizey == 0) {
        printf ("empty\n}\n");
        return;
    }
    for (int i = 0; i < matrix.sizey; i++) {
        printf ("{%5.3g", matrix.matrix_data[i][0]);
        for (int j = 1; j < matrix.sizex; j++) {
            printf (", %5.3g", matrix.matrix_data[i][j]);
        }
        printf ("}\n");
        
    }
    printf ("}\n");
    return;    
}


void swap_rows (Matrix_t *matrix_ptr, Vector_t *vector_ptr, int ri1, int ri2)
{
    double tmp = vector_ptr->vector_data[ri1];
    vector_ptr->vector_data[ri1] = vector_ptr->vector_data[ri2];
    vector_ptr->vector_data[ri2] = tmp;
    
    
    for (int i = 0; i < matrix_ptr->sizex; i++) {
        tmp = matrix_ptr->matrix_data[ri1][i];
        matrix_ptr->matrix_data[ri1][i] = matrix_ptr->matrix_data[ri2][i];
        matrix_ptr->matrix_data[ri2][i] = tmp;
    }
}

void swap_cols (Matrix_t *matrix_ptr, int ci1, int ci2)
{
    double tmp = 0.00;
    
    for (int i = 0; i < matrix_ptr->sizex; i++) {
        tmp = matrix_ptr->matrix_data[i][ci1];
        matrix_ptr->matrix_data[i][ci1] = matrix_ptr->matrix_data[i][ci2];
        matrix_ptr->matrix_data[i][ci2] = tmp;
    }
}

int max_mrow (Matrix_t *matrix_ptr, int ri)
{
    int max_index = ri;
    for (int i = ri+1; i < matrix_ptr->sizex; i++) {
        if (abs(matrix_ptr->matrix_data[ri][i]) > abs(matrix_ptr->matrix_data[ri][max_index]) ) {
            max_index = i;
        }
    }
    
    return max_index;
}

//==========================================================

bool file_dload (const char *path, Matrix_t *mstore, Vector_t *vstore) 
{
    FILE* file = fopen (path, "r");
    if (file == NULL) {
        return 0;
    }
    
    int xsz = 0, ysz = 0;
    
    fscanf (file, "%d", &xsz);
    
    if (xsz <= 0) {
        fclose (file);
        return 0;
    }
    vcreate (vstore, xsz);
    
    for (int i = 0; i < xsz; i++) {
        fscanf (file, "%lg", &(vstore->vector_data[i]));
    }
    
    fscanf (file, "%d %d", &xsz, &ysz);
    
    if (xsz <= 0 || ysz <= 0) {
        fclose (file);
        return 0;
    }
    
    mcreate(mstore, xsz, ysz);
    
    for (int i = 0; i < ysz; i++) {
        for (int j = 0; j < xsz; j++) {
            fscanf (file, "%lg ", &(mstore->matrix_data[i][j]));
        }
    }
    
    fclose (file);
    file = NULL;
    
    return 1;
}
//=====================================================================
void normalise (Matrix_t *matrix_ptr, Vector_t *vector_ptr, int ri)
{
    double divider = matrix_ptr->matrix_data[ri][ri];
    vector_ptr->vector_data[ri] /= divider;
    
    for (int i = ri; i < matrix_ptr->sizex; i++) {
        matrix_ptr->matrix_data[ri][i] /= divider;
    }
    
}

void sub_drows (Matrix_t *matrix_ptr, Vector_t *vector_ptr, int ri)
{
    double *tmp_ptr = &(matrix_ptr->matrix_data[ri][0]);
    double multiplier = 0.00;
    for (int i = ri+1; i < matrix_ptr->sizey; i++) {
        if (!matrix_ptr->matrix_data[i][ri]) {
            continue;
        } else {
            multiplier = matrix_ptr->matrix_data[i][ri];
            vector_ptr->vector_data[i] -= multiplier * vector_ptr->vector_data[ri];
            
            for (int j = 0; j < matrix_ptr->sizex; j++) { //Can be optimised to ri
                matrix_ptr->matrix_data[i][j] -= multiplier * tmp_ptr[j]; 
            }
        }
    }
}

void sub_urows (Matrix_t *matrix_ptr, Vector_t *vector_ptr, int ri)
{
    double coeff = 0.00, vector_val = vector_ptr->vector_data[ri];
    for (int i = 0; i < ri; i++) {
        coeff = matrix_ptr->matrix_data[i][ri];
        vector_ptr->vector_data[i] -= coeff * vector_val;
        for (int j = ri; j < matrix_ptr->sizex; j++) {
            matrix_ptr->matrix_data[i][j] -= coeff * matrix_ptr->matrix_data[ri][j];
        }
    }
}

void triangulate (Matrix_t *matrix_ptr, Vector_t *vector_ptr, double *det_store)
{
    int j = 0;
    *det_store = 1.00;
    
    for (int i = 0; i < matrix_ptr->sizey; i++) {
        for (j = i; !matrix_ptr->matrix_data[j][i] && j < matrix_ptr->sizey; j++);
        
        if (j >= matrix_ptr->sizey) {
            *det_store = 0.00;
            return;
        }
        swap_rows(matrix_ptr, vector_ptr, i, j);
        *det_store *= matrix_ptr->matrix_data[i][i];
        
        normalise(matrix_ptr, vector_ptr, i);
        sub_drows(matrix_ptr, vector_ptr, i);
    }
}

Vector_t m_triangulate (Matrix_t *matrix_ptr, Vector_t *vector_ptr, double *det_store)
{
    int j = 0, max_index = 0;
    double tmp = 0.0;
    *det_store = 1.00;
    Vector_t transpositions;
    
    vcreate (&transpositions, matrix_ptr->sizex);
    for (int i = 0; i < matrix_ptr->sizex; i++) {
        transpositions.vector_data[i] = i;
    }
    
    for (int i = 0; i < matrix_ptr->sizey; i++) {
        for (j = i; !matrix_ptr->matrix_data[j][i] && j < matrix_ptr->sizey; j++);
        
        if (j >= matrix_ptr->sizey) { //Think more on logic!! With main element there is no sense in searching of non-zero item - can shift rows!!
            transpositions.size = -1;
            *det_store = 0.00;
            return transpositions;
        }
        
        max_index = max_mrow(matrix_ptr, i);
        tmp = transpositions.vector_data[i];
        transpositions.vector_data[i] = transpositions.vector_data[max_index];
        transpositions.vector_data[max_index] = tmp;
        
        swap_rows(matrix_ptr, vector_ptr, i, j);
        swap_cols(matrix_ptr, i, max_index);
        *det_store *= matrix_ptr->matrix_data[i][i];
        
        normalise(matrix_ptr, vector_ptr, i);
        sub_drows(matrix_ptr, vector_ptr, i);
    }
    
    return transpositions;
}

Vector_t get_solution (Matrix_t *matrix_ptr, Vector_t *vector_ptr)
{
    Vector_t answers;
    vcreate (&answers, matrix_ptr->sizey);
    
    for (int i = matrix_ptr->sizey-1; i >= 0; i--) {
        sub_urows(matrix_ptr, vector_ptr, i);
        answers.vector_data[i] = vector_ptr->vector_data[i];
    }
    
    return answers;
}

Vector_t reshuffle (Vector_t answers, Vector_t transpositions)
{
    Vector_t new_answers;
    vcreate(&new_answers, answers.size);
    
    for (int i = 0; i < answers.size; i++) {
        new_answers.vector_data[i] = answers.vector_data[(int)(transpositions.vector_data[i]) ];
    }
    
    return new_answers;
}
//=================================================================
Vector_t gauss_it (Matrix_t matrix, Vector_t vector, double *det_store)
{
    Matrix_t mclone = mduplicate(matrix);
    Vector_t vclone = vduplicate(vector);
    
    triangulate(&mclone, &vclone, det_store);
    if (!(*det_store)) {
        Vector_t empty;
        empty.size = 0;
        mdestroy(&mclone);
        vdestroy(&vclone);
        
        return empty;
    }
    Vector_t answers = get_solution(&mclone, &vclone);
    
    mdestroy (&mclone);
    vdestroy (&vclone);
    
    return answers;
}

Vector_t mgauss_it (Matrix_t matrix, Vector_t vector, double *det_store)
{
    Matrix_t mclone = mduplicate(matrix);
    Vector_t vclone = vduplicate(vector);
    
    Vector_t transpositions = m_triangulate(&mclone, &vclone, det_store);
    if (!(*det_store)) {
        Vector_t empty;
        empty.size = 0;
        mdestroy(&mclone);
        vdestroy(&vclone);
        vdestroy(&transpositions);
        return empty;
    }
    Vector_t my_temp_answer = get_solution (&matrix, &vector);
    Vector_t answers = reshuffle (my_temp_answer, transpositions);
    
    vdestroy (&my_temp_answer);
    vdestroy (&transpositions);
    mdestroy(&mclone);
    vdestroy(&vclone);
    
    return answers;
}

Matrix_t get_inverse (Matrix_t matrix)
{
    Matrix_t mdummy;
    Vector_t vdummy;
    double det;
    mcreate (&mdummy, matrix.sizex*2, matrix.sizey);
    vcreate (&vdummy, matrix.sizex);
    
    for (int i = 0; i < matrix.sizey; i++) {
        for (int j = 0; j < matrix.sizex; j++) {
            mdummy.matrix_data[i][j] = matrix.matrix_data[i][j];
        }
        for (int j = matrix.sizex; j < matrix.sizex * 2; j++) {
            mdummy.matrix_data[i][j] = (j != matrix.sizex+i) ? 0 : 1;
        }
    }
    
    triangulate(&mdummy, &vdummy, &det);
    
    if (!det) {
        mdummy.sizex = -1;
        mdummy.sizey = -1;
        return mdummy;
    }
    
    
    for (int i = mdummy.sizey-1; i > 0; i--) {
        sub_urows(&mdummy, &vdummy, i);
    }
    
    Matrix_t inversed;
    mcreate (&inversed, matrix.sizex, matrix.sizey);
    
    for (int i = 0; i < matrix.sizey; i++) {
        for (int j = 0; j < matrix.sizex; j++) {
            inversed.matrix_data[i][j] = mdummy.matrix_data[i][j+matrix.sizey];
        }
    }
    
    mdestroy(&mdummy);
    vdestroy(&vdummy);
    
    return inversed;
}
//===================================================================
bool gen_matrix_ex1 (Matrix_t *matrix, Vector_t *vector, int variant_num)
{
    if (variant_num < 1 || variant_num > 6) {
        return 0;
    }
    
    int n = 0, m = 0;
    int i = 0, j = 0; 
    
    switch (variant_num) {
        case 1:
            n = 40;
            m = 10;
            vcreate (vector, n);
            for (i = 1; i <= n; i++) {
                vector->vector_data[i-1] = n * i + m;
            }
            break;
            
        case 2:
            n = 20;
            m = 8;
            vcreate (vector, n);
            for (i = 1; i <= n; i++) {
                vector->vector_data[i-1] = 50 * i + 200;
            }
            break;
            
        case 3:
            n = 30;
            m = 9;
            vcreate (vector, n);
            for (i = 1; i <= n; i++) {
                vector->vector_data[i-1] = i * i - 100;
            }
            break;
            
        case 4:
            n = 50;
            m = 15;
            vcreate (vector, n);
            for (i = 1; i <= n; i++) {
                vector->vector_data[i-1] = n * m - i*i*i;
            }
            break;
            
        case 5:
            n = 30;
            m = 20;
            vcreate (vector, n);
            for (i = 1; i <= n; i++) {
                vector->vector_data[i-1] = m * i + n;
            }
            break;
            
        case 6:
            n = 25;
            m = 10;
            vcreate (vector, n);
            for (i = 1; i <= n; i++) {
                vector->vector_data[i-1] = i*i - n;
            }
            break;
        
        default:
            return 0;
    }
    
    mcreate(matrix, n, n);
    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i != j) {
                matrix->matrix_data[i-1][j-1] = (double)(i+j)/(m+n);
            } else {
                matrix->matrix_data[i-1][j-1] = n + m*m + (double)j/m + (double)i/n;
            }
        }
    }
    
    return 1;
}

#endif //__GAUSS_H__