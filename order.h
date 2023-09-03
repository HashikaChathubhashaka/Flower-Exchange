#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
using namespace std;

vector<string> instruments = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};

class Order {
public:
    //variables
    //IDs

    string client_order_id;
    string order_id;
    string instrument;
    static int current_order_id ;
    int side;  // 1: Buy, 2: Sell
    int quantity;
    double price;
    int status;
    int r_quantity;
    int priority;
    //constructor

    Order(const string& _client_order_id, const string& _instrument, int _side, int _quantity, double _price){
        client_order_id= _client_order_id;
        instrument = _instrument;
        side = _side; 
        quantity = _quantity;
        price = _price; 
        r_quantity = quantity;
        priority = 1;
        order_id = "ord" + to_string(current_order_id++);

    }
    //function for checking validity
    string checkValidity() {

        string sideStr = to_string(side); // Convert side to a string
        string priceStr = to_string(price); // Convert price to a string
        string quantityStr = to_string(quantity); // Convert quantity to a string
        

        if (client_order_id.empty() || instrument.empty() || sideStr.empty() || priceStr.empty() || quantityStr.empty() ) {
            return "Invalid fields";
        }
        else if (find(instruments.begin(), instruments.end(), instrument) == instruments.end()) {
            return "Invalid instrument";
        }
        else if (side != 1 && side != 2) {
            return "Invalid side";
        }
        else if (price <= 0.00) {
            return "Invalid price";
        }
        else if (quantity % 10 != 0 || quantity <= 10 || quantity >= 1000) {
            return "Invalid size";
        }

        return ""; // Empty string indicates valid input
    }

    void execution(ofstream &fout,int Qunt){ //qunt -> exection report quntity
        
        string exec_status = "";

        auto now = chrono::system_clock::now();
        auto now_ms = chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        time_t t = chrono::system_clock::to_time_t(now);
        tm* tm = localtime(&t);
        
        if (status==0) exec_status = "New";
        else if(status==1) exec_status ="Fill";
        else if(status==2) exec_status = "PFill";
        else if(status==3) exec_status ="Reject";

        fout << order_id << "," << client_order_id << "," << instrument << "," << side << "," << exec_status << ","
        << Qunt << "," << fixed << setprecision(2) << price <<  "," << checkValidity()<< "," 
        << put_time(tm, "%Y.%m.%d-%H.%M.%S") << "." << setfill('0') << setw(3) << to_string(now_ms.count())  << "\n";

    }
};
