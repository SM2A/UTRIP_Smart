#include "Reserve.hpp"
#include <iostream>
#include <cmath>
#include "../Utility/Error.hpp"

#define EMPTY 0

using namespace std;

Reserve::Reserve(string hotel_id,string room_type,int quantity,int cost,range reservation_date_,
                 vector<Room*> rooms_ , int id_ , bool cancelled) {

	this->id = id_;
	this->hotel_id = hotel_id;
	this->room_type = room_type;
	this->quantity = quantity;
	this->cost = cost;
	this->reservation_date = reservation_date_;
	this->rooms = rooms_;
	this->cancelled = cancelled;
}

void Reserve::print() {

	if(cancelled) return;
	string output = "id: "+to_string(id)+" hotel: "+hotel_id+" room: "+room_type+" quantity: "+to_string(quantity)
			+" cost: "+to_string(cost)+" check_in "+to_string(reservation_date.start.get_day())
			+" check_out "+to_string(reservation_date.end.get_day());
	cout<<output<<endl;
}

int Reserve::cancel() {

	if(cancelled) throw Not_Found();
	this->cancelled = true;
	for(Room* room : rooms) room->cancel_reserve();
	return cost;
}

float Reserve::get_price() {

	if(cancelled)return EMPTY;
	else return (float)cost/(float)Date().duration(reservation_date);
}

float Reserve::calc_sigma(float avg_price) {

	if (cancelled) return 0;

	float sum = 0;
	int one_night_price = get_price()/rooms.size();
	for (Room* room : rooms) sum += pow((one_night_price - avg_price),2);
	return sum;
}
