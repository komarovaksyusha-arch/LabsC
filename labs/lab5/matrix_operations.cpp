#include "matrix_operations.h"

double calculateLastColumnSum(double** matrix, int rows, int cols) {
    double sum = 0.0;
    for (int i = 0; i < rows; i++) {
        sum += matrix[i][cols - 1];
    }
    return sum;
}

double calculateRowAverage(double* row, int cols) {
    double sum = 0.0;
    for (int j = 0; j < cols; j++) {
        sum += row[j];
    }
    return sum / cols;
}

void processMatrix(double** matrix, int rows, int cols, double* X) {
    double lastColSum = calculateLastColumnSum(matrix, rows, cols);
    
    if (lastColSum > 0) {
        for (int i = 0; i < rows; i++) {
            X[i] = calculateRowAverage(matrix[i], cols);
        }
    }
}