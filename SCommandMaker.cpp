#include <iostream> // DEBUG

#include "SCommandMaker.hpp"
#include "Commands.hpp"

std::map<const char *, SCommandMaker::func> SCommandMaker::initMap()
{
	std::map<const char *, func> map;

	std::cout << "Init map" << std::endl; // DEBUG
	map["push"] = NULL;
	map["pop"] = NULL;
	map["dump"] = NULL;
	map["assert"] = NULL;
	map["add"] = &Commands::Add;
	map["sub"] = &Commands::Sub;
	map["mul"] = &Commands::Mul;
	map["div"] = &Commands::Div;
	map["mod"] = NULL;
	map["print"] = NULL;
	map["exit"] = NULL;

	return map;
}

SCommandMaker::func SCommandMaker::getCommand(const std::string &cmd)
{
	static std::map<const char *, func> commands = SCommandMaker::initMap();
	std::map<const char *, func>::iterator it = commands.find(cmd.c_str());

	if (it == commands.end() && cmd.compare(it->first) != 0)
		return NULL;
	else
		return it->second;
}
