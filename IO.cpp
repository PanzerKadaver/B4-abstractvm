#include "IO.hpp"


IO::IO(VM &vm_ref) :
	AModule(vm_ref, "IO")
{
	_components["Unknown"] = NULL;
}
