#ifndef USER_HANDLER_HPP
#define USER_HANDLER_HPP

#include <string>
#include <vector>

class User;

class User_Handler {

public:

	User_Handler(){}
	User* creat_user(std::string user_name , std::string password , std::string e_mail);
	User* find(std::string user_name);
	User* login(std::string user_name , std::string password );

private:

	std::vector<User*> users;
};

#endif