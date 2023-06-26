#include <iostream>
#include <fstream>
#include <vector>

#include "Json.hpp"

int main(int argc, char const *argv[])
{
	JsonNode node;
	
	/*node["string"] = "hello: \"hi\"";
	node["char"] = "f";
	node["bool"] = "true";
	node["int"] = "100";
	node["float"] = "189.0865";

	node.write("data.json");*/

	node.read("data.json");

	std::map<std::string, std::string> map = toMapString(node["testmap"]);

	std::cout << toString(map) << std::endl;

	for (const auto& pair : node.getData())
	{
		std::cout << pair.first << " : '" << pair.second << "'" << std::endl;
	}

	return 0;
}