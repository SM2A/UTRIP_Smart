#include "UTrip.hpp"
#include <iostream>
#include "../Hotel/Hotel.hpp"
#include "../Utility/Error.hpp"
#include "../Filter/Average_Price.hpp"
#include "../Filter/Available_Room.hpp"
#include "../Filter/City.hpp"
#include "../Filter/Star_Range.hpp"

#define SUCCESS "OK"

using namespace std;

UTrip::UTrip(string path) {

	hotels = new Hotel_Handler(path);
	users = new User_Handler();
	logged_in_user = nullptr;

	filters[CITY] = nullptr;
	filters[STAR] = nullptr;
	filters[PRICE] = nullptr;
	filters[ROOMS] = nullptr;
}

void UTrip::creat_user(string user_name, string password, string e_mail) {

	if(is_user_logged_in()) throw Permission_Denied();
	try {
		logged_in_user = users->creat_user(user_name, password, e_mail);
	}catch (exception& e){
		cout<<e.what()<<endl;
		delete(logged_in_user);
		logged_in_user = nullptr;
	}
}

void UTrip::logout() {

	if(!is_user_logged_in()) throw Permission_Denied();
	for(int i = 0 ; i < FILTERS_SIZE ; i++){
		delete(filters[i]);
		filters[i] = nullptr;
	}
	logged_in_user = nullptr;
	cout<<SUCCESS<<endl;
}

void UTrip::login(string user_name, string password) {

	if(is_user_logged_in()) throw Permission_Denied();
	try {
		logged_in_user = users->login(user_name,password);
		cout<<SUCCESS<<endl;
	}catch (exception& e){
		cout<<e.what()<<endl;
		logged_in_user = nullptr;
	}
}

void UTrip::add_credit(float value) {

	if(!is_user_logged_in()) throw Permission_Denied();
	logged_in_user->add_credit(value);
}

bool UTrip::is_user_logged_in() {

	return logged_in_user != nullptr;
}

void UTrip::wallet_history(int count) {

	if(!is_user_logged_in()) throw Permission_Denied();
	logged_in_user->print_wallet_history(count);
}

void UTrip::show_hotel() {

	if(!is_user_logged_in()) throw Permission_Denied();
	try {
		hotels->print(filters);
	}catch (exception& e){
		cout<<e.what()<<endl;
	}
}

void UTrip::show_hotel(string id) {

	if(!is_user_logged_in()) throw Permission_Denied();
	try {
		hotels->print(id);
	}catch (exception& e){
		cout<<e.what()<<endl;
	}
}

void UTrip::reserve(string hotel_id, string room_type, int quantity, int check_in, int check_out) {

	if(!is_user_logged_in()) throw Permission_Denied();
	range reserve_date;
	reserve_date.start.set_day(check_in);
	reserve_date.end.set_day(check_out);
	try {
		Hotel *hotel = hotels->find(hotel_id);
		if(!logged_in_user->have_enough_credit(hotel->reserve_cost(room_type,quantity,reserve_date)))
			throw Not_Enough_Credit();
		logged_in_user->reserve(hotel,room_type,quantity,
				reserve_date,hotel->reserve_cost(room_type,quantity,reserve_date));
	}catch (exception& e){
		cout<<e.what()<<endl;
	}
}

void UTrip::show_reserves() {

	if(!is_user_logged_in()) throw Permission_Denied();
	logged_in_user->show_reserves();
}

void UTrip::cancel_reservation(int id) {

	if(!is_user_logged_in()) throw Permission_Denied();
	logged_in_user->cancel_reservation(id);
}

void UTrip::add_comment(std::string hotel_id,std::string comment) {

	if(!is_user_logged_in()) throw Permission_Denied();
	logged_in_user->add_comment(comment,hotels->find(hotel_id));
}

void UTrip::show_hotel_comment(std::string hotel_id) {

	if(!is_user_logged_in()) throw Permission_Denied();
	Hotel* hotel = hotels->find(hotel_id);
	hotel->show_comments();
}

void UTrip::add_rating(std::string hotel_id, float location, float cleanness, float staff, float facilities,
                       float value_for_money, float overall) {

	if(!is_user_logged_in()) throw Permission_Denied();
	Hotel* hotel = hotels->find(hotel_id);
	hotel->rate(logged_in_user->get_user_name(),location,cleanness,staff,facilities,value_for_money,overall);
	cout<<SUCCESS<<endl;
}

void UTrip::show_hotel_rating(std::string hotel_id) {

	if(!is_user_logged_in()) throw Permission_Denied();
	hotels->find(hotel_id)->show_average_rating();
}

void UTrip::add_city_filter(std::string city) {

	if(!is_user_logged_in()) throw Permission_Denied();
	if(filters[CITY] == nullptr) filters[CITY] = new City(city);
	else {
		delete(filters[CITY]);
		filters[CITY] = new City(city);
	}
	cout<<SUCCESS<<endl;
}

void UTrip::add_star_filter(int min, int max) {

	if(!is_user_logged_in()) throw Permission_Denied();
	if(filters[STAR] == nullptr) filters[STAR] = new Star_Range(min,max);
	else {
		delete(filters[STAR]);
		filters[STAR] =  new Star_Range(min,max);
	}
	cout<<SUCCESS<<endl;
}

void UTrip::add_price_filter(float min, float max) {

	if(!is_user_logged_in()) throw Permission_Denied();
	if(filters[PRICE] == nullptr) filters[PRICE] = new Average_Price(min,max);
	else {
		delete(filters[PRICE]);
		filters[PRICE] =  new Average_Price(min,max);
	}
	cout<<SUCCESS<<endl;
}

void UTrip::add_available_room_filter(std::string type, int quantity, range date_) {

	if(!is_user_logged_in()) throw Permission_Denied();
	if(filters[ROOMS] == nullptr) filters[ROOMS] = new Available_Room(type,quantity,date_);
	else {
		delete(filters[ROOMS]);
		filters[ROOMS] =  new Available_Room(type,quantity,date_);
	}
	cout<<SUCCESS<<endl;
}

void UTrip::remove_filter() {

	if(!is_user_logged_in()) throw Permission_Denied();
	for(int i = 0 ; i < FILTERS_SIZE ; i++){
		delete(filters[i]);
		filters[i] = nullptr;
	}
	cout<<SUCCESS<<endl;
}