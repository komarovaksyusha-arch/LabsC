#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

struct Term {
    double coefficient;
    int exponent;
};

vector<Term> parsePolynomial(const string &polyStr) {
    vector<Term> terms;
    stringstream ss(polyStr);
    string termStr;
    char op = '+'; // Первый член считается положительным

    // Удаляем все пробелы из строки
    string cleanStr;
    for (char c : polyStr) {
        if (!isspace(c)) cleanStr += c;
    }

    ss.str(cleanStr);
    ss.clear();

    size_t pos = 0;
    while (pos < cleanStr.length()) {
        // Определяем знак текущего члена
        if (cleanStr[pos] == '+' || cleanStr[pos] == '-') {
            op = cleanStr[pos];
            pos++;
        }

        // Извлекаем коэффициент
        size_t x_pos = cleanStr.find('x', pos);
        double coeff = 1.0;
        if (x_pos != string::npos && x_pos > pos) {
            string coeffStr = cleanStr.substr(pos, x_pos - pos);
            if (coeffStr == "+") coeff = 1.0;
            else if (coeffStr == "-") coeff = -1.0;
            else coeff = stod(coeffStr);
        } else if (x_pos == string::npos) {
            // Константный член
            string coeffStr = cleanStr.substr(pos);
            coeff = stod(coeffStr);
            terms.push_back({op == '+' ? coeff : -coeff, 0});
            break;
        } else {
            // Коэффициент 1 или -1
            coeff = (op == '+') ? 1.0 : -1.0;
        }

        // Обрабатываем степень
        int exp = 1;
        if (x_pos != string::npos) {
            if (x_pos + 1 < cleanStr.length() && cleanStr[x_pos + 1] == '^') {
                size_t exp_end = cleanStr.find_first_of("+-", x_pos + 2);
                string expStr = cleanStr.substr(x_pos + 2, exp_end - (x_pos + 2));
                exp = stoi(expStr);
                pos = exp_end;
            } else {
                pos = x_pos + 1;
            }
        }

        terms.push_back({coeff, exp});
    }

    return terms;
}

string computeDerivative(const vector<Term> &terms) {
    stringstream result;
    bool firstTerm = true;

    for (const Term &term : terms) {
        if (term.exponent == 0) continue; // Пропускаем константы

        double newCoeff = term.coefficient * term.exponent;
        int newExp = term.exponent - 1;

        if (!firstTerm && newCoeff > 0) {
            result << " + ";
        } else if (newCoeff < 0) {
            result << " - ";
            newCoeff = -newCoeff;
        }

        if (newExp == 0) {
            result << newCoeff;
        } else {
            if (newCoeff != 1.0) {
                result << newCoeff;
            }
            result << "x";
            if (newExp != 1) {
                result << "^" << newExp;
            }
        }

        firstTerm = false;
    }

    if (result.str().empty()) {
        return "0";
    }

    return result.str();
}

void printWelcomeMessage() {
    cout << "=============================================\n";
    cout << "  Калькулятор производных многочленов\n";
    cout << "=============================================\n";
    cout << "Введите многочлен в формате: 3x^2 + 2x - 5\n";
    cout << "Или: 4*x^3 - 2*x^2 + x/2\n";
    cout << "Для выхода введите 'exit'\n";
    cout << "=============================================\n";
}

int main() {
    printWelcomeMessage();

    while (true) {
        cout << "\nВведите многочлен: ";
        string input;
        getline(cin, input);

        if (input == "exit" || input == "quit") {
            break;
        }

        if (input.empty()) {
            cout << "Ошибка: пустой ввод. Попробуйте снова.\n";
            continue;
        }

        try {
            vector<Term> terms = parsePolynomial(input);
            string derivative = computeDerivative(terms);
            cout << "Производная: " << derivative << endl;
        } catch (const exception &e) {
            cout << "Ошибка: неверный формат многочлена. Пожалуйста, попробуйте снова.\n";
            cout << "Пример правильного формата: 3x^2 - 2x + 5\n";
        }
    }

    cout << "\nПрограмма завершена. До свидания!\n";
    return 0;
}