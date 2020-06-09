#ifndef HOTEL_HPP
#define HOTEL_HPP

#include <string>
#include "../Room/Room_handler.hpp"
#include "Hotel_Handler.hpp"
#include "../Opinion/Comment/Comment_Handler.hpp"
#include "../Opinion/Rating/Rating_Handler.hpp"

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
	friend bool sort_by_name(Hotel* one , Hotel* two);
	friend Hotel* Hotel_Handler::find(std::string id);
	int reserve_cost(std::string room_type , int quantity , range date_);
	std::vector<Room*> reserve(std::string room_type , int quantity , range date_);
	std::string get_id(){ return id;};
	void add_comment(std::string writer , std::string comment);
	void show_comments();
	void rate(std::string writer,float location,float cleanness,float staff,float facilities,
			float value_for_money,float overall);
	void show_average_rating();
	friend class City;
	friend class Star_Range;
	friend class Average_Price;
	friend class Available_Room;

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

	bool available_rooms(std::string type,int quantity,range date_);
	float calculate_average_price(room_data data);

};

bool sort_by_name(Hotel* one , Hotel* two);

#endif