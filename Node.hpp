#ifndef JSON_NODE_HPP
#define JSON_NODE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>

#include "Parser.hpp"

class JsonNode
{
private:
	std::map<std::string, std::string> data;

public:

	JsonNode()
	{

	}

	void init(const char* path)
	{
		std::ifstream file(path);

		if (!file)
		{
			std::ofstream createFile(path);
			if (!createFile)
			{
				std::cerr << "Erreur lors de la création du fichier : " << path << std::endl;
				exit(0);
			}
			createFile.close();
		}
	}

	int isLFH(std::string line)
	{
		if (line == "")
			return -1;

		if (line.at(0) == '{' && line.size() == 1)
			return true;
		else
			return false;
	}

	void write(const char* path);

	void read(const char* path)
	{
		std::ifstream file(path);

		if (file.is_open()) {
			std::string line;
			int i = 0;

			while (std::getline(file, line)) {
				load(line);
			}

			file.close();
		} else {
			std::cerr << "Erreur lors de l'ouverture du fichier : " << path << std::endl;
			exit(0);
		}
	}

	void load(std::string str)
	{
		if (str.at(0) != '{' || str.at(str.size() - 1) != '}')
		{
			std::cerr << "str is not a json value : " << str << std::endl;
			exit(0);
		}


		str.erase(str.begin());
		str.erase(str.end() - 1);

		char tv[510][1020];

		int index = 0;
		int index2 = 0;
		int crochNb = 0;
		bool InStr = false;
		char EChar;

		for (int i = 0; i < str.size(); i++)
		{
			char c = str[i];
			if (c == '"')
			{
				if (EChar == '\\')
				{
					InStr = true;
				}else
				{
					InStr = false;
				}
			}
			if (c == '{' || c == '[')
			{
				if (!InStr)
				{
					crochNb++;	
				}
			}

			if (c == '}' || c == ']')
			{
				if (!InStr)
				{
					crochNb--;
				}
			}
			if(c == ',' && !InStr && crochNb == 0)
			{
				index++;
				index2 = 0;
			}else
			{
				tv[index][index2] = c;
				index2++;
			}
			EChar = c;
		}

		std::vector<std::string> vec(tv, tv + (index + 1));
		
		memset(tv, 0, sizeof(tv));

		for (std::string line : vec)
		{
			std::vector<std::string> l = split(line.c_str(), ':');

			std::string key = l[0];
			l.erase(l.begin());

			std::string value = join(l, ":");


			//sublime data
			value = supFirstElement(value, ' ');
			value = supFirstElement(value, '\t');
			key = supFirstElement(key, ' ');
			key = supFirstElement(key, '\t');


			key = supLastElement(key, ' ');
			key = supLastElement(key, '\t');
			value = supLastElement(value, ' ');
			value = supLastElement(value, '\t');

			key = supFirstElement(key, '\"');
			key = supLastElement(key, '\"');


			if (value.at(value.length() - 1) == ',')
				value = value.substr(0, value.length() - 1);
			if (value.at(0) == '\"')
				value = value.substr(1);
			if (value.at(value.length() - 1) == '\"')
				value = value.substr(0, value.length() - 1);

			value = replace(value, "\\\"", "\"");
			value = replace(value, "\\\'", "\'");
			value = replace(value, "\\\t", "\t");
			value = replace(value, "\\n", "\n");

			data[key] = value;
		}
	}

	int length()
	{
		return data.size();
	}

	bool contains(std::string key)
	{
		if(data.find(key) != data.end())
			return true;
		else
			return false;
	}

	bool asSpecialChar(const std::string& str)
	{
		std::string specialChars = " !@#$%^&*():;,?./\\§&#'{[|`^à@)]°=+}\"";
		size_t found = str.find_first_of(specialChars);

		if(found != std::string::npos)
			return false;
		else
			return true;
	}
	bool asLeters(const std::string& str, std::string leters)
	{
		size_t found = str.find_first_of(leters);

		if(found != std::string::npos)
			return false;
		else
			return true;
	}

	std::map<std::string, std::string> getData()
	{
		return data;
	}
	
	//operator
	std::string& operator[](const std::string& key)
	{
		if (!asSpecialChar(key))
		{
			std::cerr << "forbids letter special characters in key : " << key << std::endl;
			exit(0);
		}else
			return data[key];
	}
};
#include "Verif.hpp"

void JsonNode::write(const char* path)
{
	init(path);

	std::ofstream file(path);

	if(file.is_open())
	{
		auto it = data.begin();

		file << "{";

		for (const auto& pair : data)
		{
			std::string value = pair.second;
			std::string key = pair.first;


			value = replace(value, "\"", "\\\"");
			value = replace(value, "\'", "\\\'");
			value = replace(value, "\t", "\\\t");
			value = replace(value, "\n", "\\n");
				
				
			if (value == "")
				value = "null";

			if (isInt(value) != 0 || isFloat(value) != 0 || isBool(value) != -1)
			{
				file << "\"" << key << "\": " << value;
			}else
			{
				file << "\"" << key << "\": \"" << value << "\"";
			}

			++it;

			if (it != data.end())
			{
				file << ", ";
			}
		}

		file << "}";

		file.close();
	}else
	{
		std::cerr << "error to open file : " << path << std::endl;
		exit(0);
	}
}

#endif