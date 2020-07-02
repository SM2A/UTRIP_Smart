#include "Rating.hpp"
#include "../../Utility/Error.hpp"
#include <iomanip>
#include <iostream>

#define EXPONENT 2
#define UPPER_BOUND 5
#define LOWER_BOUND 1
#define NO_WRITER "__NULL__"

Rating::Rating(std::string writer_, double location_, double cleanness_, double staff_, double facilities_,
               double value_for_money_, double overall_) {

	this->writer = writer_;
	if(is_in_range(location_)) this->location = location_;
	if(is_in_range(cleanness_)) this->cleanness = cleanness_;
	if(is_in_range(staff_)) this->staff = staff_;
	if(is_in_range(facilities_)) this->facilities = facilities_;
	if(is_in_range(value_for_money_)) this->value_for_money = value_for_money_;
	if(is_in_range(overall_)) this->overall = overall_;
}

Rating::Rating(double location_,double cleanness_,double staff_,double facilities_,double value_for_money_,double overall_){

	this->writer = NO_WRITER;
	if(is_in_range(location_)) this->location = location_;
	if(is_in_range(cleanness_)) this->cleanness = cleanness_;
	if(is_in_range(staff_)) this->staff = staff_;
	if(is_in_range(facilities_)) this->facilities = facilities_;
	if(is_in_range(value_for_money_)) this->value_for_money = value_for_money_;
	if(is_in_range(overall_)) this->overall = overall_;
}

bool Rating::is_in_range(double value) {

	if (value > UPPER_BOUND) throw Bad_Request();
	if (value < LOWER_BOUND) throw Bad_Request();
	return true;
}

void Rating::print() {

	std::cout<<std::fixed<<std::setprecision(EXPONENT);
	std::cout<<"location: "<<this->location<<std::endl;
	std::cout<<"cleanliness: "<<this->cleanness<<std::endl;
	std::cout<<"staff: "<<this->staff<<std::endl;
	std::cout<<"facilities: "<<this->facilities<<std::endl;
	std::cout<<"value for money: "<<this->value_for_money<<std::endl;
	std::cout<<"overall rating: "<<this->overall<<std::endl;
}

double Rating::calc_overall(double location_,double cleanness_,double staff_,
                   double facilities_,double value_for_money_){
	double sum = 0;
	sum+=(this->location*location_);
	sum+=(this->cleanness*cleanness_);
	sum+=(this->staff*staff_);
	sum+=(this->facilities*facilities_);
	sum+=(this->value_for_money*value_for_money_);
	return sum;
}