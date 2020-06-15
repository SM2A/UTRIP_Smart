#ifndef RATING_HANDLER_HPP
#define RATING_HANDLER_HPP

#include <vector>
#include <string>
#include <map>
#include "Rating.hpp"


class Rating;

class Rating_Handler {

public:

	Rating_Handler(){}
	void add_rating(std::string hotel_id , Rating* rating);
	Rating* add_rating(std::string writer_ , float location_,float cleanness_,float staff_,
	                float facilities_,float value_for_money_,float overall_);
	float do_rated(std::string hotel_id);

private:

	std::vector<Rating*> ratings;
	std::map<std::string,Rating*> _ratings_;
	void delete_previous_rating(std::string writer_);
};

#endif