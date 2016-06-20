#pragma once
#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <algorithm>

class CMyCalc
{
public:
	double Calculate(std::string str);
private:
	double GetNumber();

	double GetValue();

	double ParseExpression();

	double factor();
private:
	char m_char;
	std::istringstream stream;
	size_t position = 0;
};