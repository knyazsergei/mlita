#pragma once
#include <iostream>
#include <string>
#include "Tree.h"

class ��alculator
{
public:
	��alculator();
	~��alculator();
	void Calculate(const std::string & expression);
private:
	CTree m_tree;
};

