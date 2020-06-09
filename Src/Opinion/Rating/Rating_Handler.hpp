#ifndef RATING_HANDLER_HPP
#define RATING_HANDLER_HPP

#include <vector>
#include <string>

class Rating;

class Rating_Handler {

public:

	Rating_Handler(){}
	void add_rating(std::string writer_ , float location_,float cleanness_,float staff_,
	                float facilities_,float value_for_money_,float overall_);
	void print_average();

private:

	std::vector<Rating*> ratings;
	void delete_previous_rating(std::string writer_);
};

#endif