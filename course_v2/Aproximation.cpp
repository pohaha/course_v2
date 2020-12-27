#include "Aproximation.h"
#include <iostream>
#include "Matrix.h"
#include "math.h"

Aproximation::Aproximation(bool construct)
{
	if (construct)
	{
		std::cout << "Input the width of x/y table: ";
		std::cin >> size;
		std::cout << "Input the x values:" << std::endl;
		x_values = Double_Vector(size, 0);
		for (unsigned int i = 0; i < size; i++) std::cin >> x_values[i];
		std::cout << "Input the y values:" << std::endl;
		y_values = Double_Vector(size, 0);
		for (unsigned int i = 0; i < size; i++) std::cin >> y_values[i];
		std::cout << "input the amount of aproximation functions: ";
		std::cin >> amount_of_functions;
		AproximationFunctions = new Function[amount_of_functions];
		system("CLS");
	}
}

void Aproximation::aproximate(AproximationModes mode)
{
	Double_Vector free_Members(amount_of_functions, 0);
	Double_Vector* eqations = new Double_Vector[amount_of_functions];
	for (unsigned int i = 0; i < amount_of_functions; i++) eqations[i] = Double_Vector(amount_of_functions, 0);
	for (unsigned int j = 0; j < amount_of_functions; j++)
	{
		for (unsigned int i = 0; i < size; i++) free_Members[j] += y_values[i] * AproximationFunctions[j].solveFor(x_values[i]);
		for (unsigned int k = 0; k < amount_of_functions; k++)
			for (unsigned int i = 0; i < size; i++)
				eqations[j][k]+=(AproximationFunctions[j].solveFor(x_values[i])) * AproximationFunctions[k].solveFor(x_values[i]);
	}
	Matrix norm(eqations, amount_of_functions);
	Double_Vector Koefficients;
	switch (mode)
	{
	case AproximationModes::MODE_GAUSS:
		Koefficients = norm.solveFor(free_Members);
		break;
	case AproximationModes::MODE_ITERRATION:
		Koefficients = SimpleIterrations(eqations,free_Members);		
		if (FailureState)
		{
			std::cout << "unable to use Iterration method, try another one." << std::endl;
			return;
		}
		break;
	default:
		break;
	}
	std::cout << "Aproximation koefficients are:" << std::endl;
	Koefficients.show(false);
	system("PAUSE");
	system("CLS");
	double y_value;
	double leftBorder = x_values[0];
	double rightBorder = x_values[size - 1];
	double step = (rightBorder - leftBorder) / 20;
	double current = leftBorder-step;
	std::cout << "Code generated for scilab for drawing a graphic: " << std::endl;
	std::cout << "X=[";		
	while (current < (rightBorder+step))
	{
		std::cout << current << " ";
		current+= step;
	}
	std::cout << "]" << std::endl;
	current = leftBorder - step;
	std::cout << "Y=[";
	while (current < (rightBorder+step))
	{
		y_value = 0;
		for (unsigned int i = 0; i < amount_of_functions; i++)
			y_value += Koefficients[i] * (AproximationFunctions[i].solveFor(current));
		std::cout << y_value << " ";
		current+=step;
	}
	std::cout << "]" << std::endl;
	std::cout << "X1=[";
	for (unsigned int i = 0; i < size; i++) std::cout << x_values[i] << " ";
	std::cout << "]" << std::endl;
	std::cout << "Y1=[";
	for (unsigned int i = 0; i < size; i++) std::cout << y_values[i] << " ";
	std::cout << "]" << std::endl;
	std::cout << "plot(X,Y)" << std::endl;
	std::cout << "plot2d(X1,Y1,-2)" << std::endl;
	std::cout << "xgrid" << std::endl;
	system("PAUSE");
	system("CLS");
	std::cout << "Final aproximation information" << std::endl;
	double aproximation_koeficient=0;
	double max_Deviation;
	bool first = true;
	for (unsigned int i = 0; i < size; i++)
	{
		y_value = 0;
		for (unsigned int j = 0; j < amount_of_functions; j++)
			y_value += Koefficients[j] * (AproximationFunctions[j].solveFor(x_values[i]));
		
		if (first)
		{
			max_Deviation = abs(y_value - y_values[i]);
			first = false;
		}
		else if (abs(y_value - y_values[i]) > max_Deviation) max_Deviation = abs(y_value - y_values[i]);
		aproximation_koeficient += pow((y_value - y_values[i]),2);
	}
	std::cout << "Aproximation kriteria: " << aproximation_koeficient << std::endl;
	std::cout << "maximum deviation: " << max_Deviation << std::endl;
}

Double_Vector Aproximation::SimpleIterrations(Double_Vector* koefficients, Double_Vector free_members)
{
	Double_Vector output(amount_of_functions,0);
	double e;
	std::cout << "input the precision of iterration method: ";
	std::cin >> e;
	for (unsigned int i = 0; i < amount_of_functions; i++)
	{
		double lhs = abs(koefficients[i][i]);
		double rhs=0;
		for (unsigned int j = 0; j < amount_of_functions; j++)
			if (j != i)rhs += abs(koefficients[i][j]);
		if (lhs < rhs) 
		{
			//FailureState = true;
			Matrix(koefficients, amount_of_functions).show();
			std::cout << "line " << i << " [WARNING!] does not converge!!\nprefer to establish the diagonal dominance" << std::endl;
			system("PAUSE");
			//return Double_Vector();
		}
	}
	FailureState = false;
	double AchievedPrescision = e+10;
	Double_Vector tmp;
	int Execute=0;
	while (AchievedPrescision>e)
	{
		tmp = output;
		for (unsigned int i = 0; i < amount_of_functions; i++)
		{
			tmp[i] = free_members[i];
			for (unsigned int j = 0; j < amount_of_functions; j++)
				if (i != j) tmp[i] = tmp[i] - koefficients[i][j] * output[j];
			tmp[i] = tmp[i] / koefficients[i][i];
		}
		AchievedPrescision = abs(tmp[0] - output[0]);
		for (unsigned int i = 1; i < amount_of_functions; i++) if (abs(tmp[i] - output[i]) > AchievedPrescision) AchievedPrescision = abs(tmp[i] - output[i]);
		output = tmp;
		Execute++;
	}
	std::cout << "Process finished with " << Execute<<" iterrations"<<std::endl;
	return output;
}

void Aproximation::redefineFunctions()
{
	system("CLS");
	std::cout << "input new amount of functions: ";
	std::cin >> amount_of_functions;
	delete[] AproximationFunctions;
	AproximationFunctions = new Function[amount_of_functions];
}
