//
//  reservation.h
//  ENGG1340
//
//  Created by Jason Yau on 8/4/2019.
//  Copyright © 2019 Jason Yau. All rights reserved.
//

#ifndef reservation_h
#define reservation_h

void PrintReservationUI(Reservation[], int, int, string);
int ReadReservationTable(Reservation[], int);
void InsertReservation(Reservation[], int, int, Reservation);
void WriteReservationInfo(Reservation[], int, int);
void Delete(Reservation[], int&, int);
void StaffReservation(int, Table[]);

#endif /* reservation_h */
