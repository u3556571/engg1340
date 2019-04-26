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
#include <stdio.h>

#include "global.h"
#include "table.h"
#include "reservation.h"
#include "billing.h"

using namespace std;

//
//  StaffMain: the main user interface for the staff
//
void StaffMain()
{
    //
    // initialization to read the table information
    Table tableInfo[MAX_NUM_OF_TABLE];
    int num_of_table = 0;
    num_of_table = ReadTableInfo(tableInfo);
    
    string command, feedback;
    int table_no = 0;
    
    while (command != "quit")
    {
        PrintTableUI(tableInfo, num_of_table, feedback);
        
        //
        // let the user input the command
        // *** Check for the validity of the table_no
        cin >> command >> table_no;
        ToLower(command);
        
        if (command == "occupy")
        {
            feedback = Occupy(tableInfo, table_no, num_of_table);
        }
        else if (command == "free")
        {
            feedback = Free(tableInfo, table_no, num_of_table);
        }
        else if (command == "paid")
        {
            feedback = Paid(tableInfo, table_no, num_of_table);
        }
        else if (command == "billing")
        {
            StaffBilling(tableInfo, table_no);
        }
        else if (command == "reservation")
        {
            StaffReservation(table_no, tableInfo);
        }
        else
            feedback = "Wrong command. Please type again.";
    }
    
    return;
}

//CustomerVersion
void addreservation(int,Table[]);
void printfreetable(Table);
void checkavailable(Table[],int);
void checkavailable(Table[]);
void printuserUI();
void orderdishes(int,string);
void lookmenu();
void checkthebill(int);
void go_on();
void printline(char);
void removereservation(int,Table);

void addreservation(int numtable, Table tableInfo[])
{
  Reservation reservationInfo[MAX_NUM_OF_RESERVATION];
  int num_of_reservation = 0;
  string date;
  cout << "Please enter the date(exit : 0) : " << endl
  << " [ In form of [DD/MM/YYYY] ]" << endl;
  cin >> date;      
  //
  // check if the date is valid
  int flag_date;
  flag_date = CheckDateValidity(date);
  while (flag_date != 1 && date != "0")
  {
    cout << "Wrong date, please enter again(exit : 0) : ";
    cin >> date;
    if (date=="0")
      break;
    flag_date = CheckDateValidity(date);
  }
  if (flag_date == 1)
  {
    cout << "Please enter the number of people(1-8)(exit : 0) :   ";
    int num0,num1;
    cin >> num0;
    //find the suitable size of table(num1)
    if (num0<=2)
       num1=2;
    else if (num0 <=4)
       num1=4;
    else if (num0 <=8)
       num1=8;
    if (num0!=0)
    {
      cout << endl << "Please enter the time(exit : 0) : " << endl << " [ In form of [HH:MM] ]" << endl;
      string time;
      cin >> time;
      if (time != "0")
      {
        int success=0;
        for (int i=1;i<numtable+1;i++)
        {
          if (tableInfo[i].size == num1)
          {            
            num_of_reservation = ReadReservationTable(reservationInfo, i);
            int position;
            position = CheckAvailability(reservationInfo, num_of_reservation, date, time);
            string surname, phone_num;
            if (position > 0)
            {
              cout << endl << "Please enter the surname and phone_num of reserver(exit : 0) :" << endl << " [ In form of [surname] [phone_num] ]" << endl << endl;
              cin >> surname;
              if (surname!="0")
              {
                cin >> phone_num;
                ToUpper(surname);
                while (IsNumber(phone_num)==0 || phone_num.length() != 8)
                {                    
                  cout << endl << " * Error * "<< endl << "Please enter the surname and phone_num of reserver:(exit : 0) " << endl << " [ In form of [surname] [phone_num] ]" << endl << endl;
                  cin >> surname;
                  if (surname=="0")
                    break;
                  cin >> phone_num;
                  ToUpper(surname);
                }
                Reservation reservation_to_insert;
                reservation_to_insert.date = date;
                reservation_to_insert.time = time;
                reservation_to_insert.surname = surname;
                reservation_to_insert.num_of_people = num0;
                reservation_to_insert.phone_no = phone_num;          
                InsertReservation(reservationInfo, num_of_reservation, position, reservation_to_insert);
                num_of_reservation++;                
                WriteReservationInfo(reservationInfo, num_of_reservation, i);
                cout << "Table(ID : " << i << ") on " << date << " at " << time << " is reserved successfully" << endl;
                cout << "Surname : " << surname << "    Number of people : " << num0 << endl;
                success = 1;
                go_on(); 
                break;
              }
            }
          } 
        }
        if (success == 0)
        {
          cout << "Sorry, no available table." << endl;
          go_on();
        }
      }   
    }      
  }    
}


