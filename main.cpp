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

using namespace std;

//
// ReadBillingInfo: read the billing information from the file of the specific table
//
// Input: Billing billingInfo[]: empty array to store the billing information
//        int table_num: the number of the table which needed to know the billing information
//
// Output: Billing billingInfo[]: the array which already stored the billing information
//         return int: the total number of the billing
//
// Required library: <fstream>
//
int ReadBillingInfo(Billing billingInfo[], int table_num)
{
    int num_of_billing = 0;
    string file_name = BILLING_FILE_DIRECTORY + to_string(table_num) + ".txt";
    ifstream fin;
    fin.open(file_name);
    
    //
    // check file availability
    if (fin.fail())
    {
        cout << endl << "ReadBillingInfo(): Error: Failed to open " + file_name << endl;
        exit(1);
    }
    
    for (int i = 1; i <= MAX_NUM_OF_BILLING; i++)
    {
        fin >> billingInfo[i].index >> billingInfo[i].dish_name >> billingInfo[i].price >> billingInfo[i].arrival;
        if (fin.eof())break;   // break the loop if fin reaches the end of file
        num_of_billing++;
    }
    
    return num_of_billing;
}

//
// PrintBillingUI: print the user interface of the billing status
//
// Input: Billing billingInfo[]: the array stored the billing information
//        int num_of_billing: provided for the times of loop
//
// Output: cout: print the billing user interface
//
// Required library: <iomanip>, "global.h": ClearScreen(), PrintVersion()
//
void PrintBillingUI(Billing billingInfo[], int num_of_billing, int table_num, string feedback)
{
    //
    // calculate the sum of the price
    int sum = 0;
    for (int i = 1; i <= num_of_billing; i++)
        sum += billingInfo[i].price;
    
    ClearScreen();
    PrintVersion("staff");
    
    //
    // print title
    cout
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setw(34) << "Billing List of Table " << setw(2) << to_string(table_num) << setw(12) << "|" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    //
    // print header
    cout
    << "|" << setw(7) << "Index" << setw(17) << "Dish_Name" << setw(12) << "Price" << setw(12) << "Arrival  |" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl;
    
    //
    // print billing information
    //
    // no billing case
    if (num_of_billing == 0)
        cout << "|" << setw(33) << "No dishes ordered yet" << setw(15) << "|" << endl;
    //
    // normal case
    for (int i=1; i<=num_of_billing; i++)
    {
        cout << "|" << setw(6) << billingInfo[i].index << setw(23) << billingInfo[i].dish_name << setw(6) << billingInfo[i].price << setw(10) << billingInfo[i].arrival << "  |" << endl;
    }
    cout
    
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setfill('-') << setw(UI_WIDTH - 1) << "-|" << setfill(' ') << endl
    << "|" << setw(29) << "Total_Amount:" << setw(6) << sum << setw(13) << "|" << endl
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
    
    << "|" << setw(command_width) << "Add" << "  Add a dish" << setw(22) << "|" << endl
    << "|" << setw(command_width) << "Delete" << "  Delete a dish" << setw(19) << "|" << endl
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << "|" << setw(command_width) << "Return" << "  Return to the main page" << setw(9) << "|" << endl
    << "|" << setw(UI_WIDTH - 1) << "|" << endl
    << setfill('=') << setw(UI_WIDTH) << "=" << setfill(' ') << endl << endl;
    if (feedback != "") cout << " * " << feedback;
    cout << endl << " [ Type [command] to perform action ] " << endl << endl;
    
    return;
}

// *** NOT YET FINISH
// ReadDishList: read the dish list from the file
//
// Input: Dish dishList[]: an empty array of Dish for inputting value
//
// Output: Dish dishList[]: an array which already stored the value
//         return int: the total number of dish the restaurant provided
//
// Required Library: <fstream>
//
/*int ReadDishList(Dish dishList[])
{
    int num_of_dish = 0;
    ifstream fin;
    fin.open(DISH_FILE_NAME);
    
    return num_of_dish;
}*/

