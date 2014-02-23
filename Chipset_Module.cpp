#include "Chipset_Module.hpp"


Chipset_Module::Chipset_Module(VM &vm_ref) :
	AModule(vm_ref, "Chipset")
{
	_components["push"] = static_cast<AModule::func>(&Chipset_Module::push);
	_components["pop"] = static_cast<AModule::func>(&Chipset_Module::pop);
	_components["get"] = static_cast<AModule::func>(&Chipset_Module::get);
	_components["next"] = static_cast<AModule::func>(&Chipset_Module::next);
	_components["run"] = static_cast<AModule::func>(&Chipset_Module::run);
	_components["Unknown"] = NULL;
}

bool	Chipset_Module::push(va_list &args)
{
	const std::string cmd_name = va_arg(args, const std::string);
	const std::string type_name = va_arg(args, const std::string);
	const std::string value_name = va_arg(args, const std::string);
	std::pair<const char *, const char *> params;
	std::pair<const char *, std::pair<const char *, const char *>> cmd;
	
	params = std::make_pair(type_name.c_str(), value_name.c_str());
	cmd = std::make_pair(cmd_name.c_str(), params);
	_cmdsQueue.push(cmd);
	return true;
}

bool	Chipset_Module::pop(va_list &args)
{
	_cmdsQueue.pop();
	return true;
}

bool	Chipset_Module::get(va_list &args)
{
	cmd_ptr	cmd;

	cmd = va_arg(args, cmd_ptr);
	if (_cmdsQueue.empty())
		return false;
	*cmd = _cmdsQueue.front();
	return true;
}

bool	Chipset_Module::next(va_list &args)
{
	cmd_type next_cmd;

	if (!exec("get", &next_cmd))
		return false;
	_vm.getModule("CPU").exec("run", next_cmd);
	exec("pop");
	return true;
}

bool	Chipset_Module::run(va_list &args)
{
	while (exec("next")) {}
	return true;
}
