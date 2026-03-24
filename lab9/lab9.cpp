#include <cstdio>
#include <cstdlib>

double calculateProduct(double* X, int start, int end) {
    // Базовые случаи
    if (start == end) {
        // i = start + 1 (так как индексация массива с 0)
        return X[start] / (2.0 + start);  // (1 + (start + 1)) = (2 + start)
    }
    if (end - start == 1) {
        return (X[start] / (2.0 + start)) * (X[end] / (2.0 + end));
    }
    
    // Рекурсивный случай - делим пополам
    int mid = (start + end) / 2;
    return calculateProduct(X, start, mid) * calculateProduct(X, mid + 1, end);
}

int main() {
    int N;
    double* X;
    char inputFilename[256], outputFilename[256];
    
    // Ввод имен файлов
    printf("Enter input filename: ");
    scanf("%255s", inputFilename);
    
    printf("Enter output filename: ");
    scanf("%255s", outputFilename);
    
    // Открытие файлов
    FILE* inputFile = fopen(inputFilename, "r");
    FILE* outputFile = fopen(outputFilename, "w");
    
    if (!inputFile || !outputFile) {
        printf("Error opening files.\n");
        return 1;
    }
    
    // Чтение данных
    fscanf(inputFile, "%d", &N);
    X = new double[N];
    for (int i = 0; i < N; ++i) {
        fscanf(inputFile, "%lf", &X[i]);
    }
    
    // Вычисление произведения
    double product = calculateProduct(X, 0, N - 1);
    
    // Запись результата
    fprintf(outputFile, "Product: %.6lf\n", product);
    
    // Освобождение ресурсов
    delete[] X;
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}