#ifndef ABSTRACTVM_IO
# define ABSTRACTVM_IO

# include <cstdarg>

# include "VM.hpp"
# include "AModule.hpp"

class IO : public AModule
{
public:
	IO(VM &);
	~IO(void) {};

private:

};


#endif // !ABSTRACTVM_IO
