#include "../../User/Manual_Weights.hpp"
#include "Rating_Handler.hpp"
#include "Rating.hpp"
#include <algorithm>
#include <cmath>

#define EXPONENT 2
#define UPPER_BOUND 5
#define LOWER_BOUND 1
#define TYPE_COUNT 5
#define ESTIMATE_COUNT 1000
#define ALPHA 1
#define EPSILONE 0.0001

enum TYPE_NAME{LOCATION,CLEANLINESS,STAFF,FACILITIES,VALUE_FOR_MONEY};

void Rating_Handler::delete_previous_rating(std::string writer_) {

	ratings.erase(std::remove_if(ratings.begin(),ratings.end(),
			[writer_](Rating* rating){return rating->writer == writer_;}),
		ratings.end());
}

Rating* Rating_Handler::add_rating(std::string writer_, double location_, double cleanness_, double staff_, double facilities_,
                                double value_for_money_, double overall_) {

	Rating* rating = new Rating(writer_,location_,cleanness_,staff_,facilities_,value_for_money_,overall_);
	delete_previous_rating(writer_);
	ratings.push_back(rating);
	return rating;
}

void Rating_Handler::add_rating(std::string hotel_id, Rating* rating) {

	auto item = _ratings_.find(hotel_id);
	if(item != _ratings_.end()) _ratings_.erase(item);
	_ratings_.insert(std::pair<std::string,Rating*>(hotel_id,rating));
}

double Rating_Handler::do_rated(std::string hotel_id) {

	auto item = _ratings_.find(hotel_id);
	if(item != _ratings_.end()) return item->second->overall;
	return -1;
}

Manual_Weights *Rating_Handler::calc_estimated_weight() {

	double estimated_weight[TYPE_COUNT] , d[TYPE_COUNT];

	for(double& i : estimated_weight) i = rand()%UPPER_BOUND + LOWER_BOUND;

	for (int i = 0; i < ESTIMATE_COUNT ; ++i) {

		for (double& j : d) j = 0;
		auto itr = _ratings_.begin();
		for (int k = 0; k < _ratings_.size() ; ++k) {
			for (int m = 0; m < TYPE_COUNT; ++m)
				d[m] += partial_derivative(itr->second, estimated_weight, m);
			itr++;
		}

		for (int l = 0; l < TYPE_COUNT ; ++l) {
			estimated_weight[l] -= (ALPHA * d[l]);
			if(estimated_weight[l] > UPPER_BOUND) estimated_weight[l] = UPPER_BOUND;
			if(estimated_weight[l] < LOWER_BOUND) estimated_weight[l] = LOWER_BOUND;
		}
	}

	Manual_Weights* estimated = new Manual_Weights(true);
	estimated->add_manual_weight(true,estimated_weight[LOCATION],estimated_weight[CLEANLINESS],estimated_weight[STAFF],
			estimated_weight[FACILITIES],estimated_weight[VALUE_FOR_MONEY]);
	return estimated;
}

double Rating_Handler::partial_derivative(Rating *rating, double estimated_weight[], int index) {

	double new_estimated_weight[TYPE_COUNT];
	for (int i = 0; i < TYPE_COUNT ; ++i) new_estimated_weight[i] = estimated_weight[i];
	new_estimated_weight[index] += EPSILONE;

	return ((error_function(rating,new_estimated_weight) - error_function(rating,estimated_weight)) / EPSILONE);
}

double Rating_Handler::error_function(Rating *rating, double estimated_weight[]) {

	return pow((calc_estimated_overall(rating,estimated_weight) - rating->overall) ,2);
}

double Rating_Handler::calc_estimated_overall(Rating *rating, double estimated_weight[]) {

	double sum = rating->calc_overall(estimated_weight[LOCATION],estimated_weight[CLEANLINESS],estimated_weight[STAFF],
			estimated_weight[FACILITIES],estimated_weight[VALUE_FOR_MONEY]);
	double weight_sum = 0;
	for (int i = 0; i < TYPE_COUNT ; ++i) weight_sum += estimated_weight[i];
	return (sum / weight_sum);
}
