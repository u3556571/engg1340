//
//  read.cpp
//  ENGG1340
//
//  Created by Jason Yau on 2/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "global.h"

using namespace std;

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
    
    // check file availabilty
    if (fin.fail())
    {
        cout << "ReadTableInfo: Error: Failed to open " + TABLE_INFO_FILE_NAME;
        exit(1);
    }
    
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
// ReadReservationTable: read the reservation status of the required table
//
// Input: Reservation reservationInfo[]: empty array of structure Reservation
//        int table_no: the table number which the staff want to know the reservation status
//
// Output: Reservation reservationInfo[]: stored the reservation status
//         return int: the total number of reservation in the coming week
//
// Required library: <fstream>
//
int ReadReservationTable(Reservation reservationInfo[], int table_no)
{
    int num_of_reservation = 0;
    string file_name = FILE_DIRECTORY + to_string(table_no) + ".txt";
    ifstream fin;
    fin.open(file_name);
    
    // check file availability
    if (fin.fail())
    {
        cout << "ReadReservationTable: Error: Failed to open " + file_name;
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
