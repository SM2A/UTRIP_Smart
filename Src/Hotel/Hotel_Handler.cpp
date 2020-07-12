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
	return hotels_;
}

void Hotel_Handler::print(Filter* filters[FILTERS_SIZE],User* user,enum SORT_ORDER sort_order,
		enum SORT_PROPERTY sort_property,Manual_Weights* manual_weights,Manual_Weights* estimated) {

	Hotel_Handler* filtered_hotels = this;
	if(filters[CITY] != nullptr) filtered_hotels = filters[CITY]->apply(filtered_hotels,user);
	if(filters[STAR] != nullptr) filtered_hotels = filters[STAR]->apply(filtered_hotels,user);
	if(filters[PRICE] != nullptr) filtered_hotels = filters[PRICE]->apply(filtered_hotels,user);
	if(filters[ROOMS] != nullptr) filtered_hotels = filters[ROOMS]->apply(filtered_hotels,user);
	if(filters[PRICE] == nullptr) filtered_hotels = filters[DEFAULT_BUDGET]->apply(filtered_hotels,user);

	if(filtered_hotels->hotels.size() == EMPTY) throw Empty();
	sort_(filtered_hotels,sort_order,sort_property,manual_weights,estimated,user);
	for(Hotel* hotel : filtered_hotels->hotels) hotel->print_summary();
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
		Rating* rating = new Rating(stod(location),stod(cleanliness),stod(staff),
				stod(facilities),stod(value_for_money),stod(overall));
		find(hotel_id)->add_avg_rating(rating);
	}
}

void Hotel_Handler::sort_(Hotel_Handler *filtered_hotels, enum SORT_ORDER sort_order,
		enum SORT_PROPERTY sort_property,Manual_Weights* manual_weights,Manual_Weights* estimated,User* user) {

	if (sort_property == ID)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_id(first, second, sort_order); });
	else if (sort_property == NAME)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_name(first, second, sort_order); });
	else if (sort_property == STAR_RATING)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_star(first, second, sort_order); });
	else if (sort_property == CITY_)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_city(first, second, sort_order); });
	else if (sort_property == S_PRICE)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_s_price(first, second, sort_order); });
	else if (sort_property == D_PRICE)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_d_price(first, second, sort_order); });
	else if (sort_property == L_PRICE)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_l_price(first, second, sort_order); });
	else if (sort_property == P_PRICE)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_p_price(first, second, sort_order); });
	else if (sort_property == AVG_PRICE)
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order](Hotel *first, Hotel *second) { return sort_by_avg_price(first, second, sort_order); });
	else if (sort_property == RATING_PERSONAL) {
		Manual_Weights* weights = manual_weights;
		if(!manual_weights->get_state()) weights = estimated;
		sort(filtered_hotels->hotels.begin(), filtered_hotels->hotels.end(),
		     [&, sort_order, manual_weights, user](Hotel *first, Hotel *second) {
			     return sort_by_manual_weight(first, second, sort_order, user,weights);});
	}
}
