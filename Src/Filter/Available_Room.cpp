#include "Available_Room.hpp"
#include "../Hotel/Hotel.hpp"
#include "../Hotel/Hotel_Handler.hpp"

Hotel_Handler *Available_Room::apply(Hotel_Handler *hotels,User* user) {

	Hotel_Handler* filter_hotels = new Hotel_Handler();

	for(Hotel* hotel : hotels->hotels)
		if(hotel->available_rooms(room_type,quantity,filter_date))
			filter_hotels->hotels.push_back(hotel);

	return filter_hotels;
}