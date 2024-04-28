#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int total = 0, paid, change;

struct item {
    string id_item, item_name, item_price, item_stock;
};

struct buy {
    string item_name;
    int price;
    int qnt;
    int subtotal;
};

/* Current time based on system */
string current_dateTime(){
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
    /* End date section */

    /* Time section */
    // get local time
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;

    // convert time to string n add 0 in front when digit is one
    string newHour = (hour < 10) ? "0" + to_string(hour) : to_string(hour);
    string newMinute = (minute < 10) ? "0" + to_string(minute) : to_string(minute);

    string time = newHour + ":" + newMinute;
    /* End time section */

    return date + " " + time;
};

/* Open file item.csv */
vector<item> open_file_item(){
    ifstream file("../../database/item.csv", ios::in);

    if (!file.is_open()) {
        cout << "Gagal membuka file CSV" << endl;
    }

    string line;
    vector<item> data;

    // Read every line at item.csv
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, price_str, stock_str;

        // Separate each column in row
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, price_str, ',');
        getline(ss, stock_str, ',');

        // Make Item object and add to data vector
        item Item = {id, name, price_str, stock_str};
        data.push_back(Item);
    }

    // Close file
    file.close();

    return data;
}

/* Add item to buy struct */
string transaction(vector<buy>& transactions, vector<item>& data){
    // User input id item
    string input_id;
    cout << endl << "ID Barang (Ketik 0 untuk selesai): ";
    cin >> input_id;

    // Stop looping if ID is 0
    if (input_id == "0") {
        return "0";
    }

    // Search item based on ID
    bool found = false;
    for (auto& Item : data) {
        string id = Item.id_item, name = Item.item_name, price_str = Item.item_price, stock_str = Item.item_stock;
        int quantity, subtotal = 0;

        // Convert price to int
        stringstream strm(price_str);
        int price;
        strm >> price;

        // Convert stock to int
        stringstream strm2(stock_str);
        int stock;
        strm2 >> stock;

        if (id == input_id) {
            cout << "Nama     : " << name << endl;
            cout << "Harga    : Rp " << price << endl;
            do{
                cout << "Jumlah   : "; cin >> quantity;

                if(quantity > stock){
                    cout << "Maaf stok yang tersedia sebanyak " << stock << "!" <<endl;
                }
            } while(quantity > stock);
            subtotal = price * quantity;
            cout << "Subtotal : Rp " << subtotal << endl;
            total += subtotal;

            buy buy_item = {name, price, quantity, subtotal};
            transactions.push_back(buy_item);
            
            Item.id_item = id;
            Item.item_name = name;
            Item.item_price = price_str;
            stock -= quantity;
            Item.item_stock = to_string(stock);

            found = true;
            break;
        }
    }

    // If item not found
    if (!found) {
        cout << "Barang dengan ID " << input_id << " tidak ditemukan" << endl;
    }

    return input_id;
}

/* View transaction table */
void display_transactions(const vector<buy>& transactions) {
    cout << "NAMA BARANG \t\t HARGA(Rp) \t JUMLAH \t SUBTOTAL(Rp)" << endl;
    cout << "=====================================================================" << endl;
    for (const auto& transaction : transactions) {
        cout << transaction.item_name.substr(0, 20) << " \t " << transaction.price << " \t\t ";
        cout << transaction.qnt << " \t\t " << transaction.subtotal << endl;
    }
}

/* Print receipt to receipt.txt */
void print_receipt(const vector<buy>& transactions){
    // Write file
    // If file not found, file will created automatically
    ofstream printReceipt;
    printReceipt.open("receipt.txt", ios::app);

    if(!printReceipt.fail()){
        string dateTime;
        dateTime = current_dateTime();

        printReceipt << "                           INI MINIMARKET" << endl;
        printReceipt << dateTime << "                                         " << "DANISHA MARC" << endl;
        printReceipt << "=====================================================================" << endl;
        printReceipt << "NAMA BARANG \t\t HARGA(Rp) \t JUMLAH \t SUBTOTAL(Rp)" << endl;
        printReceipt << "=====================================================================" << endl;
        for (const auto& transaction : transactions) {
            printReceipt << transaction.item_name.substr(0, 20) << " \t " << transaction.price << " \t\t ";
            printReceipt << transaction.qnt << " \t\t " << transaction.subtotal << endl;
        }
        printReceipt << endl << "TOTAL\t\t: Rp " << total;
        printReceipt << endl << "TUNAI\t\t: Rp " << paid;
        printReceipt << endl << "KEMBALI\t\t: Rp " << change;
        printReceipt.close();

        cout << endl << "File telah diprint";
    } else {
        cout << "File tidak ditemukan";
    }
}

// Update stock in item.csv
void update_stock_item(const vector<item>& data){
    ofstream file("../../database/item.csv");
    for (const auto& Item : data){
        file << Item.id_item << "," << Item.item_name << "," << Item.item_price << "," << Item.item_stock << endl;
    }
    file.close();
}

/* Main Program */
void cashier(){
    string dateTime, input_id;
    dateTime = current_dateTime();
    vector<buy> transactions;
    vector<item> data = open_file_item();

    do {
        system("cls");
        cout << "                           INI MINIMARKET" << endl;
        cout << dateTime << "                                         " << "DANISHA MARC" << endl;
        cout << "=====================================================================" << endl;
        
        display_transactions(transactions);

        cout << endl << "TOTAL     : Rp " << total;
    } while ((input_id = transaction(transactions, data)) != "0");

    do {
        cout << endl << "TUNAI     : Rp "; cin >> paid;
        
        if(paid < total){
            cout << "Maaf uang kurang!";
        }
    } while (paid < total);
    change = paid - total;
    cout << "KEMBALI   : Rp " << change;

    print_receipt(transactions);
    update_stock_item(data);
}
