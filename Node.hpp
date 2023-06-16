#ifndef JSON_NODE_HPP
#define JSON_NODE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>

#include "Parser.hpp"
#include "Verif.hpp"

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

		if (line.at(0) == '{')
			return true;
		else
			return false;
	}

	void write(const char* path, bool isLisibleForHuman)
	{
		init(path);

		std::ofstream file(path);

		if(file.is_open())
		{
			auto it = data.begin();

			if (isLisibleForHuman)
				file << "{" << std::endl;
			else
				file << "{";

			for (const auto& pair : data)
			{
				std::string value = pair.second;
				std::string key = pair.first;


				value = replace(value, "\"", "\\\"");
				value = replace(value, "\'", "\\\'");
				value = replace(value, "\t", "\\\t");
				value = replace(value, "\n", "\\n");
				
				if (isLisibleForHuman)
				{
					if (value == "")
						value = "null";

					if (isInt(value) != 0 || isFloat(value) != 0 || isBool(value) != -1)
					{
						file << "\t\"" << key << "\": " << value;
					}else
					{
						file << "\t\"" << key << "\": \"" << value << "\"";
					}

					++it;

					if (it != data.end())
					{
						file << "," << std::endl;
					}else{
						file << std::endl;
					}
				}else
				{
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
			}

			file << "}";

			file.close();
		}else
		{
			std::cerr << "error to open file : " << path << std::endl;
			exit(0);
		}
	}

	void read(const char* path)
	{
		std::ifstream file(path);

		if (file.is_open()) {
			std::string line;
			int i = 0;
			int isLisibleForHuman = -2;

			while (std::getline(file, line)) {
				if (i == 0)
					isLisibleForHuman = isLFH(line);

				if (isLisibleForHuman)
				{
					if (line.at(0) != '}' && line.at(0) != '{')
					{
						line = supFirstElement(line, ' ');
						line = supFirstElement(line, '\t');

						std::vector<std::string> l = split(line.c_str(), ':');

						std::string key = l[0];
						l.erase(l.begin());

						std::string value = join(l, ":");


						//sublime data
						value = supFirstElement(value, ' ');

						key = supFirstElement(key, '\"');
						key = supLastElement(key, '\"');

						value = supFirstElement(value, ' ');
						value = supFirstElement(value, '\t');


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
				}else
				{

				}

				if (isLisibleForHuman != -1)
					i++;
			}

			file.close();
		} else {
			std::cerr << "Erreur lors de l'ouverture du fichier : " << path << std::endl;
			exit(0);
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

#endif