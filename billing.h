//
//  billing.h
//  ENGG1340
//
//  Created by Jason Yau on 8/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#ifndef billing_h
#define billing_h

void PrintBillingUI(Billing[], int, int, string);
int ReadBillingInfo(Billing[], int);
void WriteBillingInfo(Billing[], int, int);
int ReadDishList(Dish[]);
void AddBill(Billing[], Dish[], int, int&);
void DeleteBill(Billing[], int, int&);
int CheckArrivalFromStart(int, Billing[], int);
int CheckArrivalFromEnd(int, Billing[], int);
void StaffBilling(Table[], int);

#endif /* billing_h */
