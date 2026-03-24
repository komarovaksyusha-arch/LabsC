#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "file_operations.h"
#include "matrix_operations.h"

// Максимальная длина пути к файлу
#define MAX_PATH_LENGTH 256

int main() {
    char inputPath[MAX_PATH_LENGTH];
    char outputPath[MAX_PATH_LENGTH];
    
    // 1. Запрос путей к файлам
    printf("Введите путь к входному файлу: ");
    if (!fgets(inputPath, MAX_PATH_LENGTH, stdin)) {
        printf("Ошибка чтения пути!\n");
        return 1;
    }
    // Удаляем символ новой строки
    inputPath[strcspn(inputPath, "\n")] = '\0';
    
    printf("Введите путь к выходному файлу: ");
    if (!fgets(outputPath, MAX_PATH_LENGTH, stdin)) {
        printf("Ошибка чтения пути!\n");
        return 1;
    }
    outputPath[strcspn(outputPath, "\n")] = '\0';

    // 2. Открытие входного файла
    FILE* inputFile = fopen(inputPath, "r");
    if (!inputFile) {
        printf("Ошибка: не могу открыть файл %s\n", inputPath);
        return 1;
    }
    
    // 3. Открытие выходного файла
    FILE* outputFile = fopen(outputPath, "w");
    if (!outputFile) {
        printf("Ошибка: не могу создать файл %s\n", outputPath);
        printf("Проверьте:\n");
        printf("1. Существует ли папка назначения\n");
        printf("2. Есть ли права на запись\n");
        printf("3. Корректность имени файла\n");
        fclose(inputFile);
        return 1;
    }
    
    // 4. Чтение размеров матрицы
    int N, M;
    if (!readMatrixSize(inputFile, &N, &M)) {
        printf("Ошибка чтения размеров матрицы!\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }
    
    // 5. Чтение матрицы
    double** matrix = readMatrix(inputFile, N, M);
    fclose(inputFile);
    
    // 6. Создание результирующего массива
    double* X = (double*)malloc(N * sizeof(double));
    if (!X) {
        printf("Ошибка выделения памяти!\n");
        freeMatrix(matrix, N);
        fclose(outputFile);
        return 1;
    }
    
    // 7. Обработка матрицы
    processMatrix(matrix, N, M, X);
    
    // 8. Запись результатов
    writeResults(outputFile, X, N, matrix, N, M);
    
    // 9. Освобождение ресурсов
    free(X);
    freeMatrix(matrix, N);
    fclose(outputFile);
    
    printf("Программа успешно завершена. Результаты сохранены в %s\n", outputPath);
    return 0;
}