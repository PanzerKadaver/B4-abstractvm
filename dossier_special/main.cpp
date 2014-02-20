#include <iostream>
#include <string>
#include <queue>
#include <cctype>
#include <algorithm>
#include <map>
#include <utility>
#include "TOperand.hpp"
#include "Commands.hpp"
#include "IOperand.hpp"
#include "SCommandMaker.hpp"
#include "SOperandMaker.hpp"
#include "Trait.hpp"
#include <istream>

std::string	epur(std::string &str)
{
  int		i = 0;
  std::string	epur_str;

  while (isblank(str[i]) > 0 || str[i] == '\t')
    i++;
  while (str[i])
    {

      if (((isblank(str[i]) > 0) && isblank(str[i+1]) <= 0)
	  || isblank(str[i]) <= 0)
	epur_str += str[i++];
      else
	i++;
    }

  i = epur_str.length() - 1;
  while (epur_str[i] == ' ' || epur_str[i] == '\t')
    epur_str[i--] = '\0';

  return epur_str;
}

int		check_syntax(std::string &str)
{
  int		i;
  bool		dec = false;

  std::cout << "CHECK SYNTAX" << std::endl; // DEBUG

  i = str.length();
  if (i > 1 && str[0] == ';' && str[1] != ';')
    return 0;  /* that is a commentary */

  while (isalpha(str[i]) > 0)
    i++;
  if (str[i] == '\0')
    return 1; /* that is a simple instruction w/o params*/

  i++;
  while (isalnum(str[i]) > 0)
    i++;
  if (str[i] != '(')
    return -1; /* syntax error */
  while (isdigit(str[i]) > 0)
    {
      if (str[i] == '.' && dec == false)
	{
	  dec = true;
	  i++;
	}
      if (str[i] == '.' && dec == true)
	return -1;  /* syntax error */
      i++;
    }
  if (str[i] != ')' || str[i + 1] != '\0')
    return -1;  /* syntax error */
  return 2; /* that is complete instruction with params */
}

int		check_str(std::string &str)
{
  std::string	instr = epur(str);

  return (check_syntax(str));
}

/* push double(42.42) */

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

eOperandType	ret_type(std::string &str, eOperandType typelist)
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

/* function getline in file */

SCommandMaker::func	ret_cmd(std::string str)
{
  int			i;
  std::string		cmdInStr;
  SCommandMaker::func	isFunk;

  std::cout << "IN RET CMD" << std::endl; // DEBUG

  for (i = 0; str[i] != ' ' && str[i]; i++)
    cmdInStr += str[i];

  std::cout << "WILL RETURN THIS CMD 4 FUNK [" << cmdInStr << std::endl; //DEBUG

  isFunk = SCommandMaker::getCommand(cmdInStr);
  /* faire exception sur NULL */
  return (isFunk);
}

int		main(int ac, char **av)
{
  int		ret;
  eOperandType	typeEnum;
  eOperandType	enumInStr;
  std::string	str;
  std::map<std::string, eOperandType>				mymap;
  std::queue<std::pair<SCommandMaker::func, IOperand*> >	my_stack;

  if (ac != 2)
    while (1)
      {
	str.clear();
	std::getline(std::cin, str); // if ac == 2 else getline in a file
	if (str == ";;")
	  break;

	if (str.length() > 0 && (ret = check_str(str)) > 0)
	  {
	    std::pair<SCommandMaker::func, IOperand*>	mypair;
	    if (ret == 1) /*add, mul, div, dump, ...*/
	      {
		mypair = std::make_pair(ret_cmd(str), (IOperand*)NULL);
		my_stack.push(mypair);
	      }
	    else /* push, assert */
	      {
		std::cout << "ELSE IN WHILE" << std::endl;
		enumInStr = ret_type(str, typeEnum); /* get the known type */
		IOperand *new_op = SOperandMaker::createOperand(enumInStr, ret_value(str));
		my_stack.push(std::make_pair(ret_cmd(str), new_op));
	      }
	  }
	std::cout << ret << std::endl;
	// else if (ret < 0)
	//   /*
	//     exception bad syntax
	//    */	  
      }
}
