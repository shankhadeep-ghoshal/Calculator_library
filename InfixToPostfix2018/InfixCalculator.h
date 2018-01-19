#pragma once
#include <string>
#include <vector>
#include "JniAttempt_1_19_2018_InfixToPostfixTesterJni.h"
class InfixCalculator
{
private:
	std::string infix;
	std::string answer;
	std::string postfix;
	std::vector<std::string> parser;

	void toTokenList();
	int retOperatorPrec(std::string);
	bool isOperand(std::string);
	bool isOperator(std::string);
	double add(double, double);
	double subtract(double, double);
	double multiply(double, double);
	double divide(double, double);
	double mod(double,double);
	void toPostfix();

public:
	InfixCalculator();
	InfixCalculator(std::string);
	~InfixCalculator();
	std::string evalPostix();	
};