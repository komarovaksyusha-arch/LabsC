#include <iostream>
using namespace std;

class Integer {
private:
    int value;  // Приватное поле - здесь хранится само число

public:

    Integer() : value(0) {}
    
    Integer(int val) : value(val) {}
    
    int getValue() const { return value; }
    
    void setValue(int val) { value = val; }
    
    Integer& operator--() {
        --value;        // Уменьшаем value на 1
        return *this;   // Возвращаем сам объект (this - указатель на текущий объект)
    }
    
    Integer operator--(int) {
        Integer temp = *this;   // Сохраняем копию текущего объекта (старое значение)
        --value;                // Уменьшаем value текущего объекта
        return temp;            // Возвращаем копию (старое значение)
    }
    
    // Дружественная функция для префиксного ++
    friend Integer& operator++(Integer& obj);
    
    // Дружественная функция для постфиксного ++  
    friend Integer operator++(Integer& obj, int);
    
    // Дружественная функция для оператора + (сложение двух Integer)
    friend Integer operator+(const Integer& i1, const Integer& i2);
    
    void input() {
        cout << "Введите целое число: ";
        cin >> value;
        // Очистка буфера ввода на случай, если пользователь ввел не число
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    void display() const {
        cout << "Value: " << value << endl;
    }
};

// РЕАЛИЗАЦИЯ ДРУЖЕСТВЕННЫХ ФУНКЦИЙ (вне класса)

// Дружественная функция для префиксного ++ (++a)
Integer& operator++(Integer& obj) {
    ++obj.value;    // Увеличиваем value переданного объекта
    return obj;     // Возвращаем измененный объект
}

// Дружественная функция для постфиксного ++ (a++)
Integer operator++(Integer& obj, int) {
    Integer temp = obj; // Сохраняем копию объекта (старое значение)
    ++obj.value;        // Увеличиваем value оригинального объекта
    return temp;        // Возвращаем копию (старое значение)
}

// Дружественная функция для сложения двух объектов Integer
Integer operator+(const Integer& i1, const Integer& i2) {
    // Создаем новый объект с value = (i1.value + i2.value)
    return Integer(i1.value + i2.value);
}

// ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА INTEGER
void demoInteger() {
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ С КЛАССОМ INTEGER ===" << endl;
    
    Integer a(10);
    cout << "Исходное значение a: ";
    a.display();  
    
    // Используем префиксный -- 
    --a;  // Вызывается a.operator--()
    cout << "После --a (префиксный): ";
    a.display();  // Выведет: Value: 9
    
    // Используем постфиксный -- 
    Integer b = a--;  // Вызывается a.operator--(0)
    cout << "После a-- (постфиксный): " << endl;
    cout << "Значение a: ";
    a.display();  
    cout << "Значение b (возвращенное значение): ";
    b.display();  
    
    // Использование оператора ++ (дружественная функция)
    Integer c(5);
    cout << "\nИсходное значение c: ";
    c.display();  
    
    // Префиксный ++ (дружественная функция)
    ++c;  // Вызывается operator++(c)
    cout << "После ++c (префиксный): ";
    c.display();  
    
    // Постфиксный ++ (дружественная функция)
    Integer d = c++;  // Вызывается operator++
    cout << "После c++ (постфиксный): " << endl;
    cout << "Значение c: ";
    c.display();  
    cout << "Значение d (возвращенное значение): ";
    d.display();  
    
    cout << "=========================================" << endl << endl;
}

// КЛАСС ВЕЩЕСТВЕННЫХ ЧИСЕЛ (DOUBLE)
class Double {
private:
    double value;

public:

    Double() : value(0.0) {}

    Double(double val) : value(val) {}

    double getValue() const { return value; }

    void setValue(double val) { value = val; }

    Double operator-(const Double& other) const {
        return Double(value - other.value);
    }
    
    // ОБЪЯВЛЕНИЕ ДРУЖЕСТВЕННОЙ ФУНКЦИИ
    
    // Дружественная функция для оператора +
    friend Double operator+(const Double& d1, const Double& d2);
    
