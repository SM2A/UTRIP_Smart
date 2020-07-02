#include "Hotel.hpp"
#include <iostream>
#include <iomanip>
#include "../Utility/Error.hpp"

#define EMPTY 0
#define EXPONENT 2
#define NO_ROOM -1

using namespace std;

Hotel::Hotel(string id_, string name_, int star_, string overview_, string facilities_,string city_,
		geographical_coordinates location_, string image_url_, room_data data) {

	this->id = id_;
	this->name = name_;
	this->star = star_;
	this->overview = overview_;
	this->facilities = facilities_;
	this->city = city_;
	this->location = location_;
	this->image_url = image_url_;
	this->rooms = new Room_handler(data);
	this->total_rooms_count = data.standard.second + data.deluxe.second + data.luxury.second + data.premium.second;
	this->average_price = calculate_average_price(data);
	this->comments = new Comment_Handler();
	this->ratings = new Rating_Handler();
	this->avg_rating = nullptr;
	this->rooms_data = data;
}

float Hotel::calculate_average_price(room_data data) {

	float avg_price = 0;
	int type_count = 0;
	int total_price = data.standard.first+data.deluxe.first+data.luxury.first+data.premium.first;

	if(data.standard.first!=EMPTY) type_count++;
	if(data.deluxe.first!=EMPTY)type_count++;
	if(data.luxury.first!=EMPTY)type_count++;
	if(data.premium.first!=EMPTY)type_count++;

	if(type_count==EMPTY) avg_price=EMPTY;
	else avg_price = (float) total_price/(float)type_count;
	return avg_price;
}

void Hotel::print_summary() {

	string summary = id +" "+ name +" "+ to_string(star) +" "+ city +" "+ to_string(total_rooms_count)+" ";
	cout<<summary<<fixed<<setprecision(EXPONENT)<<average_price<<endl;
}

void Hotel::print_detail() {

	cout<<id<<endl<<name<<endl;
	cout<<"star: "<<star<<endl;
	cout<<"overview: "<<overview<<endl;
	cout<<"amenities: "<<facilities<<endl;
	cout<<"city: "<<city<<endl;
	cout<<"latitude: "<<fixed<<setprecision(EXPONENT)<<location.latitude<<endl;
	cout<<"longitude: "<<fixed<<setprecision(EXPONENT)<<location.longitude<<endl;
	cout<<"#rooms: "<<this->rooms->rooms_count()<<endl;
	cout<<"price: "<<this->rooms->rooms_price()<<endl;
}

int Hotel::reserve_cost(string room_type, int quantity , range date_) {

	int rooms_cost = 0;
	if(room_type == "standard") rooms_cost = rooms->check_availability_s(quantity,date_);
	else if(room_type == "deluxe") rooms_cost = rooms->check_availability_d(quantity,date_);
	else if(room_type == "premium") rooms_cost = rooms->check_availability_p(quantity,date_);
	else if(room_type == "luxury") rooms_cost = rooms->check_availability_l(quantity,date_);
	if(rooms_cost == NO_ROOM) throw Not_Enough_Room();

	return rooms_cost;
}

vector<Room*> Hotel::reserve(string room_type, int quantity, range date_) {

	vector<Room*> rooms_;
	if(room_type == "standard") rooms_ = rooms->reserve_s(quantity,date_);
	else if(room_type == "deluxe") rooms_ = rooms->reserve_d(quantity,date_);
	else if(room_type == "premium") rooms_ = rooms->reserve_p(quantity,date_);
	else if(room_type == "luxury") rooms_ = rooms->reserve_l(quantity,date_);
	return rooms_;
}

void Hotel::add_comment(string writer , string comment) {

	comments->add_comment(writer,comment);
}

void Hotel::show_comments() {

	comments->print();
}

Rating* Hotel::rate(string writer, double location, double cleanness, double staff, double facilities,
		double value_for_money,double overall) {

	return ratings->add_rating(writer,location,cleanness,staff,facilities,value_for_money,overall);
}

void Hotel::show_average_rating() {

	avg_rating->print();
}

bool Hotel::available_rooms(std::string type,int quantity,range date_) {

	return rooms->have_available_rooms(type,quantity,date_);
}

void Hotel::add_avg_rating(Rating *rating) {

	this->avg_rating = rating;
}

bool sort_by_id(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(sort_order == DESCENDING) return first->id > second->id;
	else return first->id < second->id;
}

bool sort_by_name(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->name == second->name) return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->name > second->name;
	else return first->name < second->name;
}

bool sort_by_star(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->star == second->star) return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->star > second->star;
	else return first->star < second->star;
}

bool sort_by_city(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->city == second->city) return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->city > second->city;
	else return first->city < second->city;
}

bool sort_by_s_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->rooms_data.standard.first == second->rooms_data.standard.first)
		return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->rooms_data.standard.first > second->rooms_data.standard.first;
	else return first->rooms_data.standard.first < second->rooms_data.standard.first;
}

bool sort_by_d_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->rooms_data.deluxe.first == second->rooms_data.deluxe.first)
		return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->rooms_data.deluxe.first > second->rooms_data.deluxe.first;
	else return first->rooms_data.deluxe.first < second->rooms_data.deluxe.first;
}

bool sort_by_l_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->rooms_data.luxury.first == second->rooms_data.luxury.first)
		return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->rooms_data.luxury.first > second->rooms_data.luxury.first;
	else return first->rooms_data.luxury.first < second->rooms_data.luxury.first;
}

bool sort_by_p_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->rooms_data.premium.first == second->rooms_data.premium.first)
		return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->rooms_data.premium.first > second->rooms_data.premium.first;
	else return first->rooms_data.premium.first < second->rooms_data.premium.first;
}

bool sort_by_avg_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order){

	if(first->average_price == second->average_price) return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first->average_price > second->average_price;
	else return first->average_price < second->average_price;
}

double Hotel::calc_overall(double location_,double cleanness_,double staff_,double facilities_,double value_for_money_) {

	return avg_rating->calc_overall(location_,cleanness_,staff_,facilities_,value_for_money_);
}
