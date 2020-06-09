#ifndef DELUXE_ROOM_HPP
#define DELUXE_ROOM_HPP

#include "../Room.hpp"

class Deluxe_Room : public Room{

public:

	Deluxe_Room(int id_) : Room(id_){}
	std::string get_id(){ return "d"+std::to_string(id);}

};

#endif