    // МЕТОД ДЛЯ ВВОДА ДАННЫХ С КЛАВИАТУРЫ
    void input() {
        cout << "Введите вещественное число: ";
        cin >> value;
        // Очистка буфера ввода на случай ошибок
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    // Метод для вывода значения
    void display() const {
        cout << "Value: " << value << endl;
    }
};

// РЕАЛИЗАЦИЯ ДРУЖЕСТВЕННОЙ ФУНКЦИИ +

// Дружественная функция для сложения двух объектов Double
Double operator+(const Double& d1, const Double& d2) {
    // Создаем новый объект с value = (d1.value + d2.value)
    return Double(d1.value + d2.value);
}

// ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА DOUBLE
void demoDouble() {
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ С КЛАССОМ DOUBLE ===" << endl;
    
    Double x(15.5), y(7.3);
    cout << "Исходные значения:" << endl;
    cout << "x = "; x.display(); 
    cout << "y = "; y.display();  

    Double z1 = x - y;
    cout << "\nРезультат x - y (функция-член): ";
    z1.display();  

    Double z2 = x + y;
    cout << "Результат x + y (дружественная функция): ";
    z2.display();  // Выведет: Value: 22.8
    
    // Демонстрация цепочки операций
    Double a(10.0), b(5.0), c(3.0);
    cout << "\nЦепочка операций:" << endl;
    cout << "a = "; a.display();  
    cout << "b = "; b.display();   
    cout << "c = "; c.display();  
    
    Double result = a + b - c;
    cout << "Результат a + b - c: ";
    result.display();  
    
    cout << "=======================================" << endl;
}

// ФУНКЦИЯ ДЛЯ ДЕМОНСТРАЦИИ ВВОДА ДАННЫХ С КЛАВИАТУРЫ
void demoInput() {
    cout << "\n=== ДЕМОНСТРАЦИЯ ВВОДА ДАННЫХ С КЛАВИАТУРЫ ===" << endl;
    
    // Демонстрация для класса Integer
    cout << "\n--- РАБОТА С КЛАССОМ INTEGER ---" << endl;
    
    Integer num1, num2;
    
    cout << "Введите данные для первого целого числа:" << endl;
    num1.input(); 
    
    cout << "Введите данные для второго целого числа:" << endl;
    num2.input();  
    
    cout << "\nВведенные числа:" << endl;
    cout << "num1 = "; num1.display();
    cout << "num2 = "; num2.display();
    
    // Демонстрация операций с введенными числами
    cout << "\nОперации с введенными числами:" << endl;
    
    ++num1;
    cout << "После ++num1: "; num1.display();
    
    --num2;
    cout << "После --num2: "; num2.display();

    Integer sum = num1 + num2;
    cout << "Сумма num1 + num2: "; sum.display();
    
    // Демонстрация для класса Double
    cout << "\n--- РАБОТА С КЛАССОМ DOUBLE ---" << endl;
    
    Double d1, d2;
    
    cout << "Введите данные для первого вещественного числа:" << endl;
    d1.input(); 
    
    cout << "Введите данные для второго вещественного числа:" << endl;
    d2.input(); 
    
    cout << "\nВведенные числа:" << endl;
    cout << "d1 = "; d1.display();
    cout << "d2 = "; d2.display();
    
    // Демонстрация операций с введенными числами
    cout << "\nОперации с введенными числами:" << endl;
    
    Double addition = d1 + d2;
    cout << "Сумма d1 + d2: "; addition.display();
    
    Double subtraction = d1 - d2;
    cout << "Разность d1 - d2: "; subtraction.display();
    
    cout << "=============================================" << endl;
}

// ФУНКЦИЯ ДЛЯ ИНТЕРАКТИВНОГО ВВОДА И ВЫЧИСЛЕНИЙ
void interactiveDemo() {
    cout << "\n=== ИНТЕРАКТИВНАЯ ДЕМОНСТРАЦИЯ ===" << endl;
    
    int choice;
    do {
        cout << "\nВыберите операцию:" << endl;
        cout << "1 - Работа с целыми числами" << endl;
        cout << "2 - Работа с вещественными числами" << endl;
        cout << "3 - Сравнение разных операций" << endl;
        cout << "0 - Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                // Работа с целыми числами
                Integer a, b;
                cout << "\n--- Ввод двух целых чисел ---" << endl;
                a.input();
                b.input();
                
                cout << "\nРезультаты операций:" << endl;
                cout << "a = "; a.display();
                cout << "b = "; b.display();
                
                // Префиксные операции
                ++a;
                cout << "После ++a: "; a.display();
                
                --b;
                cout << "После --b: "; b.display();
                
                // Постфиксные операции
                Integer c = a++;
                cout << "После a++: a = "; a.display();
                cout << "Возвращенное значение: "; c.display();
                
                Integer d = b--;
                cout << "После b--: b = "; b.display();
                cout << "Возвращенное значение: "; d.display();
                
                // Сложение - ТЕПЕРЬ РАБОТАЕТ
                Integer sum = a + b;
                cout << "Сумма a + b: "; sum.display();
                
                break;
            }
            case 2: {
                // Работа с вещественными числами
                Double x, y;
                cout << "\n--- Ввод двух вещественных чисел ---" << endl;
                x.input();
                y.input();
                
                cout << "\nРезультаты операций:" << endl;
                cout << "x = "; x.display();
                cout << "y = "; y.display();
                
                Double sum = x + y;
                cout << "Сумма x + y: "; sum.display();
                
                Double diff = x - y;
                cout << "Разность x - y: "; diff.display();
                
                // Цепочка операций
                Double result = x + y - Double(2.5);
                cout << "Цепочка: x + y - 2.5 = "; result.display();
                
                break;
            }
            case 3: {
                // Сравнение разных типов операций
                cout << "\n--- Сравнение префиксных и постфиксных операций ---" << endl;
                
                Integer num;
                cout << "Введите целое число для демонстрации: ";
                num.input();
                
                cout << "\nИсходное число: "; num.display();
                
                // Префиксный инкремент
                Integer prefixResult = ++num;
                cout << "После prefixResult = ++num:" << endl;
                cout << "num = "; num.display();
                cout << "prefixResult = "; prefixResult.display();
                
                // Возвращаем исходное значение
                num.setValue(prefixResult.getValue() - 1);
                cout << "\nВосстановили исходное значение: "; num.display();
                
                // Постфиксный инкремент
                Integer postfixResult = num++;
                cout << "После postfixResult = num++:" << endl;
                cout << "num = "; num.display();
                cout << "postfixResult = "; postfixResult.display();
                
                cout << "\nВЫВОД: Префиксный оператор возвращает измененное значение," << endl;
                cout << "       Постфиксный оператор возвращает исходное значение" << endl;
                
                break;
            }
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
        
        // Очистка буфера ввода
        cin.clear();
        cin.ignore(10000, '\n');
        
    } while (choice != 0);
}

// ГЛАВНАЯ ФУНКЦИЯ ПРОГРАММЫ
int main() {
    // Демонстрация работы с классом Integer (унарные операторы)
    demoInteger();
    
    // Демонстрация работы с классом Double (бинарные операторы)
    demoDouble();
    
    // Демонстрация ввода данных с клавиатуры
    demoInput();
    
    // Интерактивная демонстрация
    interactiveDemo();
    
    // Дополнительная демонстрация с пользовательским вводом
    cout << "\n=== ДОПОЛНИТЕЛЬНАЯ ДЕМОНСТРАЦИЯ ===" << endl;
    
    // Работа с Integer
    Integer num1(20);
    cout << "Создан Integer num1 = 20" << endl;
    num1.display(); 
    
    cout << "Применяем ++num1: ";
    ++num1;  // Префиксный инкремент
    num1.display();  
    
    cout << "Применяем num1--: ";
    num1--;  // Постфиксный декремент
    num1.display(); 
    
    // Работа с Double
    Double num2(12.7), num3(4.2);
    cout << "\nСозданы Double num2 = 12.7, num3 = 4.2" << endl;
    
    // Сложение
    Double sum = num2 + num3; 
    cout << "Сумма: "; 
    sum.display(); 
    
    // Вычитание  
    Double diff = num2 - num3; 
    cout << "Разность: "; 
    diff.display();  
    
    return 0;  
}