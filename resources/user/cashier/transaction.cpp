#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;

/* Create Id Transaction */
void create_id_transaction(){
    string id_transaction = "trs";    // default value
    int no_transaction = 0;         // default value

    no_transaction = no_transaction + 25; // is random number

    id_transaction = id_transaction + string(4 - to_string(no_transaction).length(), '0') + to_string(no_transaction); // to make trs00**

    cout << id_transaction << endl;
};

/* Current time based on system */
void current_dateTime(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    cout << date << endl;
    string time = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);
    cout << time;
};

/* Main Program */
int main(){
    create_id_transaction();
    current_dateTime();
}