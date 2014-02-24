#include "instr.hpp"

std::string	ret_value(const std::string &str)
{
  int		i;
  std::string	value;

  for (i = 0; str[i] != '('; i++);
  i++;
  for (i=i; str[i] != ')'; i++)  
    value += str[i];

  return value;
}

std::map<std::string, eOperandType>	init_type_map()
{
  std::map<std::string, eOperandType>	mymap;

  mymap["int8"] = Int8;
  mymap["int16"] = Int16;
  mymap["int32"] = Int32;
  mymap["float"] = Float;
  mymap["double"] = Double;

  return mymap;
}

eOperandType	get_type(std::string &typeInStr)
{
  static std::map<std::string, eOperandType>	types = init_type_map();
  std::map<std::string, eOperandType>::iterator	it = types.find(typeInStr);

  if (it == types.end() && typeInStr.compare(it->first) != 0)
    return Unknown;
  else
    return it->second;
}

eOperandType	ret_type(std::string &str)
{
  int		i;
  std::string	typeInStr;
  std::map<std::string, eOperandType> mymap;
  eOperandType	typeInEnum;

  for (i = 0; str[i] != ' '; i++);
  i++;
  for (i=i; str[i] != '('; i++)
    typeInStr += str[i];

  typeInEnum = get_type(typeInStr);
  /* faire exception sur type UNKNOWN */
  return (typeInEnum);
}

SCommandMaker::func	ret_cmd(std::string &str)
{
  int			i;
  std::string		cmdInStr;
  SCommandMaker::func	isFunk;

  std::cout << "IN RET CMD" << std::endl; // DEBUG

  for (i = 0; str[i] != ' ' && str[i]; i++)
    cmdInStr += str[i];

  std::cout << "WILL RETURN THIS CMD 4 FUNK [" << cmdInStr << "]" << std::endl; //DEBUG

  isFunk = SCommandMaker::getCommand(cmdInStr);
  /* faire exception sur NULL */
  return (isFunk);
}
