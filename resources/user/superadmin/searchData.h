#ifndef SEARCHDATA_H
#define SEARCHDATA_H

#include "../../auth/userFileLoad.h"
using namespace std;
// 0: ID    | 1: Staff Name | 2: Level User | 3: Username   | 4: Password

int searchBy(const string& mode, vector<vector<string>>& data){
    int dataSize = data.size();
    if (mode == "ID"){
        string employeeID; // input string to search by employee id
        cout << "\nEmployee ID: "; cin >> employeeID;
        for (int i = 0; i < dataSize; i++){
            if (data[i][0] == employeeID){
                cout << "Employee " << employeeID << endl;
                cout << "Name\t\t" << data[i][1];
                cout << "\nAccount Type\t" << data[i][2];
                cout << "\nUsername\t" << data[i][3];
                cout << "\nPassword\t" << data[i][4];
                sleep(1);
                return i; // returns the imployee index
            } 
        }
        cout << "Employee ID " << employeeID << " not found." << endl;
        return 1;
    }

    if (mode == "staff_name"){
        string employeeName;
        cout << "\nEmployee name: "; cin.ignore(); getline(cin, employeeName);
        cout << "Searching....\n";
        for (int i = 0; i < dataSize; i++){
            if (data[i][1] == employeeName){
                cout << "Employee Account " << data[i][0] << " " << employeeName << endl;
                cout << "Name\t\t" << data[i][1];
                cout << "\nAccount Type\t" << data[i][2];
                cout << "\nUsername\t" << data[i][3];
                cout << "\nPassword\t" << data[i][4] << endl;
                sleep(3);
                return i; // returns the imployee index
            } 
        }
        sleep(1);
        cout << "Employee \"" << employeeName << "\" not found." << endl;
        sleep(1);
        return 1;
    }

    if (mode == "username"){
        string username;
        cout << "\nUsername: "; cin.ignore(); getline(cin, username);
        cout << "Searching....\n";
        for (int i = 0; i < dataSize; i++){
            if (data[i][3] == username){
                cout << "Employee Account " << data[i][0] << " " << username << endl;
                cout << "Name\t\t" << data[i][1];
                cout << "\nAccount Type\t" << data[i][2];
                cout << "\nUsername\t" << data[i][3];
                cout << "\nPassword\t" << data[i][4] << endl;
                sleep(3);
                return i; // returns the employee index
            } 
        }
        sleep(1);
        cout << "Username \"" << username << "\" not found." << endl;
        sleep(1);
        return 1;
    }

    if (mode == "displayWHStaff"){
        for (int i = 0; i < dataSize; i++){
            if(data[i][2] == "WHStaff"){
                cout << "ID " << data[i][0] << "\t" <<  data[i][1] << "\t" << data[i][3] << endl;
            }
        }
    }
    if (mode == "displayCHStaff"){
        for (int i = 0; i < dataSize; i++){
            if(data[i][2] == "CHStaff"){
                cout << "ID " << data[i][0] << "\t" <<  data[i][1] << "\t" << data[i][3] << endl;
            }
        }
    }
}

void editName(vector<vector<string>>& data, int& userIndex){
    string newName;
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, newName);
    data[userIndex][1] = newName;
    cout << "Name updated successfully!" << endl;
    return;
}

void switchUserType(vector<vector<string>>& data, int& userIndex){
    string currentType = data[userIndex][2];
    string newType, confirmation;
    if (currentType == "CHStaff"){
        newType = "WHStaff";
    } else if (currentType == "WHStaff"){
        newType = "CHStaff";
    }
    cout << "Current user type is " << currentType << ". Switch to " << newType << "?(Y/N): "; cin >> confirmation;
    if (confirmation == "Y" || confirmation == "y"){
        data[userIndex][2] = newType;
        return;

    } else {
        cout << "Aborting operation...";
        return;
    }
}

void changeUsername(vector<vector<string>>& data, int& userIndex){
    string newUsername;
    cout << "Enter new username: ";
    cin.ignore();
    getline(cin, newUsername);
    data[userIndex][3] = newUsername;
    cout << "Username updated successfully!" << endl;
    return;
}

void changePassword(vector<vector<string>>& data, int& userIndex){
    string newPassword;
    cout << "Enter new password: ";
    cin.ignore();
    getline(cin, newPassword);
    data[userIndex][4] = newPassword;
    cout << "Password updated successfully!" << endl;
    return;
}

void modifyUser(vector<vector<string>>& data, int& userIndex){
    while (true){
        int selection;
        cout << "What operation would you like to do?\n";
        cout << "1. Edit name\n";
        cout << "2. Switch user type\n";
        cout << "3. Edit username\n";
        cout << "4. Edit password\n";
        cout << "5. Complete & Exit\n";
        cout << "Selection: ";
        cin.ignore(); cin >> selection;
        cout << endl;
        switch (selection)
        {
        case 1:
            editName(data, userIndex);
            break;
        case 2:
            switchUserType(data, userIndex);
            break;
        case 3:
            changeUsername(data, userIndex);
            break;
        case 4:
            changePassword(data, userIndex);
            break;
        case 5:
            return;
        default:
            return;
        }
    }
}

void editUser(vector<vector<string>>& data){
    while (true){
        int selection;
        string userIndex;
        cout << "\n+==============+\n";
        cout << "| User Editing |\n";
        cout << "+==============+\n";
        cout << "1. Select user via ID\n";
        cout << "2. Search for user\n";
        cout << "3. Exit\n";
        cout << "Operation: ";
        cin.ignore();
        cin >> selection;

        switch (selection) {
            case 1:
                cout << "Input user ID: "; cin >> userIndex;
                break;
            case 2:
            int selection2;
                cout << "1. Search via ID\n";
                cout << "2. Search via name\n";
                cout << "3. Search via username\n";
                cout << "Selection: "; cin >> selection2;
                switch (selection2) {
                    case 1:
                        userIndex = searchBy("ID", data);
                        break;
                    case 2:
                        userIndex = searchBy("staff_name", data);
                        break;
                    case 3:
                        userIndex = searchBy("username", data);
                        break;
                    default:
                        break;
                }
            default:
                cout << "Invalid input!";
                break;
            }
        int intUserIndex = stoi(userIndex);
        cout << "Employee ID " << userIndex << endl;
        cout << "Name\t: " << data[intUserIndex][1] << endl;
        cout << "Type\t: " << data[intUserIndex][2] << endl;
        cout << "Username\t: " << data[intUserIndex][3] << endl;
        cout << "Password\t: " << data[intUserIndex][4] << endl;

        string selectionSTR;
        cout << "Edit this user? (Y/N): "; cin >> selectionSTR;
        if (selectionSTR == "Y" || selectionSTR == "y"){
            modifyUser(data, intUserIndex);
            return;
        } else {
            cout << "\nreturning...\n";
        }
    }
}

#endif // SEARCHDATA_H