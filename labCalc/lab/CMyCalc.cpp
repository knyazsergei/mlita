#include "stdafx.h"
#include "CMyCalc.h"

double CMyCalc::Calculate(std::string str)
{
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	stream = std::istringstream(str);

	return ParseExpression();
}

double CMyCalc::GetNumber()
{
	double number = 0;
	do
	{
		if (isdigit(m_char))
		{
			number = number * 10 + m_char - '0';
		}
		else
		{
			return number;
		}
	} while (stream.get(m_char));
	return number;
}

double CMyCalc::GetValue()
{
	stream.get(m_char);
	if (m_char == '(')
	{
		return ParseExpression();
	}
	else
	{
		return GetNumber();
	}
}

double CMyCalc::ParseExpression()
{
	double value = factor();
	for (;;)
	{
		switch (m_char)
		{
		case '+':
			value += factor();
			break;
		case '-':
			value -= factor();
			break;
		case '^':
			value = pow(value, factor());
			break;
		default:
			return value;
		}
		stream.get(m_char);
	}
}

double CMyCalc::factor()
{
	double value = GetValue();
	for (;;)
	{
		switch (m_char)
		{
		case '*':
			value *= GetValue();
			break;
		case '/':
			value /= GetValue();
			break;
		default:
			return value;
		}
	}
}
