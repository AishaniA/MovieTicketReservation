//Name: Aishani Arunganesh
//Net ID: axa220346
#include "Auditorium.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>

Auditorium::Auditorium(std::string file){
    hide = true;
    std::ifstream inFS;
    inFS.open(file);
    //checks if file is opened correctly
    if (!inFS.is_open()){
        std::cout << "File not found" << std::endl;
    }
    r = 1;
    Node *temp = new Node();
    Node *top = temp;
    first = temp; 
    //creates auditorium from file
    while (!inFS.eof()){
        std::string line;
        getline(inFS, line);
        if (line.size() == 0){
            break;
        }
        int i = 0;
        c = 'A';
        while (i < (int)line.size()){
            if (line.at(i) != 'A' && line.at(i) != 'C' && line.at(i) != 'S' && line.at(i) != '.'){
                break;
            }
            Seat s = Seat(r, c, line.at(i));
            temp->setSeat(s);
            temp->setNext(new Node());
            temp = temp->getNext();
            c++;
            i++;
        }
        top->setDown(new Node());
        top = top->getDown();
        temp = top;
        r++;
    }
}

//returns ticket type of seat for Order's total price calculations (used for delete)
char Auditorium::getTicket(int r, char c){
        Node* temp = first;
        for (int i = 0; i < r; i++){
            temp = temp->getNext();
        }
        for (char i = 'A'; i < c; i++){
            temp = temp->getDown();
        }
        return temp->getSeat()->getName();
    }
    //displays auditorium in hidden view (no letters visible)
    void Auditorium::displayAuditorium(){
        char letter = 'A';
        std::cout << "  ";
        while(letter != c){
            std::cout << letter;
            letter++;
        }
        std::cout << std::endl;
        hide = true;
        //prints out auditorium using overloaded << method
        std::cout << *this;
    }
    //helper method which helps displayAuditorium print out to console - no longer used
    void Auditorium::displayHelp(Node *temp){
        while(temp){
            if (temp->getSeat()->getTicket() == 'b') {
                break; 
            }
            if (temp->getSeat()->getTicket() == '.'){
                std::cout << '.';
            }
            else{
                std::cout << '#';
            }
            temp = temp->getNext();
        }
        std::cout << std::endl;
    }
    //reserves seats (only if seats are available)
    void Auditorium::reserveSeats(int row, char seat, int adult, int child, int senior){
        Node *temp = first;
        //loops till at desired row
        while(row != 1){
            temp = temp->getDown();
            row--;
        }
        char count = 'A';
        while (count != seat){
            temp = temp->getNext();
            count++;
        }
        //sets each seat to ticket (based on tickets desired)
        while (adult > 0){
            temp->getSeat()->setTicket('A');
            adult--;
            temp = temp->getNext();
        }
        while (child > 0){
            temp->getSeat()->setTicket('C');
            child--;
            temp = temp->getNext();
        }
        while (senior > 0){
            temp->getSeat()->setTicket('S');
            senior--;
            temp = temp->getNext();
        }
    }
    //removes seats
    void Auditorium::removeSeats(int row, char seat, int total){
        Node *temp = first;
        //loops till at desired row
        while(row != 1){
            temp = temp->getDown();
            row--;
        }
        char count = 'A';
        while (count != seat){
            temp = temp->getNext();
            count++;
        }
        //sets each seat to empty (based on total tickets)
        while (total > 0){
            temp->getSeat()->setTicket('.');
            total--;
            temp = temp->getNext();
        }
    }
    //checks if each seat that user wants is available
    bool Auditorium::checkAvailability(int row, char seat, int quantity){
        Node *temp = first;
        //loops till at desired seat
        while(row != 1){
            temp = temp->getDown();
            row--;
        }
        char count = 'A';
        while (count != seat){
            temp = temp->getNext();
            count++;
        }
        //checks that number of seats is available
        while(quantity > 0){
            if (!temp){
                return false;
            }
            if (temp->getSeat()->getTicket() != '.'){
                return false;
            }
            temp = temp->getNext();
            quantity--;
        }
        return true;
    }
    //displays ticket
    void Auditorium::displayReport(){
        //variables
        adult = 0;
        child = 0;
        senior = 0;
        total = 0;
        sold = 0;
        sales = 0.0;
        Node *temp = first;
        while(temp){
            //uses helper method to print
            reportHelp(temp, adult, child, senior, total, sold, sales);
            temp = temp->getDown();
            total--; 
        }
        //prints out all the calculated values
//     	std::cout <<"Open Seats: " << total - sold << std::endl;
// 		std::cout << "Reserved Seats: " <<  sold << std::endl;
// 		std::cout << "Adult Tickets: " << adult << std::endl;
// 		std::cout << "Child Tickets: " << child << std::endl;
// 		std::cout << "Senior Tickets: " << senior << std::endl;
// 		std::cout << "Total Sales: $" << std::fixed << std::setprecision(2) << sales;
        std::cout << total - sold << "\t" << sold << "\t" << adult << "\t" << child << "\t" << senior << "\t" << "$" << std::fixed << std::setprecision(2) << sales;
        
    }
    //helper method for print report - calculates all the values for display report
    // to print in the console
    void Auditorium::reportHelp(Node *temp, int& adult, int& child, int& senior, int& total, int& sold, double& sales){
        while(temp){
            if(temp->getSeat()->getTicket() == 'A'){
                adult++;
                sold++;
                sales += 10;
            }
            if(temp->getSeat()->getTicket() == 'S'){
                senior++;
                sold++;
                sales += 7.5;
            }
            if(temp->getSeat()->getTicket() == 'C'){
                child++;
                sold++;
                sales += 5;
            }
            total++; 
            temp = temp->getNext();
        }
    }
    //finds best available seat
    Seat* Auditorium::bestAvailable(int quantity){
        double distance = INT_MAX;
        Seat* seat = new Seat();
        Node *temp = first;
        Node *down = first;
        int bestRow = (r+1)/2;
        int size = -1;
        Node *count = first;
        while (count){
            size++;
            count = count->getNext();
        }
        while (temp && down){
            down = temp;
                bool empty = true;
                for (char j = 'A'; j < c-quantity+1; j++){
                    Node *top = temp;
                    empty = true;
                    for (int h = 0; h < quantity; h++){
                        if (temp->getSeat()->getTicket() != '.'){
                            empty = false;
                            break;
                        }
                        temp = temp->getNext();
                    }
                    //calculates distance from center of the row
                    double distX = fabs((((j  - 'A') + (quantity  - 1)/2.0))  - (size - 1) / 2.0);
                    double distY = fabs(top->getSeat()->getRow() - bestRow);
                    double dist = sqrt((distX * distX) + (distY * distY));
                    if (dist == distance){
                        if(fabs(seat->getRow() - bestRow) > distY && empty == true){ 
            				seat->setRow(top->getSeat()->getRow());
            				seat->setName(top->getSeat()->getName());
            				seat->setTicket(top->getSeat()->getTicket());
                        }
                        else if (fabs(seat->getRow() - bestRow) == distY && empty == true){
                            if (seat->getRow() > top->getSeat()->getRow()){ 
                                seat->setRow(top->getSeat()->getRow());
                				seat->setName(top->getSeat()->getName());
                				seat->setTicket(top->getSeat()->getTicket());
                            }
                        }
                    }
                    else if (dist < distance && empty == true) {
        				distance = dist;
        				seat->setRow(top->getSeat()->getRow());
        				seat->setName(top->getSeat()->getName());
        				seat->setTicket(top->getSeat()->getTicket());
        			}
        			temp = top->getNext();
                }
            temp = down->getDown();
            if (temp->getSeat()->getTicket() == 'b'){
                break;
            }
        }
        return seat;
    }
    //writes auditorium to A1 file
    void Auditorium::writeToFile(std::string name){
        std::ofstream A1;
        A1.open(name);
        if (A1.fail()){
			    std::cout << "File not made" << std::endl;
		}
		else{
		  hide = false;
		  //prints to file using overloaded << operator
		  A1 << *this;
		}
		A1.close();
    }
    //overloaded operator which prints out auditorium
    std::ostream& operator<<(std::ostream& os, const Auditorium& a){
        Node *temp = a.getFirst();
        for (int i = 1; i < a.getRows(); i++){
            if (a.getHide()){
                os << i << ' ';
            }
            Node *vert = temp;
            while (temp){
                if (temp->getSeat()->getTicket() == 'b'){
                    break;
                }
                if (a.getHide() && temp->getSeat()->getTicket() != '.'){
                    os << '#';
                }
                else {
                    os << *(temp->getSeat());
                }
                temp = temp->getNext();
            }
            if (i < a.getRows() - 1){
                os << std::endl;
            }
            temp = vert->getDown();
        }
        return os;
    }
    //destructor: deletes each node in the auditorium
    Auditorium::~Auditorium(){
        while(first->getDown()){
            Node *down = first->getDown();
            while (first){
               Node *next = first->getNext();
                delete first;
                first = next; 
            }
            first = down;
        }
    }