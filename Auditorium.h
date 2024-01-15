//Name: Aishani Arunganesh
//Net ID: axa220346
#ifndef AUDITORIUM_H
#define AUDITORIUM_H
#include <string>
#include <iostream>
#include "Node.h"

class Auditorium{
    protected:
    //class variables
    int adult = 0;
    int child = 0;
    int senior = 0;
    int total = 0;
    int sold = 0;
    double sales = 0.0;
    Node *first;
    int r;
    char c;
    bool hide;
    
    public:
    //constructors
    Auditorium(){};
    Auditorium(std::string);
    //deconstructors
    ~Auditorium();
    //methods
    void displayAuditorium();
    void reserveSeats(int, char, int, int, int);
    bool checkAvailability(int, char, int);
    void displayReport();
    void writeToFile(std::string);
    Seat* bestAvailable(int);
    void removeSeats(int, char, int);
    //accessors
    Node* getFirst() const{return first;}
    char getTicket(int, char);
    int getRows() const{return r;}
    int getAdult() const{return adult;}
    int getChild() const{return child;}
    int getSenior() const{return senior;}
    int getTotal() const{return total;}
    int getSold() const{return sold;}
    double getSales() const{return sales;}
    char getCols() const{return c;}
    bool getHide() const{return hide;}
    //overloaded operator
    friend std::ostream& operator<<(std::ostream&, const Auditorium&);
    
    private:
    //helper methods
    void displayHelp(Node*);
    void reportHelp(Node*, int&, int&, int&, int&, int&, double&);
};

#endif