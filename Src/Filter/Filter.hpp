#ifndef FILTER_HPP
#define FILTER_HPP

class Hotel_Handler;
class User;

class Filter {

public:

	virtual Hotel_Handler* apply(Hotel_Handler* hotels,User* user) = 0;
	virtual void set_status(bool state){}
};

#endif