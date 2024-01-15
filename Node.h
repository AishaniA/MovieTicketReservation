//Name: Aishani Arunganesh
//Net ID: axa220346
#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>
#include "Seat.h"

class Node{
    protected:
    //class variables
    Node *next;
    Node *down;
    Seat payload;
    
    public:
    //constructors
    Node();
    Node(Seat);
    //mutators
    void setNext(Node *n) {next = n;}
    void setDown(Node *d) {down = d;}
    void setSeat(Seat s) {payload = s;}
    //accessors
    Node* getNext() const {return next;}
    Node* getDown() const {return down;}
    Seat* getSeat()  {return &payload;}
    //overloaded operators
    friend std::ostream& operator<<(std::ostream&, const Node&);
};

#endif