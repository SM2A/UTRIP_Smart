#ifndef MANUAL_WEIGHTS_HPP
#define MANUAL_WEIGHTS_HPP

#include <string>

class Hotel;
class User;
enum SORT_ORDER{ASCENDING,DESCENDING};

class Manual_Weights {

public:

	Manual_Weights(bool active_ = false) : active(active_){}
	void add_manual_weight(bool active_,double location_,double cleanliness_,double staff_,
	                       double facilities_,double value_for_money_);
	void change_state(bool active_);
	void print();
	void print(std::string name);
	double calc_overall(Hotel* hotel,User* user);
	bool get_state(){ return active;}

private:

	bool active;
	double location;
	double cleanliness;
	double staff;
	double facilities;
	double value_for_money;

	bool is_in_range(double value);
	double output_value(double value);
};

bool sort_by_manual_weight(Hotel* first , Hotel* second , enum SORT_ORDER sort_order,User* user,Manual_Weights* weights);

#endif