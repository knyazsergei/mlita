#include "stdafx.h"
#include "Calc.h"


ÑÑalculator::ÑÑalculator()
{
}

ÑÑalculator::~ÑÑalculator()
{
}

void ÑÑalculator::Calculate(const std::string & expression)
{
	enum class State {
		number,
		notNumber
	};

	float number = 0;

	State state = State::notNumber;

	for (auto ch : expression)
	{
		if (state == State::number)
		{
			m_tree.Push(number);
			state = State::notNumber;
			number = 0.f;
		}

		if (isspace(ch))
		{

		}
		else if (ch >= '0' && ch <= '9')
		{
			state = State::number;
			number *= 10.f;
			number += ch - '0';
		}
		else if (ch == '(')
		{
			m_tree.Push(Operation::openingBracket);
		}
		else if (ch == ')')
		{
			m_tree.Push(Operation::closingBracket);
		}
		else if (ch == '+')
		{
			m_tree.Push(Operation::plus);
		}
		else if (ch == '-')
		{
			m_tree.Push(Operation::minus);
		}
		else if (ch == '*')
		{
			m_tree.Push(Operation::multiplication);
		}
		else if (ch == '/')
		{
			m_tree.Push(Operation::division);
		}
		else if (ch == '^')
		{
			m_tree.Push(Operation::degree);
		}
		else
		{
			throw std::invalid_argument("incorrect char" + ch);
		}
	}
	if (state == State::number)
	{
		m_tree.Push(number);
		state = State::notNumber;
		number = 0.f;
	}
	m_tree.Show();
}
