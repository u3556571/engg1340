//
//  reservation.cpp
//  ENGG1340
//
//  Created by Jason Yau on 8/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "global.h"

using namespace std;

//
//  PrintReservationUI: print the user interface of the reservation status
//
//  Input: Reservation reservationInfo[]: the array stored the reservation information
//         int num_of_reservation: provided for the times of loop
//
//  Output: cout: print the reservation user interface
//
//  Required library: <vector>, <iomanip>, "global.h": ClearScreen(), PrintVersion()
//
void PrintReservationUI(Reservation reservationInfo[], int num_of_reservation, int table_no, string feedback)
{
    ClearScreen();
    PrintVersion("staff");
    
    //
    // print title
    cout
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setw(36) << "Reservation List of Table " << setw(2) << to_string(table_no) << setw(10) << "|" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    //
    // print header
    cout
    << "|" << setw(9) << "Date" << setw(10) << "Time" << setw(10) << "Surname" << setw(5) << "Num" << setw(14) << "Phone_Num  |" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    //
    // print reservation information
    //
    // no reservation case
    if (num_of_reservation == 0)
        cout << "|" << setw(33) << "No reservation yet" << setw(15) << "|" << endl;
    //
    // normal case
    for (int i=1; i<=num_of_reservation; i++)
    {
        cout << "|" << setw(12) << reservationInfo[i].date << setw(7) << reservationInfo[i].time << setw(10) << reservationInfo[i].surname << setw(5) << reservationInfo[i].num_of_people << setw(11) << reservationInfo[i].phone_no << "  |" << endl;
    }
    cout
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl;
    
    
    //
    // print instructions
    // * Only edit the string inside the 2d vector
    //
    vector<vector<string>> command
    {
        {"Add", "Add a reservation"},
        {"Delete", "Delete a reservation"},
        {"", ""},
        {"Return", "Return to the main page"}
    };
    PrintCommand(command);
    
    
    if (feedback != "") cout << " * " << feedback;
    cout << endl << " [ Type [command] to perform action ] " << endl << endl;
    
    return;
}

//
//  ReadReservationTable: read the reservation status of the required table
//
//  Input: Reservation reservationInfo[]: the empty array of structure Reservation
//         int table_no: the table number which the staff want to know the reservation status
//
//  Output: Reservation reservationInfo[]: the array that already stored the reservation status
//          return int: the total number of reservation in the coming week
//
//  Required library: <fstream>
//
int ReadReservationTable(Reservation reservationInfo[], int table_no)
{
    int num_of_reservation = 0;
    string file_name = RESERVATION_FILE_DIRECTORY + to_string(table_no) + ".txt";
    ifstream fin;
    fin.open(file_name);
    
    //
    // check file availability
    if (fin.fail())
    {
        cout << endl << "ReadReservationTable(): Error: Failed to open " + file_name << endl;
        exit(1);
    }
    
    for (int i=1; i<=MAX_NUM_OF_RESERVATION; i++)
    {
        fin >> reservationInfo[i].date >> reservationInfo[i].time >> reservationInfo[i].surname >> reservationInfo[i].num_of_people >> reservationInfo[i].phone_no;
        if (fin.eof())break;   // break the loop if fin reaches the end of file
        num_of_reservation++;
    }
    
    return num_of_reservation;
}

//
//  InsertReservation: insert a reservation into the position provided
//
//  Input: Reservation reservationInfo[]: stored all the reservation
//         int num_of_reservation: the total number of reservation
//         int position: the position which needed to insert a new reservation
//         Reservation reservation_to_insert: the reservation needed to be inserted
//
//  Output: Reservation reservationInfo[]: stored new reservation (pass by array)
//
//  Required Library: NONE
//
void InsertReservation(Reservation reservationInfo[], int num_of_reservation, int position, Reservation reservation_to_insert)
{
    Reservation temp;
    
    for (int i = position; i <= num_of_reservation + 1; i++)
    {
        temp = reservationInfo[i];
        reservationInfo[i] = reservation_to_insert;
        reservation_to_insert = temp;
    }
    
    return;
}

