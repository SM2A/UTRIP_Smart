#include "Rating_Handler.hpp"
#include "Rating.hpp"
#include "../../Utility/Error.hpp"
#include <iostream>
#include <iomanip>

#define EXPONENT 2

void Rating_Handler::delete_previous_rating(std::string writer_) {

	for (int i = 0; i < ratings.size() ; ++i) {
		if(ratings[i]->writer == writer_) ratings.erase(ratings.begin()+i);
	}
}

void Rating_Handler::add_rating(std::string writer_, float location_, float cleanness_, float staff_, float facilities_,
                                float value_for_money_, float overall_) {

	Rating* rating = new Rating(writer_,location_,cleanness_,staff_,facilities_,value_for_money_,overall_);
	delete_previous_rating(writer_);
	ratings.push_back(rating);
}

void Rating_Handler::print_average() {

	if(ratings.size() == 0) throw No_Rating();
	int ratings_count = ratings.size();
	float location_sum=0,cleanness_sum=0,staff_sum=0,facilities_sum=0,value_for_money_sum=0,overall_sum=0;
	for(Rating* rating : ratings){
		location_sum+=rating->location;
		cleanness_sum+=rating->cleanness;
		staff_sum+=rating->staff;
		facilities_sum+=rating->facilities;
		value_for_money_sum+=rating->value_for_money;
		overall_sum+=rating->overall;
	}
	std::cout<<std::fixed<<std::setprecision(EXPONENT);
	std::cout<<"location: "<<location_sum/(float)ratings_count<<std::endl;
	std::cout<<"cleanliness: "<<cleanness_sum/(float)ratings_count<<std::endl;
	std::cout<<"staff: "<<staff_sum/(float)ratings_count<<std::endl;
	std::cout<<"facilities: "<<facilities_sum/(float)ratings_count<<std::endl;
	std::cout<<"value for money: "<<value_for_money_sum/(float)ratings_count<<std::endl;
	std::cout<<"overall rating: "<<overall_sum/(float)ratings_count<<std::endl;
}