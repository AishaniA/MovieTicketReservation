//Name: Aishani Arunganesh
//Net ID: axa220346
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include "Auditorium.h"

//used to avoid errors in using std::stoi()
bool isNum(std::string s){
    try {
        stoi(s);
    }
    catch (...) {
        return false;
    }
    return true;
}

//class for each order made by a customer
class Order {
    private:
    Auditorium *theater;
    int auditorium;
    int adult;
    int child;
    int senior;
    int totalTickets;
    std::vector<std::string> seats;
    double total;
    
    public:
    Order();
    Order(Auditorium*, int, int, int, int, int, std::vector<char>);
    //~Order();
    double getTotal() const {return total;}
    bool removeSeat(int, char);
    int getAuditorium() const {return auditorium;}
    void addSeat(int, std::vector<char>, int, int, int);
    void cancelOrder();
    void reciept();
    friend std::ostream& operator<<(std::ostream&, const Order&);
};

Order::Order(){
    auditorium = 0;
    adult = 0;
    child = 0;
    senior = 0;
    totalTickets = 0;
    total = 0.0;
}

Order::Order(Auditorium *aud, int a, int ad, int c, int s, int row, std::vector<char> col){
    theater = aud;;
    auditorium = a;
    adult = ad;
    child = c;
    senior = s;
    totalTickets = ad + c + s;
    total = (ad * 10) + (c * 5) + (s * 7.5);
    for (int i = 0; i < (int)col.size(); i++){
        std::string seat = std::to_string(row) + col[i] + "";
        if (ad > 0){
            seat += "A";
            ad--;
        }
        else if (c > 0){
            seat += "C";
            c--;
        }
        else {
            seat += "S";
            s--;
        }
        seats.push_back(seat);
    }
}

//Used when canceling an order, calls the delete seat method
void Order::cancelOrder(){
    std::cout << seats.size() << std::endl;
    for (int i = 0; i < (int)seats.size(); i++){
        removeSeat(stoi(seats[i].substr(0, 1)), seats[i].at(1));
        i--;
    }
    total = 0;
}

//used to add seats when updating order
void Order::addSeat(int row, std::vector<char> col, int a, int ch, int s){
    for (int i = 0; i < (int)col.size(); i++){
        std::string seat = std::to_string(row) + col[i] + "";
        if (a > 0){
            seat += "A";
        }
        else if (ch > 0){
            seat += "C";
        }
        else {
            seat += "S";
        }
        seats.push_back(seat);
    }
    while (a > 0){
        adult++;
        total += 10;
        a--;
    }
    while (ch > 0){
        child++;
        total += 5;
        ch--;
    }
    while (s > 0){
        senior++;
        total += 7.5;
        s--;
    }
    std::sort(seats.begin(), seats.end());
}

//removes 1 seat from the order - given that the seat provided exists in the order
bool Order::removeSeat(int row, char col){
    for (int i = 0; i < (int)seats.size(); i++){
        if (row == std::stoi(seats[i].substr(0, 1)) && col == seats[i].at(1)){
            char temp = seats[i].at(2);
            if (temp == 'A'){
                total -= 10;
                adult--;
            }
            if (temp == 'S'){
                total -= 7.5;
                senior--;
            }
            if (temp == 'C'){
                total -= 5;
                child--;
            }
            theater->removeSeats(row, col, 1);
            seats.erase(seats.begin() + i);
            totalTickets--;
            return true;
        }
    }
    return false;
}

//prints out the reciept for the order (used for display reciept)
void Order::reciept(){
    std::cout << *this;
    std::cout << "Order Total: $" << std::fixed << std::setprecision(2) << total << std::endl;
}

//prints out order without total (used for display orders)
std::ostream& operator<<(std::ostream& os, const Order& o){
    os << "Auditorium " << o.auditorium << ", ";
    for (int i = 0; i < (int)o.seats.size() - 1; i++){
        os << o.seats[i].at(0) << o.seats[i].at(1) << ",";
    }
    os << o.seats[o.seats.size() - 1].at(0) << o.seats[o.seats.size() - 1].at(1) << std::endl;
    os << o.adult << " adult, " <<  o.child << " child, " << o.senior << " senior" << std::endl;
    return os;
}

//Customer class used to maintain each customer for hashmap
class Customer {
    private:
    std::string username;
    std::string password;
    std::vector<Order*> orders;
    double custTotal;
    
    public:
    Customer(){};
    Customer(std::string, std::string);
    std::string getUser() const {return username;}
    std::string getPass() const {return password;}
    Order* getOrder(int i) {return orders[i];}
    void viewOrders();
    void viewUpdateOrders();
    int getNumOrders();
    void displayReciept();
    void addOrders(Order*);
    void cancelOrder(Order*);
    
};

