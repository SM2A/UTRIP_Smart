#ifndef HOTEL_HPP
#define HOTEL_HPP

#include <string>
#include "../Room/Room_handler.hpp"
#include "Hotel_Handler.hpp"
#include "../Opinion/Comment/Comment_Handler.hpp"
#include "../Opinion/Rating/Rating_Handler.hpp"
#include "../Opinion/Rating/Rating.hpp"

struct coordinates{
	double longitude;
	double latitude;
};
typedef struct coordinates geographical_coordinates;

class Hotel {

public:

	Hotel(std::string id_,std::string name_,int star_,std::string overview_,std::string facilities_,std::string city_,
			geographical_coordinates location_,std::string image_url_,room_data data);

	void print_summary();
	void print_detail();

	int reserve_cost(std::string room_type , int quantity , range date_);
	std::vector<Room*> reserve(std::string room_type , int quantity , range date_);
	std::string get_id(){ return id;};
	float get_avg_price(){ return average_price;}
	void add_comment(std::string writer , std::string comment);
	void show_comments();
	Rating* rate(std::string writer,double location,double cleanness,double staff,double facilities,
			double value_for_money,double overall);
	void show_average_rating();
	void add_avg_rating(Rating* rating);
	double calc_overall(double location_,double cleanness_,double staff_,double facilities_,double value_for_money_);

	friend class City;
	friend class Star_Range;
	friend class Average_Price;
	friend class Available_Room;
	friend class Default_Budget;
	friend Hotel* Hotel_Handler::find(std::string id);
	friend bool sort_by_id(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_name(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_star(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_city(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_s_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_d_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_l_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_p_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
	friend bool sort_by_avg_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);

private:

	std::string id;
	std::string name;
	int star;
	std::string overview;
	std::string facilities;
	std::string city;
	geographical_coordinates location;
	std::string image_url;
	Room_handler* rooms;
	int total_rooms_count;
	float average_price;
	Comment_Handler* comments;
	Rating_Handler* ratings;
	Rating* avg_rating;
	room_data rooms_data;

	bool available_rooms(std::string type,int quantity,range date_);
	float calculate_average_price(room_data data);

};

bool sort_by_id(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_name(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_star(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_city(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_s_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_d_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_l_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_p_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);
bool sort_by_avg_price(Hotel* first , Hotel* second , enum SORT_ORDER sort_order);

#endif