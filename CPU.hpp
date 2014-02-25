#ifndef ABSTRACTVM_CPU
# define ABSTRACTVM_CPU

# include "VM.hpp"
# include "AModule.hpp"
# include "IOperand.hpp"

class CPU : public AModule
{
public:
	CPU(VM &);
	~CPU(void) {};

private:
	typedef std::pair<const char *, std::pair<const char *, const char *> > cmd_type;
	typedef cmd_type *cmd_ptr;
	typedef std::map<const char *, eOperandType> type_map;

	type_map _types;

	bool	run(va_list &);
	bool	type(va_list &);
	bool	push(va_list &);
	bool	pop(va_list &);
	bool	dump(va_list &);
	bool	assert(va_list &);
	bool	add(va_list &);
	bool	sub(va_list &);
	bool	mul(va_list &);
	bool	div(va_list &);
	bool	mod(va_list &);
	bool	print(va_list &);
	bool	exit(va_list &);
};

#endif // !ABSTRACTVM_CPU
