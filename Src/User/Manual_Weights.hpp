#ifndef MANUAL_WEIGHTS_HPP
#define MANUAL_WEIGHTS_HPP

class Hotel;
class User;
enum SORT_ORDER{ASCENDING,DESCENDING};

class Manual_Weights {

public:

	Manual_Weights(){}
	void add_manual_weight(bool active_,float location_,float cleanliness_,float staff_,
	                       float facilities_,float value_for_money_);
	void change_state(bool active_);
	void print();
	float calc_overall(Hotel* hotel,User* user);

private:

	bool active;
	float location;
	float cleanliness;
	float staff;
	float facilities;
	float value_for_money;

	bool is_in_range(float value);
	float output_value(float value);
};

bool sort_by_manual_weight(Hotel* first , Hotel* second , enum SORT_ORDER sort_order,User* user,Manual_Weights* weights);

#endif