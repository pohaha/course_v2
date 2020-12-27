#include "Matrix.h"
#include "Vector.h"
#include "Aproximation.h"
#include <iostream>

int main()
{
	Aproximation test(true);
	int ap_type;
	std::cout << "chose the aproximation mode" << std::endl;
	std::cout << "if you wold like to use the gauss method input 1" << std::endl;
	std::cout << "if you wold like to use the iterrations method input 2" << std::endl;
	std::cin >> ap_type;
	switch (ap_type)
	{
	case 1:
		test.aproximate(AproximationModes::MODE_GAUSS);
		break;
	case 2:
		test.aproximate(AproximationModes::MODE_ITERRATION);
		break;
	default:
		std::cout << "[WARNING!] wrong type" << std::endl;
		break;
	}
	int Do_Again;
	do 
	{
		std::cout << "would you like to aproximate with new functions? [0/1]: ";
		std::cin >> Do_Again;
		if (Do_Again)
		{
			test.redefineFunctions();
			std::cout << "chose the aproximation mode" << std::endl;
			std::cout << "if you wold like to use the gauss method input 1" << std::endl;
			std::cout << "if you wold like to use the iterrations method input 2" << std::endl;
			std::cin >> ap_type;
			switch (ap_type)
			{
			case 1:
				test.aproximate(AproximationModes::MODE_GAUSS);
				break;
			case 2:
				test.aproximate(AproximationModes::MODE_ITERRATION);
				break;
			default:
				std::cout << "[WARNING!] wrong type" << std::endl;
				break;
			}
		}

	} while (Do_Again);
}