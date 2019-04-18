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
const int MAX_NUM_OF_BILLING = 50;
const int MAX_NUM_OF_RESERVATION = 50;
const int MAX_NUM_OF_DISH = 50;
const int UI_WIDTH = 49;
const int COMMAND_BOX_WIDTH = 14;
const string TABLE_INFO_FILE_NAME = "tableInfo.txt";
const string BILLING_FILE_DIRECTORY = "billing/";
const string RESERVATION_FILE_DIRECTORY = "reservation/";
const string DISH_FILE_NAME = "dishList.txt"; 

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
struct Billing
{
    int index;
    string dish_name;
    int price;
    string arrival;
};
struct Reservation
{
    string date;
    string time;
    string surname;
    int num_of_people;
    string phone_no;
};
struct Dish
{
    int index;
    string name;
    int price;
};

//
// global variable
//
//Table tableInfo[MAX_NUM_OF_TABLE];
//Dish dishList[MAX_NUM_OF_DISH] = {};
//int num_of_dish = 0;

//
// global function
//
bool IsNumber(string);
void Debug(string);
void ToLower(string&);
void ToUpper(string&);
void ClearScreen();
void PrintVersion(string);
void PrintCommand(vector<vector<string>>);
int CheckDateValidity(string);
int CheckTimeValidity(string);
int CheckAvailability(Reservation[], int, string, string);
double CheckTimeDiff(string, string, string, string);
string GetTime();

#endif /* global_h */