void removereservation(int numtable, Table tableInfo[])
{
  Reservation reservationInfo[MAX_NUM_OF_RESERVATION];
  int num_of_reservation = 0;
  string date;
  cout << "Please enter the date(exit : 0) : " << endl
  << " [ In form of [DD/MM/YYYY] ]" << endl;
  cin >> date;      
  //
  // check if the date is valid
  int flag_date;
  flag_date = CheckDateValidity(date);
  while (flag_date != 1 && date != "0")
  {
    cout << "Wrong date, please enter again(exit : 0) : " << endl;
    cin >> date;
    if (date=="0")
      break;
    flag_date = CheckDateValidity(date);
  }                               
  string surname="0", phone_num;
  if (date!="0")
  {
    cout << endl << "Please enter the surname and phone_num of reserver(exit : 0) :" << endl << " [ In form of [surname] [phone_num] ]" << endl;
    cin >> surname;
  }
  if (surname!="0")
  {
    cin >> phone_num;
    ToUpper(surname);
  }
  int success=0;
  if (surname!="0")
  {
    for (int i=1;i<numtable+1;i++)
    {       
      num_of_reservation = ReadReservationTable(reservationInfo, i);
      int position;
      for (int j=1;j<num_of_reservation+1;j++)
      {
        if (reservationInfo[j].surname==surname && reservationInfo[j].phone_no==phone_num && reservationInfo[j].date==date)
        {
          position=j;
          success=1;
          break;
        }
      }
      if (success==1)
      {
        Delete(reservationInfo, num_of_reservation, position);
        WriteReservationInfo(reservationInfo, num_of_reservation, i);
        cout << "Reservation on " << date << " is canceled successfully" << endl;
        cout << "Surname : " << surname << "    Phone number : " << phone_num << endl;
        go_on();
      }
      if (i==numtable && success == 0)
      {
        cout << "No corresponding reservation is found, please try again." << endl;
        go_on();
      }
    }
  }
}

void printline(char x)
{
    cout << setfill(x) << setw(UI_WIDTH) << x << setfill(' ') << endl;
}

void go_on()
{
    string nothing;
    cout << "[Press enter to go on]" << endl;
    cin.ignore();
    cin.get();
    ClearScreen();
}

void checkthebill(int tablenum)
{
    ClearScreen();
    string filename= BILLING_FILE_DIRECTORY + to_string(tablenum) + ".txt";
    ifstream fin;
    string input;
    int total=0;
    fin.open(filename);
    if (fin.fail())
    {
        cout << endl << "Error: Failed to open " + filename << endl;
        exit(1);
    }
    printline('=');
    cout << "||" << setw((UI_WIDTH - 2)/2+6) << "Bill Checking" << setw((UI_WIDTH - 2)/2-5) << "||" << endl ;
    cout << "||" << setw((UI_WIDTH - 2)/2+2) << "Table " << tablenum << setw((UI_WIDTH - 2)/2-2) << "||" << endl ;
    printline('-');
    
    cout << "|" << setw((UI_WIDTH - 1)/4-8) << "ID";
    cout << setw((UI_WIDTH - 1)/2-7) << "Dish_Name" << setw((UI_WIDTH - 1)/3+2);
    cout << setw((UI_WIDTH - 1)/2-13) << "Price" << setw((UI_WIDTH - 1)/3+2);
    cout << setw((UI_WIDTH - 1)/4+2) << "Arrrival" << setw(2) << "|" << endl ;
    printline('-');
    
    while (fin>>input)
    {
        cout << "|" << setw((UI_WIDTH - 1)/4-8) << input;
        fin >> input;
        cout << setw((UI_WIDTH - 1)/2-4) << input << setw((UI_WIDTH - 1)/3+3);
        fin >> input;
        total+=stoi(input);
        cout << setw((UI_WIDTH - 1)/4-5) << input;
        fin >> input;
        cout << setw((UI_WIDTH - 1)/4+3) << input << setw(2) << "|" << endl ;
    }
    printline('=');
    cout << endl << "Total : $" << total << endl;
    go_on();
    cout << endl << endl << endl << endl << endl;
}

void orderdishes(int tablenum,string addfood)
{
    string original[50];
    string store;
    int oldnum=0;
    string filename= BILLING_FILE_DIRECTORY + to_string(tablenum) + ".txt";
    ifstream fin;
    //copy the original bill
    fin.open(filename);
    if (fin.fail())
    {
        cout << endl << "Error: Failed to open " + filename << endl;
        exit(1);
    }
    while (getline(fin,store))
    {
        original[oldnum]=store;
        oldnum++;
    }
    fin.close();
    ofstream fout;
    fout.open(filename);
    for (int i=0;i<oldnum;i++)
    {
        fout << original[i] << endl;
    }
    oldnum=0;
    // add the new food;
    fout << addfood << " Not_Yet";
    fout.close();
}

