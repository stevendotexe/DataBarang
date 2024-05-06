#include "searchData.h"
using namespace std;

ofstream file;
void saveData(vector<vector<string>>& userData, const string fileName, bool exitProgram=false){
    file.open(fileName);
    
    if (!file.is_open()){ // if file isn't opened, an error will be raised
        cerr << "Tidak bisa membuka file.\n";
        exit(1);
    }
    
    for (size_t i = 0; i < userData.size(); i++){ // for loop to write to file
        for (size_t j = 0; j < 5; j++){ // j to access the inside of the <vector<vector<string>>
            file << userData[i][j];
            if (j < 4){
                file << ","; // makes sure the tailing line is not a comma
            }
        }
        file << "\n";
    }
    file.close();
    if (exitProgram == true){
        cout << "\nSedang keluar...";
        sleep(1);
        cout << "\nTerima kasih sudah menggunakan DataBarang.";
        exit(0);
    }
}

void addData(vector<vector<string>>& userData, int& linecount){
    string account_id = to_string(linecount - 1);
    bool correct; // to confirm user input is correct on staff level
    string staff_name, level_user, username, password;
    while (true){
        correct = false;
        cout << "\n|-=================-|\n";
        cout << "|+|Manambahkan Data |+|\n";
        cout << "|-=================-|\n";
        cout << "|1| Masukkan nama staf\t: "; 
        cin.ignore(); getline(cin, staff_name);
        cout << "|2| Username\t: "; getline(cin, username);
        cout << "|3| Password\t: "; getline(cin, password);
        cout << "|4| Pilih level user\t: "; 
        cout << "\n\ta. WHStaff";
        cout << "\n\tb. CHStaff";
        cout << "\nPilihan: " ; getline(cin, level_user);
        if (level_user == "a" || level_user == "A"){
            level_user = "WHStaff";
            correct = true; 
        } else if (level_user == "b" || level_user == "B") {
            level_user = "CHStaff";
            correct = true;
        } else {
            cout << "\nSeleksi Salah!";
            correct = false;
        }

        if (correct == true){
            string selection;

            cout << "Konfirmasi Penambahan: \n";
            cout << "Account ID\t:" << account_id;
            cout << "\nNama Staf\t:" << staff_name;
            cout << "\nUsername\t:" << username;
            cout << "\nPassword\t:" << password;
            cout << "\nUser level\t:" << level_user;
            
            cout << "\nTambahkan akun? (Y/N): ";
            cin >> selection;
            if (selection == "Y" || selection == "y"){

                vector<string> newUser = {account_id, staff_name, level_user, username, password};
                userData.push_back(newUser);
                cout << "[i] Akun baru ditambahkan.";
                linecount = linecount + 1; // makes sure linecount adds as a new user is added
                return;

            } else {
                cout << "Penambahan akun dibatalkan.";
                return;
            }
        }

    }
};

void searchData(vector<vector<string>>& userData){
    int selection, employeeIndex;
    cout << "\nDataBarang SearchData\n";
    cout << "1. Search lewat Account ID\n";
    cout << "2. Search lewat nama\n";
    cout << "3. Search lewat username\n";
    cout << "4. Print semua WHStaff\n";
    cout << "5. Print semua CHStaff\n";
    cout << "6. Keluar";
    cout << "Pilihan: "; cin >> selection;
    switch(selection){
        case 1:
            searchBy("ID", userData);
            break;
        case 2:
            searchBy("staff_name", userData);
            break;
        case 3:
            searchBy("username", userData);
            break;
        case 4:
            searchBy("displayWHStaff", userData);
            break;
        case 5:
            searchBy("displayCHStaff", userData);
            break;
        case 6:
            return;
        default:
            cout << "Input Salah!";
            break;
    }
}

void mainMenu(vector<vector<string>>& userData, int& linecount){
    int selection;
    cout << "\n+-------------------------------------+\n";
    cout << "| DataBarang SUPERADMIN Control Panel |\n";
    cout << "+-------------------------------------+\n";
    cout << "\nApa yang anda ingin lakukan? \n";
    cout << "1.\tPrint data user\n";
    cout << "2.\tTambah user data\n";
    cout << "3.\tCari user\n";
    cout << "4.\tEdit & hapus user data\n";
    cout << "5.\tSimpan & keluar\n";
    cout << "Pilihan: "; cin >> selection;

    switch(selection){
        case 1:
            printData(userData); 
            break; 
        case 2: 
            addData(userData, linecount);
            saveData(userData, "../../database/login.csv");
            break;
        case 3:
            searchData(userData);
            break;
        case 4: 
            editUser(userData);
            saveData(userData, "../../database/login.csv", false);
            break;
        case 5:
            saveData(userData, "../../database/login.csv", true);
            break;
        default:
            cout << "Invalid selection!";
            break;
    }
}

int superAdmin(){
    cout << "Memuat data...\n";
    vector<vector<string>> userData = loadData("../../database/login.csv"); // load data into memory
    int linecount = userData.size(); // get linecount (size of the data)
    cout << "Memuat selesai!\n";
    sleep(1);
    cout << "Jumlah akun yang telah terdaftar (selain superAdmin): " << linecount - 2;

    while (true){
        mainMenu(userData, linecount);
    }
    
    return 0; 
}