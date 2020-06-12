#include "Star_Range.hpp"
#include "../Hotel/Hotel.hpp"
#include "../Hotel/Hotel_Handler.hpp"
#include "../Utility/Error.hpp"

#define LOWER_BOUND 0

Star_Range::Star_Range(int min_, int max_) {

	if(min_ > max_) throw Bad_Request();
	if(max_ < LOWER_BOUND) throw Bad_Request();
	if(min_ < LOWER_BOUND) throw Bad_Request();

	this->min = min_;
	this->max = max_;
}

Hotel_Handler* Star_Range::apply(Hotel_Handler *hotels,User* user) {

	Hotel_Handler* filter_hotels = new Hotel_Handler();
	for(Hotel* hotel : hotels->hotels)
		if((hotel->star >= min)&&(hotel->star <= max))
			filter_hotels->hotels.push_back(hotel);

	return filter_hotels;
}