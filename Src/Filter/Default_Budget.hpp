#ifndef DEFAULT_BUDGET_HPP
#define DEFAULT_BUDGET_HPP

#include "Filter.hpp"
#include "../Reserve/Reserve_Handler.hpp"

#define MIN_RESERVES 10
#define ALERT "* Results have been filtered by the default price filter."

class Default_Budget : public Filter {

public:

	Default_Budget(){this->is_on = true;}
	Hotel_Handler* apply(Hotel_Handler* hotels,User* user);
	void set_status(bool state){this->is_on=state;}

private:

	bool is_on;
	bool check_reservations(Reserve_Handler* reserves);
	double calc_standard_deviation(Reserve_Handler* reserves , double avg_price);
};

#endif