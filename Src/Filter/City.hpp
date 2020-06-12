#ifndef CITY_HPP
#define CITY_HPP

#include <string>
#include "Filter.hpp"
#include "../Hotel/Hotel_Handler.hpp"

class City : public Filter{

public:

	City(std::string city_) : city(city_){}
	Hotel_Handler* apply(Hotel_Handler* hotels,User* user);

private:

	std::string city;
};

#endif