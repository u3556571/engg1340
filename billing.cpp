//
//  billing.cpp
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
//  PrintBillingUI: print the user interface of the billing status
//
//  Input: Billing billingInfo[]: the array stored the billing information
//         int num_of_billing: provided for the times of loop
//
//  Output: cout: print the billing user interface
//
//  Required library: <vector>, <iomanip>, "global.h": ClearScreen(), PrintVersion()
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
    // * Only edit the string inside the 2d vector
    vector<vector<string>> command
    {
        {"Arrived", "Change arrival to arrived"},
        {"Add", "Add a dish"},
        {"Delete", "Delete a dish"},
        {"", ""},
        {"Return", "Return to the main page"}
    };
    PrintCommand(command);
    
    if (feedback != "") cout << " * " << feedback;
    cout << endl << " [ Type [command] to perform action ] " << endl << endl;
    
    return;
}

//
//  ReadBillingInfo: read the billing information from the file of the specific table
//
//  Input: Billing billingInfo[]: empty array to store the billing information
//         int table_num: the number of the table which needed to know the billing information
//
//  Output: Billing billingInfo[]: the array which already stored the billing information
//          return int: the total number of the billing
//
//  Required library: <fstream>
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
//  WriteBillingInfo: write the billing information in to the file
//
//  Input: Billing billingInfo[]: the billing information of the table
//         int num_of_billing: the total number of billing of the table
//         int table_num: the table number
//
//  Output: ofstream fout: write the billing information into the file
//
//  Required library: <fstream>
//
void WriteBillingInfo(Billing billingInfo[], int num_of_billing, int table_num)
{
    string file_name = BILLING_FILE_DIRECTORY + to_string(table_num) + ".txt";
    ofstream fout;
    fout.open(file_name);
    
    //
    // check file availability
    if (fout.fail())
    {
        cout << endl << "ReadBillingInfo(): Error: Failed to open " + file_name << endl;
        exit(1);
    }
    
    for (int i = 1; i <= num_of_billing; i++)
        fout << billingInfo[i].index << " " << billingInfo[i].dish_name << " " << billingInfo[i].price << " " << billingInfo[i].arrival << endl;
    
    return;
}

//
//  ReadDishList: read the dish list from the file
//
//  Input: Dish dishList[]: an empty array of Dish for inputting value
//
//  Output: Dish dishList[]: an array which already stored the value
//          return int: the total number of dish the restaurant provided
//
//  Required Library: <fstream>
//
int ReadDishList(Dish dishList[])
{
    int num_of_dish = 0;
    ifstream fin;
    fin.open(DISH_FILE_NAME);
    
    //
    // check file availability
    if (fin.fail())
    {
        cout << endl << "ReadDishList(): Error: Failed to open " + DISH_FILE_NAME;
        exit(1);
    }
    
    for (int i = 1; i <= MAX_NUM_OF_DISH; i++)
    {
        fin >> dishList[i].index >> dishList[i].name >> dishList[i].price;
        if (fin.eof())break;   // break the loop if fin reaches the end of file
        num_of_dish++;
    }
    
    return num_of_dish;
}

//
//  AddBill: add a dish to the billing list of the required table
//
//  Input: Billing billingInfo[]: the billing information of the table
//         int index: the index of the dish
//         int num_of_billing: the total number of billing the table has
//
//  Output: Billing billingInfo[]: the new array which has already been add a new dish
//
//  Required library: NONE
//
void AddBill(Billing billingInfo[], Dish dishList[], int index, int &num_of_billing)
{
    num_of_billing++;
    billingInfo[num_of_billing].index = dishList[index].index;
    billingInfo[num_of_billing].dish_name = dishList[index].name;
    billingInfo[num_of_billing].price = dishList[index].price;
    billingInfo[num_of_billing].arrival = "Not_Yet";
    
    return;
}

//
//  DeleteBill: delete a dish form the billing list of the required table
//
//  Input: Billing billingInfo[]: the billing information of the table
//         int pos: the position of the delete dish in the array
//
//  Output: Billing billingInfo[]: the new array which has already been delete a dish
//
//  Required library: NONE
//
void DeleteBill(Billing billingInfo[], int pos, int &num_of_billing)
{
    for (int i = pos; i < num_of_billing; i++)
    {
        billingInfo[i] = billingInfo[i + 1];
        billingInfo[i + 1] = {};
    }
    num_of_billing--;
    
    return;
}

//
//  CheckArrivalFromStart: check whether the dish is ordered or not, or arrived or not from the beginning
//
//  Input: int index: the index of the dish
//         Billing billingInfo[]: the billing information of the table
//         int num_of_billing: the total number of billing the table has
//
//  Output: return int: i if the dish is found and it is not yet arrived
//                      -1 if the dish is ordered and all order have arrived
//                      -2 if the dish is not ordered
//
//  Required library: NONE
//
int CheckArrivalFromStart(int index, Billing billingInfo[], int num_of_billing)
{
    bool flag_ordered = false;
    bool flag_arrived = false;
    
    for (int i = 1 ; i <= num_of_billing; i++)
    {
        if (billingInfo[i].index == index)
        {
            flag_ordered = true;
            if (billingInfo[i].arrival == "Not_Yet")
                return i;
            else
                flag_arrived = true;
        }
    }
    
    if (flag_arrived)
        return -1;
    else
        return -2;
}

