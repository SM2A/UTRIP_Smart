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

int Reserve_Handler::number_of_reserves() {

	int count = 0;
	for(Reserve* reserve_ : reserves) if(!reserve_->is_cancelled()) count++;
	return count;
}

float Reserve_Handler::calc_avg_price() {

	float sum = 0;
	for (Reserve* reserve_ : reserves) sum+=reserve_->get_price();
	return sum/(float)total_reserved_rooms();
}

int Reserve_Handler::total_reserved_rooms() {

	int count = 0;
	for(Reserve* reserve_ : reserves) if(!reserve_->is_cancelled()) count += reserve_->get_quantity();
	return count;
}

float Reserve_Handler::calc_sigma(float avg_price) {

	float sum = 0;
	for(Reserve* reserve_ : reserves) sum+=reserve_->calc_sigma(avg_price);
	return sum;
}
