#include "Chipset.hpp"


Chipset::Chipset(VM &vm_ref) :
	AModule(vm_ref, "Chipset")
{
	_components["push"] = reinterpret_cast<AModule::func>(&Chipset::push);
	_components["pop"] = reinterpret_cast<AModule::func>(&Chipset::pop);
	_components["get"] = reinterpret_cast<AModule::func>(&Chipset::get);
	_components["next"] = reinterpret_cast<AModule::func>(&Chipset::next);
	_components["run"] = reinterpret_cast<AModule::func>(&Chipset::run);
	_components["Unknown"] = NULL;
}

bool	Chipset::push(va_list &args)
{
	const char *cmd_name = va_arg(args, const char *);
	const char *type_name = va_arg(args, const char *);
	const char *value_name = va_arg(args, const char *);
	std::pair<const char *, const char *> params;
	std::pair<const char *, std::pair<const char *, const char *> > cmd;
	
	params = std::make_pair(type_name, value_name);
	cmd = std::make_pair(cmd_name, params);
	_cmdsQueue.push(cmd);
	return true;
}

bool	Chipset::pop(va_list &args)
{
	(void)args;
	_cmdsQueue.pop();
	return true;
}

bool	Chipset::get(va_list &args)
{
	cmd_ptr	cmd;

	(void)args;
	cmd = va_arg(args, cmd_ptr);
	if (_cmdsQueue.empty())
		return false;
	*cmd = _cmdsQueue.front();
	return true;
}

bool	Chipset::next(va_list &args)
{
	cmd_type next_cmd;

	(void)args;
	if (!exec("get", &next_cmd))
		return false;
	_vm.getModule("CPU").exec("run", &next_cmd);
	exec("pop");
	return true;
}

bool	Chipset::run(va_list &args)
{
	(void)args;
	while (exec("next")) {}
	return true;
}
