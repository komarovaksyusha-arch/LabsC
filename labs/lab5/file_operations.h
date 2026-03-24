#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Объявление структуры FILE из стандартной библиотеки C
struct _iobuf;
typedef struct _iobuf FILE;

// Прототипы функций
int readMatrixSize(FILE* file, int* rows, int* cols);
double** readMatrix(FILE* file, int rows, int cols);
void writeResults(FILE* file, double* X, int size, double** matrix, int rows, int cols);
void freeMatrix(double** matrix, int rows);

#endif