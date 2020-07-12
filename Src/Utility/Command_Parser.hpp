#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <string>
#include <map>
#include "../UTRIP/UTrip.hpp"

#define METHOD_COUNT 3

typedef std::pair<std::string,std::string> argument_value;
typedef std::map<std::string,std::string> arguments;
enum method_index {GET,POST,DELETE};

class Command_Parser {

public:

	Command_Parser(std::string hotels_path,std::string ratings_path);
	void get_command(std::string command);

private:

	UTrip* utrip;
	const std::string method[METHOD_COUNT] = {"GET","POST","DELETE"};

	void signup(const arguments& args);
	void login(const arguments& args);
	void logout(const arguments &args);
	void add_credit(const arguments &args);
	void show_wallet_history(const arguments &args);
	void show_hotels(const arguments &args);
	void add_filter(const arguments &args);
	void remove_filters(const arguments &args);
	void reserve(const arguments &args);
	void show_reserves(const arguments &args);
	void cancel_reserve(const arguments& args);
	void show_hotel_ratting(const arguments &args);
	void show_hotel_comments(const arguments &args);
	void add_comment(const arguments &args);
	void add_ratting(const arguments &args);
	void default_price_filter(const arguments &args);
	void sort_selection(const arguments &args);
	void manual_weights(const arguments &args);
	void show_manual_weights(const arguments &args);
	void show_estimated_weights(const arguments &args);

	void get_parser(std::string command_ ,const arguments& args);
	void post_parser(std::string command_ ,const arguments& args);
	void delete_parser(std::string command_ ,const arguments& args);
	void method_check(std::string method_);
	std::string find_arg_val(const arguments& args,std::string arg);
};

#endif