#ifndef ABSTRACTVM_IO_MODULE
# define ABSTRACTVM_IO_MODULE

# include <cstdarg>

# include "VM.hpp"
# include "AModule.hpp"

class IO_Module : public AModule
{
public:
	IO_Module(VM &);
	~IO_Module(void) {};

private:

};


#endif // !ABSTRACTVM_IO_MODULE
