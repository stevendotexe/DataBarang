#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* Create Id Transaction */
void create_id_transaction(){
    string id_transaction = "trs";    // default value
    int no_transaction = 0;         // default value

    no_transaction = no_transaction + 25;

    id_transaction = id_transaction + string(4 - to_string(no_transaction).length(), '0') + to_string(no_transaction);

    cout << id_transaction;
};

/* Main Program */
int main(){
    create_id_transaction();
}