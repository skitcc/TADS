#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *A;   // Ненулевые элементы
    int *JA;  // Индексы столбцов ненулевых элементов
    int *IA;  // Индексы начала строк
    int rows; // Количество строк
    int cols; // Количество столбцов
    int nnz;  // Количество ненулевых элементов
} CSRMatrix;

typedef struct {
    CSRMatrix matrix;
    int error_code;
} CSRMatrixResult;

typedef struct {
    int rows;      // Количество строк
    int cols;      // Количество столбцов
    int percent;   // Процент заполнения
} MatrixParams;


 #endif
