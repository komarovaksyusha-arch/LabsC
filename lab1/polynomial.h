#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;

class Polynomial {
protected:
    double a, b, c;

public:
    // Конструкторы
    Polynomial();
    Polynomial(double a_val, double b_val, double c_val);
    Polynomial(const Polynomial& other);

    // Свойства
    double getA() const;
    void setA(double value);
    double getB() const;
    void setB(double value);
    double getC() const;
    void setC(double value);

    // Методы
    double calculate(double x) const;
    void display() const;
    string getDescription() const;
    bool isZero() const;
    
    virtual ~Polynomial() = default;
};

class PolynomialOperations : public Polynomial {
public:
    // Конструкторы
    PolynomialOperations();
    PolynomialOperations(double a_val, double b_val, double c_val);
    PolynomialOperations(const Polynomial& p);
    
    // Операции
    PolynomialOperations add(const Polynomial& other) const;
    PolynomialOperations subtract(const Polynomial& other) const;
    PolynomialOperations multiply(const Polynomial& other) const;
};

#endif