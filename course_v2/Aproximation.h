#pragma once
#include "Function.h"
#include "Vector.h"
enum class AproximationModes {
	MODE_GAUSS,
	MODE_ITERRATION
};
class Aproximation
{
private:
	Function* AproximationFunctions=nullptr;
	unsigned int size=0;
	unsigned int amount_of_functions=0;
	Double_Vector x_values;
	Double_Vector y_values;
	bool FailureState = false;
public:
	Aproximation(bool construct = false);
	void aproximate(AproximationModes mode);
	void redefineFunctions();
	
private:
	Double_Vector SimpleIterrations(Double_Vector* koefficients, Double_Vector free_members);
	
};

