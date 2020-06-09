#ifndef COMMENT_HPP
#define COMMENT_HPP

#include <string>

class Comment {

public:

	Comment(std::string writer_ , std::string comment_) : writer(writer_) , comment(comment_){}
	void print();

private:

	std::string comment;
	std::string writer;
};

#endif