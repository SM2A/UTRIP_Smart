#include "Rating_Handler.hpp"
#include "Rating.hpp"
#include <algorithm>

#define EXPONENT 2

void Rating_Handler::delete_previous_rating(std::string writer_) {

	ratings.erase(std::remove_if(ratings.begin(),ratings.end(),
			[writer_](Rating* rating){return rating->writer == writer_;}),
		ratings.end());
}

Rating* Rating_Handler::add_rating(std::string writer_, float location_, float cleanness_, float staff_, float facilities_,
                                float value_for_money_, float overall_) {

	Rating* rating = new Rating(writer_,location_,cleanness_,staff_,facilities_,value_for_money_,overall_);
	delete_previous_rating(writer_);
	ratings.push_back(rating);
	return rating;
}

void Rating_Handler::add_rating(std::string hotel_id, Rating* rating) {

	auto item = _ratings_.find(hotel_id);
	if(item != _ratings_.end()) _ratings_.erase(item);
	_ratings_.insert(std::pair<std::string,Rating*>(hotel_id,rating));
}

float Rating_Handler::do_rated(std::string hotel_id) {

	auto item = _ratings_.find(hotel_id);
	if(item != _ratings_.end()) return item->second->overall;
	return -1;
}

