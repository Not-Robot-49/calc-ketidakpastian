#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// Biar windows tua bisa nampilin warna
void enableVirtualTerminalProcessing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}


// Best practice belajar catat dengan 3 warna tapi disini ada 5
class Color {
public:
    // Text Color
    static const string RED;
    static const string GREEN;
    static const string YELLOW;
    static const string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string GRAY;

    // Background Colors
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    static const std::string BG_BLUE;
    static const std::string BG_MAGENTA;
    static const std::string BG_CYAN;
    static const std::string BG_WHITE;

    // Text Effects
    static const std::string BOLD;
    static const std::string UNDERLINE;

    // Reset
    static const string RESET;
};

// Warna itu apa
const string Color::RED = "\033[31m";
const string Color::GREEN = "\033[32m";
const string Color::YELLOW = "\033[33m";
const string Color::BLUE = "\033[34m";
const std::string Color::MAGENTA = "\033[35m";
const std::string Color::CYAN = "\033[36m";
const std::string Color::WHITE = "\033[37m";
const std::string Color::GRAY = "\033[90m";

// Background Colors
const std::string Color::BG_RED = "\033[41m";
const std::string Color::BG_GREEN = "\033[42m";
const std::string Color::BG_YELLOW = "\033[43m";
const std::string Color::BG_BLUE = "\033[44m";
const std::string Color::BG_MAGENTA = "\033[45m";
const std::string Color::BG_CYAN = "\033[46m";
const std::string Color::BG_WHITE = "\033[47m";

// Text Effects
const std::string Color::BOLD = "\033[1m";
const std::string Color::UNDERLINE = "\033[4m";

// Reset color
const string Color::RESET = "\033[0m";

struct pengukuran
{
    // Berapa angka pentingnya 
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
};

void home();
int get_Int(string errorMessage, int min, int max);
long double get_Long_Double(string errorMessage);
vector<long double> get_Multiple_Long_Double(string errorMessage);
void round_To_Decimal_Places(long double *ptrValue, int *decimalPlaces);
void get_String_Num(string errorMessage, string &output, int *ptrAngkaPenting, int *ptrPresisi, long double *ptrValue);
int mencariAP(float value/*, int *jumlahDesimal*/);
void ketidakpastian_Tunggal(int *presisi, long double *ptrKetidakpastian, string strKetidakpastian);
long double range(vector<long double> sample, long double *rerata);
long double standart_Deviation_Sample(vector<long double> sample, long double *rerata);

int main() {
    int menuPengukuran = 0;
    while (menuPengukuran != 5) {
        pengukuran hasil;

        home();
        menuPengukuran = get_Int("Masukkan angka 1-5: ", 1, 5);
        cout << "" << endl;

        switch (menuPengukuran) {
        case 1:
            get_String_Num("Nilai: ", hasil.strValue, &hasil.angkaPenting, NULL, &hasil.value);
            get_String_Num("Skala terkecil: ", hasil.strKetidakpastian, NULL, &hasil.presisi, NULL);
            hasil.value = stold(hasil.strValue);
            hasil.ketidakpastian = stold(hasil.strKetidakpastian);

            ketidakpastian_Tunggal(&hasil.presisi, &hasil.ketidakpastian, hasil.strKetidakpastian);

            round_To_Decimal_Places(&hasil.value, &hasil.presisi);
            cout << fixed << setprecision(hasil.presisi + 1) << Color::BOLD << Color::BLUE << hasil.value << Color::RESET << Color::BOLD << " +- " << Color::RED << hasil.ketidakpastian << Color::RESET << endl;
            break;
        
        case 2:
            get_String_Num("Skala terkecil: ", hasil.strKetidakpastian, NULL, &hasil.presisi, NULL);
            hasil.vectorValue = get_Multiple_Long_Double("Masukkan hasil pengukuran dipisahkan spasi: ");
            
            cout << Color::BOLD << Color::GREEN << endl << "Hasil: " << Color::RESET << endl;
            
            hasil.ketidakpastianRange = range(hasil.vectorValue, &hasil.rerataRange);
            cout << "Range: " << endl;
            cout << fixed << setprecision(hasil.presisi) << Color::BOLD <<Color::BLUE << hasil.rerataRange << Color::RESET << " +- " << Color::BOLD << Color::RED << hasil.ketidakpastianRange << Color::RESET << endl;
            
            hasil.ketidakpastianDeviasi = standart_Deviation_Sample(hasil.vectorValue, &hasil.rerataDeviasi);
            cout << "Standar deviasi sampel: " << endl;
            cout << fixed << setprecision(hasil.presisi) << Color::BOLD << Color::BLUE << hasil.rerataDeviasi << Color::RESET << Color::BOLD << " +- " << Color::RED << hasil.ketidakpastianDeviasi << Color::RESET << endl;
        
            cout << Color::CYAN << "Mohon maaf bila ada kesalahan" << endl << "~ Daffa, Raihan, & Josh (7027)" << Color::RESET << endl;
            break;

        case 3:
            get_String_Num("3. Angka Penting: ", hasil.strValue, &hasil.angkaPenting, &hasil.presisi, &hasil.value);
            cout << "Angka Penting: " << Color::BOLD << Color::BLUE << hasil.angkaPenting << Color::RESET << endl; 
            cout << "Presisi: " << Color::BOLD <<Color::GREEN << hasil.presisi << Color::RESET << " angka dibelakang koma" << endl;
            break;

        case 4:
            cout << "Tutorial: " << endl;
            cout << "Docs: github.com/not-robot-49/calc-ketidakpastian" << endl;
            cout << "YT: link youtube" << endl;
            cout << endl << "Made by Daffa Satya (Creator) & Raihan Altaf (Co Creator)" << endl;
            cout << "Contact: " << endl << "ig: @rhn.alt / @sat1rya" << endl << "github: github.com/not-robot-49 atau github.com/badutpenusuk" << endl;
            cout << "" << endl;
        default:
            break;
        }
        cout << endl;
    }
    cout << Color::RESET;
    return 0;
}

