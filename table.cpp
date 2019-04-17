//
//  table.cpp
//  ENGG1340
//
//  Created by Jason Yau on 8/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "global.h"

using namespace std;

//
// PrintTableUI: print the user interface of the current table status
//
// Input: Table tableInfo[]: the array of structure Table which already read the information
//        int num_of_table: the total number of table the restaurant has
//
// Output: cout: the user interface
//
// Required library: <iomanip>, "global.h": ClearScreen(), PrintVersion()
//
void PrintTableUI(Table tableInfo[], int num_of_table, string feedback)
{
    ClearScreen();
    PrintVersion("staff");
    
    //
    // print title
    cout
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setw(33) << "Current Table Status" << setw(15) << "|" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    //
    // print header
    cout
    << setw(7) << "| Number" << setw(6) << "Size" << setw(12) << "Occupancy" << setw(12) << "Start_From" << setw(11) << "Billing |" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    //
    // print table information
    for (int i=1; i<=num_of_table; i++)
        cout << "|" << setw(7) << tableInfo[i].number << setw(6) << tableInfo[i].size << setw(12) << tableInfo[i].occupancy << setw(12) <<  tableInfo[i].occupy_time << setw(9) << tableInfo[i].billing_status << " |" << endl;
    cout
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl;
    
    //
    // print instructions
    int command_width = 14;
    cout
    << endl << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setw(command_width) << "Command" << "  Description" << setw(21) << "|" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl
    
    << "|" << setw(command_width) << "Occupy" << "  Change occupancy to occupied" << setw(4) << "|" << endl
    << "|" << setw(command_width) << "Free" << "  Change occupancy to available" << setw(3) << "|" << endl
    << "|" << setw(command_width) << "Paid" << "  Change billing to paid" << setw(10) << "|" << endl
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setw(command_width) << "Billing" << "  Check the billing detail" << setw(8) << "|" << endl
    << "|" << setw(command_width) << "Reservation" << "  Check the reservation status" << setw(4) << "|" << endl
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl << endl;
    if (feedback != "") cout << " * " << feedback;
    cout << endl << " [ Type [command] [table_num] to perform action ] " << endl << endl;
    
    return;
}

//
// ReadTableInfo: read the table information text file
//
// Input: Table tableInfo[]: the empty array of structure Table
//
// Output: Table tableInfo[]: the array of structure Table which already read the information
//         return int: the total number of table the restaurant has
//
// Required library: <fstream>
//
int ReadTableInfo(Table tableInfo[])
{
    
    int num_of_table = 0;
    ifstream fin;
    fin.open(TABLE_INFO_FILE_NAME);
    
    //
    // check file availabilty
    if (fin.fail())
    {
        cout << endl << "ReadTableInfo(): Error: Failed to open " + TABLE_INFO_FILE_NAME << endl;
        exit(1);
    }
    
    //
    // read the file
    for (int i=1; i<=MAX_NUM_OF_TABLE; i++)
    {
        fin >> tableInfo[i].number >> tableInfo[i].size >> tableInfo[i].occupancy >> tableInfo[i].occupy_time >> tableInfo[i].billing_status;
        if (fin.eof())break;   // break the loop if fin reaches the end of the file
        num_of_table++;
    }
    
    return num_of_table;
}

//
// WriteTableInfo: write the table information into the table_info_file
//
// Input: Table tableInfo[]: the array that stored the table information
//        int num_of_table: the total number of table
//
// Output: ofstream fout: write the table information into the table_info_file
//
// Required library: <fstream>
//
void WriteTableInfo(Table tableInfo[], int num_of_table)
{
    ofstream fout;
    fout.open(TABLE_INFO_FILE_NAME);
    
    if (fout.fail())
    {
        cout << endl << "WriteTableInfo: Error: Failed to open " + TABLE_INFO_FILE_NAME << endl;
        exit(1);
    }
    
    for (int i = 1; i <= num_of_table; i++)
        fout << tableInfo[i].number << " " << tableInfo[i].size  << " " << tableInfo[i].occupancy << " " << tableInfo[i].occupy_time << " " << tableInfo[i].billing_status << endl;
    
    return;
}

