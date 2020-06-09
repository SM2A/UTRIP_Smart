#include "Room.hpp"

Room::Room(int id_) : id(id_) {

	this->reserve_date_.start.set_day(NOT_RESERVED);
	this->reserve_date_.end.set_day(NOT_RESERVED);
}

bool Room::is_available(range request_date) {

	return !Date().have_interference(reserve_date_,request_date);
}

void Room::reserve(range _reserve_date_) {

	reserve_date_.start = _reserve_date_.start;
	reserve_date_.end = _reserve_date_.end;
}

void Room::cancel_reserve() {

	reserve_date_.start.set_day(NOT_RESERVED);
	reserve_date_.end.set_day(NOT_RESERVED);
}