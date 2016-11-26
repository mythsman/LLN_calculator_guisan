#ifndef PARSER_H
#define PARSER_H
#include<iostream>
#include<sstream>
#include<string>
#include<math.h>
namespace Parser{
	const int SUCCESS=0;
	const int FAILURE=1;
	const int PARTIAL=2;
	class Parser{
	private:
		std::string expr;
		int status;
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
		int getStatus();
	};
}
#endif
