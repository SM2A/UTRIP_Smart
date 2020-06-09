#ifndef COMMENT_HANDLER_HPP
#define COMMENT_HANDLER_HPP

#include <vector>
#include "Comment.hpp"

class Comment_Handler {

public:

	Comment_Handler(){}
	void add_comment(std::string writer , std::string comment);
	void print();

private:

	std::vector<Comment*> comments;
};

#endif