// *** NOT YET FINISH
// StaffBilling: the billing user interface for the staff
//
/*void StaffBilling(Table tableInfo[], int table_num)
{
    //
    // initialization to read the reservation status of the target table
    Billing billingInfo[MAX_NUM_OF_BILLING];
    int num_of_billing = 0;
    num_of_billing = ReadBillingInfo(billingInfo, table_num);
    
    string command, feedback;
    
    while (command != "return")
    {
        PrintBillingUI(billingInfo, num_of_billing, table_num, feedback);
        
        //
        // let the user input the command
        cin >> command;
        ToLower(command);
        
        if (command == "arrived")
        {
            Debug("Arrived");
        }
        else if (command == "add")
        {
            //
            // let the user input the index of the dish
            string index;
            cout << endl
            << " * Type the index of the dish:" << endl << endl;
            cin >> index;
            
            //
            // check if the dish is valid
            int flag_date;
            flag_date = CheckDateValidity(date);
            
            if (flag_date == 1)
            {
                //
                // let the user input the time of the reservation
                string time;
                cout << endl
                << " * Type the index of the dish:" << endl << endl;
                cin >> time;
                
                //
                // check if the dish is valid
                
                
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
                else cout << endl << "StaffReservation(): Error: Unknown exceptional case of CheckTimeValidity() returning value: " + to_string(flag_time) << endl;
            }
            else if (flag_date == -1)
                feedback = "\"Add\" is not performed due to wrong format.";
            else if (flag_date == -2)
                feedback = "\"Add\" is not performed due to wrong date.";
            else if (flag_date == -3)
                feedback  = "\"Add\" is not performed due to out of range.";
            else cout << endl << "StaffReservation(): Error: Unknown exceptional case of CheckDateValidity() returning value: " + to_string(flag_date) << endl;
        }
        else if (command == "delete")
        {
            Debug("Delete");
        }
        else
            feedback = "Wrong command. Please type again.";
    }
    
    return;
}*/

//
// StaffMain: the main user interface for the staff
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
            //StaffBilling(tableInfo, table_no);
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
void printfreetable(Table);
void checkavailable(Table[],int);
void checkavailable(Table[]);
void printuserUI();
void orderdishes(int,string);
void lookmenu();
void checkthebill(int);
void go_on();

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
  while (fin>>input)
  {
    cout << input << " ";
    fin >> input;
    cout << input << " ";
    fin >> input;
    cout << input << " ";
    total+=stoi(input);
    fin >> input;
    cout << input << " " << endl;
  }
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
  while (getline(menu,food))
  {
    cout << food << endl;
  }
  menu.close();
  cout << endl << "Order : 1 " << endl << "exit : 0" << endl;
  int input,tablenum;
  cin >> input;
  if (input==1)
  {
    cout << "Please enter the table ID :";
  }
  cin >> tablenum ;
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
  //ClearScreen();
  cout << "Welcome!" << endl;
  cout << "How can I help you?" << endl;
  cout << "check current available table : 1" << endl;
  cout << "Order dishes : 2" << endl; 
  cout << "Check the bill : 3" << endl;
  cout << "exit : 0" << endl;

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
  cout << "Total " << total << " of table is available" << endl << endl;
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
    //check the current bill
    if (input==2)
    {
      ClearScreen();
      lookmenu();
    }
    if (input==3)
    {
      cout << "please enter the table ID :";
      int tablenum;
      cin >> tablenum;
      checkthebill(tablenum);
    }
    cout << endl;
    printuserUI();
    cin >> input;
  }
  cout << endl << "Thank you for using";
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
    
    //StaffMain();
    
    //StaffReservation(1);
    
    /*string date, time;
    
    cin >> date >> time;
    
    cout << CheckTimeDiff("09/04/2019", "13:30", date, time);*/
    
    Billing billingInfo[MAX_NUM_OF_BILLING];
    int num_of_billing = 0;
    string feedback;
    num_of_billing = ReadBillingInfo(billingInfo, 1);
    PrintBillingUI(billingInfo, num_of_billing, 1, feedback);
    
    return 0;
}