//
//  WriteReservationInfo: write the reservation information into the reservation_info_file
//
//  Input: Reservation reservationInfo[]: the array that stored the reservation information
//         int num_of_reservation: the total number of reservation
//
//  Output: ofstream fout: write the reservation information into the reservation_info_file
//
//  Required library: <fstream>, "global.h"
//
void WriteReservationInfo(Reservation reservationInfo[], int num_of_reservation, int table_num)
{
    ofstream fout;
    string path;
    path = RESERVATION_FILE_DIRECTORY + to_string(table_num) + ".txt";
    fout.open(path);
    
    if (fout.fail())
    {
        cout << endl << "WriteReservationInfo: Error: Failed to open " + path << endl;
        exit(1);
    }
    
    for (int i = 1; i <= num_of_reservation; i++)
        fout << reservationInfo[i].date << " " << reservationInfo[i].time << " " << reservationInfo[i].surname << " " << reservationInfo[i].num_of_people << " " << reservationInfo[i].phone_no << endl;
    
    return;
}

//
// Delete: delete a reservation from the array
//
// Input: Reservation reservationInfo[]: stored all the reservation information
//        int &num_of_reservation: the total number of reservation
//        int position: the position of the reservation that needed to be delete
//
// Output: NONE
//
// Required library: NONE
//
void Delete(Reservation reservationInfo[], int &num_of_reservation, int position)
{
    for (int i = position; i < num_of_reservation; i++)
        reservationInfo[i] = reservationInfo[i + 1];
    num_of_reservation--;
    
    return;
}

