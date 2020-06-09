#ifndef UTRIP_HPP
#define UTRIP_HPP

#include "../Hotel/Hotel_Handler.hpp"
#include "../User/User_Handler.hpp"
#include "../Filter/Filter.hpp"
#include "../User/User.hpp"

#define FILTERS_SIZE 4

class UTrip {

public:

	UTrip(std::string path);
	void cancel_reservation(int id);
	void creat_user(std::string user_name , std::string password , std::string e_mail);
	void logout();
	void login(std::string user_name , std::string password);
	void add_credit(float value);
	void wallet_history(int count);
	void show_hotel();
	void show_hotel(std::string id);
	void reserve(std::string hotel_id,std::string room_type,int quantity,int check_in,int check_out);
	void show_reserves();
	void add_comment(std::string hotel_id,std::string comment);
	void show_hotel_comment(std::string hotel_id);
	void add_rating(std::string hotel_id,float location,float cleanness,float staff,float facilities,
	                float value_for_money,float overall);
	void show_hotel_rating(std::string hotel_id);
	void add_city_filter(std::string city);
	void add_star_filter(int min , int max);
	void add_price_filter(float min , float max);
	void add_available_room_filter(std::string type , int quantity , range date_);
	void remove_filter();

private:

	Hotel_Handler* hotels;
	User_Handler* users;
	User* logged_in_user;
	Filter* filters[FILTERS_SIZE];

	bool is_user_logged_in();
};

#endif