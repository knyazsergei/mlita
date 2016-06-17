#pragma once
#include "stdafx.h"
#include <map>
#include <algorithm>
#include <climits>
#include <list>
#include "Node.h"
#include "Visualization.h"
#include <functional>
#include <fstream>
#include <sstream>

class CGraph
{
	using StepHandler = std::function<void(const std::string &dotCode)>;
public:
	CGraph(std::shared_ptr<CVisualization> visualization);
	~CGraph() = default;
	void Init(unsigned cities, unsigned roads);

	void ReadGraph();
	void SaveResult();

	void Update();
	void WriteDot(const std::string & styles);
	void WriteDot(const std::string & styles, unsigned timer);
private:
	void SetRoad(unsigned from, unsigned to, unsigned cost);
	void DetermineMaximumLoad();

	std::vector<int> m_nodes;
	size_t m_countCities;

	std::map<unsigned, CNode> m_edges;
	std::shared_ptr<CVisualization> m_visualization;

	std::string fileName = "g.dot";
};

