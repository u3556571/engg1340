//
//  main.cpp
//  ENGG1340
//
//  Created by Jason Yau on 1/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "global.h"
#include "read.h"

using namespace std;

//
// PrintTableUI: print the user interface of the current table status
//
// Input: Table tableInfo[]: the array of structure Table which already read the information
//        int num_of_table: the total number of table the restaurant has
//
// Output: cout: the user interface
//
// Required library: <iomanip>
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
    << "|" << setw(command_width) << "Billing" << "  Check the billing detail" << setw(8) << "|" << endl
    << "|" << setw(command_width) << "Reservation" << "  Check the reservation status" << setw(4) << "|" << endl
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl << endl;
    if (feedback != "") cout << " * " << feedback;
    cout << endl << " [ Type [command] [table_num] to perform action ] " << endl << endl;
    
    return;
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
    
    for (int i=1; i<=num_of_table; i++)
        fout << tableInfo[i].number << " " << tableInfo[i].size  << " " << tableInfo[i].occupancy << " " << tableInfo[i].occupy_time << " " << tableInfo[i].billing_status << endl;
    
    return;
}

//
// Occupy: change the occupancy of the target table to occupied
//
// Input: Table tableInfo[]: the array that stored all table information
//        int table_no: the target table number
//
// Output: return string: the feedback to print on screen
//
// Required library: NONE
//
string Occupy(Table tableInfo[], int table_no)
{
    string feedback;
    
    if (tableInfo[table_no].occupancy == "Occupied")
    {
        feedback = "Table " + to_string(table_no) + " is already occupied.";
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
// Output: return string: the feedback to print on screen
//
// Required library: NONE
//
string Free(Table tableInfo[], int table_no, int num_of_table)
{
    string feedback;
    
    if (tableInfo[table_no].occupancy == "Available")
    {
        feedback = "Table " + to_string(table_no) + " is already available.";
    }
    else
    {
        tableInfo[table_no].occupancy = "Available";
        tableInfo[table_no].occupy_time = "--:--:--";
        tableInfo[table_no].billing_status = "------";
        WriteTableInfo(tableInfo, num_of_table);
        feedback = "\"Free " + to_string(table_no) + "\" is finished.";
    }
    
    return feedback;
}

//
// PrintReservationUI: print the user interface of the reservation status
//
// Input: Reservation reservationInfo[]: the array stored the reservation information
//        int num_of_reservation: provided for the times of loop
//
// Output: cout: print the reservation user interface
//
// Required library: <iomanip>
//
void PrintReservationUI(Reservation reservationInfo[], int num_of_reservation, int table_no)
{
    ClearScreen();
    PrintVersion("staff");
    
    // print title
    cout
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setw(36) << "Reservation List of Table " << setw(2) << to_string(table_no) << setw(10) << "|" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    // print header
    cout
    << "|" << setw(9) << "Date" << setw(10) << "Time" << setw(10) << "Surname" << setw(5) << "Num" << setw(14) << "Phone_Num  |" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    // print reservation information
    for (int i=1; i<=num_of_reservation; i++)
    {
        cout << "|" << setw(12) << reservationInfo[i].date << setw(7) << reservationInfo[i].time << setw(10) << reservationInfo[i].surname << setw(5) << reservationInfo[i].num_of_people << setw(11) << reservationInfo[i].phone_no << "  |" << endl;
    }
    cout
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl;
    
    return;
}

//
// StaffVersion: for staff version of the table management system
//
void StaffVersion()
{
    // initialization for the table information
    Table tableInfo[MAX_NUM_OF_TABLE];
    int num_of_table = 0;
    num_of_table = ReadTableInfo(tableInfo);
    
    string command, feedback;
    int table_no = 0;
    
    while (command != "quit")
    {
        PrintTableUI(tableInfo, num_of_table, feedback);
        
        // let the user input the command
        cin >> command >> table_no;
        ToLower(command);
        
        if (command == "occupy")
        {
            feedback = Occupy(tableInfo, table_no);
        }
        else if (command == "free")
        {
            feedback = Free(tableInfo, table_no, num_of_table);
        }
        else if (command == "billing")
        {
            Debug("billing");
        }
        else if (command == "reservation")
        {
            Reservation reservationInfo[MAX_NUM_OF_RESERVATION];
            int num_of_reservation = 0;
            
            num_of_reservation = ReadReservationTable(reservationInfo, table_no);
            
            PrintReservationUI(reservationInfo, num_of_reservation, table_no);
        }
        else
        {
            feedback = "Wrong command. Please type again.";
        }
    }
    
    return;
}

int main()
{
    /*Table tableInfo[MAX_NUM_OF_TABLE];
    int num_of_table = 0;
    num_of_table = ReadTableInfo(tableInfo);
    PrintTableUI(tableInfo, num_of_table);*/
    
    /*Reservation reservationInfo[MAX_NUM_OF_RESERVATION];
    int num_of_reservation = 0;
    num_of_reservation = ReadReservationTable(reservationInfo, 1);
    PrintReservationUI(reservationInfo, num_of_reservation, 1);*/
    
    StaffVersion();
    
    return 0;
}
