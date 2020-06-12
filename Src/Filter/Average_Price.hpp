#ifndef AVERAGE_PRICE_HPP
#define AVERAGE_PRICE_HPP

#include "Filter.hpp"

class Average_Price : public Filter {

public:

	Average_Price(float min_, float max_);
	Hotel_Handler* apply(Hotel_Handler* hotels,User* user);

private:

	float min;
	float max;
};

#endif