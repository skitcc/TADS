#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *A;  
    int *JA;  
    int *IA;  
    int rows; 
    int cols; 
    int nnz;  
} CSRMatrix;

typedef struct {
    CSRMatrix matrix;
    int error_code;
} CSRMatrixResult;

typedef struct {
    int rows;      
    int cols;      
    int percent;   
} MatrixParams;


 #endif
