//
//  table.h
//  ENGG1340
//
//  Created by Jason Yau on 8/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#ifndef table_h
#define table_h

void PrintTableUI(Table[], int, string);
int ReadTableInfo(Table[]);
void WriteTableInfo(Table[], int);
string Occupy(Table[], int, int);
string Free(Table[], int, int);
string Paid(Table[], int, int);

#endif /* table_h */
