#include "input.h"
#include <iostream>
#include <sstream>
#include <limits>

int get_Int(std::string errorMessage, int min, int max) {
    std::cout << Color::BG_GREEN << errorMessage << Color::RESET;
    int output = 0;

    //Angka min adalah kode rahasia biar min max nya ga ada 
    if (min < 0) {
        min = INT_MIN;
        max = INT_MAX;
    }

    bool validInput = false;
    while (!validInput) {
        std::cin >> output;

        if (std::cin.fail() || (min > output || output > max)) {
            std::cout << errorMessage;

            // Clear the failbit and ignore the remaining input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        else {
            // Input is valid
            validInput = true;
        }
    }
    return output;
}

long double get_Long_Double(std::string errorMessage) {
    long double output = 0;
    bool validInput = false;

    std::cout << Color::BG_GREEN << errorMessage << Color::RESET;
    while (!validInput) {
        std::cin >> output;

        if (std::cin.fail()) {
            std::cout << errorMessage;

            // Clear the failbit and ignore the remaining input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        else {
            // Input is valid
            validInput = true;
        }
    }
    return output;
}

std::vector<long double> get_Multiple_Long_Double(std::string errorMessage) {
    std::string input;
    std::vector<long double> numbers;

    // Clear any leftover newline characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Get all float values in one input
    std::cout << Color::BG_GREEN << errorMessage << Color::RESET << std::endl;
    std::getline(std::cin, input);

    // Use stringstream to parse the input
    std::istringstream iss(input);
    long double number;

    // Extract numbers from the input
    while (iss >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

void get_String_Num(std::string errorMessage, std::string &output, int *ptrAngkaPenting, int *ptrPresisi, long double *ptrValue) {
    bool desimal = false;
    bool inputValid = true;
    // If number that is not zero found in the string
    bool findNotZero =  false;
    // Zero after decimal
    int rightZeroAmount = 0;
    // Zero before the first non-zero number
    int leadingZero = 0;
    // Zero after the fisrt non-zero number and before decimal or another non-zero number
    int zeroUntilDecimal = 0;

    std::cout<< Color::BG_GREEN << errorMessage << Color::RESET;
    std::cin >> output;
    for (int i = 0; output[i] != '\0' || i == 0; i++) {
        // Cek Input
        if(!inputValid || (!isdigit(output[i]) && output[i] !='.')) {
            output.clear();

            std::cout << errorMessage;
            std::cin >> output;
            i = 0;
            inputValid = true;
        }

        // Angka bukan 0 pertama
        if (!desimal && isdigit(output[i]) && output[i] != '0' && !findNotZero) {
            leadingZero = i;
            findNotZero = true;
            rightZeroAmount = 0;
        }
        // Tidak boleh ada koma di awal
        else if (i == 0 && output[i] == '.') {
            inputValid = false;
        }
        // Ketemu titik pertama
        else if (output[i] == '.' && !desimal && !findNotZero) {
            if (output[i-1] == '0') {
                leadingZero = i-1;
            }
            desimal = true;
        }
        // Tidak boleh lebih dari 1 titik
        else if (output[i] == '.' && desimal) {
            inputValid = false;
        }
        else if (output[i] == '0' && !desimal && !findNotZero) {
            leadingZero++;
        }
        else if(output[i] == '0' && findNotZero && !desimal) {
            zeroUntilDecimal++;
        }
        else if(output[i] == '0' && desimal) {
            rightZeroAmount++;
        }
        else if(output[i] == '.') {
            desimal = true;
        }
        // New
        if (output[i] != '0' && !desimal) {
            zeroUntilDecimal = 0;
        }
        else if (output[i] != '0' && desimal) {
            rightZeroAmount = 0;
        }
    }

    // Erase leading zero
    if (leadingZero > 0) {
        output.erase(0, leadingZero);
    }
    
    if (output[0] == '0') {
        rightZeroAmount = 0;
        for (int i = 0; output[i] != '\0'; i++) {
            if (output[i] == '0') {
                rightZeroAmount++;
            }
            else if (isdigit(output[i])) {
                break;
            }
        }
        if (ptrAngkaPenting != NULL) {
            *ptrAngkaPenting = output.length() - rightZeroAmount;
        }
    }

    // Hitung angka penting
    if (ptrAngkaPenting != NULL) {
        if (!desimal) {
            *ptrAngkaPenting = output.length() - zeroUntilDecimal;
        }
        else if (output[0] != '0' && desimal) {
            *ptrAngkaPenting = output.length() - desimal;
        }
        else {
            *ptrAngkaPenting = output.length() - (desimal + zeroUntilDecimal + rightZeroAmount);
        }
    }

    // Hitung Presisi
    if (ptrPresisi != NULL) {
        if (desimal) {
            bool foundDesimal = false;
            for (int i = 0; output[i] != '\0'; i++) {
                if (output[i] == '.') {
                    foundDesimal = true;
                    *ptrPresisi = output.length() - (i + 1);
                    break;
                }
            }
        }
        else {
            int zero = 0;
            for (int i = 0; output[i] != '\0'; i++) {
                if (output[i] == '0') {
                    zero++;
                }
                else {
                    zero = 0;
                }
            }
            if (zero == 0) {
                *ptrPresisi = 0;
            }
            else {
                *ptrPresisi = 0 - zero;
            }
            
        }
    }

    //Hitung Value
    if (ptrValue != NULL) {
        *ptrValue = stold(output);
    }
}
