#ifndef STAR_RANGE_HPP
#define STAR_RANGE_HPP

#include "Filter.hpp"

class Star_Range : public Filter {

public:

	Star_Range(int min_,int max_);
	Hotel_Handler* apply(Hotel_Handler* hotels,User* user);

private:

	int min;
	int max;
};

#endif