#ifndef DATE_HPP
#define DATE_HPP

typedef struct r_date range;

class Date {

public:

	Date(){}
	void set_day(int day_) {this->day = day_;}
	int get_day(){ return day;}
	bool have_interference(range first , range second);
	int duration(range range_);

private:

    int day;

};

struct r_date{
	Date start;
	Date end;
};

#endif