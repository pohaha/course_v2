#include "Function.h"
#include <iostream>
#include <math.h>

double Function::solveFor(double arg)
{
	double output=0;
	switch (type)
	{
	case UNDEFINED:
		std::cout << "This function is lame";
		break;
	case X_SQARE:
		output = constant * arg * arg;
		break;
	case X_POW_N:
		output = pow(arg, constant);
		break;
	case COS_X:
		output = constant * cos(arg);
		break;
	case SIN_X:
		output = constant * sin(arg);
		break;
	case LN_X:
		output = constant * log(arg);
		break;
	case SIMPLE:
		output = constant;
		break;
	case OTHER:
		output = constant*arg*arg - 1;
		break;
	default:
		break;
	}
    return output;
}

Function::Function(bool construct)
{
	if (construct)
	{
		int TypeAsInt;
		std::cout << "input the type of a function: "<<std::endl;
		std::cout << "If you want a (a*x^2),	input 1" << std::endl;
		std::cout << "If you want a (x^a),		input 2" << std::endl;
		std::cout << "If you want a (a*cos(x)), input 3" << std::endl;
		std::cout << "If you want a (a*sin(x)), input 4" << std::endl;
		std::cout << "If you want a (a*ln(x)),	input 5" << std::endl;
		std::cout << "If you want a (a),		input 6" << std::endl;
		std::cout << "If you want a (a*(x^2)-1), input 7" << std::endl;
		std::cin >> TypeAsInt;
		switch (TypeAsInt)
		{
		case 1:
			type = FunctionTypes::X_SQARE;
			break;
		case 2:
			type = FunctionTypes::X_POW_N;
			break;
		case 3:
			type = FunctionTypes::COS_X;
			break;
		case 4:
			type = FunctionTypes::SIN_X;
			break;
		case 5:
			type = FunctionTypes::LN_X;
			break;
		case 6:
			type = FunctionTypes::SIMPLE;
			break;
		case 7:
			type = FunctionTypes::OTHER;
			break;
		default:
			type = FunctionTypes::UNDEFINED;
			break;
		}
		std::cout << "input constant (a): ";
		std::cin >> constant;
	}
}
