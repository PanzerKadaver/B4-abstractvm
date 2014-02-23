#include "IO.hpp"


IO::IO(VM &vm_ref) :
	AModule(vm_ref, "IO")
{
  exec("init_instr_map");
  exec("init_type_map");


  _components["Unknown"] = NULL;
}

bool	IO::init_instr_map(va_list &args)
{
  mymap["push"] = true;
  mymap["assert"] = true;
  mymap["pop"] = false;
  mymap["dump"] = false;
  mymap["add"] = false;
  mymap["mul"] = false;
  mymap["div"] = false;
  mymap["mod"] = false;
  mymap["sub"] = false;
  mymap["print"] = false;
  mymap["exit"] = false;
  mymap["unknown"] = false;

  return true;
}

bool            IO::init_type_map(va_list &args)
{
  types_map["int8"] = false;
  types_map["int16"] = false;
  types_map["int32"] = false;
  types_map["float"] = true;
  types_map["double"] = true;
  types_map["unknown"] = false;

  return true;
}
