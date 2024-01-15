//Name: Aishani Arunganesh
//Net ID: axa220346
#include "Node.h"
#include <iostream>

//Default constructor - sets pointers to null and Seat to default seat
Node::Node(){
    next = nullptr;
    down = nullptr;
    payload = Seat();
}
//Overloaded constructor - sets seat to given Seat value
Node::Node(Seat s){
    payload = s;
}
//Overloaded << prints out payload's ticket (using seat's overloaded <<)
std::ostream& operator<<(std::ostream& os, const Node& n){
    os << n.payload;
    return os;
}