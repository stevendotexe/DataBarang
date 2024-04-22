#ifndef SEARCHDATA_H
#define SEARCHDATA_H

#include "../../auth/userFileLoad.h"

// 0: ID    | 1: Staff Name | 2: Level User | 3: Username   | 4: Password

int searchBy(const string& mode, vector<vector<string>>& data){
    int dataSize = data.size();
    if (mode == "ID"){
        string employeeID;
        cout << "\nEmployee ID: "; cin >> employeeID;
        for (size_t i = 0; i < dataSize; i++){
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
        for (size_t i = 0; i < dataSize; i++){
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
        for (size_t i = 0; i < dataSize; i++){
            if (data[i][3] == username){
                cout << "Employee Account " << data[i][0] << " " << username << endl;
                cout << "Name\t\t" << data[i][1];
                cout << "\nAccount Type\t" << data[i][2];
                cout << "\nUsername\t" << data[i][3];
                cout << "\nPassword\t" << data[i][4] << endl;
                sleep(3);
                return i; // returns the imployee index
            } 
        }
        sleep(1);
        cout << "Username \"" << username << "\" not found." << endl;
        sleep(1);
        return 1;
    }

    if (mode == "displayWHStaff"){
        for (size_t i = 0; i < dataSize; i++){
            if(data[i][2] == "WHStaff"){
                cout << "ID " << data[i][0] << "\t" <<  data[i][1] << "\t" << data[i][3] << endl;
            }
        }
    }
    if (mode == "displayCHStaff"){
        for (size_t i = 0; i < dataSize; i++){
            if(data[i][2] == "CHStaff"){
                cout << "ID " << data[i][0] << "\t" <<  data[i][1] << "\t" << data[i][3] << endl;
            }
        }
    }
}
#endif // SEARCHDATA_H