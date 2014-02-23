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
	std::map<const char *, func>::iterator it = _components.find(cmd.c_str());
	va_list vl;

	/*if (it == _fcts.end())
	throw exception */
	bool r;
	va_start(vl, cmd);
	r = (*this.*(it->second))(vl);
	va_end(vl);
	return r;
}
