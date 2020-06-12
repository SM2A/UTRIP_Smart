#include "Average_Price.hpp"
#include "../Hotel/Hotel.hpp"
#include "../Hotel/Hotel_Handler.hpp"
#include "../Utility/Error.hpp"

#define LOWER_BOUND 0

Average_Price::Average_Price(float min_, float max_) {

	if(min_ > max_) throw Bad_Request();
	if(max_ < LOWER_BOUND) throw Bad_Request();
	if(min_ < LOWER_BOUND) throw Bad_Request();

	this->min = min_;
	this->max = max_;
}

Hotel_Handler *Average_Price::apply(Hotel_Handler *hotels,User* user) {

	Hotel_Handler* filter_hotels = new Hotel_Handler();
	for(Hotel* hotel : hotels->hotels)
		if((hotel->average_price >= min)&&(hotel->average_price <= max))
			filter_hotels->hotels.push_back(hotel);

	return filter_hotels;
}