#ifndef RATING_HANDLER_HPP
#define RATING_HANDLER_HPP

#include <vector>
#include <string>
#include <map>
#include "Rating.hpp"


class Rating;
class Manual_Weights;

class Rating_Handler {

public:

	Rating_Handler(){}
	void add_rating(std::string hotel_id , Rating* rating);
	Rating* add_rating(std::string writer_ , double location_,double cleanness_,double staff_,
	                double facilities_,double value_for_money_,double overall_);
	double do_rated(std::string hotel_id);
	int get_ratings_count(){ return _ratings_.size();}
	Manual_Weights* calc_estimated_weight();

private:

	std::vector<Rating*> ratings;
	std::map<std::string,Rating*> _ratings_;
	void delete_previous_rating(std::string writer_);

	double partial_derivative(Rating* rating , double estimated_weight[] , int index);
	double error_function(Rating* rating , double estimated_weight[]);
	double calc_estimated_overall(Rating* rating , double estimated_weight[]);
};

#endif