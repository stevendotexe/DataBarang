#include "fileLoad.h"

using namespace std;

tuple<bool, string, string> authenticate(vector<vector<string>> data){ // function to authenticate the user 
    // 0: Account ID | 1: Staff Name | 2: User Level | 3: Username | 4: Password //
    while (true){
        string inputUsername, inputPassword, userPassword;
        cout << "\nUsername\t: ";
        getline(cin, inputUsername);
        cout << "Password\t: ";
        getline(cin, inputPassword);

        for(int i = 0; i < data.size(); i++){ // iterate over data
            if (data[i][3] == inputUsername){ 
                if(data[i][4] == inputPassword){
                    tuple<bool, string, string> authResult(true, inputUsername, data[i][2]);
                    return authResult; // returns a tuple object
                }
            }
        }
        tuple<bool, string, string> fail(false, "-", "Username Not Found");
        return fail;
    }
}

void login(){
    cout << "======================================================================" << endl;
    cout << "Welcome to DataBarang, please wait a moment while we load some data..." << endl;
    cout << "======================================================================" << endl;

    vector<vector<string>> accountData = loadData("../../database/login.csv"); // load account data into vector

    cout << ("\nData loaded!\n");
    tuple<bool, string, string> loginResult = authenticate(accountData);
    bool loginStatus = get<0>(loginResult); // boolean to determine account is logged in or not
    string username = get<1>(loginResult);
    string accountType = get<2>(loginResult);

    cout << "Selamat datang, " << accountType;

    return 0;
}
