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
  std::map<std::string, bool>	instr_map;
  std::map<std::string, bool>	types_map;

  bool		init_instr_map(va_list &);
  bool		init_type_map(va_list &);
};


#endif // !ABSTRACTVM_IO
