#pragma once
#include <string>
#include <iostream>
#include <map>

std::cout << calc.Calculate("1+2*3^(1-2/3^4)") << " = " << 6.8394 << std::endl;

std::string process(std::string str)
{
	k++;
	std::cout << k << "    " << std::endl;

	std::string newStr;
	size_t checkPoint = 0;
	std::map<size_t, char> mp;
	for (size_t i = 0;i < str.size();++i)
	{
		auto & ch = str[i];
		if (ch == '^')
		{
			size_t j = i;
			size_t brackets = 0;
			for (;j > 0;--j)
			{
				if (str[j] == '+' || str[j] == '-' || str[j] == '/' || str[j] == '*')
				{
					newStr.append(str.substr(checkPoint, j + 1 - checkPoint));
					newStr += '(';


					size_t end = i;
					bool notBrackets = true;
					for (;end < str.size();end++)
					{
						if (str[end] == '(')
						{
							brackets++;
						}
						else if (str[end] == ')')
						{
							brackets--;
						}
						if ((str[end] == '+' || str[end] == '-' || str[end] == '/' || str[end] == '*') && brackets == 0)
						{
							break;
						}
					}

					auto miniResult = process(str.substr(j + 1, end - j - 1));
					std::cout << "M " << miniResult << std::endl;

					newStr.append(miniResult);
					newStr += ')';
					checkPoint = end;
					break;
				}
			}
			if (j == 0)
			{
				if (str[j] == '+' || str[j] == '-' || str[j] == '/' || str[j] == '*')
				{
					newStr.append(str.substr(checkPoint, j + 1 - checkPoint));
					newStr += '(';


					size_t end = i;
					bool notBrackets = true;
					for (;end < str.size();end++)
					{
						if (str[end] == '(')
						{
							brackets++;
						}
						else if (str[end] == ')')
						{
							brackets--;
						}
						if ((str[end] == '+' || str[end] == '-' || str[end] == '/' || str[end] == '*') && brackets == 0)
						{
							break;
						}
					}

					auto miniResult = process(str.substr(j + 1, end - j - 1));
					std::cout << "M " << miniResult << std::endl;

					newStr.append(miniResult);
					newStr += ')';
					checkPoint = end;
					break;
				}
			}
		}
	}
	k--;
	std::cout << k << " ";
	newStr.append(str.substr(checkPoint, str.size()));
	return newStr;
}
