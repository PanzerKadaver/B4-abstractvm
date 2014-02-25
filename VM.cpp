#include <iostream>

#include "VM.hpp"
#include "IO.hpp"
#include "Chipset.hpp"
#include "CPU.hpp"

VM::VM()
{
	_modules.insert(_modules.end(), std::make_pair("IO", new IO(*this)));
	_modules.insert(_modules.end(), std::make_pair("Chipset", new Chipset(*this)));
	_modules.insert(_modules.end(), std::make_pair("CPU", new CPU(*this)));
	//_modules["StackMemory"];
	_modules.insert(_modules.end(), std::make_pair("unknown", static_cast<IModule *>(NULL)));
}

IModule &VM::getModule(const std::string &mod) const
{
	std::map<const char *, IModule *>::const_iterator start = _modules.begin();
	std::map<const char *, IModule *>::const_iterator end = _modules.end();

	std::cout << "Get module [" << mod << "]" << std::endl;
	while (start != end && mod.compare(start->first) != 0)
		++start;
	/*if (it == _modules.end())
	throw exception */
	return *(start->second);
}
