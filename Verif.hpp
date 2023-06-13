#ifndef NODE_JSON_VERIF_HPP
#define NODE_JSON_VERIF_HPP

#include <string>
#include <sstream>
#include <iomanip>

bool isInt(std::string str)
{
	try {
		size_t pos = 0;
		int nb = std::stoi(str, &pos);
		if (pos == str.length())
			return true;
		else
			return false;
	} catch (const std::exception&) {
		return false;
	}
}
int toInt(std::string str)
{
	try {
		size_t pos = 0;
		int nb = std::stoi(str, &pos);
		if (pos == str.length())
			return nb;
	} catch (const std::exception&) {}

	return 0;
}

bool isFloat(std::string str)
{
	try {
		float f = std::stof(str);
		return true;
	} catch (const std::exception&) {
		return false;
	}
}
float toFloat(std::string str)
{
	try {
		float f = std::stof(str);
		return f;
	} catch (const std::exception&) {}

	return 0;
}

int isBool(const std::string& str)
{
	if (str == "true")
		return 1;
	else if (str == "false")
		return 0;
	else
		return -1;
}

char isChar(std::string str)
{
	if (str.size() == 1)
		return str[0];
	else
		return '\0';
}

bool isTable(std::string v)
{
	if (v.at(0) != '[' || v.at(v.size() - 1) != ']')
	{
		return false;
	}
	return true;
}

std::vector<std::string> toVecString(std::string v)
{
	if (v == "")
		return {};
	if (v.at(0) != '[' || v.at(v.size() - 1) != ']')
	{
		std::cerr << "string : '" << v << "' not a table" << std::endl;
		exit(0);
	}

	v = supFirstElement(v, '[');

	std::vector<std::string> vec = split(v.c_str(), "\", \"");

	return vec;
}

std::vector<int> toVecInt(std::string v)
{
	std::vector<std::string> vS = toVecString(v);
	std::vector<int> vec;

	for (std::string value : vS)
	{
		vec.push_back(toInt(value));
	}

	return vec;
}

std::vector<float> toVecFloat(std::string v)
{
	std::vector<std::string> vS = toVecString(v);
	std::vector<float> vec;

	for (std::string value : vS)
	{
		vec.push_back(toFloat(value));
	}

	return vec;
}
std::vector<bool> toVecBool(std::string v)
{
	std::vector<std::string> vS = toVecString(v);
	std::vector<bool> vec;

	for (std::string value : vS)
	{
		vec.push_back(isBool(value));
	}

	return vec;
}
std::vector<char> toVecChar(std::string v)
{
	std::vector<std::string> vS = toVecString(v);
	std::vector<char> vec;

	for (std::string value : vS)
	{
		vec.push_back(isChar(value));
	}

	return vec;
}

std::string toString(int v)
{
	return std::to_string(v);
}
std::string toString(float v)
{
	// 5 number after '.'.
	std::ostringstream oss;
    oss << std::fixed << std::setprecision(5) << v;
    return oss.str();
}
std::string toString(bool v)
{
	if (v == true)
		return "true";
	else
		return "false";
}
std::string toString(char v)
{
	return std::string(1, v);;
}

std::string toString(std::vector<std::string> v)
{
	std::string result;

	int index = 0;
	for (const std::string& str : v) {
		if (str != "")
		{
			if (str.at(0) == '-')
			{
				std::cerr << "invalid character '-' in string : " << str << std::endl;
				exit(0);
			}	
		}
		if (index != 0)
			result += "\", \"";
		result += str;
		index++;
	}

	result = "[\"" + result + "\"]";

	return result;
}
std::string toString(std::vector<int> v)
{
	std::vector<std::string> vS;

	for (int value : v)
	{
		vS.push_back(toString(value));
	}

	std::string result = toString(vS);

	return result;
}
std::string toString(std::vector<float> v)
{
	std::vector<std::string> vS;

	for (float value : v)
	{
		vS.push_back(toString(value));
	}

	std::string result = toString(vS);

	return result;
}
std::string toString(std::vector<bool> v)
{
	std::vector<std::string> vS;

	for (bool value : v)
	{
		vS.push_back(toString(value));
	}

	std::string result = toString(vS);

	return result;
}
std::string toString(std::vector<char> v)
{
	std::vector<std::string> vS;

	for (char value : v)
	{
		vS.push_back(toString(value));
	}

	std::string result = toString(vS);

	return result;
}

#endif