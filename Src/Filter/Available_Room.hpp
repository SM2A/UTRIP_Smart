#ifndef AVAILABLE_ROOM_HPP
#define AVAILABLE_ROOM_HPP

#include <string>
#include "Filter.hpp"
#include "../Utility/Date.hpp"

class Available_Room : public Filter{

public:

	Available_Room(std::string room_type_ , int quantity , range filter_date_)
		: room_type(room_type_) , quantity(quantity) , filter_date(filter_date_){}
	Hotel_Handler* apply(Hotel_Handler* hotels,User* user);

private:

	std::string room_type;
	int quantity;
	range filter_date;
};

#endif