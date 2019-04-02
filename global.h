//
//  global.h
//  ENGG1340
//
//  Created by Jason Yau on 2/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#ifndef global_h
#define global_h

using namespace std;

//
// global constant
//
const int MAX_NUM_OF_TABLE = 50;
const int MAX_NUM_OF_RESERVATION = 50;
const int UI_WIDTH = 49;
const string TABLE_INFO_FILE_NAME = "tableInfo.txt";
const string FILE_DIRECTORY = "reservation/";

//
// global structure
//
struct Table
{
    int number;
    int size;
    string occupancy;
    string occupy_time;
    string billing_status;
};

struct Reservation
{
    string date;
    string time;
    string surname;
    int num_of_people;
    string phone_no;
};

//
// global function
//
void Debug(string);
void ToLower(string&);
void ClearScreen();
void PrintVersion(string);

#endif /* global_h */
