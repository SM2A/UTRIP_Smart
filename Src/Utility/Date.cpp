#include "Date.hpp"
#include "../Room/Room.hpp"

bool Date::have_interference(range first, range second) {

	if((first.start.day==NOT_RESERVED)&&(first.end.day==NOT_RESERVED)) return false;
	if((second.start.day==NOT_RESERVED)&&(second.end.day==NOT_RESERVED)) return false;
	if ((first.start.day == second.start.day) || (first.end.day == second.end.day)) return true;
	else if ((first.start.day > second.start.day) || (first.end.day < second.end.day)) return true;
	else if ((first.start.day < second.start.day) || (first.end.day > second.end.day)) return true;
	else if ((first.start.day < second.start.day) || (first.end.day < second.end.day)) return true;
	else if ((first.start.day > second.start.day) || (first.end.day > second.end.day)) return true;
	else return false;
}

int Date::duration(range range_) { return (range_.end.day - range_.start.day)+1;}
