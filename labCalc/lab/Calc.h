#pragma once
#include <iostream>
#include <string>
#include "Tree.h"

class ÑÑalculator
{
public:
	ÑÑalculator();
	~ÑÑalculator();
	void Calculate(const std::string & expression);
private:
	CTree m_tree;
};

