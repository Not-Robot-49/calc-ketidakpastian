#include <iostream>
#include <limits>

using namespace std;

void welcome();
int get_Int(string errorMessage, int min, int max);
float get_Float(string errorMessage);
float hitung_Waktu(bool berulang);
float hitung_Jumlah_Zat(bool berulang);
float hitung_Panjang(bool berulang);
float hitung_intensitas_Cahaya(bool berulang);
float hitung_Kuat_Arus(bool berulang);
float hitung_Suhu(bool berulang);
float hitung_Massa(bool berulang);

//test github
//±
int main() {
    float ketidakpastian;
    short besaranUser;
    string besaran[7] = {"waktu", "jumlah zat", "panjang", "floatensitas cahaya", "kuat arus", "suhu", "massa"};
    bool validInput = false;

    //Welcoming the user
    welcome();

    besaranUser = get_Int("Masukkan angka 1-7: ", 1, 7);
    cout << endl;

    char answerYN;
    bool berulang = false;
    while (!(answerYN == 'y' || answerYN == 'Y' || answerYN == 'n' || answerYN == 'N')) {
        cout << "Pengukuran berulang? (y/N) ";
        cin >> answerYN;
    }   
    cout << endl;
    if (answerYN == 'y' || answerYN == 'Y') {
        berulang = true;
    } else {
        berulang = false;
    }

    switch (besaranUser) {
    case 1:
        ketidakpastian = hitung_Waktu(berulang);
        break;
    case 2:
        ketidakpastian = hitung_Jumlah_Zat(berulang);
        break;
    case 3:
        ketidakpastian = hitung_Panjang(berulang);
        break;
    case 4:
        ketidakpastian = hitung_intensitas_Cahaya(berulang);
        break;
    case 5:
        ketidakpastian = hitung_Kuat_Arus(berulang);
        break;
    case 6:
        ketidakpastian = hitung_Suhu(berulang);
        break;
    case 7:
        ketidakpastian = hitung_Massa(berulang);
        break;
    }
}

void welcome() {
    cout << "Besaran yang ingin diukur\n";
    cout << "1. Waktu\n";
    cout << "2. Jumlah Zat\n";
    cout << "3. Panjang\n";
    cout << "4. floatensitas cahaya\n";
    cout << "5. Kuat Arus listrik\n";
    cout << "6. Suhu\n";
    cout << "7. Massa\n";
}

bool check_Input(string errorMessage) {
    // Check for type mismatch of the input
    if (cin.fail()) {
        cout << errorMessage;

        // Clear the failbit and ignore the remaining input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        return false;
    }
    else {
        // Input is valid
        return true;
    }
    return true;
}

int get_Int(string errorMessage, int min, int max) {
    cout << errorMessage;
    int output = 0;

    //-69 adalah kode rahasia biar min max nya ga ada 
    if (min = -69) {
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

float get_Float(string errorMessage) {
    float output = 0;
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

float hitung_Waktu(bool berulang) {
    float skalaKecil = 0;
    cout << "Pilih alat pengukuran\n";
    cout << "1. Stopwatch digital\n";
    cout << "2. Stopwatch analog\n";
    
    int alat = get_Int("Masukkan angka 1-2: ", 1, 2);
    cout << endl;

    skalaKecil = get_Float("Masukkan skala terkecilnya dalam sekon: ");
    cout << endl;

    switch (alat) {
        case 1:
            //Hitung  Stopwatch digital
            break;
        case 2:
            // Hitung stopwatch analog
            break;
        case 3:
            //Serah user
            break;
    }

    return 0;
}

float hitung_Jumlah_Zat(bool berulang) {
    return 1;
}

float hitung_Panjang(bool berulang) {
    return 1;
}

float hitung_intensitas_Cahaya(bool berulang) {
    return 1;
}

float hitung_Kuat_Arus(bool berulang) {
    return 1;
}

float hitung_Suhu(bool berulang) {
    return 1;
}

float hitung_Massa(bool berulang) {
    return 1;
} 