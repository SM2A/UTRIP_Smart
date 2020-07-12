#include "UTrip.hpp"
#include <iostream>
#include "../Hotel/Hotel.hpp"
#include "../Utility/Error.hpp"
#include "../Filter/Average_Price.hpp"
#include "../Filter/Available_Room.hpp"
#include "../Filter/City.hpp"
#include "../Filter/Star_Range.hpp"
#include "../Filter/Default_Budget.hpp"

#define SUCCESS "OK"
#define ESTIMATED "estimated"

using namespace std;

UTrip::UTrip(string hotels_path,string ratings_path) {

	hotels = new Hotel_Handler(hotels_path,ratings_path);
	users = new User_Handler();
	logged_in_user = nullptr;
	manual_weights = new Manual_Weights();
	estimated = new Manual_Weights();

	filters[CITY] = nullptr;
	filters[STAR] = nullptr;
	filters[PRICE] = nullptr;
	filters[ROOMS] = nullptr;
	filters[DEFAULT_BUDGET] = new Default_Budget();
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
	reset_filter();
	logged_in_user = nullptr;
	reset_sort();
	manual_weights->change_state(false);
	cout<<SUCCESS<<endl;
}

void UTrip::login(string user_name, string password) {

	if(is_user_logged_in()) throw Permission_Denied();
	try {
		logged_in_user = users->login(user_name,password);
		filters[DEFAULT_BUDGET] = new Default_Budget();
		reset_sort();
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
		hotels->print(filters,logged_in_user,sort_order,sort_property,manual_weights,estimated);
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

void UTrip::add_comment(string hotel_id,string comment) {

	if(!is_user_logged_in()) throw Permission_Denied();
	logged_in_user->add_comment(comment,hotels->find(hotel_id));
}

void UTrip::show_hotel_comment(string hotel_id) {

	if(!is_user_logged_in()) throw Permission_Denied();
	Hotel* hotel = hotels->find(hotel_id);
	hotel->show_comments();
}

void UTrip::add_rating(string hotel_id, float location, float cleanness, float staff, float facilities,
                       float value_for_money, float overall) {

	if(!is_user_logged_in()) throw Permission_Denied();
	Hotel* hotel = hotels->find(hotel_id);
	Rating* rating =
	hotel->rate(logged_in_user->get_user_name(),location,cleanness,staff,facilities,value_for_money,overall);
	logged_in_user->save_rating(hotel->get_id(),rating);
	estimated->change_state(false);
	cout<<SUCCESS<<endl;
}

void UTrip::show_hotel_rating(string hotel_id) {

	if(!is_user_logged_in()) throw Permission_Denied();
	hotels->find(hotel_id)->show_average_rating();
}

void UTrip::add_city_filter(string city) {

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

void UTrip::add_available_room_filter(string type, int quantity, range date_) {

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
	reset_filter();
	cout<<SUCCESS<<endl;
}

void UTrip::default_price_filter(bool state) {

	if(!is_user_logged_in()) throw Permission_Denied();
	filters[DEFAULT_BUDGET]->set_status(state);
	cout<<SUCCESS<<endl;
}

void UTrip::reset_sort() {

	sort_order = ASCENDING;
	sort_property = ID;
}

void UTrip::reset_filter() {

	for(int i = 0 ; i < FILTERS_SIZE ; i++){
		delete(filters[i]);
		filters[i] = nullptr;
	}
}

void UTrip::parse_sort_property(string property, string order) {

	if(!is_user_logged_in()) throw Permission_Denied();

	if(property == "id") sort_property = ID;
	else if(property == "name") sort_property = NAME;
	else if(property == "star_rating") sort_property = STAR_RATING;
	else if(property == "city") sort_property = CITY_;
	else if(property == "standard_room_price") sort_property = S_PRICE;
	else if(property == "deluxe_room_price") sort_property = D_PRICE;
	else if(property == "luxury_room_price") sort_property = L_PRICE;
	else if(property == "premium_room_price") sort_property = P_PRICE;
	else if(property == "average_room_price") sort_property = AVG_PRICE;
	else if(property == "rating_personal") personal_rating();
	else throw Bad_Request();

	if(order == "ascending") sort_order = ASCENDING;
	else if(order == "descending") sort_order = DESCENDING;
	else throw Bad_Request();

	cout<<SUCCESS<<endl;
}

void UTrip::show_manual_weights() {

	if(!is_user_logged_in()) throw Permission_Denied();
	manual_weights->print();
}

void UTrip::manual_weights_state(bool active) {

	if(!is_user_logged_in()) throw Permission_Denied();
	manual_weights->change_state(active);
	cout<<SUCCESS<<endl;
}

void UTrip::add_manual_weights(bool active, float location, float cleanliness, float staff, float facilities,
                               float value_for_money) {

	if(!is_user_logged_in()) throw Permission_Denied();
	manual_weights->add_manual_weight(active,location,cleanliness,staff,facilities,value_for_money);
	cout<<SUCCESS<<endl;
}

void UTrip::personal_rating() {

	if(!is_user_logged_in()) throw Permission_Denied();
	if(manual_weights->get_state()) sort_property = RATING_PERSONAL;
	else {
		if (!logged_in_user->do_have_enough_rating()) throw Insufficient_Ratings();
		if(!estimated->get_state()){
			delete (estimated);
			estimated = logged_in_user->calc_estimated_weight();
			estimated->change_state(true);
			sort_property = RATING_PERSONAL;
		}
	}
}

void UTrip::show_estimated_weights() {

	if(!is_user_logged_in()) throw Permission_Denied();
	if (!logged_in_user->do_have_enough_rating()) throw Insufficient_Ratings();
	estimated->print(ESTIMATED);
}
