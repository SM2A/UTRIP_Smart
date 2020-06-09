#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "../Reserve/Reserve_Handler.hpp"
#include "User_Handler.hpp"
#include "../Utility/Date.hpp"

class Hotel;

class User {

public:

	User(std::string user_name , std::string password_ , std::string e_mail);
	void identity_taken_check(User* new_user , User* user);
	void cancel_reservation(int id);
	void is_credentials_valid(std::string password);
	void add_credit(float value);
	void print_wallet_history(int count);
	bool have_enough_credit(int credit_);
	void reserve(Hotel* hotel , std::string room_type , int quantity , range date_ ,int price);
	void show_reserves();
	void add_comment(std::string comment,Hotel* hotel);
	std::string get_user_name(){ return name;}

private:

	std::string name;
	size_t password;
	std::string email;
	float credit;
	std::vector<float> credit_report;
	Reserve_Handler* reservations;

	void pay_for_reserve(int price);
	friend User* User_Handler::find(std::string user_name);
};

#endif