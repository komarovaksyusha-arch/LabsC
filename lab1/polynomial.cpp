#include "polynomial.h"
#include <sstream>

// Конструкторы
Polynomial::Polynomial() : a(0), b(0), c(0) {}

Polynomial::Polynomial(double a_val, double b_val, double c_val) 
    : a(a_val), b(b_val), c(c_val) {}

Polynomial::Polynomial(const Polynomial& other) 
    : a(other.a), b(other.b), c(other.c) {}

// Геттеры
double Polynomial::getA() const { 
    return a; 
}

double Polynomial::getB() const { 
    return b; 
}

double Polynomial::getC() const { 
    return c; 
}

// Сеттеры
void Polynomial::setA(double value) { 
    if (!isfinite(value)) {
        throw invalid_argument("Коэффициент a должен быть конечным числом");
    }
    a = value; 
}

void Polynomial::setB(double value) { 
    if (!isfinite(value)) {
        throw invalid_argument("Коэффициент b должен быть конечным числом");
    }
    b = value; 
}

void Polynomial::setC(double value) { 
    if (!isfinite(value)) {
        throw invalid_argument("Коэффициент c должен быть конечным числом");
    }
    c = value; 
}

// Вычисление значения
double Polynomial::calculate(double x) const {
    if (!isfinite(x)) {
        throw invalid_argument("Аргумент x должен быть конечным числом");
    }
    return a * x * x + b * x + c;
}

// Вывод на экран
void Polynomial::display() const {
    cout << getDescription() << endl;
}

// Форматирование числа
string formatNumber(double num) {
    stringstream ss;
    
    // Проверяем, целое ли число
    if (num == static_cast<int>(num)) {
        ss << static_cast<int>(num);
    } else {
        // Для дробных чисел
        ss.precision(6);
        ss << fixed << num;
        string str = ss.str();
        
        // Убираем лишние нули в конце
        size_t dot_pos = str.find('.');
        if (dot_pos != string::npos) {
            // Убираем trailing zeros
            while (str.back() == '0') {
                str.pop_back();
            }
            // Если осталась только точка, убираем её
            if (str.back() == '.') {
                str.pop_back();
            }
        }
        return str;
    }
    return ss.str();
}

// Получение строкового представления
string Polynomial::getDescription() const {
    string result;
    bool first_term = true;
    
    // Обработка коэффициента a
    if (a != 0) {
        if (a == 1) {
            result += "x^2";
        } else if (a == -1) {
            result += "-x^2";
        } else {
            result += formatNumber(a) + "x^2";
        }
        first_term = false;
    }
    
    // Обработка коэффициента b
    if (b != 0) {
        if (!first_term) {
            result += (b > 0) ? " + " : " - ";
        } else if (b < 0) {
            result += "-";
        }
        
        double abs_b = fabs(b);
        if (abs_b != 1) {
            result += formatNumber(abs_b);
        }
        result += "x";
        first_term = false;
    }
    
    // Обработка коэффициента c
    if (c != 0) {
        if (!first_term) {
            result += (c > 0) ? " + " : " - ";
        } else if (c < 0) {
            result += "-";
        }
        result += formatNumber(fabs(c));
    } else if (first_term) {
        result = "0";
    }
    
    return result;
}

// Проверка на нулевой многочлен
bool Polynomial::isZero() const {
    return a == 0 && b == 0 && c == 0;
}

// Конструкторы
PolynomialOperations::PolynomialOperations() : Polynomial() {}

PolynomialOperations::PolynomialOperations(double a_val, double b_val, double c_val) 
    : Polynomial(a_val, b_val, c_val) {}

PolynomialOperations::PolynomialOperations(const Polynomial& p) 
    : Polynomial(p) {}

// Операции
PolynomialOperations PolynomialOperations::add(const Polynomial& other) const {
    return PolynomialOperations(
        a + other.getA(),
        b + other.getB(), 
        c + other.getC()
    );
}

PolynomialOperations PolynomialOperations::subtract(const Polynomial& other) const {
    return PolynomialOperations(
        a - other.getA(),
        b - other.getB(),
        c - other.getC()
    );
}

PolynomialOperations PolynomialOperations::multiply(const Polynomial& other) const {
    double other_a = other.getA();
    double other_b = other.getB();
    double other_c = other.getC();
    
    if (other_a != 0) {
        cout << "Предупреждение: Умножение на многочлен степени 2, результат усечен до степени 2" << endl;
    }
    
    double result_a = a * other_c + b * other_b + c * other_a;
    double result_b = b * other_c + c * other_b;
    double result_c = c * other_c;
    
    return PolynomialOperations(result_a, result_b, result_c);
}