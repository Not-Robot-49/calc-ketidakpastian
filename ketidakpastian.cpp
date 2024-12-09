#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <windows.h>
#include "source/ketidakpastian_tunggal_berulang.h"
#include "source/ketidakpastian_gabungan.h"
#include "source/input.h"
#include "source/pembulatan_dan_ap.h"
#include "source/warna.h"

// Tak nak ketik std:: setiap saat
using namespace std;

void home() {
    cout << "----------CALC-KETIDAKPASTIAN----------" << endl;
    cout << "1. Ketidakpastian Tunggal" << endl;
    cout << "2. Ketidakpastian Berulang" << endl;
    cout << "3. Ketidakpastian Gabungan" << endl;
    cout << "4. Angka Penting" << endl;
    cout << "5. Tutorial dan Credit" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    // Menu pengukuran
    int menuPengukuran = 0;
    // Variabel untuk menyimpan angka penting 
    int angkaPenting = 0;
    // Berapa desimal presisinya, "+" untuk dibelakang ".", "-" untuk di depan "."
    int presisi = 0;
    // Nilai pengukuran (jika pengukuran banyak maka ini nilai reratanya)
    long double value = 0;
    // Ketidakpastiannya
    long double ketidakpastian = 0;
    // Nilai pengukuran dalam string
    string strValue;
    // Nilai ketidakpastian dalam string
    string strKetidakpastian;

    // Buat pengukuran lebih dari 1 kali
    // Buat deviasi (Cara 2)
    long double rerataDeviasi = 0;
    long double ketidakpastianDeviasi = 0;
    // Buat range (cara 1)
    long double rerataRange = 0;
    long double ketidakpastianRange = 0;

    // Vector buat pengukuran lebih dari 1 kali
    vector<long double> vectorValue;
    vector<string> vcrStrValue;

    while (menuPengukuran != 6) {

        home();
        menuPengukuran = get_Int("Masukkan angka 1-6:", 1, 6);
        cout << "" << endl;

        // Menu Pengukuran
        switch (menuPengukuran) {
        // Ketidakpastian tunggal
        case 1: 
            //* Pengertian
            cout << "Ketidakpastian yang dihasilkan dari 1 kali pengukuran\n";
            cout << Color::BLUE << "Rumus: " << Color::RESET << "1/2 skala terkecil alat ukut yang digunakan\n";

            // Digital (1), Analog (2)
            int skala;
            skala = get_Int("Digital/Analog (1/2):", 1, 2);
            get_String_Num("Nilai:", strValue, &angkaPenting, NULL, &value);
            get_String_Num("Skala terkecil:", strKetidakpastian, NULL, &presisi, NULL);
            value = stold(strValue);
            ketidakpastian = stold(strKetidakpastian);

            if (skala == 1) {
                pembulatan_AP(strKetidakpastian, 1);
                pembulatan_AP(strValue, 1); 
            }
            else {
                ketidakpastian_Tunggal_Analog(&presisi, &ketidakpastian, strKetidakpastian);

                pembulatan_AP(strKetidakpastian, 1);
                pembulatan_AP(strValue, 1);
            }

            if (stold(strKetidakpastian) < ketidakpastian) {
                ketidakpastian = stold(strKetidakpastian);
            }
            cout << endl;
            cout << Color::BG_BLUE << "Dilaporkan:" << Color::RESET << " " << fixed << setprecision(hitung_Presisi(strKetidakpastian, 0)) << Color::BOLD << Color::UNDERLINE << Color::BLUE << value << Color::RESET << Color::BOLD << Color::UNDERLINE << " +- " << Color::RED << ketidakpastian << Color::RESET << endl;
            break;
        
        // Ketidakpastian Berulang
        case 2:
            //* Pengertian
            cout << "Ketidakpastian yang dihasilkan dari 2 atau lebih kali pengukuran\n";
            cout << "Ada 2 cara untuk menghitung ketidakpastian berulang\n";

            // get_String_Num("Skala terkecil: ", strKetidakpastian, NULL, &presisi, NULL);
            vectorValue = get_Multiple_Long_Double("Masukkan hasil pengukuran dipisahkan spasi:");
            
            cout << Color::BOLD << Color::GREEN << endl << "Hasil: " << Color::RESET << endl;
            cout << endl;
            
            // Range
            cout << Color::CYAN << "Range" << Color::RESET << endl;
            cout << "Range: rerata          = (nilai max + nilai min) / 2\n";
            cout << "Range: ketidakpastian  = (nilai max - nilai min) / 2\n";
            ketidakpastianRange = range(vectorValue, &rerataRange);

            strKetidakpastian = to_string(ketidakpastianRange);
            pembulatan_AP(strKetidakpastian, 1);
            presisi = hitung_Presisi(strKetidakpastian, 0);

            cout << Color::BG_BLUE << "Dilaporkan:" << Color::RESET << " " << fixed << setprecision(presisi) << Color::BOLD << Color::UNDERLINE <<Color::BLUE << rerataRange << Color::RESET << Color::BOLD << " +- " << Color::BOLD << Color::RED << ketidakpastianRange << Color::RESET << endl;
            cout << endl;


            // Deviasi
            cout << Color::CYAN << "Standar deviasi sampel: " << Color::RESET << endl;
            cout << "Deviasi: rerata            = Jumlah Data /  Banyak Data\n";
            cout << "Deviasi: ketidakpastian    = sqrt((1/Banyak Data - 1)*(Jumlah Data * Jumlah Data))\n";
            ketidakpastianDeviasi = standart_Deviation_Sample(vectorValue, &rerataDeviasi);
            
            strKetidakpastian = to_string(ketidakpastianDeviasi);
            pembulatan_AP(strKetidakpastian, 1);
            presisi = hitung_Presisi(strKetidakpastian, 0);

            cout << Color::BG_BLUE << "Dilaporkan:" << Color::RESET << " " << fixed << setprecision(presisi) << Color::BOLD << Color::UNDERLINE << Color::BLUE << rerataDeviasi << Color::RESET << Color::BOLD << " +- " << Color::RED << ketidakpastianDeviasi << Color::RESET << endl;
            break;
        
        // Ketidakpastian gabungan
        case 3:
            //* Hanya tuhan yang tahu cara ini bekerja
            cout << "Jika operasinya + atau - maka ketidakpastiannya adalah hasil jumlah dari ketidakpastian mutlaknya\n";
            cout << "Jika operasinya * atau / maka ketidakpastiannya adalah jumlah dari ketidakpastian relatifnya\n";
            calculateUncertaintyCombined();
            break;

        // Angka Penting
        case 4:
            cout << "Aturan angka penting: semua angka penting kecuali\n";
            cout << "1. Angka nol di kiri tidak penting\n";
            cout << "2. Angka nol di kanan tidak penting, tapi angka nol desimal di kanan penting\n";
            get_String_Num("Angka Penting:", strValue, &angkaPenting, &presisi, &value);

            cout << Color::BG_BLUE <<  "Angka Penting:" << Color::RESET << " " << Color::BOLD << Color::BLUE << angkaPenting << Color::RESET << endl; 
            cout << Color::BG_BLUE << "Presisi:" << Color::RESET << " " << Color::BOLD <<Color::GREEN << presisi << Color::RESET << " angka dibelakang koma" << endl;
            break;

        case 5:
            cout << Color::BG_CYAN << "Tutorial: " << Color::RESET << endl;
            cout << "Docs & Source: " << Color::UNDERLINE << "github.com/not-robot-49/calc-ketidakpastian" << Color::RESET << endl;
            cout << "YT: " << Color::UNDERLINE << "link youtube" << Color::RESET << endl;


            cout << endl << Color::BG_CYAN << "Made With love <3 and glued with hope by" << Color::RESET << endl;
            cout << "Daffa Satya (Creator) , Raihan Altaf (Co Creator), & Joshua Leonardo (Co Creator)" << endl;
            cout << endl;

            cout << Color::BG_CYAN << "Contact: " << Color::RESET << endl; 
            cout << "ig: " << Color::UNDERLINE << "@sat1rya" << Color::RESET << " / " << Color::UNDERLINE << "@rhn.alt" << Color::RESET << endl;
            cout << "github: " << Color::UNDERLINE << "github.com/not-robot-49" << Color::RESET << " atau " << Color::UNDERLINE << "github.com/badutpenusuk" << Color::RESET << endl;
            cout << "" << endl;
        default:
            break;
        }
        cout << endl;
    }
    cout << "----------Terimakasih :)---------------";
    cout << Color::RESET << endl;
    return 0;
}
