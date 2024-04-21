#include "fileLoad.h"
using namespace std;

int main(){
    vector<vector<string>> accountData = loadData("login.csv");

    printData(accountData);
}