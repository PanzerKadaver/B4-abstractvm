#include <iostream>
#include <sstream>

#include "CPU.hpp"
#include "SOperandMaker.hpp"


CPU::CPU(VM &vm_ref) :
	AModule(vm_ref, "CPU")
{
	_components["push"] = reinterpret_cast<AModule::func>(&CPU::push);
	_components["pop"];
	_components["dump"];
	_components["assert"];
	_components["add"];
	_components["sub"];
	_components["mul"];
	_components["div"];
	_components["mod"];
	_components["print"];
	_components["exit"];
	_components["Unknown"] = NULL;

	_types["int8"] = Int8;
	_types["int16"] = Int16;
	_types["int32"] = Int32;
	_types["float"] = Float;
	_types["double"] = Double;
	_types["Unknown"] = Unknown;
}

bool	CPU::run(va_list &args)
{
	cmd_type cmd = *va_arg(args, cmd_ptr);

	std::string cmd_name(cmd.first);
	std::string type(cmd.second.first);
	std::string value(cmd.second.second);
	eOperandType eType;

	if (type.empty() && value.empty())
		exec(cmd_name.c_str(), NULL);
	else
	{
		exec("type", type.c_str(), &eType);
		IOperand *op = SOperandMaker::createOperand(eType, value);
		exec(cmd_name.c_str(), op);
	}
	return true;
}

bool	CPU::type(va_list &args)
{
	const char *type_name = va_arg(args, const char *);
	eOperandType *eType = va_arg(args, eOperandType *);
	type_map::iterator it = _types.find(type_name);

	/*if (it == _types.end())
	throw exeception */
	*eType = it->second;
	return true;
}

bool	CPU::push(va_list &args)
{
	IOperand *op = va_arg(args, IOperand *);

	/*if (op == NULL)
	throw exception */
	_vm.getModule("StackMemory").exec("push", op);
	return true;
}

bool	CPU::pop(va_list &args)
{
	IOperand *op = va_arg(args, IOperand *);

	_vm.getModule("StackMemory").exec("pop", op);
	return true;
}

bool	CPU::dump(va_list &args)
{
	(void)args;
	_vm.getModule("StackMemory").exec("dump");
	return true;
}

bool	CPU::assert(va_list &args)
{
	IOperand *op = va_arg(args, IOperand *);
	IOperand *top = NULL;

	_vm.getModule("StackMemory").exec("front", top);
	if (op->toString().empty() && top->getType() == op->getType())
		return true;
	else if (op->toString() == top->toString() && top->getType() == op->getType())
		return true;
	return false; // Throw exception
}

bool	CPU::add(va_list &args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("pop", right);
	exec("pop", left);
	result = (*left + *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::sub(va_list &args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("pop", right);
	exec("pop", left);
	result = (*left - *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::mul(va_list &args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("pop", right);
	exec("pop", left);
	result = (*left * *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::div(va_list &args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("pop", right);
	exec("pop", left);
	result = (*left / *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::mod(va_list &args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("pop", right);
	exec("pop", left);
	result = (*left % *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::print(va_list &args)
{
	IOperand *test8 = SOperandMaker::createOperand(Int8, "");
	IOperand *top = NULL;
	char c;

	(void)args;
	exec("assert", test8);
	_vm.getModule("StackModule").exec("front", top);
	std::istringstream t_ss(top->toString());
	t_ss >> c;
	/* to IO */
	return true;
}

bool	CPU::exit(va_list &args)
{
	(void)args;
	/* _vm.exit() */
	return true;
}
