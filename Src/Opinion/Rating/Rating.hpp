#ifndef RATING_HPP
#define RATING_HPP

#include <string>

class Rating {

public:

	Rating(std::string writer_ , double location_,double cleanness_,double staff_,
			double facilities_,double value_for_money_,double overall_);
	Rating(double location_,double cleanness_,double staff_,
	       double facilities_,double value_for_money_,double overall_);
	double calc_overall(double location_,double cleanness_,double staff_,
	       double facilities_,double value_for_money_);
	friend class Rating_Handler;
	void print();

private:

	std::string writer;
	double location;
	double cleanness;
	double staff;
	double facilities;
	double value_for_money;
	double overall;

	bool is_in_range(double value);
};

#endif