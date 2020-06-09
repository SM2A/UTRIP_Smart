#ifndef RATING_HPP
#define RATING_HPP

#include <string>

class Rating {

public:

	Rating(std::string writer_ , float location_,float cleanness_,float staff_,
			float facilities_,float value_for_money_,float overall_);
	friend class Rating_Handler;

private:

	std::string writer;
	float location;
	float cleanness;
	float staff;
	float facilities;
	float value_for_money;
	float overall;

	bool is_in_range(float value);
};

#endif