#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int n;
double a, b;
double eps;
int k1 = 0, k2 = 0;

double func1(double x);
double func2(double x);
double bisection_method(double a, double b, int* k, double (*func)(double), double eps);
double secant_method(double a, double b, int* k, double (*func)(double), double eps);
void print_table(double (*func)(double), const char* func_name, double a, double b, int n);

int main() {
    printf("Значение A (0 < A < 2): ");
    while (scanf("%lf", &a) != 1 || a <= 0 || a >= 2) {
        printf("Ошибка! Введите A снова (0 < A < 2): ");
        while (getchar() != '\n');
    }

    printf("Значение B (%.6f < B < 2): ", a);
    while (scanf("%lf", &b) != 1 || b <= a || b >= 2) {
        printf("Ошибка! Введите B снова (%.6f < B < 2): ", a);
        while (getchar() != '\n');
    }

    printf("Значение N (1 <= N <= 10): ");
    while (scanf("%d", &n) != 1 || n < 1 || n > 10) {
        printf("Ошибка! Введите N снова (1 <= N <= 10): ");
        while (getchar() != '\n');
    }

    print_table(func1, "(sqrt7(x) - ln(x+0.3))/(sqrt(x+1)) - x", a, b, n);
    print_table(func2, "sqrt(sqrt3(e^x) - (6/7)x·sin(x) - 0.3) - x", a, b, n);

    return 0;
}

double func1(double x) {
    if (x <= -0.3 || x < 0) return NAN;
    double numerator = pow(x, 1.0/7.0) - log(x + 0.3);
    double denominator = sqrt(x + 1.0);
    if (fabs(denominator) < 1e-15) return NAN;
    return (numerator / denominator)-x;
}

double func2(double x) {
    double sqrt_arg = pow(exp(x), 1.0/3.0) - (6.0/7.0)*x*sin(x) - 0.3;
    if (sqrt_arg < 0) return NAN;
    return sqrt(sqrt_arg) - x;
}

double bisection_method(double a, double b, int* k, double (*func)(double), double eps) {
    double fa = func(a), fb = func(b);
    *k = 0;
    if (isnan(fa) || isnan(fb)) return NAN;
    
    while (fabs(b - a) > eps && *k < 1000) {
        double c = (a + b)/2.0;
        double fc = func(c);
        if (isnan(fc)) return NAN;
        if (fc * fa < 0) { b = c; fb = fc; }
        else { a = c; fa = fc; }
        (*k)++;
    }
    return (a + b)/2.0;
}

double secant_method(double a, double b, int* k, double (*func)(double), double eps) {
    double x0 = a, x1 = b, f0 = func(x0), f1 = func(x1);
    *k = 0;
    if (isnan(f0) || isnan(f1)) return NAN;
    
    while (fabs(x1 - x0) > eps && *k < 1000) {
        if (fabs(f1 - f0) < 1e-15) break;
        double x2 = x1 - f1*(x1 - x0)/(f1 - f0);
        if (x2 < a || x2 > b) x2 = (a + b)/2.0;
        double f2 = func(x2);
        if (isnan(f2)) return NAN;
        x0 = x1; x1 = x2; f0 = f1; f1 = f2;
        (*k)++;
    }
    return x1;
}

void print_table(double (*func)(double), const char* func_name, double a, double b, int n) {
    if (func(a) * func(b) > 0) {
        printf("\nФункция %s не имеет корня на отрезке [%.2f, %.2f]\n", func_name, a, b);
        return;
    }

    printf("\nФункция: %s\n", func_name);
    printf("Погрешность\tМетод бисекции (Корень\tИтераций)\tМетод секущих (Корень\tИтераций)\n");
    printf("------------\t-----------------------\t----------\t----------------------\t----------\n");

    for (int i = 1; i <= n; i++) {
        eps = pow(10, -i);
        double r1 = bisection_method(a, b, &k1, func, eps);
        double r2 = secant_method(a, b, &k2, func, eps);
        
        printf("%-12.*f\t", i, eps);
        
        if (isnan(r1)) {
            printf("Нет корня\t\t-\t\t");
        } else {
            printf("%-23.*f\t%-10d\t", i, r1, k1);
        }
        
        if (isnan(r2)) {
            printf("Нет корня\t\t-\n");
        } else {
            printf("%-22.*f\t%-10d\n", i, r2, k2);
        }
    }
    printf("\n");
}