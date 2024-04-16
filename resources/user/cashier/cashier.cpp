#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct item {
    string id_item;
    string item_name;
    string item_price;
};

/* Create Id Transaction */
void create_id_transaction(){
    string id_transaction = "trs";    // default value
    int no_transaction = 0;         // default value

    no_transaction = no_transaction + 25; // is random number

    id_transaction = id_transaction + string(4 - to_string(no_transaction).length(), '0') + to_string(no_transaction); // to make trs00**

    cout << id_transaction << endl;
};

/* Current time based on system */
void current_dateTime(){
    time_t now = time(0);   // get current time now
    tm *ltm = localtime(&now);

    /* Date Section */
    // get local date
    int day = ltm->tm_mday;
    int month = ltm->tm_mon + 1;  // month start at 0
    int year = ltm->tm_year + 1900; // year start at 1900

    // convert date to string n add 0 in front when digit is one
    string newDay = (day < 10) ? "0" + to_string(day) : to_string(day);
    string newMonth = (month < 10) ? "0" + to_string(month) : to_string(month);
    string newYear = to_string(year);
    
    string date = newDay + "/" + newMonth + "/" + newYear;
    cout << date << endl;
    /* End date section */

    /* Time section */
    // get local time
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;

    // convert time to string n add 0 in front when digit is one
    string newHour = (hour < 10) ? "0" + to_string(hour) : to_string(hour);
    string newMinute = (minute < 10) ? "0" + to_string(minute) : to_string(minute);

    string time = newHour + ":" + newMinute;
    cout << time << endl;
    /* End time section */
};

vector<item> open_file_item(){
    ifstream file("D:\\Tugas Kuliah\\Semester 2\\RL105 - Struktur Data dan Algoritma\\DataBarang\\database\\item.csv", ios::in);

    if (!file.is_open()) {
        cout << "Gagal membuka file CSV" << endl;
    }

    string line;
    vector<item> data;

    // Baca setiap baris dalam file CSV
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, price_str;

        // Pisahkan setiap kolom dalam baris
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, price_str, ',');

        // Buat objek Barang dan tambahkan ke vektor data
        item Item = {id, name, price_str};
        data.push_back(Item);
    }

    // Tutup file
    file.close();

    return data;
}

void transaction(){
    vector<item> data = open_file_item();

    // Meminta pengguna untuk memasukkan ID barang
    string input_id;
    cout << "ID Barang: ";
    cin >> input_id;

    // Mencari barang berdasarkan ID
    bool ditemukan = false;
    for (const auto& Item : data) {
        if (Item.id_item == input_id) {
            cout << "Nama: " << Item.item_name << endl;
            cout << "Harga: " << Item.item_price << endl;
            ditemukan = true;
            break;
        }
    }

    // Jika barang tidak ditemukan
    if (!ditemukan) {
        cout << "Barang dengan ID " << input_id << " tidak ditemukan" << endl;
    }
}

/* Main Program */
int main(){
    cout << "********** MINIMARKET NAME **********" << endl;
    cout << "=====================================" << endl;
    transaction();
}