Customer::Customer(std::string name, std::string pass){
    username = name;
    password = pass;
    custTotal = 0.0;
}

int Customer::getNumOrders(){
    for (int i = 0; i < (int)orders.size(); i++){
        if (orders[i]->getTotal() == 0.0){
            orders.erase(orders.begin() + i);
            i--;
        }
    }
    return (int)orders.size();
}

//adds orders to the customer's orders
void Customer::addOrders(Order *o){
    orders.push_back(o);
    custTotal += o->getTotal();
}

//prints out each order for view orders
void Customer::viewOrders(){
    for (int i = 0; i < (int)orders.size(); i++){
        if (orders[i]->getTotal() == 0.0){
            orders.erase(orders.begin() + i);
            i--;
        }
    }
    if (orders.size() == 0){
        std::cout << "No orders" << std::endl;
    }
    for (int i = 0; i < (int)orders.size(); i++){
        std::cout << *orders[i] << std::endl;
    }
}

//prints out each order but with a number in front of it
void Customer::viewUpdateOrders(){
    for (int i = 0; i < (int)orders.size(); i++){
        if (orders[i]->getTotal() == 0.0){
            orders.erase(orders.begin() + i);
            i--;
        }
    }
    if (orders.size() == 0){
        std::cout << "No orders" << std::endl;
    }
    for (int i = 0; i < (int)orders.size(); i++){
        std::cout << i+1 << ". " << *orders[i] << std::endl;
    }
}

//prints out the reciept for each order as well as the total cost
void Customer::displayReciept(){
    for (int i = 0; i < (int)orders.size(); i++){
        if (orders[i]->getTotal() == 0.0){
            orders.erase(orders.begin() + i);
            i--;
        }
    }
    custTotal = 0;
    for (int i = 0; i < (int)orders.size(); i++){
        orders[i]->reciept();
        custTotal += orders[i]->getTotal();
        std::cout << std::endl;
    }
    std::cout << "Customer Total: $" << std::fixed << std::setprecision(2) << custTotal << std::endl;
}

//used when reserving seats, whether that is for update order or for reserve seats
bool reservingSeats(Auditorium *a, int number, Customer *c, bool update, Order *o){
    int row;
    int adult;
    int child;
    int senior;
    // collects information on desired reservation
	a->displayAuditorium();
	std::string input;
	std::cout << std::endl << "Row number: " << std::endl;
 	getline(std::cin, input);
	//loop until valid row number is given
	while (isNum(input) == false || stoi(input) > a->getRows() || stoi(input) < 0) {
	    getline(std::cin, input);
	}
	row = stoi(input);
	//ask for desired seat
	std::cout << "Starting seat letter: " << std::endl;
	char seat;
	std::cin >> seat;
	std::string seats = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string valSeats = seats.substr(0,seats.find(a->getCols()));
	//loop until valid seat letter is given
	while (valSeats.find(seat) == std::string::npos) {
		std::cin >> seat;
	}
	//prompt for # of tickets and loop until valid # of tickets inputted (non negative)
	std::cout << "# of adult tickets: " << std::endl;
	getline(std::cin, input);
	while (isNum(input) == false || stoi(input) < 0 || stoi(input) > (a->getCols() - 'A')) {
		getline(std::cin, input);
	}
	adult = stoi(input);
	std::cout << "# of child tickets: " << std::endl;
	getline(std::cin, input);
	while (isNum(input) == false || stoi(input) < 0 || stoi(input) > a->getCols() - 'A') {
		getline(std::cin, input);
	}
	child = stoi(input);
	std::cout << "# of senior tickets: " << std::endl;
	getline(std::cin, input);
	while (isNum(input) == false || stoi(input) < 0 || stoi(input) > a->getCols() - 'A') {
	    getline(std::cin, input);
	}
	senior = stoi(input);
	//finds seat using the user's desired seating, and saves it, if user picks available seats
	if (a->checkAvailability(row, seat, adult + senior + child)) {
		a->reserveSeats(row, seat, adult, child, senior);
		std::vector<char> letters;
		
	    for (int i = 0; i < adult + child + senior; i++){
	        letters.push_back(seat);
	        seat++;
	    }
	    if (update == true){
	        o->addSeat(row, letters, adult, child, senior);
	    }
	    else {
	        Order *o = new Order(a, number, adult, child, senior, row, letters);
		    c->addOrders(o);
	    }
	}
	else {
	    if (update == true){
	        std::cout << "Invalid Seat Selection" << std::endl;
	        return false;
	    }
	    else {
	        Seat *s = a->bestAvailable(adult+child+senior);
		    if (s->getTicket() == 'b'){
		        std::cout << "no available seats" << std::endl;
		    }
		    else {
		        //print out best seat in required format
		        char name = s->getName();
		        for (int i = 0; i < adult+child+senior-1; i++){
		            name++;
		        }
		        std::cout << s->getRow() << s->getName() << " - " << s->getRow() << name << std::endl;
		        std::cout << "Would you like to reserve these seats? Y or N " << std::endl;
    		    std::string answer;
    			getline(std::cin, answer);
    			//loop until valid answer is given
    			while (answer != "Y" && answer != "N"){
    			    getline(std::cin, answer);
    			}
    			//if user decides to book best seats, reserve seats
    			if (answer == "Y"){
    			    row = s->getRow();
    			    seat = s->getName();
    			    a->reserveSeats(row, seat, adult, child, senior);
    			    std::vector<char> letters;
    			    for (int i = 0; i < adult + child + senior; i++){
    			        letters.push_back(seat);
    			        seat++;
    			    }
    			    Order *o = new Order(a, number, adult, child, senior, row, letters);
    		        c->addOrders(o);
    			}
		    }
	    }
	}
	return true;
}

