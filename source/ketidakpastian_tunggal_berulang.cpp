#include "ketidakpastian_tunggal_berulang.h"
#include <string>

void ketidakpastian_Tunggal_Analog(int *presisi, long double *ptrKetidakpastian, std::string &strKetidakpastian) {
    if (ptrKetidakpastian != NULL && &strKetidakpastian != NULL) {
        *ptrKetidakpastian /= 2;
    }
    *presisi++;
    strKetidakpastian = std::to_string(*ptrKetidakpastian);
}

long double range(std::vector<long double> sample, long double *rerata) {
    long double terkecil = sample[0];
    long double terbesar = sample[0];
    for (int i = 0; i < sample.size(); i++) {
        if (terbesar < sample[i]) {
            terbesar = sample[i];
        }
        else if (terkecil > sample[i]) {
            terkecil = sample[i];
        }
    }

    *rerata = (terbesar + terkecil) / 2;
    return (terbesar - terkecil) / 2;
}

long double standart_Deviation_Sample(std::vector<long double> sample, long double *rerata) {
    long double sigma = 0;

    int jumlah = 0;
    while (jumlah < sample.size()) {
        *rerata += sample[jumlah];
        jumlah++;
    }
    *rerata /= jumlah;
    jumlah = 0;

    while (jumlah < sample.size()) {
        sigma += pow(sample[jumlah] - *rerata, 2);
        jumlah++;
    } 

    return sqrtl((1.0 / (jumlah - 1.0) * sigma));
}
