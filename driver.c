#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matmul.c"


void read_matrix(const char *filename, int ***matrix, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    
    fscanf(file, "%d %d", rows, cols);

    *matrix = malloc(*rows * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = malloc(*cols * sizeof(int));
    }

    
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &((*matrix)[i][j]));
        }
    }

    fclose(file);
}


int compare_matrices(int **A, int **B, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (A[i][j] != B[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}


void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    const char *unit_test_folder = "Unit_test/unit_1"; 
    char path_A[100], path_B[100], path_C[100];
    sprintf(path_A, "%s/A.txt", unit_test_folder);
    sprintf(path_B, "%s/B.txt", unit_test_folder);
    sprintf(path_C, "%s/C.txt", unit_test_folder);

    int **A, **B, **C, **Result;
    int rows_A, cols_A, rows_B, cols_B, rows_C, cols_C;

   
    read_matrix(path_A, &A, &rows_A, &cols_A);
    read_matrix(path_B, &B, &rows_B, &cols_B);
    read_matrix(path_C, &C, &rows_C, &cols_C);

    
    if (cols_A != rows_B || rows_A != rows_C || cols_B != cols_C) {
        printf("Failed\n");
        free_matrix(A, rows_A);
        free_matrix(B, rows_B);
        free_matrix(C, rows_C);
        exit(EXIT_FAILURE);
    }

    
    Result = malloc(rows_A * sizeof(int *));
    for (int i = 0; i < rows_A; i++) {
        Result[i] = malloc(cols_B * sizeof(int));
    }

   
    matrix_multiply_ijk(A, B, Result, rows_A, cols_A, cols_B);

    
    if (compare_matrices(Result, C, rows_C, cols_C)) {
        printf("Matrix multiplication successful!\n");
    } else {
        printf("Matrix multiplication failed!\n");
    }

    
    free_matrix(A, rows_A);
    free_matrix(B, rows_B);
    free_matrix(C, rows_C);
    free_matrix(Result, rows_A);

    return 0;
}
