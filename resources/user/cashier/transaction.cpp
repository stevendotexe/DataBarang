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
    time_t now = time(0);   // get current time now
    tm *ltm = localtime(&now);

    /* Date Section */
    // get local date
    int day = ltm->tm_mday;
    int month = ltm->tm_mon + 1;  // month start at 0
    int year = ltm->tm_year + 1900; // year start at 1900

    // convert date to string n add 0 in front when digit is one
    string newDay = (day < 10) ? "0" + to_string(day) : to_string(day);
    string newMonth = (month < 10) ? "0" + to_string(month) : to_string(month);
    string newYear = to_string(year);
    
    string date = newDay + "/" + newMonth + "/" + newYear;
    cout << date << endl;
    /* End date section */

    /* Time section */
    // get local time
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;

    // convert time to string n add 0 in front when digit is one
    string newHour = (hour < 10) ? "0" + to_string(hour) : to_string(hour);
    string newMinute = (minute < 10) ? "0" + to_string(minute) : to_string(minute);

    string time = newHour + ":" + newMinute;
    cout << time;
    /* End time section */
};

/* Main Program */
int main(){
    create_id_transaction();
    current_dateTime();
}