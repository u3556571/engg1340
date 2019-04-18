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
void printfreetable(Table);
void checkavailable(Table[],int);
void checkavailable(Table[]);
void printuserUI();
void orderdishes(int,string);
void lookmenu();
void checkthebill(int);
void go_on();
void printline(char);

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
        cin >> tablenum ;
        cout << "Please enter the table ID :";
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
        //check the current bill
        if (input==2)
        {
            ClearScreen();
            lookmenu();
        }
        if (input==3)
        {
            cout << "please enter the table ID (exit : 0):";
            int tablenum;
            cin >> tablenum;
            if (tablenum!=0)
                checkthebill(tablenum);
        }
        cout << endl;
        printuserUI();
        cin >> input;
    }
    ClearScreen();
    cout << endl << "Thank you for using";
}

int main()
{
    StaffMain();
    
    //CustomerVersion();
    
    return 0;
}
