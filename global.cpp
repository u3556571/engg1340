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
// Input: string string_: a string that needs to perform the action
//
// Output: string string_: whole string that already all convert into lower case (pass-by-reference)
//
// Required library: NONE
//
void ToLower(string &string_)
{
    for (int i=0; i<string_.length(); i++)
    {
        string_[i] = tolower(string_[i]);
    }
    
    return;
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
// Input: string version: staff or customer
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
    
    cout
    << "||" << setw(UI_WIDTH - 2) << "||" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl;
}
