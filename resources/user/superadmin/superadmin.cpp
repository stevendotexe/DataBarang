#include "../../auth/userFileLoad.h"
#include <unistd.h>
#include <csignal>
using namespace std;

ofstream file;
void saveData(vector<vector<string>>& userData, const string fileName, bool exitProgram=false){
    file.open(fileName);
    
    if (!file.is_open()){ // if file isn't opened, an error will be raised
        cerr << "Cannot open file\n";
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
        cout << "\nExiting program...";
        sleep(1);
        cout << "\nThank you for using DataBarang.";
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
        cout << "|+| Add User Data |+|\n";
        cout << "|-=================-|\n";
        cout << "|1| Input staff name\t: "; 
        cin.ignore(); getline(cin, staff_name);
        cout << "|2| Input username\t: "; getline(cin, username);
        cout << "|3| Input password\t: "; getline(cin, password);
        cout << "|4| Pick level user\t: "; 
        cout << "\n\ta. WHStaff";
        cout << "\n\tb. CHStaff";
        cout << "\nSelection: " ; getline(cin, level_user);
        if (level_user == "a" || level_user == "A"){
            level_user = "WHStaff";
            correct = true; 
        } else if (level_user == "b" || level_user == "B") {
            level_user = "CHStaff";
            correct = true;
        } else {
            cout << "\nInvalid selection";
            correct = false;
        }

        if (correct == true){
            string selection;

            cout << "Confirm addition: \n";
            cout << "Account ID\t:" << account_id;
            cout << "\nStaff name\t:" << staff_name;
            cout << "\nUsername\t:" << username;
            cout << "\nPassword\t:" << password;
            cout << "\nUser level\t:" << level_user;
            
            cout << "\nAdd new account? (Y/N): ";
            cin >> selection;
            if (selection == "Y" || selection == "y"){

                vector<string> newUser = {account_id, staff_name, level_user, username, password};
                userData.push_back(newUser);
                cout << "[i] New account added.";
                linecount = linecount + 1; // makes sure linecount adds as a new user is added
                return;

            } else {
                cout << "New account addition cancelled.";
                return;
            }
        }

    }
};

void mainMenu(vector<vector<string>>& userData, int& linecount){
    int selection;
    cout << "\n+-------------------------------------+\n";
    cout << "| DataBarang SUPERADMIN Control Panel |\n";
    cout << "+-------------------------------------+\n";
    cout << "\nWhat would you like to do? \n";
    cout << "1.\tPrint user data\n";
    cout << "2.\tAdd user data\n";
    cout << "3.\tRemove user data\n";
    cout << "4.\tSearch user\n";
    cout << "5.\tEdit user data\n";
    cout << "6.\tSave & Exit\n";
    cout << "Pilihan: "; cin >> selection;

    switch(selection){
        case 1:
            printData(userData); 
            break; 
        case 2: 
            addData(userData, linecount);
            saveData(userData, "../../../database/login.csv", false);
            break;
        case 3:
            //TODO: ADD SEACH FEATURE
            break; 
        case 4: 
            //TODO: REMOVE USER DATA 
            break; 
        case 5: 
            //TODO: EDIT USER DATA
            break;
        case 6:
            saveData(userData, "../../../database/login.csv", true);
            break;
    }
}

int main(){
    cout << "Loading data...\n";
    vector<vector<string>> userData = loadData("../../../database/login.csv"); // load data into memory
    int linecount = userData.size(); // get linecount (size of the data)
    cout << "Loading complete!\n";
    sleep(1);
    cout << "Accounts registered currently (exclusive of superadmin): " << linecount - 2;

    while (true){
        mainMenu(userData, linecount);
    }
    
    return 0; 
}
// void signalHandler(int signal){
//     string selection;
//     cout << "CTRL + C Pressed. Would you like to exit and save?";
//     cin >> selection;
//     if (selection == "N" || selection == "N"){
//         main();
//     } else if (file.is_open()){
//         cout << "Saving file...";
//         file.close();
//         cout << "Thank you for using DataBarang.";
//         exit(0);
//     }
// };