void lookmenu()
{
    ifstream menu;
    string food;
    menu.open(DISH_FILE_NAME);
    printline('=');
    cout << "||" << setw((UI_WIDTH - 2)/2+1) << "MENU" << setw((UI_WIDTH - 2)/2) << "||" << endl ;
    printline('-');
    cout << "|" << setw((UI_WIDTH - 1)/4-4) << "ID";
    cout << setw((UI_WIDTH - 1)/2-4) << "Dish_Name" << setw((UI_WIDTH - 1)/3+2);
    cout << setw((UI_WIDTH - 1)/4+3) << "Price" << setw(5) << "|" << endl ;
    printline('-');
    while (menu >> food)
    {
        cout << "|" << setw((UI_WIDTH - 1)/4-5) << food << " : ";
        menu >> food;
        cout << setw((UI_WIDTH - 1)/2-5) << food << setw((UI_WIDTH - 1)/3);
        menu >> food;
        cout << setw((UI_WIDTH - 1)/4) << food << setw(7) << "|" << endl ;
    }
    menu.close();
    printline('-');
    cout << "||" << setw((UI_WIDTH - 2)/2+9) << "Order : 1   exit : 0" << setw((UI_WIDTH - 2)/2-8) << "||" << endl ;
    printline('=');
    cout << "Please enter your choice : ";
    int input,tablenum;
    cin >> input;
    if (input==1)
    {
        cout << "Please enter the table ID :";
        cin >> tablenum ;
    }
    while (input != 0)
    {
        if (input==1)
        {
            cout << "please enter the Food ID (exit : 0) : ";
            while (input!=0)
            {
                cin >> input;
                if (input==0)
                    break;
                menu.open(DISH_FILE_NAME);
                for (int i=0;i<input;i++)
                {
                    getline(menu,food);
                }
                menu.close();
                cout << "Food is ordered, anything else? (exit : 0)" << endl;
                orderdishes(tablenum,food);
            }
        }
    }
}

void printuserUI(){
    ClearScreen();
    PrintVersion("customer");
    cout << "||" << setw((UI_WIDTH - 2)/2+3) << "Welcome!" << setw((UI_WIDTH - 2)/2-2) << "||" << endl ;
    cout << "||" << setw((UI_WIDTH - 2)/2+9) << "How can I help you?" << setw((UI_WIDTH - 2)/2-8) << "||" << endl ;
    printline('-');
    cout << "|" << setw((UI_WIDTH - 1)/2+13) <<"check current available table : 1" << setw((UI_WIDTH - 1)/2-13) << "|" << endl;
    cout << "|" << setw((UI_WIDTH - 1)/2+13) <<"Read menu : 2" << setw((UI_WIDTH - 1)/2-13) << "|" << endl;
    cout << "|" << setw((UI_WIDTH - 1)/2+13) <<"Check the bill : 3" << setw((UI_WIDTH - 1)/2-13) << "|" << endl;
    cout << "|" << setw((UI_WIDTH - 1)/2+13) <<"Reserve table : 4" << setw((UI_WIDTH - 1)/2-13) << "|" << endl;
    cout << "|" << setw((UI_WIDTH - 1)/2+13) <<"Cancel reservation : 5" << setw((UI_WIDTH - 1)/2-13) << "|" << endl;
    cout << "|" << setw((UI_WIDTH - 1)/2+13) <<"exit : 0" << setw((UI_WIDTH - 1)/2-13) << "|" << endl;
    printline('=');
    
}

void checkavailable(Table tableInfo[],int num_of_table)
{
    ClearScreen();
    int total=0;
    cout << "What is the size of the table?" << "(size : 1-8)" << endl;
    int input;
    cin >> input;
    if (input<=2)
        input=2;
    else if (input <=4)
        input=4;
    else if (input <=8)
        input=8;
    for (int i=0;i<num_of_table;i++)
    {
        if ((tableInfo[i].occupancy=="Available")&&(tableInfo[i].size==input))
        {
            printfreetable(tableInfo[i]);
            total++;
        }
    }
    if (total > 1)
        cout << "Total " << total << " tables are available" << endl << endl;
    else
        cout << "Total " << total << " table is available" << endl << endl;
    go_on();
}

void printfreetable(Table target)
{
    ClearScreen();
    cout << "Table ID " << target.number << "(size " << target.size << ") is available";
    cout << endl;
}
void CustomerVersion()
{
    //read in the table information
    int tablenum;
    Table tableInfo[MAX_NUM_OF_TABLE];
    int num_of_table = 0;
    num_of_table = ReadTableInfo(tableInfo);
    printuserUI();
    // user input
    int input;
    cin >> input;
    ClearScreen();
    while (input !=0)
    {
        //check free table
        if (input==1)
            checkavailable(tableInfo,num_of_table);
        //read menu
        else if (input==2)
        {
            ClearScreen();
            lookmenu();
        }
        // check the bill
        else if (input==3)
        {
            cout << "please enter the table ID (exit : 0):";
            int tablenum;
            cin >> tablenum;
            if (tablenum!=0)
                checkthebill(tablenum);
        }
        // add reservation
        else if (input==4)
        {
          addreservation(num_of_table,tableInfo);
        }
        // delete reservation
        else if (input==5)
        {
          removereservation(num_of_table,tableInfo);
        }
        cout << endl;
        printuserUI();
        cin >> input;
    }
    ClearScreen();
    cout << endl << "Thank you for using." << endl;
}

int main()
{
    int mode;

    cout << endl << "Staffmode : 1       Customermode : 2" << endl;

    cin >> mode;
    
    if (mode==1)
      StaffMain();
    
    if (mode==2)
      CustomerVersion();
    
    return 0;
}
