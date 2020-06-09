#ifndef LUXURY_ROOM_HPP
#define LUXURY_ROOM_HPP

#include "../Room.hpp"

class Luxury_Room : public Room{

public:

	Luxury_Room(int id_) : Room(id_){}
	std::string get_id(){ return "l"+std::to_string(id);}

};

#endif