#include "User.hpp"
#include "../Utility/Error.hpp"
#include <iostream>
#include "../Hotel/Hotel.hpp"

#define INIT_CREDIT 0
#define SUCCESS "OK"
#define CANCEL_RESERVE 2
#define ENOUGH_RATING 5

using namespace std;

User::User(string user_name, string password_, string e_mail) {

	name = user_name;
	password = hash<string>{}(password_);
	email = e_mail;
	credit = INIT_CREDIT;
	reservations = new Reserve_Handler();
	ratings = new Rating_Handler();
	credit_report.push_back(credit);
}

void User::identity_taken_check(User *new_user, User *user) {

	if(new_user->name == user->name) throw Bad_Request();
	if(new_user->email == user->email) throw Bad_Request();
}

void User::is_credentials_valid(string password_) {
	size_t pass = hash<string>{}(password_);
	if(pass!=password) throw Bad_Request();
}

void User::add_credit(float value) {

	if(value <= INIT_CREDIT) throw Bad_Request();
	credit+=value;
	credit_report.push_back(credit);
	cout<<SUCCESS<<endl;
}

void User::print_wallet_history(int count) {

	for (int i = 0; (i < credit_report.size()) && (i != count); i++)
		cout << (int)credit_report[(credit_report.size() - 1) - i] << endl;
}

bool User::have_enough_credit(int credit_) {
	return credit_ <= this->credit;
}

void User::pay_for_reserve(int price) {

	credit-=price;
}

void User::reserve(Hotel *hotel, string room_type, int quantity, range date_,int price) {

	vector<Room*> rooms = hotel->reserve(room_type,quantity,date_);
	reservations->reserve(hotel->get_id(),room_type,quantity,price,date_,rooms);
	pay_for_reserve(price);
	credit_report.push_back(credit);

}

void User::show_reserves() {

	reservations->print();
}

void User::cancel_reservation(int id) {

	float cost = reservations->cancel(id);
	credit+=cost/CANCEL_RESERVE;
	credit_report.push_back(credit);
	cout<<SUCCESS<<endl;
}

void User::add_comment(string comment , Hotel* hotel) {

	hotel->add_comment(name,comment);
	cout<<SUCCESS<<endl;
}

void User::save_rating(string hotel_id, Rating *rating) {

	ratings->add_rating(hotel_id,rating);
}

double User::do_rated(Hotel* hotel) {

	return ratings->do_rated(hotel->get_id());
}

bool User::do_have_enough_rating() {

	return ratings->get_ratings_count() >= ENOUGH_RATING;
}

Manual_Weights *User::calc_estimated_weight() {

	return ratings->calc_estimated_weight();
}
