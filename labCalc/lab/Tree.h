#pragma once
#include <stdexcept>
#include <memory>
#include <iostream>


enum class Operation{
	plus,
	minus,
	division,
	multiplication,
	degree,
	openingBracket,
	closingBracket
};

class CTree
{
	enum class NodeType {
		value,
		operation
	};
	class CNode
	{
	public:
		CNode()
		{

		}
		CNode(float number)
		{
			m_type = NodeType::value;
			m_value = number;
		}
		CNode(Operation operation)
		{
			m_type = NodeType::operation;
			m_operation = operation;
		}
		std::shared_ptr<CNode> parent;
		std::shared_ptr<CNode> left;
		std::shared_ptr<CNode> right;
		NodeType m_type = NodeType::operation;
		void SetOperationType(Operation operation)
		{
			m_operation = operation;
		}
	//private:
		float m_value;
		Operation m_operation;
	};
public:
	CTree();
	~CTree();
	void Push(Operation operation);
	void Push(float number);
	void Show();
private:
	float ShowNode(std::shared_ptr<CNode> node);
	float Calc(float first, Operation operation, float second);
	std::string OperationToString(Operation operation);
	std::shared_ptr<CNode> m_head;
	std::shared_ptr<CNode> m_current;
};

