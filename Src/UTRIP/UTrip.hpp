#ifndef UTRIP_HPP
#define UTRIP_HPP

#include "../Hotel/Hotel_Handler.hpp"
#include "../User/Manual_Weights.hpp"
#include "../User/User_Handler.hpp"
#include "../Filter/Filter.hpp"
#include "../User/User.hpp"

#define FILTERS_SIZE 5

class UTrip {

public:

	UTrip(std::string hotels_path,std::string ratings_path);
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
	void default_price_filter(bool state);
	void parse_sort_property(std::string property , std::string order);
	void manual_weights_state(bool active);
	void add_manual_weights(bool active,float location,float cleanliness,float staff,
			float facilities,float value_for_money);
	void show_manual_weights();
	void show_estimated_weights();

private:

	Hotel_Handler* hotels;
	User_Handler* users;
	User* logged_in_user;
	Filter* filters[FILTERS_SIZE];
	Manual_Weights* manual_weights;
	Manual_Weights* estimated;
	enum SORT_ORDER sort_order;
	enum SORT_PROPERTY sort_property;

	bool is_user_logged_in();
	void reset_sort();
	void reset_filter();
	void personal_rating();
};

#endif