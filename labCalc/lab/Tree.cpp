#include "stdafx.h"
#include "Tree.h"


CTree::CTree()
{
}


CTree::~CTree()
{
}

void CTree::Push(Operation operation)
{
	if (operation == Operation::openingBracket)
	{
		if (m_current == nullptr)
		{
			m_head = std::make_shared<CNode>();
			m_current = m_head;
		}
		else
		{
			if (m_current->left == nullptr)
			{
				m_current->left = std::make_shared<CNode>();
				auto parent = m_current;
				m_current = m_current->left;
				m_current->parent = parent;
			}
			else
			{
				if (m_current->right == nullptr)
				{
					m_current->right = std::make_shared<CNode>();
					auto parent = m_current;
					m_current = m_current->right;
					m_current->parent = parent;
				}
				else
				{
					auto node = m_current->right;
					m_current->right = std::make_shared<CNode>();
					auto parent = m_current;
					m_current = m_current->right;
					m_current->parent = parent;
					m_current->left = node;
				}
			}
		}
	}
	else if (operation == Operation::closingBracket)
	{
		m_current = m_current->parent;
	}
	else
	{
		//for -1
		if (m_current == nullptr && operation == Operation::minus)
		{
			m_head = std::make_shared<CNode>();
			m_current = m_head;
			m_current->SetOperationType(operation);
			m_current->left = 0;
		}
		else if (m_current->right != nullptr && m_current->right->m_type == NodeType::value)
		{
			auto node = m_current->right;
			m_current->right = std::make_shared<CNode>();
			auto parent = m_current;
			m_current = m_current->right;
			m_current->parent = parent;
			m_current->left = node;
		}
		m_current->SetOperationType(operation);
	}
}

void CTree::Push(float number)
{
	if (m_current == nullptr)
	{
		m_head = std::make_shared<CNode>();
		m_current = m_head;
		m_current->left = std::make_shared<CNode>(number);
	}
	else if (m_current->left == nullptr)
	{
		m_current->left = std::make_shared<CNode>(number);
	}
	else if (m_current->right == nullptr)
	{
		m_current->right = std::make_shared<CNode>(number);
	}
	else
	{
		throw std::logic_error("the excess number");
	}
}

void CTree::Show()
{
	ShowNode(m_head);
}

float CTree::ShowNode(std::shared_ptr<CNode> node)
{
	if (node == nullptr)
	{
		return 0;
	}
	if (node->m_type == NodeType::value)
	{
		return node->m_value;
	}
	else
	{
		auto result = Calc(ShowNode(node->left), node->m_operation, ShowNode(node->right));
		std::cout << 
			ShowNode(node->left) << 
			" (" << OperationToString(node->m_operation).c_str() << 
			") " << ShowNode(node->right) << 
			"=" << result << 
			std::endl;
		return result;
	}
}

float CTree::Calc(float first, Operation operation, float second)
{
	switch (operation)
	{
	case Operation::plus:
		return first + second;
		break;
	case Operation::minus:
		return first - second;
		break;
	case Operation::division:
		return first / second;
		break;
	case Operation::multiplication:
		return first * second;
		break;
	case Operation::degree:
		return pow(first, second);
		break;
	default:
		throw std::invalid_argument("unknown operation");
		break;
	}
}

std::string CTree::OperationToString(Operation operation)
{
	switch (operation)
	{
	case Operation::plus:
		return "+";
		break;
	case Operation::minus:
		return "-";
		break;
	case Operation::division:
		return "/";
		break;
	case Operation::multiplication:
		return "*";
		break;
	case Operation::degree:
		return "^";
		break;
	default:
		break;
	}
	return std::string();
}
