#include <iostream>

#include "VM.hpp"
#include "IO.hpp"
#include "Chipset.hpp"
#include "CPU.hpp"
#include "StackMemory.hpp"
#include "Exception.hpp"

VM::VM()
{
	_modules["IO"] = new IO(*this);
	_modules["Chipset"] = new Chipset(*this);
	_modules["CPU"] = new CPU(*this);
	_modules["StackMemory"] = new StackMemory(*this);
}

IModule &VM::getModule(const char *mod) const
{
	std::map<const char *, IModule *>::const_iterator it = _modules.find(mod);

	std::cout << "Get module [" << mod << "]" << std::endl;
	try
	{
		if (it == _modules.end())
			throw Exception("Invalid module");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x01);
	}
	return *(it->second);
}
