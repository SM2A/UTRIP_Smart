#include "Hotel_Handler.hpp"
#include "../Utility/Error.hpp"
#include "../Filter/Filter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Hotel.hpp"

#define COLUMN_DELIMITER ','
#define EMPTY 0

using namespace std;

Hotel_Handler::Hotel_Handler(string hotels_path,string ratings_path) {

	this->hotels = read_hotel_file(hotels_path);
	add_avg_rating(ratings_path);
}

Hotel_Handler::Hotel_Handler(const Hotel_Handler* hotel_handler){

	for(Hotel* hotel : hotel_handler->hotels) {
		this->hotels.push_back(hotel);
	}
}

vector<Hotel*> Hotel_Handler::read_hotel_file(string path) {

	vector<Hotel*> hotels_;

	ifstream file(path);
	string first_row , row;
	getline(file,first_row);

	while (getline(file,row)){
		stringstream stream(row);
		string id,name,overview,facilities,city,image_url,star,longitude,latitude,rooms_data;
		geographical_coordinates geo_coordinates;
		room_data rooms;
		getline(stream,id,COLUMN_DELIMITER);
		getline(stream,name,COLUMN_DELIMITER);
		getline(stream,star,COLUMN_DELIMITER);
		getline(stream,overview,COLUMN_DELIMITER);
		getline(stream,facilities,COLUMN_DELIMITER);
		getline(stream,city,COLUMN_DELIMITER);
		getline(stream,latitude,COLUMN_DELIMITER);
		getline(stream,longitude,COLUMN_DELIMITER);
		getline(stream,image_url,COLUMN_DELIMITER);
		geo_coordinates.latitude = stod(latitude);
		geo_coordinates.longitude = stod(longitude);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.standard.second = stoi(rooms_data);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.deluxe.second = stoi(rooms_data);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.luxury.second = stoi(rooms_data);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.premium.second = stoi(rooms_data);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.standard.first = stoi(rooms_data);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.deluxe.first = stoi(rooms_data);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.luxury.first = stoi(rooms_data);
		getline(stream,rooms_data,COLUMN_DELIMITER);
		rooms.premium.first = stoi(rooms_data);
		Hotel* _hotel = new Hotel(id,name,stoi(star),overview,facilities,city,geo_coordinates,image_url,rooms);
		hotels_.push_back(_hotel);
	}
	sort(hotels_.begin(),hotels_.end(),sort_by_name);
	return hotels_;
}

void Hotel_Handler::print(Filter* filters[FILTERS_SIZE]) {

	Hotel_Handler* filtered_hotels = this;

	if(filters[CITY] != nullptr) filtered_hotels = filters[CITY]->apply(filtered_hotels);
	if(filters[STAR] != nullptr) filtered_hotels = filters[STAR]->apply(filtered_hotels);
	if(filters[PRICE] != nullptr) filtered_hotels = filters[PRICE]->apply(filtered_hotels);
	if(filters[ROOMS] != nullptr) filtered_hotels = filters[ROOMS]->apply(filtered_hotels);

	if(filtered_hotels->hotels.size() == EMPTY) throw Empty();
	for(Hotel* hotel : filtered_hotels->hotels)
		hotel->print_summary();
}

void Hotel_Handler::print(std::string id) {

	find(id)->print_detail();
}

Hotel *Hotel_Handler::find(std::string id) {

	auto hotel = find_if(hotels.begin(),hotels.end(),[=](Hotel* hotel_){ return id==hotel_->id;});
	if(hotel!=hotels.end()) return *hotel;
	throw Not_Found();
}

void Hotel_Handler::add_avg_rating(std::string path){

	ifstream file(path);
	string first_row , row;
	getline(file,first_row);

	while (getline(file,row)){
		stringstream stream(row);
		string hotel_id,location,cleanliness,staff,facilities,value_for_money,overall;
		getline(stream,hotel_id,COLUMN_DELIMITER);
		getline(stream,location,COLUMN_DELIMITER);
		getline(stream,cleanliness,COLUMN_DELIMITER);
		getline(stream,staff,COLUMN_DELIMITER);
		getline(stream,facilities,COLUMN_DELIMITER);
		getline(stream,value_for_money,COLUMN_DELIMITER);
		getline(stream,overall,COLUMN_DELIMITER);
		Rating* rating = new Rating(stof(location),stof(cleanliness),stof(staff),
				stof(facilities),stof(value_for_money),stof(overall));
		find(hotel_id)->add_avg_rating(rating);
	}
}