#ifndef ABSTRACTVM_IO_MODULE
# define ABSTRACTVM_IO_MODULE

# include <cstdarg>

# include "IModule.hpp"
# include "VM.hpp"

class IO_Module : public IModule
{
public:
	IO_Module(VM &);
	~IO_Module(void) {};

	const std::string &name(void) const;
	bool exec(const std::string &, ...);

private:
	typedef	bool (IO_Module::*func)(va_list &);

	VM				&_vm;
	std::string		_name;
	std::map<const char *, func> _fcts;

	bool	parseFile(va_list &);
	bool	parseCin(va_list &);
};


#endif // !ABSTRACTVM_IO_MODULE
