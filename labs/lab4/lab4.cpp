#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

const double xx[7] = {-0.98, -0.5, 0.1, 0.5, 0.95};

// Функция для вычисления контрольной формулы
double control_formula(double x) {
    return 1.0 + (x/2.0)*sin(x) + (x*x/2.0 - 1.0)*cos(x);
}

int main() {
    int n, i, k;
    double e, current_term, sum, f, *x;
    
    SetConsoleOutputCP(1251);
    srand((unsigned int)GetTickCount());

    // Ввод точности
    printf("Введите точность e (0 < e < 0.1): ");
    scanf("%lf", &e);
    if (e <= 0 || e >= 0.1) {  // Исправлено: добавлен оператор ||
        printf("Некорректная точность! Должно быть: 0 < e < 0.1\nНажмите любую клавишу");
        getch();
        return 1;
    }
    fflush(stdin);

    // Ввод количества точек
    printf("Введите количество точек n (1-20): ");
    scanf("%d", &n);
    if (n < 1 || n > 20) {  // Исправлено: добавлен оператор ||
        printf("Некорректное количество! Должно быть: 1 <= n <= 20\nНажмите любую клавишу");
        getch();
        return 1;
    }
    fflush(stdin);

    // Выделение памяти
    x = (double*)malloc(n * sizeof(double));
    if (x == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    // Ввод значений X
    printf("Введите %d значений X из интервала (-1, +1):\n", n);
    for (i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
        
        if (fabs(x[i]) >= 1) {
            x[i] = xx[rand() % 7];
            printf("Некорректное значение заменено на %15.10lf\n", x[i]);
        }
    }

    // Определение точности вывода
    int precision = (int)fabs(log10(e)) + 1;
    
    // Вывод заголовка таблицы
    printf("\nТочность e = %.*lf\n", precision, e);
    printf("+----+----------------+----------------+---+----------------+-------------------+\n");
    printf("| №  |       X        |     Sum(X)     | K |      F(X)      |   |Sum(X)-F(X)|   |\n");
    printf("+----+----------------+----------------+---+----------------+-------------------+\n");

    // Вычисление и вывод результатов для каждого X
    for (i = 0; i < n; i++) {
        double x_squared = x[i] * x[i];
        sum = 0.0;
        k = 0;
        
        // Инициализация рекуррентного соотношения
        // Первый член ряда (i=1): (2*1? + 1)/2! * x? = 3/2 * x?
        current_term = (3.0/2.0) * x_squared;
        sum = current_term;
        k = 1;
        
        // Вычисление последующих членов рекуррентно
        for (int m = 2; ; m++) {
            // Исправленное рекуррентное соотношение:
            // a_m = a_{m-1} * [-x? * (2m? + 1)] / [(2m)(2m-1)(2(m-1)? + 1)]
            double denominator_part = 2*(m-1)*(m-1) + 1;  // 2(i-1)? + 1
            double factor = -x_squared * (2*m*m + 1) / ((2*m)*(2*m-1)*denominator_part);
            current_term *= factor;
            
            sum += current_term;
            k++;
            
            // Проверка точности и защита от бесконечного цикла
            if (fabs(current_term) < e || k >= 500) {
                break;
            }
        }

        // Вычисление контрольной формулы
        f = control_formula(x[i]);
        
        // Вывод строки результатов
        printf("| %2d | %14.*lf | %14.*lf | %2d | %14.*lf | %17.*lf |\n",
               i+1, precision, x[i], precision, sum, k, precision, f, precision+2, fabs(sum - f));
    }

    printf("+----+----------------+----------------+---+----------------+-------------------+\n");
    printf("Нажмите любую клавишу для выхода");
    
    free(x);
    getch();
    return 0;
}