#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
using namespace std;

vector<array<string>> loadData(string fileName){

    fstream theFile;
    theFile.open(fileName);

    vector<array<string, 5>> account_data = {
        "account_id", 
        "staff_name", 
        "level_user", 
        "username", 
        "password"
    };

    int linecount;
    string line;
    while(getline(theFile, line)){
        ++linecount;
    }

    // TODO: INPUT ACCOUNT ID, STAFF NAME, USERNAME, PASSWORD, INTO ACCOUNT_DATA VECTOR

    theFile.close();


    return account_data;  
};

int main(){
    vector<array<string>> accountData;
    loadData("login.csv");

}
