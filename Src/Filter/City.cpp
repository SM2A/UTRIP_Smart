#include "City.hpp"
#include "../Hotel/Hotel.hpp"
#include "../Hotel/Hotel_Handler.hpp"

Hotel_Handler *City::apply(Hotel_Handler *hotels,User* user) {

	Hotel_Handler* filter_hotels = new Hotel_Handler();
	for(Hotel* hotel : hotels->hotels)
		if(hotel->city == city)
			filter_hotels->hotels.push_back(hotel);

	return filter_hotels;
}