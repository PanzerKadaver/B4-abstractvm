#ifndef ABSTRACTVM_IO
# define ABSTRACTVM_IO

# include <vector>
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
  std::string			commandline;
  std::vector<const char *>	commandtab;

  bool		init_instr_map(va_list &);
  bool		init_type_map(va_list &);
  bool		parser(va_list &);
  bool		jarvis(va_list &);
  bool		lexer(va_list &);
  bool		token_is_ok(va_list &);
  bool		is_digit(va_list &);
  bool		check_value(va_list &);
  bool		token_order(va_list &);

  bool		printit(va_list &); // DEBUG FUNK

};


#endif // !ABSTRACTVM_IO