//used to validate the login when customer logs in
Customer* Login(std::unordered_map<std::string, Customer*> cust){
    int tries;
    std::string username;
    std::string password;
    do {
        std::cout << "Enter username: " << std::endl;
        std::cin >> username;
        std::cout << "Enter password: " << std::endl;
        std::cin >> password;
        tries = 1;
        while (cust.at(username)->getPass() != password && tries < 3){
            std::cout << "Invalid password" << std::endl;
            std::cin >> password;
            tries++;
        }
        if (tries == 3 && cust.at(username)->getPass() != password){
                tries = 4;
            }
    } while (tries == 4);
    return cust.at(username);
}

//if the admin logs in, provides a menu for admin to use
bool adminMenu(Auditorium *A1, Auditorium *A2, Auditorium *A3){
    int ans;
    do {
        //prints out menu
        std::cout << "1. Print Report" << std::endl;
        std::cout << "2. Logout" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::string input;
        getline(std::cin, input);
        while (isNum(input) == false || stoi(input) > 3 || stoi(input) < 1) {
    		    getline(std::cin, input);
    	}
    	ans = stoi(input);
    	//displays the report for all three theaters
    	if (ans == 1){
    	    std::cout << "Auditorium 1" << "\t";
    	    A1->displayReport();
    	    std::cout << std::endl;
    	    std::cout << "Auditorium 2" << "\t";
    	    A2->displayReport();
    	    std::cout << std::endl;
    	    std::cout << "Auditorium 3" << "\t";
    	    A3->displayReport();
    	    std::cout << std::endl;
    	    
    	    std::cout << "Total" << "\t" << "\t";
    	    std::cout << A1->getTotal() + A2->getTotal() + A3->getTotal() - A1->getSold() - A2->getSold() - A3->getSold() << "\t";
    	    std::cout << A1->getSold() + A2->getSold() + A3->getSold() << "\t";
    	    std::cout << A1->getAdult() + A2->getAdult() + A3->getAdult() << "\t";
    		std::cout << A1->getChild() + A2->getChild() + A3->getChild() << "\t";
    		std::cout << A1->getSenior() + A2->getSenior() + A3->getSenior() << "\t";
    		std::cout << "$" << std::fixed << std::setprecision(2) << A1->getSales() + A2->getSales() + A3->getSales() <<std::endl;
    	}
    	else if (ans == 2){
    	    //prevents the program from ending if admin logs out
    	    return false;
    	}
    	else {
    	    // creates files for the theaters and ends program
    	    A1->writeToFile("A1Final.txt");
    	    A2->writeToFile("A2Final.txt");
    	    A3->writeToFile("A3Final.txt");
    	    return true;
    	}
    }
    while (ans != 3 && ans != 2);
    return false;
}

