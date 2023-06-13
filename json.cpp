#include <iostream>
#include <fstream>
#include <vector>

#include "Json.hpp"

int main(int argc, char const *argv[])
{
	JsonNode node;
	
	node["string"] = "hello";
	node["char"] = "f";
	node["bool"] = "true";
	node["int"] = "100";
	node["float"] = "189.0865";

	node.write("data.json", true);

	return 0;
}