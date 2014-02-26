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

bool AModule::exec(const char *cmd, ...)
{
	std::map<const char *, AModule::func>::iterator start = _components.begin();
	std::map<const char *, AModule::func>::iterator end = _components.end();
	va_list vl;
	const std::string s_cmd(cmd);

	std::cout << "Exec function [" << s_cmd << "]" << std::endl;
	while (start != end && s_cmd.compare(start->first) != 0)
		++start;
	/*if (it == _fcts.end())
	throw exception */
	bool r;
	va_start(vl, cmd);
	r = (*this.*(start->second))(&vl);
	va_end(vl);
	return r;
}
