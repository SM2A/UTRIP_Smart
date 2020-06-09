#ifndef RESERVE_HPP
#define RESERVE_HPP

#include <string>
#include "Reserve_Handler.hpp"
#include "../Utility/Date.hpp"
#include "../Room/Room.hpp"

class Reserve {

public:

	Reserve(std::string hotel_id , std::string room_type , int quantity , int cost , range reservation_date_
				, std::vector<Room*> rooms_ ,int id_,bool cancelled = false);

	void print();
	int cancel();

private:

	int id;
	std::string hotel_id;
	std::string room_type;
	int quantity;
	int cost;
	range reservation_date;
	std::vector<Room*> rooms;
	bool cancelled;
};

#endif