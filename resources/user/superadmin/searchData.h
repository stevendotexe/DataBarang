#ifndef SEARCHDATA_H
#define SEARCHDATA_H

#include "../../auth/userFileLoad.h"
using namespace std;
// 0: ID    | 1: Staff Name | 2: Level User | 3: Username   | 4: Password

int searchBy(const string& mode, vector<vector<string>>& data){
    int dataSize = data.size();
    if (mode == "ID"){
        string employeeID; // input string to search by employee id
        cout << "\nID Akun: "; cin >> employeeID;
        for (int i = 0; i < dataSize; i++){
            if (data[i][0] == employeeID){
                cout << "Akun " << employeeID << endl;
                cout << "Nama\t\t" << data[i][1];
                cout << "\nTipe Akun\t" << data[i][2];
                cout << "\nUsername\t" << data[i][3];
                cout << "\nPassword\t" << data[i][4] << endl;
                sleep(1);
                return i; // returns the employee index
            } 
        }
        cout << "ID akun " << employeeID << " tidak ditemukan." << endl;
        return 1;

    } else if (mode == "staff_name"){
        string employeeName;
        cout << "\nNama akun: "; cin.ignore(); getline(cin, employeeName);
        cout << "Mencari....\n";
        for (int i = 0; i < dataSize; i++){
            if (data[i][1] == employeeName){
                cout << "Akun ID " << data[i][0] << " " << employeeName << endl;
                cout << "Nama\t\t" << data[i][1];
                cout << "\nTipe Akun\t" << data[i][2];
                cout << "\nUsername\t" << data[i][3];
                cout << "\nPassword\t" << data[i][4] << endl;
                sleep(3);
                return i; // returns the imployee index
            } 
        }
        sleep(1);
        cout << "Nama akun \"" << employeeName << "\" tidak ditemukan." << endl;
        sleep(1);
        return 1;

    } else if (mode == "username"){
        string username;
        cout << "\nUsername: "; cin.ignore(); getline(cin, username);
        cout << "Mencari....\n";
        for (int i = 0; i < dataSize; i++){
            if (data[i][3] == username){
                cout << "Akun ID " << data[i][0] << " " << username << endl;
                cout << "Nama\t\t" << data[i][1];
                cout << "\nTipe Akun\t" << data[i][2];
                cout << "\nUsername\t" << data[i][3];
                cout << "\nPassword\t" << data[i][4] << endl;
                sleep(3);
                return i; // returns the employee index
            } 
        }
        sleep(1);
        cout << "Username \"" << username << "\" tidak ditemukan" << endl;
        sleep(1);
        return 1;

    } else if (mode == "displayWHStaff"){
        for (int i = 0; i < dataSize; i++){
            if(data[i][2] == "WHStaff"){
                cout << "ID " << data[i][0] << "\t" <<  data[i][1] << "\t" << data[i][3] << endl;
            }
        }

    } else if (mode == "displayCHStaff"){
        for (int i = 0; i < dataSize; i++){
            if(data[i][2] == "CHStaff"){
                cout << "ID " << data[i][0] << "\t" <<  data[i][1] << "\t" << data[i][3] << endl;
            }
        }
    } else {
        cout << "Mode tidak sesuai dengan mode yang ada.";
        return 1;
    }
    return 1;
}

void editUserType(vector<vector<string>>& data, int& userIndex){
    string currentType = data[userIndex][2];
    string newType, confirmation;
    if (currentType == "CHStaff"){
        newType = "WHStaff";
    } else if (currentType == "WHStaff"){
        newType = "CHStaff";
    }
    cout << "Tipe user sekarang " << currentType << ". Ubah menjadi " << newType << "?(Y/N): "; cin >> confirmation;
    if (confirmation == "Y" || confirmation == "y"){
        data[userIndex][2] = newType;
        return;

    } else {
        cout << "Membatalkan operasi...";
        return;
    }
}

void editEmployeeName(vector<vector<string>>& data, int& userIndex){ // done
    string newName;
    cout << "Nama baru: ";
    cin.ignore();
    getline(cin, newName);
    cout << "Nama telah diubah.";
    
    data[userIndex][1] = newName;

    return;
}

