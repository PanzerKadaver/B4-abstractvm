#include "VM.hpp"
#include "IO_Module.hpp"

VM::VM()
{
	_modules["IO"] = new IO_Module(*this);
	_modules["Chipset"];
	_modules["CPU"];
	_modules["StackMemory"];
	_modules["Unknown"] = NULL;
}

IModule &VM::getModule(const std::string &mod) const
{
	std::map<const char *, IModule *>::const_iterator it = _modules.find(mod.c_str());

	/*if (it == _modules.end())
	throw exception */
	return *(it->second);
}
