#ifndef PARSER_H
#define PARSER_H
#include<iostream>
#include<string>
class Parser{
private:
	std::string expr;
	int pos;
	bool match(std::string cmp);
	double matchE();
	double matche();
	double matchT();
	double matcht();
	double matchN();
	double matchn();
	double matchM();
public:
	Parser();
	std::string calculate(std::string s);
};
#endif

