#ifndef ABSTRACTVM_STACKMEMORY_HPP_
# define ABSTRACTVM_STACKMEMORY_HPP_

# include <stack>

# include "AModule.hpp"
# include "IOperand.hpp"

class StackMemory :	public AModule
{
public:
	StackMemory(VM &);
	~StackMemory(void) {};

private:
	std::stack<IOperand *> _stack;

	bool	push(va_list *);
	bool	pop(va_list *);
	bool	dump(va_list *);
	bool	front(va_list *);
	bool	size(va_list *);
};

#endif // !ABSTRACTVM_STACKMEMORY_HPP_
