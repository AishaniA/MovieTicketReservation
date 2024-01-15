//Name: Aishani Arunganesh
//Net ID: axa220346
//header guard
#ifndef SEAT_H
#define SEAT_H
#include <string>
#include <iostream>

class Seat{
   protected:
   // class variables
    int row;
    char name;
    char ticket;
    
public:
    //constructors
    Seat();
    Seat(int, char, char);
    //accesors
    int getRow() const {return row;}
    char getName() const {return name;}
    char getTicket() const {return ticket;}
    //mutators
    void setRow(int r) {row = r;}
    void setName(char n) {name = n;}
    void setTicket(char t) {ticket = t;}
    //overloaded operators
    friend std::ostream& operator<<(std::ostream&, const Seat&);
    
};

#endif