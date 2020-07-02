#include "Default_Budget.hpp"
#include "../User/User.hpp"
#include "../Hotel/Hotel_Handler.hpp"
#include "../Hotel/Hotel.hpp"
#include <cmath>
#include <iostream>

Hotel_Handler *Default_Budget::apply(Hotel_Handler *hotels, User *user) {

	if(!is_on||!check_reservations(user->get_reserves())) return hotels;

	Hotel_Handler* filter_hotels = new Hotel_Handler();
	double reservations_avg = user->get_reserves()->calc_avg_price();
	double limit = (double)2 * calc_standard_deviation(user->get_reserves(),reservations_avg);

	for(Hotel* hotel : hotels->hotels)
		if(fabs(reservations_avg - hotel->get_avg_price()) <= limit)
			filter_hotels->hotels.push_back(hotel);

	if(filter_hotels->hotels.size()!=0) std::cout<<ALERT<<std::endl;
	return filter_hotels;
}

bool Default_Budget::check_reservations(Reserve_Handler *reserves) {

	return MIN_RESERVES<=reserves->number_of_reserves();
}

double Default_Budget::calc_standard_deviation(Reserve_Handler* reserves , double avg_price) {

	int sample_size = reserves->total_reserved_rooms()-1;
	double sigma = reserves->calc_sigma(avg_price);
	return sqrt(sigma/(double)sample_size);
}
