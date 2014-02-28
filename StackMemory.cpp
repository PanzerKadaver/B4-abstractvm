#include <iostream>

#include "StackMemory.hpp"
#include "Exception.hpp"
#include "SOperandMaker.hpp"

StackMemory::StackMemory(VM &vm_ref) :
	AModule(vm_ref, "StackMemory")
{
	_components["push"] = reinterpret_cast<AModule::func>(&StackMemory::push);
	_components["pop"] = reinterpret_cast<AModule::func>(&StackMemory::pop);
	_components["dump"] = reinterpret_cast<AModule::func>(&StackMemory::dump);
	_components["front"] = reinterpret_cast<AModule::func>(&StackMemory::front);
	_components["size"] = reinterpret_cast<AModule::func>(&StackMemory::size);
}

bool	StackMemory::push(va_list *args)
{
	IOperand *op = va_arg(*args, IOperand *);

	_stack.push(op);
	return true;
}

bool	StackMemory::pop(va_list *args)
{
	IOperand **op = va_arg(*args, IOperand **);
	IOperand *front = NULL;

	try
	{
		if (_stack.size() == 0)
			throw Exception("Stack Error : pop on empty stack");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x40);
	}
	if (op == NULL)
		_stack.pop();
	else
	{
		exec("front", &front);
		*op = SOperandMaker::createOperand(front->getType(), front->toString());
		_stack.pop();
	}
	return true;
}

bool	StackMemory::dump(va_list *args)
{
	std::stack<IOperand *> _cpy_stack(_stack);

	while (!_cpy_stack.empty())
	{
		std::cout << _cpy_stack.top()->toString() << std::endl;
		_cpy_stack.pop();
	}
	return true;
}

bool	StackMemory::front(va_list *args)
{
	IOperand **op = va_arg(*args, IOperand **);

	*op = _stack.top();
	return true;
}

bool	StackMemory::size(va_list *args)
{
	size_t	*s = va_arg(*args, size_t *);

	*s = _stack.size();
	return true;
}