//
// Occupy: change the occupancy of the target table to occupied
//
// Input: Table tableInfo[]: the array that stored all table information
//        int table_no: the target table number
//
// Output: ofstream: write into the table_info_file
//         return string: the feedback to print on screen
//
// Required library: "global.h": GetTime()
//
string Occupy(Table tableInfo[], int table_no, int num_of_table)
{
    string feedback;
    
    if (tableInfo[table_no].occupancy == "Occupied")
    {
        feedback = "Table " + to_string(table_no) + " is already occupied.";
    }
    else
    {
        tableInfo[table_no].occupancy = "Occupied";
        tableInfo[table_no].occupy_time = GetTime().substr(11, 8);
        tableInfo[table_no].billing_status = "Unpaid";
        WriteTableInfo(tableInfo, num_of_table);
        feedback = "\"Occupy " + to_string(table_no) + "\" is performed.";
    }
    
    return feedback;
}

//
// Free: change the occupancy of the target table to available
//
// Input: Table tableInfo[]: the array that stored all table information
//        int table_no: the target table number
//        int num_of_table: the total number of table
//
// Output: ofstream: write into the table_info_file
//         return string: the feedback to print on screen
//
// Required library: "global.h": ToLower()
//
string Free(Table tableInfo[], int table_no, int num_of_table)
{
    string feedback;
    bool run_flag = false;
    
    if (tableInfo[table_no].occupancy == "Available")
    {
        feedback = "Table " + to_string(table_no) + " is already available.";
    }
    else if (tableInfo[table_no].billing_status == "Unpaid")
    {
        string reply;
        cout << endl
        << " * This table has not yet paid. Confirm paid?" << endl
        << " [ Type \"Yes\" / \"No\" ]" << endl << endl;
        cin >> reply;
        ToLower(reply);
        if (reply == "yes")
            run_flag = true;
        else if (reply == "no")
            feedback = "\"Free " + to_string(table_no) + "\" is not performed due to unpayment.";
        else
            feedback = "\"Free " + to_string(table_no) + "\" is not performed due to wrong input.";
    }
    else
        run_flag = true;
    
    if (run_flag)
    {
        tableInfo[table_no].occupancy = "Available";
        tableInfo[table_no].occupy_time = "--:--:--";
        tableInfo[table_no].billing_status = "------";
        WriteTableInfo(tableInfo, num_of_table);
        feedback = "\"Free " + to_string(table_no) + "\" is performed.";
    }
    
    return feedback;
}

//
// Paid: change the billing status of the target table to paid
//
// Input: Table tableInfo[]: the array that stored all table information
//        int table_no: the target table number
//        int num_of_table: the total number of table
//
// Output: ofstream: write into the table_info_file
//         return string: the feedback to print on screen
//
// Required library: NONE
//
string Paid(Table tableInfo[], int table_no, int num_of_table)
{
    string feedback;
    
    if (tableInfo[table_no].billing_status == "Paid")
    {
        feedback = "Table " + to_string(table_no) + " has already paid.";
    }
    else if (tableInfo[table_no].billing_status == "------")
    {
        feedback = "Table " + to_string(table_no) + " is not occupied yet.";
    }
    else if (tableInfo[table_no].billing_status == "Unpaid")
    {
        tableInfo[table_no].billing_status = "Paid";
        WriteTableInfo(tableInfo, num_of_table);
        feedback = "\"Paid " + to_string(table_no) + "\" is performed.";
    }
    else cout << endl << "Paid(): Error: Unknown exceptional case of struct \"Table\" member \"billing_status\": " + tableInfo[table_no].billing_status << endl;
    
    return feedback;
}