//
//  CheckArrivalFromEnd: check whether the dish is ordered or not, or arrived or not from the end
//
//  Input: int index: the index of the dish
//         Billing billingInfo[]: the billing information of the table
//         int num_of_billing: the total number of billing the table has
//
//  Output: return int: i if the dish is found and it is not yet arrived
//                      0 if the dish is not ordered
//                      -i if the dish is ordered and all order have arrived
//
//  Required library: NONE
//
int CheckArrivalFromEnd(int index, Billing billingInfo[], int num_of_billing)
{
    for (int i = num_of_billing ; i >= 1; i--)
    {
        Debug(to_string(i));
        if (billingInfo[i].index == index)
        {
            if (billingInfo[i].arrival == "Not_Yet")
                return i;
            else
                return -i;
        }
    }
    
    return 0;
}

//
//  StaffBilling: the billing user interface for the staff
//
//  Input: Table tableInfo[]: the array that stored the table information
//         int table_num: the table number
//
//  Output: cout: the billing user interface
//
//  Required library: NONE
//
void StaffBilling(Table tableInfo[], int table_num)
{
    //
    // initialization to read the billing status of the target table
    Billing billingInfo[MAX_NUM_OF_BILLING];
    int num_of_billing = 0;
    num_of_billing = ReadBillingInfo(billingInfo, table_num);
    
    Dish dishList[MAX_NUM_OF_DISH];
    int num_of_dish = 0;
    num_of_dish = ReadDishList(dishList);
    
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
            //
            // let the user input the index of the dish
            // *** exceptional case of non int
            int index;
            cout << endl
            << " * Type the index of the dish:" << endl << endl;
            cin >> index;
            
            //
            // check the dish is ordered or not
            int flag_ordered = 0;
            flag_ordered = CheckArrivalFromStart(index, billingInfo, num_of_billing);
            
            if (flag_ordered > 0)
            {
                billingInfo[flag_ordered].arrival = "Arrived";
                WriteBillingInfo(billingInfo, num_of_billing, table_num);
                feedback = "\"Arrived " + to_string(index) + "\" is performed.";
            }
            else if (flag_ordered == -1)
                feedback = "\"Arrived " + to_string(index) + "\" is not performed due to all dish arrived.";
            else if (flag_ordered == -2)
                feedback = "\"Arrived " + to_string(index) + "\" is not performed due to no matching dish.";
            else
            {
                cout << endl << "StaffBilling(): Error: Unknown exceptional case of CheckArrival() returning value: " + to_string(flag_ordered) << endl;
                exit(1);
            }
        }
        else if (command == "add")
        {
            //
            // let the user input the index of the dish
            // *** Exceptional case of non int
            int index;
            cout << endl
            << " * Type the index of the dish:" << endl << endl;
            cin >> index;
            
            //
            // check if the dish is valid
            if (index <= num_of_dish)
            {
                AddBill(billingInfo, dishList, index, num_of_billing);
                WriteBillingInfo(billingInfo, num_of_billing, table_num);
                feedback = "\"Add " + to_string(index) + "\" is performed.";
            }
            else
                feedback = "\"Add " + to_string(index) + "\" is not performed due to no matching dish.";
        }
        else if (command == "delete")
        {
            //
            // let the user input the index of the index
            // *** exceptional case of non int
            int index;
            cout << endl
            << " * Type the index of the dish:" << endl << endl;
            cin >> index;
            
            //
            // check the dish is ordered or not
            int flag_ordered = 0;
            flag_ordered = CheckArrivalFromEnd(index, billingInfo, num_of_billing);
            
            if (flag_ordered > 0)
            {
                DeleteBill(billingInfo, flag_ordered, num_of_billing);
                WriteBillingInfo(billingInfo, num_of_billing, table_num);
                feedback = "\"Delete " + to_string(index) + "\" is performed.";
            }
            else if (flag_ordered == 0)
                feedback = "\"Delete " + to_string(index) + "\" is not performed due to no matching dish.";
            else if (flag_ordered < 0)
            {
                string reply;
                cout << endl
                << " * This dish has already arrived. Confirm delete?" << endl
                << " [ Type \"Yes\" / \"No\" ]" << endl << endl;
                cin >> reply;
                ToLower(reply);
                if (reply == "yes")
                {
                    DeleteBill(billingInfo, abs(flag_ordered), num_of_billing);
                    WriteBillingInfo(billingInfo, num_of_billing, table_num);
                    feedback = "\"Delete " + to_string(index) + "\" is performed.";
                }
                else if (reply == "no")
                    feedback = "\"Delete " + to_string(index) + "\" is not performed due to dish arrived.";
                else
                    feedback = "\"Delete " + to_string(index) + "\" is not performed due to wrong input.";
            }
            
            else
            {
                cout << endl << "StaffBilling(): Error: Unknown exceptional case of CheckArrival() returning value: " + to_string(flag_ordered) << endl;
                exit(1);
            }
        }
        else
            feedback = "Wrong command. Please type again.";
    }
    
    return;
}
