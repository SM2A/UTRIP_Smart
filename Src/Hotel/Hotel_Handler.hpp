#ifndef HOTEL_HANDLER_HPP
#define HOTEL_HANDLER_HPP

#include <string>
#include <vector>

#define FILTERS_SIZE 4
enum FILTERS{CITY,STAR,PRICE,ROOMS};

class Hotel;
class Filter;

class Hotel_Handler {

public:

	Hotel_Handler(){}
	Hotel_Handler(std::string path);
	Hotel_Handler(const Hotel_Handler* hotel_handler);
	void print(Filter* filters[FILTERS_SIZE]);
	void print(std::string id);
	Hotel* find(std::string id);
	friend class City;
	friend class Star_Range;
	friend class Average_Price;
	friend class Available_Room;

private:

	std::vector<Hotel*> read_hotel_file(std::string path);
	std::vector<Hotel*> hotels;
};

#endif