//separate menu for customer when they hit the "update menu" option
void updateMenu(Customer *c, Auditorium *a1, Auditorium *a2, Auditorium *a3){
    c->viewUpdateOrders();
    if (c->getNumOrders() > 0){
        std::cout << "Select an order to modify from above" << std::endl;
        int ans;
        std::string input;
        getline(std::cin, input);
        while (isNum(input) == false || stoi(input) > c->getNumOrders() || stoi(input) < 1) {
        	    getline(std::cin, input);
        }
        ans = stoi(input);
        Order *o = c->getOrder(ans - 1);
        int aud = o->getAuditorium();
        do {
            //prints out the menu once the customer selects a valid order
            std:: cout << "1. Add tickets to order" << std::endl;
            std:: cout << "2. Delete tickets from order" << std::endl;
            std:: cout << "3. Cancel Order" << std::endl;
            getline(std::cin, input);
            while (isNum(input) == false || stoi(input) > 5 || stoi(input) < 1) {
            	    getline(std::cin, input);
            }
            ans = stoi(input);
            if (ans == 1){
                //adds tickets using the reserve seats method
            	bool success;
            	if (aud == 1){
            	    success = reservingSeats(a1, 1, c, true, o);
            	}
            	else if (aud == 2){
            	    success = reservingSeats(a2, 2, c, true, o);
            	}
            	else {
            	    success = reservingSeats(a3, 3, c, true, o);
            	}
            	if (success == false){
            	    ans = 4;
            	}
                
            }
            else if (ans == 2){
                //removes seats from the chosen order
                int r;
                int c;
                if (aud == 1){
                    r = a1->getRows();
                    c = a1->getCols();
                }
                if (aud == 2){
                    r = a2->getRows();
                    c = a2->getCols();
                }
                if (aud == 3){
                    r = a3->getRows();
                    c = a3->getCols();
                }
                int row;
                char col;
                std::cout << "Enter desired row" << std::endl;
                getline(std::cin, input);
                while (isNum(input) == false || stoi(input) > r || stoi(input) < 1) {
                	    getline(std::cin, input);
                }
                row = stoi(input);
                std::cout << "Enter desired col" << std::endl;
                std::cin >> col;
                std::string seats = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            	std::string valSeats = seats.substr(0,c);
            	while (valSeats.find(col) == std::string::npos) {
            		std::cin >> col;
            	}
            	//validity of chosen seat is done in Order's remove seat
                bool success = o->removeSeat(row, col);
                if (success == false){
                    ans = 4;
                }
            }
            else {
                o->cancelOrder();
            }
        }
        while (ans == 4);
    }
    
}

//Customer menu that is originally opened up when a customer logs in
void customerMenu(Customer *c, Auditorium *a1, Auditorium *a2, Auditorium *a3){
    int ans;
    do {
        std:: cout << "1. Reserve Seats" << std::endl;
        std:: cout << "2. View Orders" << std::endl;
        std:: cout << "3. Update Order" << std::endl;
        std:: cout << "4. Display Reciept" << std::endl;
        std:: cout << "5. Log Out" << std::endl;
        std::string input;
        getline(std::cin, input);
        while (isNum(input) == false || stoi(input) > 5 || stoi(input) < 1) {
        	    getline(std::cin, input);
        }
        ans = stoi(input);
        if (ans == 1){
            //allows customer to choose an auditorium and use reserve seats to obtain a seat
            std::cout << "1. Auditorium 1" << std::endl;
            std::cout << "2. Auditorium 2" << std::endl;
            std::cout << "3. Auditorium 3" << std::endl;
            int aud;
            getline(std::cin, input);
            while (isNum(input) == false || stoi(input) > 3 || stoi(input) < 1) {
        		    getline(std::cin, input);
        	}
        	aud = stoi(input);
        	Order *o = new Order();
        	if (aud == 1){
        	    reservingSeats(a1, 1, c, false, o);
        	}
        	else if (aud == 2){
        	    reservingSeats(a2, 2, c, false, o);
        	}
        	else {
        	    reservingSeats(a3, 3, c, false, o);
        	}
        	
        }
        else if (ans == 2){
            //uses the customer view orders method to display orders
            c->viewOrders();
        }
        else if (ans == 3){
            // sends the customer to the separate method for update menu
            updateMenu(c, a1, a2, a3);
        }
        else if (ans == 4){
            //displays customer's reciept using Customer's display reciept method
            c->displayReciept();
        }
    }
	while (ans != 5);
}


int main()
{
    //loads in all the given files
    std::unordered_map<std::string, Customer*> cust;
    std::ifstream inFS("userdb.dat");
    while (!inFS.eof()){
        std::string line;
        getline(inFS, line);
        std::string name = line.substr(0, line.find(' '));
        line = line.substr(line.find(' ') + 1);
        Customer *c = new Customer(name, line);
        cust[name] = c;
    }
    Auditorium *a1 = new Auditorium("A1.txt");
    Auditorium *a2 = new Auditorium("A2.txt");
    Auditorium *a3 = new Auditorium("A3.txt");
    
    //system where the customer/admin logs in and performs their orders/tasks
    bool end = false;
    while (end == false){
        Customer *temp = Login(cust);
        
        if (temp->getUser() == "admin"){
            end = adminMenu(a1, a2, a3);
        }
        else {
            customerMenu(temp, a1, a2, a3);
        }
    }
    
    delete a1;
    delete a2;
    delete a3;

    return 0;
}
