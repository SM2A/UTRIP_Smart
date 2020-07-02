#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>

class Not_Found : public std::exception{
public:
	virtual const char* what() const throw(){ return "Not Found";}
};

class Bad_Request : public std::exception{
public:
	virtual const char* what() const throw(){ return "Bad Request";}
};

class Permission_Denied : public std::exception{
public:
	virtual const char* what() const throw(){ return "Permission Denied";}
};

class Empty : public std::exception{
public:
	virtual const char* what() const throw(){ return "Empty";}
};

class Not_Enough_Credit : public std::exception{
public:
	virtual const char* what() const throw(){ return "Not Enough Credit";}
};

class Not_Enough_Room : public std::exception{
public:
	virtual const char* what() const throw(){ return "Not Enough Room";}
};

class No_Rating : public std::exception{
public:
	virtual const char* what() const throw(){ return "No Rating";}
};

class Insufficient_Ratings : public std::exception{
public:
	virtual const char* what() const throw(){ return "Insufficient Ratings";}
};

#endif