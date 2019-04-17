//
//  global.cpp
//  ENGG1340
//
//  Created by Jason Yau on 2/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#include <iostream>
#include <iomanip>

#include "global.h"

using namespace std;

//
// Debug: print debug message in a faster way
//
// Input: string msg: the message which need to print
//
// Output: cout: the debug message
//
// Required library: NONE
//
void Debug(string msg)
{
    cout << "Debug: " + msg << endl;
    
    return;
}

//
// ToLower: convert whole c++ string into lower case
//
// Input: string string_: the string that needs to change into lower case
//
// Output: string string_: the string that already converted into lower case (pass-by-reference)
//
// Required library: NONE
//
void ToLower(string &string_)
{
    for (int i = 0; i < string_.length(); i++)
        string_[i] = tolower(string_[i]);
    
    return;
}

//
// ToUpper: convert whole c++ string into upper case
//
// Input: string string_: the string that needs to change into upper case
//
// Output: string string_: the string that already converted into upper case (pass-by-reference)
//
// Required library: NONE
//
void ToUpper(string &string_)
{
    for (int i = 0; i < string_.length(); i++)
        string_[i] = toupper(string_[i]);
    
    return;
}

//
// IsNumber: check whether the string is all number or not
//
// Input: string string_: the string which needed to check
//
// Output: return bool: true if the string is all number
//                      false if the string is not all number
//
// Required library: NONE
//
bool IsNumber(string string_)
{
    for (int i = 0; i < string_.length(); i++)
        if (string_[i] < 48 || string_[i] > 57)
            return false;
    
    return true;
}

//
// ClearScreen: clear the screen by printing 50 empty lines
//
// Input: NONE
//
// Output: cout: 50 empty lines
//
// Required library: NONE
//
void ClearScreen()
{
    for (int i=0; i<10; i++)
        cout << endl << endl << endl << endl << endl;
    
    return;
}

//
// PrintVersion: print the version of this system for the user interface
//
// Input: string version: "staff" or "customer"
//
// Output: cout: print the user interface
//
// Required library: <iomanip>
//
void PrintVersion(string version)
{
    cout
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl
    << "||" << setw(UI_WIDTH - 2) << "||" << endl;
    
    int staff_width = UI_WIDTH / 2 + 14;
    int customer_width = UI_WIDTH / 2 - 17;
    if (version == "staff")
        cout << "||" << setw(staff_width) << "Table Management System (Staff)" << setw(UI_WIDTH - staff_width - 2) << "||" << endl;
    else if (version == "customer")
        cout << "||" << setw(UI_WIDTH - customer_width - 2) << "Table Management System (Customer)" << setw(customer_width) << "||" << endl;
    else cout << endl << "PrintVersion(): Error: Unknown exceptional case of input string \"version\": " + version << endl;
    
    cout
    << "||" << setw(UI_WIDTH - 2) << "||" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl;
}

//
// CheckDateValidity: check whether the date string is valid or not
//
// Input: string date: stored the date of the reservation
//
// Output: return int: 1 if the date is within one week since today
//                     -1 if the format is wrong
//                     -2 if the date is invalid
//                     -3 if the date is not within one week since today
//
// Required library: NONE
//
// *** Citation: This method is cited from http://www.cplusplus.com/reference/ctime/
//
int CheckDateValidity(string date)
{
    //
    // check if the format is valid
    if (date.length() > 10) return -1;
    if (date[2] != '/' || date[5] != '/') return -1;
    for (int i=0; i<10; i++)
    {
        if (i == 2 || i == 5) continue;
        if (date[i] < '0' || date[i] > '9') return -1;
    }
    
    //
    // check if the date is valid
    if (date.substr(3, 2) < "01" || date.substr(3, 2) > "12") return -2;
    
    if (date.substr(0, 2) < "01") return -2;
    
    if (date.substr(3, 2) == "02")
        {if (date.substr(0, 2) > "29") return -2;}
    else if (date.substr(3, 2) == "04" || date.substr(3, 2) == "06" || date.substr(3, 2) == "09" || date.substr(3, 2) == "11")
        {if (date.substr(0, 2) > "30") return -2;}
    else if (date.substr(0, 2) > "31") return -2;
    
    //
    // check if the date is within one week after
    struct tm today, reservation;
    time_t rawtime;
    time(& rawtime);
    today = * localtime(& rawtime);
    today.tm_hour = 0;
    today.tm_min = 0;
    today.tm_sec = 0;
    //
    reservation = today;
    reservation.tm_year = stoi(date.substr(6, 4)) - 1900;
    reservation.tm_mon = stoi(date.substr(3, 2)) - 1;
    reservation.tm_mday = stoi(date.substr(0, 2));
    //
    double diff;
    diff = difftime(mktime(& reservation), mktime(& today));
    if (diff < 0) return -3;
    if (diff > 86400 * 6 /*num of date*/) return -3;
    
    return 1;
}

