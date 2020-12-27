#pragma once
enum FunctionTypes {
	UNDEFINED,
	X_SQARE,
	X_POW_N,
	COS_X,
	SIN_X,
	LN_X,
	SIMPLE,
	OTHER
};
class Function
{
	
private:
	FunctionTypes type=FunctionTypes::UNDEFINED;
	int constant=0;
public:
	double solveFor(double arg);
	Function(bool construct = true);
};

