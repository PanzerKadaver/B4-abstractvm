#include <iostream>
#include <sstream>
#include <cstdlib>

#include "CPU.hpp"
#include "SOperandMaker.hpp"
#include "Exception.hpp"


CPU::CPU(VM &vm_ref) :
	AModule(vm_ref, "CPU")
{
	_components["run"] = reinterpret_cast<AModule::func>(&CPU::run);
	_components["type"] = reinterpret_cast<AModule::func>(&CPU::type);
	_components["push"] = reinterpret_cast<AModule::func>(&CPU::push);
	_components["pop"] = reinterpret_cast<AModule::func>(&CPU::pop);
	_components["dump"] = reinterpret_cast<AModule::func>(&CPU::dump);
	_components["assert"] = reinterpret_cast<AModule::func>(&CPU::assert);
	_components["doop"] = reinterpret_cast<AModule::func>(&CPU::doop);
	_components["add"] = reinterpret_cast<AModule::func>(&CPU::add);
	_components["sub"] = reinterpret_cast<AModule::func>(&CPU::sub);
	_components["mul"] = reinterpret_cast<AModule::func>(&CPU::mul);
	_components["div"] = reinterpret_cast<AModule::func>(&CPU::div);
	_components["mod"] = reinterpret_cast<AModule::func>(&CPU::mod);
	_components["print"] = reinterpret_cast<AModule::func>(&CPU::print);
	_components["exit"] = reinterpret_cast<AModule::func>(&CPU::exit);

	_types["int8"] = Int8;
	_types["int16"] = Int16;
	_types["int32"] = Int32;
	_types["float"] = Float;
	_types["double"] = Double;
}

bool	CPU::run(va_list *args)
{
	cmd_type cmd = *va_arg(*args, cmd_ptr);

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

bool	CPU::type(va_list *args)
{
	std::string type_name(va_arg(*args, const char *));
	eOperandType *eType = va_arg(*args, eOperandType *);
	type_map::iterator it = _types.find(type_name);

	try
	{
		if (it == _types.end())
			throw Exception("Invalid operand type");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		::exit(0x31);
	}
	*eType = it->second;
	return true;
}

bool	CPU::push(va_list *args)
{
	IOperand *op = va_arg(*args, IOperand *);

	/*if (op == NULL)
	throw exception */
	_vm.getModule("StackMemory").exec("push", op);
	return true;
}

bool	CPU::pop(va_list *args)
{
	IOperand **op = va_arg(*args, IOperand **);

	_vm.getModule("StackMemory").exec("pop", op);
	return true;
}

bool	CPU::dump(va_list *args)
{
	(void)args;
	_vm.getModule("StackMemory").exec("dump");
	return true;
}

bool	CPU::assert(va_list *args)
{
	IOperand *op = va_arg(*args, IOperand *);
	IOperand *top = NULL;

	_vm.getModule("StackMemory").exec("front", &top);
	try
	{
		if (op->toString().empty() && top->getType() == op->getType())
			return true;
		else if (op->toString() == top->toString() && top->getType() == op->getType())
			return true;
		else
			throw Exception("Assertion fail");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		::exit(0x32);
	}
	return true;
}

bool	CPU::doop(va_list *args)
{
	IOperand **left = va_arg(*args, IOperand **);
	IOperand **right = va_arg(*args, IOperand **);

	try
	{
		size_t	size;

		_vm.getModule("StackMemory").exec("size", &size);
		if (size < 2)
			throw Exception("Unable to do op with less than 2 value");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		::exit(0x33);
	}
	exec("pop", right);
	exec("pop", left);
	return true;
}

bool	CPU::add(va_list *args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("doop", &left, &right);
	result = (*left + *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::sub(va_list *args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("doop", &left, &right);
	result = (*left - *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::mul(va_list *args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("doop", &left, &right);
	result = (*left * *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::div(va_list *args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("doop", &left, &right);
	result = (*left / *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::mod(va_list *args)
{
	IOperand *left = NULL;
	IOperand *right = NULL;
	IOperand *result = NULL;

	(void)args;
	exec("doop", &left, &right);
	result = (*left % *right);
	delete left;
	delete right;
	exec("push", result);
	return true;
}

bool	CPU::print(va_list *args)
{
	IOperand *test8 = SOperandMaker::createOperand(Int8, "");
	IOperand *top = NULL;
	int16 c;

	(void)args;
	exec("assert", test8);
	_vm.getModule("StackMemory").exec("front", &top);
	std::istringstream t_ss(top->toString());
	t_ss >> c;
	std::cout << static_cast<char>(c) << std::endl;
	return true;
}

bool	CPU::exit(va_list *args)
{
	(void)args;
	_vm.exit();
	return true;
}
