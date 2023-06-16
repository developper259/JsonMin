#ifndef NODE_JSON_PARSER_HPP
#define NODE_JSON_PARSER_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <string>

std::vector<std::string> split(const char* str, char delimiter)
{
	char tv[100][255];
	int index = 0;
	int index2 = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		char c = str[i];
		if(c == delimiter)
		{
			index++;
			index2 = 0;
		}else
		{
			tv[index][index2] = c;
			index2++;
		}
	}

	std::vector<std::string> result(tv, tv + (index + 1));
	
	memset(tv, 0, sizeof(tv));

	return result;
}

std::vector<std::string> split(const char* str, std::string delimiter)
{
	char tv[100][255];
	int index = 0;
	int index2 = 0;
	int index3 = 0;
	for (int i = 0; i < strlen(str) - 1; i++)
	{
		char c = str[i];
		
		if (c == delimiter[index3])
		{
			index3++;
		}else
		{
			index3 = 0;
			tv[index][index2] = c;
			index2++;
		}

		if (index3 == delimiter.size())
		{
			index++;
			index3 = 0;
			index2 = 0;
		}

	}

	std::vector<std::string> result(tv, tv + (index + 1));

	memset(tv, 0, sizeof(tv));

	return result;
}

std::string join(const std::vector<std::string>& vec, std::string delimiter) {
	std::string result;
	int index = 0;

	for (const std::string& str : vec) {
		if (index != 0)
			result += delimiter;
		result += str;
		index++;
	}
	
	return result;
}

std::string replace(std::string str, char holdStr, char newStr)
{
	std::string result;
	int index = 0;

	for (int i = 0; i < str.size() - 1; i++)
	{
		char c = str.at(i);
		
		if (c == holdStr)
		{
			result += newStr;
		}else
		{
			result += c;
		}
	}

	return result;
}
std::string replace(const std::string& str, const std::string& holdStr, const std::string& newStr) {
    std::string result = str;
    size_t index = result.find(holdStr);
    while (index != std::string::npos) {
        result.replace(index, holdStr.length(), newStr);
        index = result.find(holdStr, index + newStr.length());
    }
    return result;
}

std::string supFirstElement(std::string str, char c)
{
	if (str == "")
		return str;
	size_t pos = str.find_first_not_of(c);
	if (pos != std::string::npos)
		return str.substr(pos);
	else
		return str;
}
std::string supLastElement(std::string str, char c) {
	if (str == "")
		return str;
	size_t pos = str.find_last_not_of(c);
	if (pos != std::string::npos)
		return str.substr(0, pos + 1);
	else
		return str;
}

std::vector<std::string> vecCharPTRtoVecString(const std::vector<const char*>& charPtrVector)
{
	std::vector<std::string> stringVector;
	
	for (const char* charPtr : charPtrVector)
	{
		std::string str(charPtr);
		stringVector.push_back(str);
	}
	
	return stringVector;
}

#endif