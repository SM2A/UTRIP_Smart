#include "Room_handler.hpp"

#define NO_ROOM -1

using namespace std;

Room_handler::Room_handler(room_data data) {

	creat_standard_room(data.standard);
	creat_deluxe_room(data.deluxe);
	creat_luxury_room(data.luxury);
	creat_premium_room(data.premium);
}

void Room_handler::creat_standard_room(price_count standard_) {

	this->standard.first = standard_.first;
	for (int i = 0; i < standard_.second; ++i) {
		Standard_Room *room = new Standard_Room(i + 1);
		this->standard.second.push_back(room);
	}
}

void Room_handler::creat_deluxe_room(price_count deluxe_) {

	this->deluxe.first = deluxe_.first;
	for (int i = 0; i < deluxe_.second; ++i) {
		Deluxe_Room *room = new Deluxe_Room(i + 1);
		this->deluxe.second.push_back(room);
	}
}

void Room_handler::creat_luxury_room(price_count luxury_) {

	this->luxury.first = luxury_.first;
	for (int i = 0; i < luxury_.second; ++i) {
		Luxury_Room *room = new Luxury_Room(i + 1);
		this->luxury.second.push_back(room);
	}
}

void Room_handler::creat_premium_room(price_count premium_) {

	this->premium.first = premium_.first;
	for (int i = 0; i < premium_.second; ++i) {
		Premium_Room *room = new Premium_Room(i + 1);
		this->premium.second.push_back(room);
	}
}

string Room_handler::rooms_count() {

	string out = to_string(standard.second.size()) + " " + to_string(deluxe.second.size()) + " " +
	             to_string(luxury.second.size()) + " " + to_string(premium.second.size());
	return out;
}

string Room_handler::rooms_price() {

	string out = to_string(standard.first) + " " + to_string(deluxe.first) + " " + to_string(luxury.first) + " " +
	             to_string(premium.first);
	return out;
}

int Room_handler::check_availability_s(int quantity, range date_) {

	int available_rooms = 0;

	for (Standard_Room *room : standard.second)
		if (room->is_available(date_)) available_rooms++;

	if (available_rooms >= quantity) return (quantity * standard.first* Date().duration(date_));

	return NO_ROOM;
}

int Room_handler::check_availability_d(int quantity, range date_) {

	int available_rooms = 0;

	for (Deluxe_Room *room : deluxe.second)
		if (room->is_available(date_)) available_rooms++;

	if (available_rooms >= quantity) return (quantity * deluxe.first * Date().duration(date_));

	return NO_ROOM;
}

int Room_handler::check_availability_p(int quantity, range date_) {

	int available_rooms = 0;

	for (Premium_Room *room : premium.second)
		if (room->is_available(date_)) available_rooms++;

	if (available_rooms >= quantity) return (quantity * premium.first* Date().duration(date_));

	return NO_ROOM;
}

int Room_handler::check_availability_l(int quantity, range date_) {

	int available_rooms = 0;

	for (Luxury_Room *room : luxury.second)
		if (room->is_available(date_)) available_rooms++;

	if (available_rooms >= quantity) return (quantity * luxury.first* Date().duration(date_));

	return NO_ROOM;
}

vector<Room*> Room_handler::reserve_s(int quantity, range date_) {

	vector<Room*> rooms;
	int reserved = 0;
	for(Standard_Room* room : standard.second)
		if(room->is_available(date_)){
			room->reserve(date_);
			rooms.push_back(room);
			reserved++;
			if(quantity==reserved) break;
		}
	return rooms;
}

vector<Room*> Room_handler::reserve_d(int quantity, range date_) {

	vector<Room*> rooms;
	int reserved = 0;
	for(Deluxe_Room* room : deluxe.second)
		if(room->is_available(date_)){
			room->reserve(date_);
			rooms.push_back(room);
			reserved++;
			if(quantity==reserved) break;
		}
	return rooms;
}

vector<Room*> Room_handler::reserve_p(int quantity, range date_) {

	vector<Room*> rooms;
	int reserved = 0;
	for(Premium_Room* room : premium.second)
		if(room->is_available(date_)){
			room->reserve(date_);
			rooms.push_back(room);
			reserved++;
			if(quantity==reserved) break;
		}
	return rooms;
}

vector<Room*> Room_handler::reserve_l(int quantity, range date_) {

	vector<Room*> rooms;
	int reserved = 0;
	for(Luxury_Room* room : luxury.second)
		if(room->is_available(date_)){
			room->reserve(date_);
			rooms.push_back(room);
			reserved++;
			if(quantity==reserved) break;
		}
	return rooms;
}

bool Room_handler::have_available_rooms(std::string type,int quantity ,range date_) {

	if(type == "standard"){
		return check_availability_s(quantity, date_) != NO_ROOM;
	} else if(type == "deluxe"){
		return check_availability_d(quantity, date_) != NO_ROOM;
	}else if(type == "luxury"){
		return check_availability_l(quantity, date_) != NO_ROOM;
	}else if(type == "premium"){
		return check_availability_p(quantity, date_) != NO_ROOM;
	}
}