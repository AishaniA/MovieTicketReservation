//Name: Aishani Arunganesh
//Net ID: axa220346
#include "Seat.h"
#include <iostream>

//default constructor - sets seat's variables to invalid data
Seat::Seat(){
    row = -1;
    name = 'a';
    ticket = 'b';
}
//overloaded constructor - sets seat's variables to given data
Seat::Seat(int r, char n, char t){
    row = r;
    name = n;
    ticket = t;
}
//overloads << and prints out Seat's ticket type
std::ostream& operator<<(std::ostream& os, const Seat& s){
    os << s.ticket;
    return os;
}