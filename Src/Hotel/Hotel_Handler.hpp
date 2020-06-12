#ifndef HOTEL_HANDLER_HPP
#define HOTEL_HANDLER_HPP

#include <string>
#include <vector>

#define FILTERS_SIZE 5
enum FILTERS{CITY,STAR,PRICE,ROOMS,DEFAULT_BUDGET};

class Hotel;
class Filter;
class User;

class Hotel_Handler {

public:

	Hotel_Handler(){}
	Hotel_Handler(std::string hotels_path,std::string ratings_path);
	Hotel_Handler(const Hotel_Handler* hotel_handler);
	void print(Filter* filters[FILTERS_SIZE],User* user);
	void print(std::string id);
	Hotel* find(std::string id);
	friend class City;
	friend class Star_Range;
	friend class Average_Price;
	friend class Available_Room;
	friend class Default_Budget;

private:

	std::vector<Hotel*> read_hotel_file(std::string path);
	void add_avg_rating(std::string path);
	std::vector<Hotel*> hotels;
};

#endif