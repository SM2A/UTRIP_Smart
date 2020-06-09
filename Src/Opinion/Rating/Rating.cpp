#include "Rating.hpp"
#include "../../Utility/Error.hpp"

#define UPPER_BOUND 5
#define LOWER_BOUND 1

Rating::Rating(std::string writer_, float location_, float cleanness_, float staff_, float facilities_,
               float value_for_money_, float overall_) {

	this->writer = writer_;
	if(is_in_range(location_)) this->location = location_;
	if(is_in_range(cleanness_)) this->cleanness = cleanness_;
	if(is_in_range(staff_)) this->staff = staff_;
	if(is_in_range(facilities_)) this->facilities = facilities_;
	if(is_in_range(value_for_money_)) this->value_for_money = value_for_money_;
	if(is_in_range(overall_)) this->overall = overall_;
}

bool Rating::is_in_range(float value) {

	if (value > UPPER_BOUND) throw Bad_Request();
	if (value < LOWER_BOUND) throw Bad_Request();
	return true;
}