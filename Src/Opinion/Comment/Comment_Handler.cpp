#include "Comment_Handler.hpp"

void Comment_Handler::print() {

	if(comments.size() == 0) return;
	for(int i= comments.size()-1 ; i>=0 ;i--)
		comments[i]->print();
}

void Comment_Handler::add_comment(std::string writer , std::string comment) {

	Comment* comment_ = new Comment(writer,comment);
	comments.push_back(comment_);
}