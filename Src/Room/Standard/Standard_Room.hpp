#ifndef STANDARD_ROOM_HPP
#define STANDARD_ROOM_HPP

#include "../Room.hpp"

class Standard_Room : public Room {

public:

	Standard_Room(int id_) : Room(id_){}
	std::string get_id(){ return "s"+std::to_string(id);}

};

#endif