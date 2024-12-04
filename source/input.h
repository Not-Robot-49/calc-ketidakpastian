#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "warna.h"

//----------FUNCTION PROTOTYPE----------//

// Return integer from user
int get_Int(std::string errorMessage, int min, int max);
// Return long double from user
long double get_Long_Double(std::string errorMessage);
// Return multiple long double from user in vector
std::vector<long double> get_Multiple_Long_Double(std::string errorMessage);
// Get number in string format with many args
void get_String_Num(std::string errorMessage, std::string &output, int *ptrAngkaPenting, int *ptrPresisi, long double *ptrValue);


#endif