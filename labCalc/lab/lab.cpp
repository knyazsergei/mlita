// lab.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Calc.h"
#include "CMyCalc.h"

int main()
{
	CMyCalc calc;
	std::cout << calc.Calculate("(1/2+2/3)*(3/4-4/5)*1000") << " = " << -58.3333 << std::endl;
	return EXIT_SUCCESS;
}
