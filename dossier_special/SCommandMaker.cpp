#include <iostream> // DEBUG

#include "SCommandMaker.hpp"
#include "Commands.hpp"

std::map<const char *, SCommandMaker::func> SCommandMaker::initMap()
{
	std::map<const char *, func> map;

	std::cout << "Init map IN SCOMMAND" << std::endl; // DEBUG
	map["push"] = &Commands::Push;
	map["pop"] = &Commands::Pop;
	map["dump"] = &Commands::Dump;
	map["assert"] = &Commands::Assert;
	map["add"] = &Commands::Add;
	map["sub"] = &Commands::Sub;
	map["mul"] = &Commands::Mul;
	map["div"] = &Commands::Div;
	map["mod"] = &Commands::Mod;
	map["print"] = &Commands::Print;
	map["exit"] = &Commands::Exit;

	std::cout << "OUT OF INIT MAP IN SCOMMAND" << std::endl; // DEBUG

	return map;
}

SCommandMaker::func SCommandMaker::getCommand(const std::string &cmd)
{
	static std::map<const char *, func> commands = SCommandMaker::initMap();
	std::map<const char *, func>::iterator it = commands.find(cmd.c_str());

	std::cout << "IN GETCOMMAND [" << cmd << "]" << std::endl; // DEBUG
	std::cout << "[" << it->first << "]" << std::endl; // DEBUG

	if (it == commands.end() && cmd.compare(it->first) != 0)
		return NULL;
	else
		return it->second;
}
