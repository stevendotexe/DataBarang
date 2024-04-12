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

int main(){
    ifstream file("D:\\Tugas Kuliah\\Semester 2\\RL105 - Struktur Data dan Algoritma\\DataBarang\\database\\item.csv", ios::in);

    if (!file.is_open()) {
        cout << "Gagal membuka file CSV" << endl;
        return 1;
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