#include "IO_Module.hpp"


IO_Module::IO_Module(VM &vm_ref) :
	AModule(vm_ref, "IO")
{
	_components["Unknown"] = NULL;
}

