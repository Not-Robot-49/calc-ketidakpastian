#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <cstring>
#include <algorithm>
#include "ketidakpastian_gabungan.h"
#include "warna.h"

// Type alias defined in the header file
using UncertainValue = std::pair<double, double>;

// Forward declarations for internal functions
UncertainValue evaluateFunction(const std::string& func, const std::string& args);
UncertainValue applyOperation(const UncertainValue& a, const UncertainValue& b, char op);
int precedence(char op);

// Function to determine precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // Default precedence for unknown operators
}

// Function to apply an operator to two uncertain values
UncertainValue applyOperation(const UncertainValue& a, const UncertainValue& b, char op) {
    double value = 0, uncertainty = 0;
    switch (op) {
        case '+': 
            value = a.first + b.first;
            uncertainty = a.second + b.second;
            break;
        case '-': 
            value = a.first - b.first;
            uncertainty = a.second + b.second;
            break;
        case '*': 
            value = a.first * b.first;
            uncertainty = std::sqrt(std::pow(b.first * a.second, 2) + std::pow(a.first * b.second, 2));
            break;
        case '/': 
            if (b.first == 0) throw std::runtime_error("Pembagian dengan nol!");
            value = a.first / b.first;
            uncertainty = std::sqrt(std::pow(b.first * a.second, 2) + std::pow(a.first * b.second, 2)) / (b.first * b.first);
            break;
        default:
            throw std::runtime_error("Operator tidak valid!");
    }
    return {value, uncertainty};
}

// Function to evaluate functions like sqrt or pow
UncertainValue evaluateFunction(const std::string& func, const std::string& args) {
    if (func == "sqrt") {
        UncertainValue arg = evaluateExpression(args);
        if (arg.first < 0) throw std::runtime_error("Akar jangan negatif ya!");
        double value = std::sqrt(arg.first);
        double uncertainty = arg.second / (2 * value);
        return {value, uncertainty};
    } else if (func == "pow") {
        size_t commaPos = args.find(',');
        if (commaPos == std::string::npos) throw std::runtime_error("Argumen pow invalid!");
        UncertainValue base = evaluateExpression(args.substr(0, commaPos));
        UncertainValue exp = evaluateExpression(args.substr(commaPos + 1));
        double value = std::pow(base.first, exp.first);
        double relativeUncertainty = std::sqrt(
            std::pow(exp.first * base.second / base.first, 2) + 
            std::pow(std::log(base.first) * exp.second, 2)
        );
        return {value, relativeUncertainty * value};
    }
    throw std::runtime_error("Fungsi tak diketahui: " + func);
}

// Function to evaluate an expression
UncertainValue evaluateExpression(const std::string& expression) {
    std::stack<UncertainValue> values;    // Stack for uncertain values
    std::stack<char> operators;          // Stack for operators

    for (size_t i = 0; i < expression.length(); i++) {
        if (std::isspace(expression[i])) continue;

        // Parse numbers with uncertainty
        if (std::isdigit(expression[i]) || expression[i] == '.') {
            std::stringstream ss;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                ss << expression[i++];
            }
            double value = std::stod(ss.str());
            double uncertainty = 0;

            if (i < expression.length() && expression[i] == '+') { // Parse uncertainty
                if (i + 1 < expression.length() && expression[i + 1] == '-') {
                    i += 2; // Skip "+-"
                    ss.str("");
                    ss.clear();
                    while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                        ss << expression[i++];
                    }
                    uncertainty = std::stod(ss.str());
                }
            }
            values.push({value, uncertainty});
            i--;
        }
        // Parse functions like sqrt or pow
        else if (std::isalpha(expression[i])) {
            std::string func;
            while (i < expression.length() && std::isalpha(expression[i])) {
                func += expression[i++];
            }
            if (expression[i] != '(') throw std::runtime_error("Pemanggilan fungsi invalid!");
            int parenCount = 1;
            i++;
            std::string args;
            while (i < expression.length() && parenCount > 0) {
                if (expression[i] == '(') parenCount++;
                else if (expression[i] == ')') parenCount--;
                if (parenCount > 0) args += expression[i];
                i++;
            }
            i--;
            values.push(evaluateFunction(func, args));
        }
        // Handle parentheses
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                UncertainValue b = values.top(); values.pop();
                UncertainValue a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            if (!operators.empty()) operators.pop(); // Pop the '('
        }
        // Handle operators
        else if (std::strchr("+-*/", expression[i])) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
                UncertainValue b = values.top(); values.pop();
                UncertainValue a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(expression[i]);
        } else {
            throw std::runtime_error("Expressi karakter invalid!");
        }
    }

    // Perform remaining operations
    while (!operators.empty()) {
        UncertainValue b = values.top(); values.pop();
        UncertainValue a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top();
}

// Function to calculate uncertainty for combined measurements
void calculateUncertaintyCombined() {
    std::string input;
    std::cout << "Penggunaan fungsi:\n";
    std::cout << "2 Pangkat 3 = pow(2, 3)\n";
    std::cout << "Akar = sqrt(angka)\n";
    std::cout << Color::BG_GREEN << "Masukkan ketidakpastian gabungan (e.g., 123+-0.1*3): " << Color::RESET << std::endl;
    std::cin.ignore();
    std::getline(std::cin, input);

    try {
        UncertainValue result = evaluateExpression(input);
        std::cout << std::endl;
        std::cout << Color::BG_BLUE << "Dilaporkan:" << Color::RESET << " " << Color::BOLD << Color::BLUE << Color::UNDERLINE << result.first << Color::RESET << Color::BOLD << Color::UNDERLINE << " +- " << Color::RED << result.second << Color::RESET << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << Color::BG_RED << "Error: " << ex.what() << Color::RESET << std::endl;
    }
}