//
// *** to-do: add if-function to check whether the time is within the opening hour or not
//
// CheckTimeValidity: check whether the time string is valid or not
//
// Input: string time: stored the time of the reservation
//
// Output: return int: 1 if the time is in half an hour interval
//                     -1 if the format is wrong
//                     -2 if the time is wrong
//                     -3 if the time is not in half an hour interval
//
// Required library: NONE
//
int CheckTimeValidity(string time)
{
    //
    // check if the format is valid
    if (time.length() > 5) return -1;
    if (time[2] != ':') return -1;
    for (int i=0; i<5; i++)
    {
        if (i == 2) continue;
        if (time[i] < '0' || time[i] > '9') return -1;
    }
    
    //
    // check if the time is valid
    if (time.substr(0, 2) > "23") return -2;
    if (time.substr(3, 2) > "59") return -2;
    
    //
    // check if the time is in half an hour interval
    if (time.substr(3, 2) != "00" && time.substr(3, 2) != "30") return -3;
    
    //
    // check if the time is within the opening hour or not
    
    return 1;
}

//
// CheckTimeDiff: check the difference between the two provided time
//
// Input: string date_1: the first date string
//        string time_1: the first time string
//        string date_2: the second date string
//        string time_2: the second time string
//
// Output: return diff: the difference between the two provided time
//
// Required library: NONE
//
// *** Citation: This method is cited from http://www.cplusplus.com/reference/ctime/
//
double CheckTimeDiff(string date_1, string time_1, string date_2, string time_2)
{
    //
    // check if the date is within two hour
    struct tm info_1, info_2;
    time_t rawtime;
    time(& rawtime);
    info_1 = * localtime(& rawtime);
    info_2 = info_1;
    //
    info_1.tm_year = stoi(date_1.substr(6, 4)) - 1900;
    info_1.tm_mon = stoi(date_1.substr(3, 2)) - 1;
    info_1.tm_mday = stoi(date_1.substr(0, 2));
    info_1.tm_hour = stoi(time_1.substr(0, 2));
    info_1.tm_min = stoi(time_1.substr(3, 2));
    info_1.tm_sec = 0;
    //
    info_2.tm_year = stoi(date_2.substr(6, 4)) - 1900;
    info_2.tm_mon = stoi(date_2.substr(3, 2)) - 1;
    info_2.tm_mday = stoi(date_2.substr(0, 2));
    info_2.tm_hour = stoi(time_2.substr(0, 2));
    info_2.tm_min = stoi(time_2.substr(3, 2));
    info_2.tm_sec = 0;
    //
    double diff;
    diff = difftime(mktime(& info_1), mktime(& info_2));
    // CheckWithinTwoHr()
    //if (diff <= -1800 * 4 /*number of half hour*/) return false;
    //if (diff >= 1800 * 4 /*number of half hour*/) return false;
    
    return diff;
}

//
// CheckAvailability: check whether the date and time of the reservation is valid or not
//
// Input: Reservation reservationInfo[]: stored the reservation information
//        int num_of_reservation: the total number of reservation
//        string date: stored the date of the reservation
//        string time: stored the time of the reservation
//
// Output: return int: -1 if the date and time of the reservation is not available
//                     i (the position in the array) if the date and time of the reservation is available
//
// Required library: <ctime>
//
int CheckAvailability(Reservation reservationInfo[], int num_of_reservation, string date, string reservation_time)
{
    int i;
    double prev = -1, now = 0;
    
    for (i = 1; i<=num_of_reservation; i++)
    {
        now = CheckTimeDiff(reservationInfo[i].date, reservationInfo[i].time, date, reservation_time);
        
        // check whether the time difference is between two hour
        if (now > -1800 * 4 /*number of half hour*/ && now < 1800 * 4 /*number of half hour*/) return -1;
        
        // return the position if it is available
        if (prev < 0 && now > 0)
            return i;
        
        prev = now;
    }
    
    return i;
}

//
// GetTime: return full details of the current date and time
//
// Input: NONE
//
// Output: return string: return the current date and time in string form
//
// Required library: <ctime>
//
// *** Citation: This method is cited from http://www.cplusplus.com/reference/ctime/ctime/
//
string GetTime()
{
    string date_time;
    
    time_t rawtime;
    time(&rawtime);
    
    date_time = ctime(&rawtime);
    
    return date_time;
}
