#ifndef PREMIUM_ROOM_HPP
#define PREMIUM_ROOM_HPP

#include "../Room.hpp"

class Premium_Room : public Room{

public:

	Premium_Room(int id_) : Room(id_){}
	std::string get_id(){ return "p"+std::to_string(id);}
};

#endif