#include <iostream>
#include "Reserve_Handler.hpp"
#include "../Utility/Error.hpp"
#include "Reserve.hpp"

using namespace std;

#define EMPTY 0

void Reserve_Handler::print() {

	if(reserves.size()==EMPTY) throw Empty();
	for(int i = reserves.size()-1 ; i >= 0 ; i--)
		reserves[i]->print();
}

float Reserve_Handler::cancel(int id) {

	try {
		if((id > reserves.size())||(id <= 0)) throw Not_Found();
		float cost = (float)reserves[id-1]->cancel();
		return cost;
	}catch (...){
		throw Not_Found();
	}
}

void Reserve_Handler::reserve(string hotel_id,string room_type, int quantity, int cost, range reservation_date_,
		vector<Room *> rooms) {

	Reserve* reserve_ = new Reserve(hotel_id,room_type,quantity,cost,reservation_date_,rooms,reserves.size()+1);
	for(Room* room : rooms) cout<<room->get_id()<<" ";
	cout<<endl;
	reserves.push_back(reserve_);
}