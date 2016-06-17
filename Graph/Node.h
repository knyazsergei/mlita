#pragma once
#include <map>
#include <vector>
#include <set>

struct SCost
{
	unsigned first;
	unsigned second;
};

class CNode
{
public:
	CNode();
	~CNode();
	bool visited = false;
	//to, cost
	std::map<unsigned, int> m_road;
};

