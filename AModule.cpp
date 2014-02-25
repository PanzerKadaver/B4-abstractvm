#include <iostream>

#include "AModule.hpp"


AModule::AModule(VM &vm_ref, const std::string &name) :
	_vm(vm_ref),
	_name(name)
{
}

const std::string &AModule::name() const
{
	return _name;
}

bool AModule::exec(const std::string &cmd, ...)
{
	std::map<const char *, AModule::func>::iterator start = _components.begin();
	std::map<const char *, AModule::func>::iterator end = _components.end();
	va_list vl;

	std::cout << cmd.c_str() << std::endl;
	while (start != end && cmd.compare(start->first) != 0)
		++start;
	/*if (it == _fcts.end())
	throw exception */
	bool r;
	va_start(vl, cmd);
	r = (*this.*(start->second))(vl);
	va_end(vl);
	return r;
}
