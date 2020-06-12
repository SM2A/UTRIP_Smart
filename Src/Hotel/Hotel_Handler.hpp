#ifndef HOTEL_HANDLER_HPP
#define HOTEL_HANDLER_HPP

#include <string>
#include <vector>
#include <map>

#define FILTERS_SIZE 5

enum FILTERS{CITY,STAR,PRICE,ROOMS,DEFAULT_BUDGET};
enum SORT_PROPERTY{ID,NAME,STAR_RATING,CITY_,S_PRICE,D_PRICE,L_PRICE,P_PRICE,AVG_PRICE};
enum SORT_ORDER{ASCENDING,DESCENDING};

class Hotel;
class Filter;
class User;

class Hotel_Handler {

public:

	Hotel_Handler(){}
	Hotel_Handler(std::string hotels_path,std::string ratings_path);
	Hotel_Handler(const Hotel_Handler* hotel_handler);
	void print(Filter* filters[FILTERS_SIZE],User* user,enum SORT_ORDER sort_order,
			enum SORT_PROPERTY sort_property);
	void print(std::string id);
	Hotel* find(std::string id);
	void sort_(enum SORT_ORDER sort_order,enum SORT_PROPERTY sort_property);

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