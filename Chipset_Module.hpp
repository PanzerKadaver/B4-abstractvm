#ifndef ABSTRACTVM_CHIPSET_MODULE
# define ABSTRACTVM_CHIPSET_MODULE

# include <cstdarg>
# include <queue>
# include <utility>

# include "VM.hpp"
# include "AModule.hpp"

class Chipset_Module :	public AModule
{
public:
	Chipset_Module(VM &);
	~Chipset_Module(void) {};

private:
	typedef std::pair<const char *, std::pair<const char *, const char *>> cmd_type;
	typedef cmd_type *cmd_ptr;

	std::queue<cmd_type> _cmdsQueue;

	bool	push(va_list &);
	bool	pop(va_list &);
	bool	get(va_list &);
	bool	next(va_list &);
	bool	run(va_list &);
};


#endif // !ABSTRACTVM_CHIPSET_MODULE