void editUsername(vector<vector<string>>& data, int& userIndex){ // done
    string newUsername;
    cout << "Username baru: ";
    cin.ignore();
    getline(cin, newUsername);
    cout << "Username telah diubah.";
    
    data[userIndex][3] = newUsername;

    return;
}

void editPassword(vector<vector<string>>& data, int& userIndex){ // done
    string newPassword;
    cout << "Password baru: ";
    cin.ignore();
    getline(cin, newPassword);
    cout << "Password telah diubah.";
    
    data[userIndex][4] = newPassword;

    return;
}

void deleteUser(vector<vector<string>>& data, int& userIndex){
    string selection;
    cout << "Apakah anda ingin menghapus user ID" << data[userIndex][0] << "?\n";
    sleep(0.5);
    cout << "Aksi ini tidak dapat diurungkan.\n";
    sleep(0.5);
    cout << "Ketik KONFIRMASI mengkonfirmasi penghapusan akun: "; cin.ignore(); getline(cin, selection);
    if (selection == "KONFIRMASI"){
        cout << "Delete account ID" << data[userIndex][0] << "? \n";
        sleep(1);
        cout << "Y/N\t";
        cin >> selection;
        if (selection == "y" || selection == "Y"){
            data.erase(data.begin() + userIndex);
            cout << "Data dihapus.";
            sleep(1);
            return;
        }

    } else {
        cout << "Penghapusan akun dibatalkan.";
        return;
    }
}

void modifyUser(vector<vector<string>>& data, int& userIndex){
    while (true){
        int selection;
        cout << "Operasi apa yang ingin anda lakukan?\n";
        cout << "1. Edit nama\n";
        cout << "2. Ubah tipe user\n";
        cout << "3. Ubah username\n";
        cout << "4. Ubah password\n";
        cout << "5. Hapus user\n";
        cout << "6. Selesai dan keluar\n";
        cout << "Pilihan: ";
        cin.ignore(); cin >> selection;
        cout << endl;
        switch (selection)
        {
            case 1:
                editEmployeeName(data, userIndex);
                break;
            case 2:
                editUserType(data, userIndex);
                break;
            case 3:
                editUsername(data, userIndex);
                break;
            case 4:
                editPassword(data, userIndex);
                break;
            case 5:
                deleteUser(data, userIndex);
                break;
            case 6:
                break;
            default:
                break; // switch case break
        }
        break; // while loop break
    } 
    return;
}

int userEditMenu(vector<vector<string>>& data){
    int userIndex;
    int selection;

    while(true){
        cout << "\n+==============+\n";
        cout << "| User Editing |\n";
        cout << "+==============+\n";
        cout << "1. Pilih user lewat ID\n";
        cout << "2. Cari user\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";
        cin.ignore();
        cin >> selection;
        switch (selection) {
            case 1:
                cout << "Masukkan user ID: "; 
                cin >> userIndex;
                return userIndex;
            case 2:
                int selection2;
                cout << "1. Cari via ID\n";
                cout << "2. Cari via nama\n";
                cout << "3. Cari via username\n";
                cout << "Pilihan: "; cin >> selection2;
                switch (selection2) {
                    case 1:
                        userIndex = searchBy("ID", data);
                        return userIndex;
                    case 2:
                        userIndex = searchBy("staff_name", data);
                        return userIndex;
                    case 3:
                        userIndex = searchBy("username", data);
                        return userIndex;
                    default:
                        cout << "Invalid input!";
                        break;
                }
            case 3:
                return -1;
            default:
                cout << "Input salah!";
                break;
        } break;
    }
    return 0;
}

void editUser(vector<vector<string>>& data){
    int userIndex;

    userIndex = userEditMenu(data)+1;

    cout << "ID Akun " << userIndex << endl;
    cout << "Nama\t\t: " << data[userIndex][1] << endl;
    cout << "Tipe\t\t: " << data[userIndex][2] << endl;
    cout << "Username\t: " << data[userIndex][3] << endl;
    cout << "Password\t: " << data[userIndex][4] << endl;

    string selectionSTR;
    cout << "Edit user ini? (Y/N): "; cin >> selectionSTR;
    if (selectionSTR == "Y" || selectionSTR == "y"){
        modifyUser(data, userIndex);
        return;
    } else {
        cout << "\nsedang kembali...\n";
        return;
    }
    }

#endif // SEARCHDATA_H