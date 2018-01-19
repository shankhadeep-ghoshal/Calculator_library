#include "stdafx.h"
#include "InfixCalculator.h"
#include <stack>
#include <algorithm>
#include <cmath>


InfixCalculator::InfixCalculator():postfix(""),infix(""),parser(),answer(""){}

InfixCalculator::InfixCalculator(std::string s) {
	s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
	this->infix = s.c_str();
	this->answer = "";
}

InfixCalculator::~InfixCalculator(){
	this->parser.clear();
}

int InfixCalculator::retOperatorPrec(std::string c)
{
	if (c == "s" || c == "c" || c == "t" || c == "m")return 4;
	else if (c == "^" || c == "r")return 3;
	else if (c == "/" || c == "%" || c == "*")return 2;
	else if (c == "-" || c == "+")return 1;
	else return -1;
}

bool InfixCalculator::isOperand(std::string c)
{
	std::string s[] = { "0","1","2","3","4","5","6","7","8","9",".","," };
	bool temp = false;
	for (std::string k : s) {
		if (k == c)temp = true;
	}
	return temp;
}

bool InfixCalculator::isOperator(std::string c)
{
	return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "%" || c == "s" || c == "c" || c == "t" || c == "m" || c == "r");
}

double InfixCalculator::add(double a, double b)
{
	return a+b;
}

double InfixCalculator::subtract(double a, double b)
{
	return add(a,-b);
}

double InfixCalculator::multiply(double a, double b)
{
	return a*b;
}

double InfixCalculator::divide(double a, double b)
{
	return multiply(a, 1/b);
}

double InfixCalculator::mod(double a, double b)
{
	return ((int)a%(int) b) + 0.0;
}


void InfixCalculator::toTokenList()
{
	for (int i = 0; i < this->infix.length(); i++) {
		int k2 = i - 1;
		int k3 = i + 1;
		if (this->infix[i] == ' ')continue;
		if (this->infix[i] == '-') {
			if (k2 >= 0 && (this->infix[k2] == '(' || this->infix[k2] == '-' || isOperator(std::string(1, this->infix[k2])))) {
				this->parser.push_back(std::string(1, '0'));
				this->parser.push_back(std::string(1, this->infix[i]));
			}
			else if (this->infix[0] == '-' && this->parser.size() == 0) {
				this->parser.insert(this->parser.begin(), "0");
				this->parser.push_back(std::string(1, this->infix[i]));
			}
			//else if(k2>=0 )
			else this->parser.push_back(std::string(1, this->infix[i]));
		}
		else if (this->infix[i] == '(' && k2>=0 && isOperand(std::string(1, this->infix[k2]))) {
			this->parser.push_back(std::string(1,'*'));	
			this->parser.push_back(std::string(1, this->infix[i]));
		}
		else if (this->infix[i] == ')' && k3 >= 0 && isOperand(std::string(1, this->infix[k3]))) {
			this->parser.push_back(std::string(1, this->infix[i]));
			this->parser.push_back(std::string(1,'*'));
		}
		else if (isOperand(std::string(1, this->infix[i]))) {
			std::string oper = "";
			while (isOperand(std::string(1, this->infix[i]))) {
				oper += this->infix[i];
				i++;
			}
			parser.push_back(oper);
			i--;
		}
		else {
			parser.push_back(std::string(1,infix[i]));
		}	
	}
}

void InfixCalculator::toPostfix()
{
	toTokenList();
	std::stack<std::string> charStack;
	//std::vector<std::string> tempVector = (*this).parser;
	for (int i = 0; i < parser.size(); i++) {
		if (isOperator(this->parser[i])) {
			this->postfix += " ";
			if (!charStack.empty()) {
				while (!charStack.empty() && retOperatorPrec(parser[i]) <= retOperatorPrec(charStack.top())) {
					postfix += charStack.top();
					charStack.pop();
				}
			}
			charStack.push(parser[i]);
		}
		else if ((*this).parser[i] == "(")charStack.push(parser[i]);
		else if (parser[i] == ")") {
			while (!charStack.empty() && charStack.top() != "(") {
				postfix += charStack.top();
				charStack.pop();
			}
			if (!charStack.empty())charStack.pop();
		} 
		else {
			postfix += parser[i];
		}
	}
	while (!charStack.empty()) {
		postfix += charStack.top();
		charStack.pop();
	}
}

std::string InfixCalculator::evalPostix()
{
	toPostfix();
	std::stack<double> numStack;
	double tot,x,y;
	x = y = tot = 0.0;
	for (int i = 0; i < this->postfix.length(); i++) {
		if (isOperand(std::string(1, postfix[i]))) {
			std::string oper = "";
			while (isOperand(std::string(1, this->postfix[i]))) {
				oper += this->postfix[i];
				i++;
			}
			numStack.push(stod(oper));
			i--;
		}
		else if (isOperator(std::string(1, this->postfix[i]))) {
			switch (this->postfix[i]) {
			case '+': 
				x = numStack.top();
				numStack.pop();
				y = numStack.top();
				numStack.pop();
				tot = add(y, x);
				numStack.push(tot);
				break;
			case '-': 
				x = numStack.top(); 
				numStack.pop();
				y = numStack.top(); 
				numStack.pop();
				tot = subtract(y, x); 
				numStack.push(tot);
				break;
			case '*':
				x = numStack.top(); 
				numStack.pop();
				y = numStack.top(); 
				numStack.pop();
				tot = multiply(y, x); 
				numStack.push(tot);
				break;
			case '/':
				x = numStack.top(); 
				numStack.pop();
				y = numStack.top(); 
				numStack.pop();
				if (y == 0) throw std::overflow_error("divide by zero error"); 
				else {
					tot = divide(y, x); 
					numStack.push(tot);
				}
				break;
			case 's':
				x = numStack.top(); 
				numStack.pop();
				tot = sin(x);
				numStack.push(tot);
				break;
			case 'c':
				x = numStack.top(); 
				numStack.pop();
				tot = cos(x);
				numStack.push(tot);
				break;
			case 't':
				x = numStack.top(); 
				numStack.pop();
				tot = tan(x);
				numStack.push(tot);
				break;
			case 'm':
				x = numStack.top(); 
				numStack.pop();
				tot = sqrt(x*x);
				numStack.push(tot);
				break;
			case 'r':
				x = numStack.top(); 
				numStack.pop();
				numStack.push(sqrt(x));
				break;
			case '%':
				x = numStack.top(); 
				numStack.pop();
				y = numStack.top(); 
				numStack.pop();
				if (x <= 0 || y <= 0) throw std::invalid_argument("cannot be negative numbers or zero for modulo operation");
				else numStack.push(mod(y,x));
				break;
			case '^':
				x = numStack.top(); 
				numStack.pop();
				y = numStack.top(); 
				numStack.pop();
				numStack.push(pow(y, x));
				break;
			default:
				throw std::invalid_argument("Invalid expression");
			}
		}
	}
	this->answer = (this->infix == "" || this->infix.empty()) ? "no input provided" : std::to_string(numStack.top());
	return this->answer;
}

JNIEXPORT jstring JNICALL Java_JniAttempt_11_119_12018_InfixToPostfixTesterJni_getPostfix
(JNIEnv * env, jobject obj, jstring str) {
	const char* inf = env->GetStringUTFChars(str, 0);
	std::string myString(inf);
	jstring tempStr = env->NewStringUTF(InfixCalculator(myString).evalPostix().c_str());
	env->ReleaseStringUTFChars(str, inf);
	return tempStr;
}
