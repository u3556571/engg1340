main.o:global.cpp global.h billing.cpp billing.h global.cpp global.h reservation.cpp reservation.h
  g++ -c main.o

global.o:global.cpp global.h
  g++ -c global.cpp
  
billing.o:billing.cpp billing.h global.cpp global.h
  g++ -c billing.cpp
  
reservation.o:reservation.cpp reservation.h global.cpp global.h
  g++ -c reservation.cpp
  
table.o:table.cpp table.h global.cpp global.h
  g++ -c table.cpp
  
 main:main.o global.o billing.o reservation.o table.o
  g++ main.o global.o billing.o reservation.o table.o -o main
  
