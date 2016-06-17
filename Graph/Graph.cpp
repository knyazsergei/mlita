#include "stdafx.h"
#include "Graph.h"
#include <Windows.h>
#include <stdlib.h>

CGraph::CGraph(std::shared_ptr<CVisualization> visualization) :
	m_visualization(visualization)
{
	visualization->SetLoad(std::bind(&CGraph::ReadGraph, this));
	visualization->SetSave(std::bind(&CGraph::SaveResult, this));
}

void CGraph::Init(unsigned cities, unsigned roads)
{
	m_edges.clear();
	m_nodes.clear();
	m_visualization->SetState("creating nodes");
	for (unsigned i = 0; i < cities;++i)
	{
		m_edges[i] = CNode();
		WriteDot("");
	}
	m_countCities = cities;
}

void CGraph::ReadGraph()
{
	const char *filters[] = { "*.txt" };
	char const *result = tinyfd_openFileDialog("Select input file", "", 1, filters, "", false);
	// ������������ ������� ����� �����.
	if (result == nullptr)
	{
		return;
	}

	std::ifstream in(result);
	if (!in.is_open())
	{
		tinyfd_messageBox("Error", "I/O error when reading input file", "ok", "error", 1);
	}
	else
	{
		try
		{
			m_visualization->SetState("reading graph");
			std::string line;
			getline(in, line);
			unsigned cities;
			unsigned roads;
			{
				std::stringstream lineStrm(line);
				lineStrm >> cities >> roads;
			}
			std::cout << cities << " " << roads << std::endl;
			if (cities > 10'000 || roads > 10'000'0)
			{
				tinyfd_messageBox("Error", "I/O error when reading input file", "ok", "error", 1);
				return;
			}
			Init(cities, roads);
			while (getline(in, line))
			{
				std::stringstream lineStrm(line);
				unsigned from;
				unsigned to;
				unsigned cost;
				lineStrm >> from >> to >> cost;
				SetRoad(from - 1, to - 1, cost);
			}
			WriteDot("");
			DetermineMaximumLoad();
		}
		catch (...)
		{
			tinyfd_messageBox("Error", "I/O error when reading input file", "ok", "error", 1);
		}
	}
}

void CGraph::SaveResult()
{
	const char *filters[] = { "*.txt" };
	char const *result = tinyfd_saveFileDialog("Select output file", "", 1, filters, "");
	// ������������ ������� ����� �����.
	if (result == nullptr)
	{
		return;
	}
	std::ofstream out(result);
	if (!out.is_open())
	{
		tinyfd_messageBox("Error", "I/O error when writing output file", "ok", "error", 1);
	}
	else
	{
		for (size_t i = 1;i < m_nodes.size();i++)
		{
			out << m_nodes[i] << '\n';
		}
		WriteDot("");
		tinyfd_messageBox("Success", "File saved OK", "ok", "info", 1);
	}
}

void CGraph::Update()
{

}

void CGraph::WriteDot(const std::string & styles)
{
	WriteDot(styles, 500);
}

void CGraph::WriteDot(const std::string & styles, unsigned timer)

{
	/*
	graph graphname {
		 a -- b -- c;
		 b -- d;
	 }
	 */
	std::cout << "next" << m_edges.size() << "\n";
	std::set<std::pair<unsigned, unsigned>> ref;
	std::ofstream out(fileName);
	out << "graph mygraph{\n";
	out << "node [shape=doublecircle]; 1 ;\n";
	out << styles;
	out << "node [shape=circle];\n";
	for (size_t i = 0; i < m_nodes.size();i++)
	{
		if (i != 0)
			out << i + 1 << " [ label = \"" << std::to_string(i + 1) << ":" << std::to_string(m_nodes[i]) << "\" ];\n";
	}
	for (auto it : m_edges)
	{
		for (auto road : it.second.m_road)
		{
			if (ref.find({ it.first, road.first }) == ref.end())
			{
				out << it.first + 1 << "--" << road.first + 1 << "[label = " << road.second << " ] " << '\n';
				ref.insert({ road.first, it.first });
			}
		}
		out << '\n';
	}
	out << "}\n";
	out << std::endl;
	system("dot g.dot -Tpng -og.png");
	m_visualization->Update();
	Sleep(timer);
}


void CGraph::SetRoad(unsigned from, unsigned to, unsigned cost)
{
	m_visualization->SetState("road construction");
	m_edges[from].m_road[to] = cost;
	m_edges[to].m_road[from] = cost;
	WriteDot("");
}


void CGraph::DetermineMaximumLoad()
{
	m_visualization->SetState("start calculating maximum loads");
	//init
	m_nodes.resize(m_countCities, -1);
	m_nodes[0] = INT_MAX;
	std::list<unsigned> pq; //������� <number, cost>
	pq.push_back(0);

	//���� ������� �� �����
	while (!pq.empty())
	{
		std::string styles;
		for (auto it : pq)
		{
			styles.append( std::to_string(it) + " [color=\"0.650 0.700 0.700\"];\n");
		}
		std::cout << styles;
		WriteDot(styles);
		
		auto & current = pq.front();

		//������� ��� ������� �������
		m_visualization->SetState("Go around all adjacent city");
		for (auto it : m_edges[current].m_road)
		{
			if (!m_edges[it.first].visited)
			{
				std::string style = std::to_string(it.first) + " [ shape = Mdiamond, style = filled, color = salmon2];\n";
				WriteDot(style, 1500);
				//���� ������������ ���������������� ������ ���� ������ �������� ������, �� ������������ �
				if (m_nodes[it.first] < it.second)
				{
					m_nodes[it.first] = it.second;
				}
				pq.push_back(it.first);
			}
		}
		m_edges[current].visited = true;

		pq.pop_front();
		WriteDot("");
	}
}