//
// StaffReservation: the reservation user interface for the staff
//
// Input: int table_no: the table number which reservation status is being checked
//        Table tableInfo[]: stored all the table information
//
// Output: cout: the user interface
//
// Required library: "global.h": CheckDateValidity(), CheckTimeValidity()
//
void StaffReservation(int table_no, Table tableInfo[])
{
    //
    // initialization to read the reservation status of the target table
    Reservation reservationInfo[MAX_NUM_OF_RESERVATION];
    int num_of_reservation = 0;
    num_of_reservation = ReadReservationTable(reservationInfo, table_no);
    
    string command, feedback;
    
    while (command != "return")
    {
        PrintReservationUI(reservationInfo, num_of_reservation, table_no, feedback);
        
        //
        // let the user input the command
        cin >> command;
        ToLower(command);
        
        if (command == "add")
        {
            //
            // let the user input the date of the reservation
            string date;
            cout << endl
            << " * Type the date of the reservation:" << endl
            << " [ In form of [DD/MM/YYYY] ]" << endl << endl;
            cin >> date;
            
            //
            // check if the date is valid
            int flag_date;
            flag_date = CheckDateValidity(date);
            
            if (flag_date == 1)
            {
                //
                // let the user input the time of the reservation
                string time;
                cout << endl
                << " * Type the time of the reservation:" << endl
                << " [ In form of [HH:MM] ]" << endl << endl;
                cin >> time;
                
                //
                // check if the time is valid
                int flag_time;
                flag_time = CheckTimeValidity(time);
                
                if (flag_time == 1)
                {
                    int position = 0;
                    position = CheckAvailability(reservationInfo, num_of_reservation, date, time);
                    
                    if (position != -1)
                    {
                        string surname, phone_num;
                        cout << endl
                        << " * Type the surname and phone_num of reserver:" << endl
                        << " [ In form of [surname] [phone_num] ]" << endl << endl;
                        cin >> surname >> phone_num;
                        ToUpper(surname);
                        if (IsNumber(phone_num) && phone_num.length() == 8)
                        {
                            int num_of_people;
                            cout << endl
                            << " * Type the number of the people to reserve:" << endl << endl;
                            cin >> num_of_people;
                            
                            if (num_of_people <= tableInfo[table_no].size)
                            {
                                Reservation reservation_to_insert;
                                reservation_to_insert.date = date;
                                reservation_to_insert.time = time;
                                reservation_to_insert.surname = surname;
                                reservation_to_insert.num_of_people = num_of_people;
                                reservation_to_insert.phone_no = phone_num;
                                
                                InsertReservation(reservationInfo, num_of_reservation, position, reservation_to_insert);
                                num_of_reservation++;
                                
                                WriteReservationInfo(reservationInfo, num_of_reservation, table_no);
                                
                                feedback = "\"Add\" is performed.";
                            }
                            else
                                feedback = "\"Add\" is not performed due to over size.";
                        }
                        else
                            feedback = "\"Add\" is not performed due to wrong input.";
                    }
                    else
                        feedback = "\"Add\" is not performed due to time crash.";
                }
                else if (flag_time == -1)
                    feedback = "\"Add\" is not performed due to wrong time format.";
                else if (flag_time == -2)
                    feedback = "\"Add\" is not performed due to wrong time.";
                else if (flag_time == -3)
                    feedback = "\"Add\" is not performed due to wrong time interval.";
                else
                {
                    cout << endl << "StaffReservation(): Error: Unknown exceptional case of CheckTimeValidity() returning value: " + to_string(flag_time) << endl;
                    exit(1);
                }
            }
            else if (flag_date == -1)
                feedback = "\"Add\" is not performed due to wrong format.";
            else if (flag_date == -2)
                feedback = "\"Add\" is not performed due to wrong date.";
            else if (flag_date == -3)
                feedback  = "\"Add\" is not performed due to out of range.";
            else
            {
                cout << endl << "StaffReservation(): Error: Unknown exceptional case of CheckDateValidity() returning value: " + to_string(flag_date) << endl;
                exit(1);
            }
        }
        else if (command == "delete")
        {
            //
            // let the user input the date of the reservation
            string date;
            cout << endl
            << " * Type the date of the reservation:" << endl
            << " [ In form of [DD/MM/YYYY] ]" << endl << endl;
            cin >> date;
            
            //
            // check if the date is valid
            int flag_date;
            flag_date = CheckDateValidity(date);
            
            if (flag_date == 1 || flag_date == -3)
            {
                bool flag_date = false;
                for (int i = 1; i < num_of_reservation; i++)
                {
                    if (reservationInfo[i].date == date)
                        flag_date = true;
                }
                
                if (flag_date)
                {
                    //
                    // let the user input the time of the reservation
                    string time;
                    cout << endl
                    << " * Type the time of the reservation:" << endl
                    << " [ In form of [HH:MM] ]" << endl << endl;
                    cin >> time;
                    
                    //
                    // check if the time is valid
                    int flag_time;
                    flag_time = CheckTimeValidity(time);
                    
                    if (flag_time == 1)
                    {
                        int flag_found = false;
                        for (int i = 1; i < num_of_reservation; i++)
                        {
                            if (reservationInfo[i].date == date)
                                if (reservationInfo[i].time == time)
                                {
                                    Delete(reservationInfo, num_of_reservation, i);
                                    WriteReservationInfo(reservationInfo, num_of_reservation, table_no);
                                    flag_found = true;
                                }
                        }
                        if (flag_found)
                            feedback = "\"Delete\" is performed.";
                        else
                            feedback = "\"Delete\" is not performed due to unmatching.";
                    }
                    else if (flag_time == -1)
                        feedback = "\"Delete\" is not performed due to wrong format.";
                    else if (flag_time == -2)
                        feedback = "\"Delete\" is not performed due to wrong time.";
                    else if (flag_time == -3)
                        feedback = "\"Delete\" is not performed due to wrong interval.";
                    else
                    {
                        cout << endl << "StaffReservation(): Error: Unknown exceptional case of CheckTimeValidity() returning value: " + to_string(flag_time) << endl;
                        exit(1);
                    }
                }
                else
                    feedback = "\"Delete\" is not performed due to unmatching.";
            }
            else if (flag_date == -1)
                feedback = "\"Delete\" is not performed due to wrong format.";
            else if (flag_date == -2)
                feedback = "\"Delete\" is not performed due to wrong date.";
            else
            {
                cout << endl << "StaffReservation(): Error: Unknown exceptional case of CheckDateValidity() returning value: " + to_string(flag_date) << endl;
                exit(1);
            }
        }
        else
            feedback = "Wrong command. Please type again.";
    }
    
}
