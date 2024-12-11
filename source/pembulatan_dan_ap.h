#ifndef PEMBULATAN_DAN_AP_H
#define PEMBULATAN_DAN_AP_H

#include <string>


//*----------FUNCTION PROTOTYPE----------*//

// Pembulatan hingga AP menjadi jumlah AP
//! Jangan dipakai kecuali stringnya benar2 mau dibulatkan dari belakang
//* contoh: (0.546), (0.450); C++ --> (0.5), (0.5); pembulatan_AP --> (0.6), (0.4)
void pembulatan_AP(std::string &s, int jumlahAP);

// Pembulatan tapi pake presisi boy
void pembulatan_Presisi(std::string &s, int presisi);

// Menghitung angka penting yang ada di dalam suatu string
int hitungAngkaPenting(const std::string &s);

// Menghitung presisi suatu bilangan relatif dengan titik 0, min untuk minimal presisi yang akan dikeluarkan
int hitung_Presisi(const std::string &s, int min);

#endif