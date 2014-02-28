#include <iostream>

#include "AModule.hpp"
#include "Exception.hpp"


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
	std::string s_cmd(cmd);
	std::map<std::string, AModule::func>::iterator it = _components.find(s_cmd);
	va_list vl;
	bool r = false;

	std::cout << "Exec function [" << s_cmd << "]" << std::endl;

	try
	{
		if (it == _components.end())
			throw Exception("Invalid function");
		
		va_start(vl, cmd);
		r = (*this.*(it->second))(&vl);
		va_end(vl);
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x02);
	}
	return r;
}
