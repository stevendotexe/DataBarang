#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/* Struct untuk data barang */
struct Barang {
    string id_item;
    string item_name;
    float item_price;
    int item_stock;
    Barang *next; //linked list
    Barang *prev;
};

/* ADD data barang */
void tambahBarang(Barang*& head, string id_item, string item_name, float item_price, int item_stock) {
    Barang *baru = new Barang;
    baru->id_item = id_item;
    baru->item_name = item_name;
    baru->item_price = item_price;
    baru->item_stock = item_stock;
    baru->next = nullptr;
    baru->prev = nullptr;

    if (head == nullptr) {
        head = baru;
    } else {
        Barang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
        baru->prev = temp;
    }
}

/* Menampilkan data barang */
void tampilkanBarang(Barang *head) {
    if (head == nullptr) {
        cout << "Data barang kosong" << endl;
        return;
    } else {
        Barang* temp = head;
        cout << "=============================================================================" << endl;
        cout << "ID BARANG \tNAMA BARANG \t\t\tHARGA(Rp) \tSTOK" << endl;
        cout << "=============================================================================" << endl;
        while (temp != nullptr) {
        cout << temp->id_item << " \t" << temp->item_name << "\t\t" << temp->item_price << "  \t\t" << temp->item_stock << endl;
        temp = temp->next;
        }
    }
}

/* Ubah data barang */
void ubahBarang(Barang* head, string id_item, string item_name, float item_price, int item_stock) {
    Barang* temp = head;
    while (temp != nullptr) {
        if (temp->id_item == id_item) {
            temp->item_name = item_name;
            temp->item_price = item_price;
            temp->item_stock = item_stock;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan ID " << id_item << " tidak ditemukan" << endl;
}

/* Menghapus data barang */
void hapusBarang(Barang*& head, string id_item) {
    if (head == nullptr) {
        cout << "Data barang kosong" << endl;
        return;
    }
    Barang* temp = head;
    while (temp != nullptr) {
        if (temp->id_item == id_item) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
            delete temp;
            cout << "Barang dengan ID " << id_item << " berhasil dihapus" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan ID " << id_item << " tidak ditemukan" << endl;
}

/* Menyimpan data ke CSV */
void simpanData(Barang* head, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        
        //header CSV
        file << "id_item,item_name,item_price,item_stock" << endl;
        
        //simpan data barang
        Barang* temp = head;
        while (temp != nullptr) {
            file << temp->id_item << "," << temp->item_name << "," << temp->item_price << "," << temp->item_stock << endl;
            temp = temp->next;
        }
        file.close(); //close file
        cout << "Data berhasil disimpan ke dalam file" << endl;
    } else {
        cout << "Gagal membuka file" << endl;
    }
}

int bagianBarang() {
    Barang* head = nullptr;

/* Read CSV */
    ifstream file("../../database/item.csv");
    if (!file.is_open()) {
        cout << "File tidak ditemukan" << endl;
    }

    string line;
        while (getline(file, line)){
            string id_item;
            int item_stock;
            float item_price;
            string item_name;
            file >> id_item;
            file.ignore();
            getline(file, item_name, ',');
            file >> item_price;
            file.ignore();
            file >> item_stock;
            tambahBarang(head, id_item, item_name, item_price, item_stock); 
        }
    file.close();


/* main */
    int pilihan;
    do {
        cout << "=============================================================================" << endl;
        cout << "                         PROGRAM BAGIAN GUDANG" << endl;
        cout << "=============================================================================" << endl;
        cout << "Menu:" << endl;
        cout << "1. Tambah data barang" << endl;
        cout << "2. Tampilkan data barang" << endl;
        cout << "3. Ubah data barang" << endl;
        cout << "4. Hapus data barang" << endl;
        cout << "5. Selesai" << endl;
        cout << "=============================================================================" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string id_item, item_name;
                float item_price;
                int item_stock;
                cout << "Masukkan ID (4 huruf 3 angka): ";
                cin >> id_item;
                cout << "Masukkan nama: ";
                cin.ignore();
                getline(cin, item_name);
                cout << "Masukkan harga: ";
                cin >> item_price;
                cout << "Masukkan stock: ";
                cin >> item_stock;
                tambahBarang(head, id_item, item_name, item_price, item_stock);
                simpanData(head, "../../database/item.csv");
                break;
            }
            case 2:
                tampilkanBarang(head);
                break;
            case 3: {
                string id_item, item_name;
                float item_price;
                int item_stock;
                cout << "Masukkan ID barang yang ingin diubah: ";
                cin >> id_item;
                cout << "Masukkan nama baru: ";
                cin.ignore();
                getline(cin, item_name);
                cout << "Masukkan harga baru: ";
                cin >> item_price;
                cout << "Masukkan stock baru: ";
                cin >> item_stock;
                ubahBarang(head, id_item, item_name, item_price, item_stock);
                simpanData(head, "../../database/item.csv");
                break;
            }
            case 4: {
                string id_item;
                cout << "Masukkan ID barang yang ingin dihapus: ";
                cin >> id_item;
                hapusBarang(head, id_item);
                simpanData(head, "../../database/item.csv");
                break;
            }
            case 5:
                // Simpan data ke dalam file CSV sebelum keluar dari program
                simpanData(head, "../../database/item.csv");
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 5);

    /* Bersihkan memori linked list */
    Barang* temp = head;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

  return 0;
}