/*
Code by ->

    Hashika Chathubhshaka -  https://github.com/HashikaChathubhashaka
    Sandeepa Dilshan      -  https://github.com/sandeepa0105

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>

#include "order.h"

using namespace std;

//----For read the inputs--
vector<Order> readOrders(const string& filename) {
    vector<Order> orders;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening the order.csv file " << filename << "." << endl;
        return orders;
    }

    string line;
    getline(inputFile, line); // Assuming the first line is a header and can be skipped

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string client_order_id, instrument;
        int side, quantity;
        double price;

        getline(ss, client_order_id, ',');
        getline(ss, instrument, ',');
        ss >> side;
        ss.ignore();
        ss >> quantity;
        ss.ignore();
        ss >> price;

        orders.emplace_back(client_order_id, instrument, side, quantity, price);
    }
    inputFile.close();
    return orders;
}

class Compare  {
    public:
    bool operator() (Order ord1, Order ord2) {
        if(ord1.price == ord2.price) {
            return ord1.priority < ord2.priority;
        }
        if(ord1.side == 1) {
            return ord1.price < ord2.price;
        } else {
            return ord1.price > ord2.price;
        }
    }
};


int Order::current_order_id =1;

int main() {
    
    ofstream fileout;
    fileout.open("exec_reports.csv", ios::out);  //*name of the output file
    fileout << "Order ID,Cl. Ord. ID,Instrument,Side,Exec Status,Quantity,Price,Reason,Transaction Time\n";




    priority_queue<Order, vector<Order>, Compare> roseBuy;
    priority_queue<Order, vector<Order>, Compare> roseSell;
    priority_queue<Order, vector<Order>, Compare> lavenderBuy;
    priority_queue<Order, vector<Order>, Compare> lavenderSell;
    priority_queue<Order, vector<Order>, Compare> lotusBuy;
    priority_queue<Order, vector<Order>, Compare> lotusSell;
    priority_queue<Order, vector<Order>, Compare> tulipBuy;
    priority_queue<Order, vector<Order>, Compare> tulipSell;
    priority_queue<Order, vector<Order>, Compare> orchidBuy;
    priority_queue<Order, vector<Order>, Compare> orchidSell;

    // abstraction of priority_queues
    priority_queue<Order, vector<Order>, Compare>* roseOB[2] = {&roseBuy, &roseSell};
    priority_queue<Order, vector<Order>, Compare>* lavenderOB[2] = {&lavenderBuy, &lavenderSell};
    priority_queue<Order, vector<Order>, Compare>* lotusOB[2] = {&lotusBuy, &lotusSell};
    priority_queue<Order, vector<Order>, Compare>* tulipOB[2] = {&tulipBuy, &tulipSell};
    priority_queue<Order, vector<Order>, Compare>* orchidOB[2] = {&orchidBuy, &orchidSell};

    priority_queue<Order, vector<Order>, Compare>** orderBooks[5] = {roseOB, lavenderOB, lotusOB, tulipOB, orchidOB};

    string filename ="orders.csv";  //* name of the input file

    vector<Order> orders = readOrders(filename);

    for (Order& order : orders) {
        string validityResult = order.checkValidity();
        if (validityResult.empty()) {
            order.status =0; //putting default status as New.

            int instrument_number = (int)(find(begin(instruments), end(instruments), order.instrument) - begin(instruments));
            priority_queue<Order, vector<Order>, Compare>** orderBook = orderBooks[instrument_number];

        if (order.side ==1){//buy side

        //! orderbook[1] -> sell side
        //! orderbook[2]  -> buy side

                while(!(orderBook[1]->empty()) && ((orderBook[1]->top()).price <= order.price)) {


                    Order topOrder = (orderBook[1]->top()); //making new object as toporder
                    if(order.r_quantity == topOrder.r_quantity) {             // most attractive sell order quantity = buy order quantity
                        order.status = 1; //fill
                        topOrder.status = 1; //fill
                        order.price = topOrder.price;
                        order.execution(fileout,order.r_quantity);
                        topOrder.execution(fileout,order.r_quantity);
                        order.r_quantity = 0;
                        topOrder.r_quantity = 0;
                        orderBook[1]->pop();
                        break;

                    } else if(order.r_quantity > topOrder.r_quantity) {       // most attractive sell order quantity < buy order quantity
                        double temp = order.price;
                        order.status = 2; //Pfill
                        topOrder.status = 1; //fill
                        order.price = topOrder.price;
                        order.execution(fileout, topOrder.r_quantity);
                        topOrder.execution(fileout, topOrder.r_quantity);
                        order.r_quantity = order.r_quantity - topOrder.r_quantity;
                        topOrder.r_quantity = 0;
                        order.price = temp;
                        orderBook[1]->pop();


                    } else {                                                    // most attractive sell order quantity > buy order quantity
                        order.status = 1; //fill
                        topOrder.status = 2; //pfill
                        order.price = topOrder.price;
                        order.execution(fileout,order.r_quantity);
                        topOrder.execution(fileout,order.r_quantity);
                        topOrder.r_quantity = topOrder.r_quantity - order.r_quantity;
                        topOrder.priority++;
                        orderBook[1]->pop();
                        orderBook[1]->emplace(topOrder);
                        order.r_quantity = 0;
                        break;
                    }
                }

                if(order.status==0){
                    order.execution(fileout,order.r_quantity);
                }

                if(order.r_quantity > 0){
                    orderBook[0] -> emplace(order);
                }


        }else if(order.side==2){  //sell side

            while(!(orderBook[0]->empty()) && ((orderBook[0]->top()).price >= order.price)) {

                    Order topOrder = orderBook[0]->top();
                    if(order.r_quantity == topOrder.r_quantity) {                 // most attractive buy order quantity = sell order quantity
                        order.status = 1;
                        topOrder.status = 1;
                        order.price = topOrder.price; 
                        order.execution(fileout,order.r_quantity);
                        topOrder.execution(fileout,topOrder.r_quantity);
                        order.r_quantity = 0;
                        topOrder.r_quantity = 0;
                        orderBook[0]->pop();
                        break;

                    } else if(order.r_quantity > topOrder.r_quantity) {           // most attractive buy order quantity < sell order quantity
                        double temp2 = order.price;
                        order.status = 2;
                        topOrder.status = 1;
                        order.price = topOrder.price; 
                        order.execution(fileout, topOrder.r_quantity);
                        order.r_quantity = order.r_quantity - topOrder.r_quantity;
                        topOrder.execution(fileout,topOrder.r_quantity);
                        topOrder.r_quantity = 0;
                        order.price = temp2;
                        orderBook[0]->pop();
                    } else {                                                        // most attractive buy order quantity > sell order quantity+
                        order.status = 1;
                        topOrder.status = 2;
                        order.price = topOrder.price;
                        order.execution(fileout, topOrder.r_quantity);
                        topOrder.execution(fileout, topOrder.r_quantity);
                        topOrder.r_quantity = topOrder.r_quantity - order.r_quantity;
                        topOrder.priority++;
                        orderBook[0]->pop();
                        orderBook[0]->emplace(topOrder);
                        order.r_quantity = 0;
                        break;
                    }
                }

                // Depicts a 'New' order being put into the order book
                if(order.status == 0) {
                    order.execution(fileout,order.r_quantity);
                }

                // If the aggressive order is not fully executed, then put it into the order book 
                if(order.r_quantity > 0.0) {
                    orderBook[1]->emplace(order);
                }
        }

        }
        // if rejected
        else {
            order.status = 3;
            order.execution(fileout,order.quantity);
            
        }

    }
    return 0;
}
