#ifndef KETIDAKPASTIAN_TUNGGAL_BERULANG_H
#define KETIDAKPASTIAN_TUNGGAL_BERULANG_H

#include <vector>
#include <string>
#include <cmath>

//*----------FUNCTION PROTOTYPE----------*//

// Ketidakpastian tunggal analog
void ketidakpastian_Tunggal_Analog(int *presisi, long double *ptrKetidakpastian, std::string &strKetidakpastian);

// Ketidakpastian gabungan range
long double range(std::vector<long double> sample, long double *rerata);

// Ketidakpastian gabungan deviasi
long double standart_Deviation_Sample(std::vector<long double> sample, long double *rerata);

#endif