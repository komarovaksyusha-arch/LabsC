#include "polynomial.h"


void demonstrateBaseClass() {
    cout << "=== ДЕМОНСТРАЦИЯ БАЗОВОГО КЛАССА POLYNOMIAL ===" << endl << endl;
    
    try {
        cout << "1. Создание многочленов:" << endl;
        Polynomial p1;
        Polynomial p2(2, -3, 1);
        Polynomial p3(0, 4, -2);
        Polynomial p4(-1, 0, 5);
        
        cout << "p1 (по умолчанию): "; p1.display();
        cout << "p2(2, -3, 1): "; p2.display();
        cout << "p3(0, 4, -2): "; p3.display();
        cout << "p4(-1, 0, 5): "; p4.display();
        cout << endl;
        
        cout << "2. Работа со свойствами:" << endl;
        p1.setA(1);
        p1.setB(-2);
        p1.setC(3);
        cout << "После установки свойств p1: "; p1.display();
        cout << "p1.getA() = " << p1.getA() << endl;
        cout << "p1.getB() = " << p1.getB() << endl;
        cout << "p1.getC() = " << p1.getC() << endl;
        cout << endl;
        
        cout << "3. Вычисление значений:" << endl;
        cout << "p2(2, -3, 1) при x = 0: " << p2.calculate(0) << endl;
        cout << "p2(2, -3, 1) при x = 1: " << p2.calculate(1) << endl;
        cout << "p2(2, -3, 1) при x = 2: " << p2.calculate(2) << endl;
        cout << endl;
        
        cout << "4. Обработка ошибок:" << endl;
        try {
            p1.setA(numeric_limits<double>::infinity());
        } catch (const invalid_argument& e) {
            cout << "Поймано исключение: " << e.what() << endl;
        }
        
        try {
            p1.calculate(numeric_limits<double>::quiet_NaN());
        } catch (const invalid_argument& e) {
            cout << "Поймано исключение: " << e.what() << endl;
        }
        cout << endl;
        
    } catch (const exception& e) {
        cerr << "Неожиданная ошибка: " << e.what() << endl;
    }
}

void demonstrateDerivedClass() {
    cout << "=== ДЕМОНСТРАЦИЯ ДОЧЕРНЕГО КЛАССА POLYNOMIALOPERATIONS ===" << endl << endl;
    
    try {
        cout << "1. Исходные многочлены:" << endl;
        PolynomialOperations poly1(2, -3, 1);
        PolynomialOperations poly2(1, 2, -1);
        PolynomialOperations poly3(0, 1, 2);
        
        cout << "poly1: "; poly1.display();
        cout << "poly2: "; poly2.display();
        cout << "poly3: "; poly3.display();
        cout << endl;
        
        cout << "2. Операции с многочленами:" << endl;
        
        // Сложение
        PolynomialOperations sum = poly1.add(poly2);
        cout << "Сложение: "; 
        poly1.display(); 
        cout << " + "; 
        poly2.display();
        cout << " = "; 
        sum.display();
        cout << endl;
        
        // Вычитание
        PolynomialOperations diff = poly1.subtract(poly2);
        cout << "Вычитание: ";
        poly1.display();
        cout << " - ";
        poly2.display();
        cout << " = ";
        diff.display();
        cout << endl;
        
        // Умножение
        PolynomialOperations product = poly1.multiply(poly3);
        cout << "Умножение: ";
        poly1.display();
        cout << " * ";
        poly3.display();
        cout << " = ";
        product.display();
        cout << endl;
        
        // Проверка вычислений
        cout << "3. Проверка вычислений:" << endl;
        double x = 2;
        cout << "При x = " << x << ":" << endl;
        cout << "poly1(x) = " << poly1.calculate(x) << endl;
        cout << "poly2(x) = " << poly2.calculate(x) << endl;
        cout << "Сумма poly1(x) + poly2(x) = " << (poly1.calculate(x) + poly2.calculate(x)) << endl;
        cout << "Сумма многочленов sum(x) = " << sum.calculate(x) << endl;
        cout << "Результаты совпадают: " << 
            (sum.calculate(x) == poly1.calculate(x) + poly2.calculate(x)) << endl;
        
    } catch (const exception& e) {
        cerr << "Неожиданная ошибка: " << e.what() << endl;
    }
}

void demonstrateUserInput() {
    cout << "=== ДЕМОНСТРАЦИЯ ВВОДА ДАННЫХ С КЛАВИАТУРЫ ===" << endl << endl;
    
    try {
        double a, b, c, x;
        
        cout << "Введите коэффициенты первого многочлена (a b c): ";
        cin >> a >> b >> c;
        Polynomial poly1(a, b, c);
        cout << "Первый многочлен: "; 
        poly1.display();
        
        cout << "Введите коэффициенты второго многочлена (a b c): ";
        cin >> a >> b >> c;
        Polynomial poly2(a, b, c);
        cout << "Второй многочлен: "; 
        poly2.display();
        
        PolynomialOperations op1(poly1);
        PolynomialOperations op2(poly2);
        
        cout << endl << "Результаты операций:" << endl;
        cout << "Сумма: "; 
        op1.add(op2).display();
        
        cout << "Разность: "; 
        op1.subtract(op2).display();
        
        cout << "Произведение: "; 
        op1.multiply(op2).display();
        
        cout << endl << "Введите значение x для вычисления: ";
        cin >> x;
        
        cout << "Значения многочленов при x = " << x << ":" << endl;
        cout << "Первый многочлен: " << poly1.calculate(x) << endl;
        cout << "Второй многочлен: " << poly2.calculate(x) << endl;
        cout << "Сумма многочленов: " << op1.add(op2).calculate(x) << endl;
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

int main() {
    
    cout << "ПРОГРАММА ДЛЯ РАБОТЫ С МНОГОЧЛЕНАМИ" << endl;
    cout << "=====================================" << endl << endl;
    
    demonstrateBaseClass();
    demonstrateDerivedClass();
    demonstrateUserInput();
    
    cout << endl << "=== ПРОГРАММА ЗАВЕРШЕНА ===" << endl;
    
    return 0;
}