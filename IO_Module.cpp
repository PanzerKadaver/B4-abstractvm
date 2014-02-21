#include "IO_Module.hpp"


IO_Module::IO_Module(VM &vm_ref) :
	_vm(vm_ref),
	_name("IO")
{
	_fcts["parseFile"] = &IO_Module::parseFile;
	_fcts["parseCin"] = &IO_Module::parseCin;
	_fcts["Unknown"] = NULL;
}

const std::string	&IO_Module::name() const
{
	return _name;
}

bool	IO_Module::exec(const std::string &cmd, ...)
{
	std::map<const char *, func>::iterator it = _fcts.find(cmd.c_str());
	va_list vl;

	if (it != _fcts.end())
	{
		bool r;
		va_start(vl, cmd);
		r = (*this.*(it->second))(vl);
		va_end(vl);
		return r;
	}
	/* else
	throw exception*/
}

bool	IO_Module::parseFile(va_list &vl)
{
	return false;
}

bool	IO_Module::parseCin(va_list &vl)
{
	return false;
}