void home() {
    cout << "1. Ketidakpastian Tunggal" << endl;
    cout << "2. Ketidakpastian Berulang" << endl;
    cout << "3. Angka Penting" << endl;
    cout << "4. Tutorial dan Credit" << endl;
    cout << "5. Exit" << endl;
}

void get_String_Num(string errorMessage, string &output, int *ptrAngkaPenting, int *ptrPresisi, long double *ptrValue) {
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

    cout<< errorMessage;
    cin >> output;
    for (int i = 0; output[i] != '\0' || i == 0; i++) {
        // Cek Input
        if(!inputValid || (!isdigit(output[i]) && output[i] !='.')) {
            output.clear();

            cout << errorMessage;
            cin >> output;
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

int get_Int(string errorMessage, int min, int max) {
    cout << errorMessage;
    int output = 0;

    //Angka min adalah kode rahasia biar min max nya ga ada 
    if (min < 0) {
        min = INT_MIN;
        max = INT_MAX;
    }

    bool validInput = false;
    while (!validInput) {
        cin >> output;

        if (cin.fail() || (min > output || output > max)) {
            cout << errorMessage;

            // Clear the failbit and ignore the remaining input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        else {
            // Input is valid
            validInput = true;
        }
    }
    return output;
}

long double get_Long_Double(string errorMessage) {
    long double output = 0;
    bool validInput = false;

    cout << errorMessage;
    while (!validInput) {
        cin >> output;

        if (cin.fail()) {
            cout << errorMessage;

            // Clear the failbit and ignore the remaining input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        else {
            // Input is valid
            validInput = true;
        }
    }
    return output;
}

vector<long double> get_Multiple_Long_Double(string errorMessage) {
    string input;
    vector<long double> numbers;

    // Clear any leftover newline characters in the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get all float values in one input
    cout << errorMessage << endl;
    getline(cin, input);

    // Use stringstream to parse the input
    istringstream iss(input);
    long double number;

    // Extract numbers from the input
    while (iss >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

// Ngitung ketidakpastian
long double standart_Deviation_Sample(vector<long double> sample, long double *rerata) {
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

long double range(vector<long double> sample, long double *rerata) {
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

void round_To_Decimal_Places(long double *ptrValue, int *ptrPresisi) {
    long double multiplier = powl(10.0, *ptrPresisi);
    *ptrValue = round(*ptrValue * multiplier) / multiplier;
}

void ketidakpastian_Tunggal(int *presisi, long double *ptrKetidakpastian, string strKetidakpastian) {
    if (ptrKetidakpastian != NULL && &strKetidakpastian != NULL) {
        *ptrKetidakpastian /= 2;
    }
    *presisi++;
}