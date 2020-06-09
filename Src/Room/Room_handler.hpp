#ifndef ROOM_HANDLER_HPP
#define ROOM_HANDLER_HPP

#include <vector>
#include "string"
#include "Delux/Deluxe_Room.hpp"
#include "Luxury/Luxury_Room.hpp"
#include "Premium/Premium_Room.hpp"
#include "Standard/Standard_Room.hpp"

typedef std::pair<int,int> price_count;
struct rooms_data{
	price_count standard;
	price_count deluxe;
	price_count luxury;
	price_count premium;
};
typedef struct rooms_data room_data;

class Room_handler {

public:

	Room_handler(room_data data);
	std::string rooms_count();
	std::string rooms_price();

	int check_availability_s(int quantity, range date_);
	int check_availability_d(int quantity, range date_);
	int check_availability_p(int quantity, range date_);
	int check_availability_l(int quantity, range date_);

	std::vector<Room*> reserve_s(int quantity, range date_);
	std::vector<Room*> reserve_d(int quantity, range date_);
	std::vector<Room*> reserve_p(int quantity, range date_);
	std::vector<Room*> reserve_l(int quantity, range date_);

	bool have_available_rooms(std::string type ,int quantity,range date_);

private:

	std::pair<int,std::vector<Standard_Room*>> standard;
	std::pair<int,std::vector<Deluxe_Room*>> deluxe;
	std::pair<int,std::vector<Luxury_Room*>> luxury;
	std::pair<int,std::vector<Premium_Room*>> premium;

	void creat_standard_room(price_count standard_);
	void creat_deluxe_room(price_count deluxe_);
	void creat_luxury_room(price_count luxury_);
	void creat_premium_room(price_count premium_);
};

#endif