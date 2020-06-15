#include "Manual_Weights.hpp"
#include "../Utility/Error.hpp"
#include "../Hotel/Hotel_Handler.hpp"
#include "../Hotel/Hotel.hpp"
#include "User.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

#define UPPER_BOUND 5
#define LOWER_BOUND 1
#define SUCCESS "OK"
#define EXPONENT 2

bool Manual_Weights::is_in_range(float value) {

	if (value > UPPER_BOUND) throw Bad_Request();
	if (value < LOWER_BOUND) throw Bad_Request();
	return true;
}

void Manual_Weights::change_state(bool active_) {

	this->active = active_;
	std::cout<<SUCCESS<<std::endl;
}

void Manual_Weights::print() {

	if(!active) std::cout<<"active false"<<std::endl;
	else{
		std::cout<<std::fixed<<std::setprecision(EXPONENT)
		         <<"active true"
		         <<" location "<<output_value(location)
		         <<" cleanliness "<<output_value(cleanliness)
		         <<" staff "<<output_value(staff)
		         <<" facilities "<<output_value(facilities)
		         <<" value_for_money "<<output_value(value_for_money)
		         <<std::endl;
	}
}

void
Manual_Weights::add_manual_weight(bool active_, float location_, float cleanliness_, float staff_, float facilities_,
                                  float value_for_money_) {

	this->active = active_;
	if(is_in_range(location_)) this->location = location_;
	if(is_in_range(cleanliness_)) this->cleanliness = cleanliness_;
	if(is_in_range(staff_)) this->staff = staff_;
	if(is_in_range(facilities_)) this->facilities = facilities_;
	if(is_in_range(value_for_money_)) this->value_for_money = value_for_money_;
}

float Manual_Weights::output_value(float value) {

	value*=100;
	return trunc(value)/100;
}

float Manual_Weights::calc_overall(Hotel *hotel, User* user) {

	if(user->do_rated(hotel) != -1) return user->do_rated(hotel);
	float weigh_sum = location+cleanliness+staff+facilities+value_for_money;
	return hotel->calc_overall(location,cleanliness,staff,facilities,value_for_money)/weigh_sum;
}

bool sort_by_manual_weight(Hotel* first , Hotel* second , enum SORT_ORDER sort_order,User* user,Manual_Weights* weights){

	float first_ = weights->calc_overall(first,user);
	float second_ = weights->calc_overall(second,user);
	if(first_ == second_) return sort_by_id(first,second,ASCENDING);

	if(sort_order == DESCENDING) return first_ > second_;
	else return second_ > first_;
}