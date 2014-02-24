#include "IO.hpp"
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include "IOperand.hpp"
#include "SCommandMaker.hpp"
#include "SOperandMaker.hpp"


IO::IO(VM &vm_ref) :
	AModule(vm_ref, "IO")
{
  exec("init_instr_map");
  exec("init_type_map");


  _components["Unknown"] = NULL;
}

bool	IO::init_instr_map(va_list &args)
{
  instr_map["push"] = true;
  instr_map["assert"] = true;
  instr_map["pop"] = false;
  instr_map["dump"] = false;
  instr_map["add"] = false;
  instr_map["mul"] = false;
  instr_map["div"] = false;
  instr_map["mod"] = false;
  instr_map["sub"] = false;
  instr_map["print"] = false;
  instr_map["exit"] = false;
  instr_map["unknown"] = false;

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

bool            IO::parser(va_list &args)
{
  int i = 0;
  std::string                   token;

  if (commandline.length() >= 0)                                                                                
    return false;

  while (commandline[i])
    {
      if (commandline[i] == ';' && commandline[i+1] != ';') // if commentary, copy all from ';' in a token and break
        {
	  std::cout << "in com cuz of [" << commandline[i] << "]"<< std::endl;
          while (commandline[i])
            token += commandline[i++];
          commandtab.push_back(token.c_str());
          break;
        }

      if (commandline[i] != ' ' && commandline[i] != '\t') // if not space nor tab, copy in token                    
        token += commandline[i];

      if (commandline[i] == ' ' || commandline[i] == '\t' // if end of token, push token in tab                      
          || commandline[i+1] == '(' || commandline[i] == '('
          || commandline[i+1] == ')' || commandline[i] == ')'
          || commandline[i+1] == '\0')
        {
	  std::cout << "tokened' success" << std::endl; // DEBUG                                                     
          commandtab.push_back(token.c_str());
          token.clear();
        }
      i++;
    }
}

bool		IO::is_digit(va_list &args)
{
  int	c = va_arg(args, int);
  int	*p = va_arg(args, int*);

  if (c >= '0' && c <= '9')
    *p = 0;
  else if (c == '.')
    *p = 1;
  *p = -1;
}

bool            IO::check_value(va_list &args)
{
  int           i = 0;
  int		ret = 0;
  bool          is_dec = false;
  const char	*token = va_arg(args, char *);

  if (token[i] == '-')
    i++;

  for (int j = i; token[j] != '\0'; j++)
    {
      exec("is_digit", (int)token[i], &ret);
      if (ret == -1)
        return false; // NON DIGIT VALUE                                                                             
      if (ret == 1 && is_dec == false)
        is_dec = true;
      else if (ret == 1 && is_dec == true)
        return false; // NON DIGIT VALUE (TOO MUCH '.')                                                              
      i++;
    }
  return true;
}

bool            IO::token_is_ok(va_list &args)
{
 /*check if token, whatever is type, is correct*/

  const char *getToken = va_arg(args, const char *);
  std::string token(getToken);


  bool                                  is_ok = false;
  std::map<std::string, bool>::iterator it;

  it = instr_map.find(token);
  if (it != instr_map.end()) // if token is INSTR                                                                        
    {
      std::cout << "token [" << token << "] found as INSTR" << std::endl; // DEBUG                                   
      is_ok = true;
    }

  it = types_map.find(token);
  if (it != types_map.end() && is_ok == false) // if token is TYPE                                                       
    {
      std::cout << "token [" << token << "] found as TYPE" << std::endl; // DEBUG                                    
      is_ok = true;
    }

  if (is_ok == false) // if not INSTR nor TYPE, check if VALUE                                                       
    if ((exec("check_value", token.c_str())) == true)
      {
	std::cout << "token [" << token << "] found as VALUE" << std::endl; // DEBUG                                 
        is_ok = true;
      }

  if ((token == "(" || token == ")") && is_ok == false) // if token is PARENTHESIS                                   
    {
      std::cout << "token [" << token << "] found as PARENTHESIS" << std::endl; // DEBUG                           
      is_ok = true;
    }

  if (token[0] == ';' && is_ok == false)
    {
      std::cout << "token [" << token << "] found as COMM" << std::endl; // DEBUG                                  
      is_ok = true;
    }


  if (is_ok == false)
    std::cout << "token [" << token << "] not found as OK TOKEN" << std::endl; // DEBUG                              
  /* exception BAD SYNTAX */
}

bool            IO::token_order(va_list &args)
{
  int   i = 0;
  //  std::vector<std::string> commandtab = va_arg(args, std::string); // seems not to be usefull anymore with the class
  std::map<std::string, bool>::iterator it;


  it = instr_map.find(commandtab[i++]); // got an iterator to the right INSTR                                            

  if (commandtab.size() == 1) // it MUST BE an INSTR like PUSH or ASSERT                                             
    {
      if (it->second == true)
	std::cout << "bad syntax 1 (bad instr (cant be push or assert))" << std::endl; // exception UNEXPECTED TOKEN
    }
  else
    {
      if (it->second == false)
	std::cout << "bad syntax 2 (bad instr, must be push or assert)" << std::endl; // exception UNEXPECTED TOKEN  

      it = types_map.find(commandtab[i++]); // got an iterator to the right INSTR                                        
      if (it == types_map.end())
	std::cout << "bad syntax 3 (type not found)" << std::endl; // exception UNEXPECTED TOKEN                     

      if (commandtab[i++][0] != '(')
	std::cout << "bad syntax 4 (must be '(') " << std::endl; // exception UNEXPECTED TOKEN                       

      if ((exec("check_value", commandtab[i++])) == false)
	std::cout << "bad syntax 5 (bad value) " << std::endl; // exception UNEXPECTED TOKEN                         

      std::cout << "AV" << std::endl;

      if (commandtab[i][0] != ')')
	std::cout << "bad syntax 6 (must be ')') " << std::endl; // exception UNEXPECTED TOKEN                       

      std::cout << "AF" << std::endl;

      if (commandtab.size() == 6 && commandtab[i][0] != ';')
	std::cout << "bad syntax 6 (must be comm) " << std::endl; // exception UNEXPECTED TOKEN                      
    }

}

bool            IO::lexer(va_list &args)
{
  int len = commandtab.size();

  if (len != 1 && len != 5 && len != 6)
    std::cout << "\n***bad syntax CODE ZERO***\n" << std::endl; // DEBUG   /*exception BAD SYNTAX*/

  /* check if token, whatever is type, is correct */
  for_each(commandtab.begin(), commandtab.end(), exec("token_is_ok"));

  exec("token_order");  /* check if token syntax is ok */

}

/*DEBUG FUNK*/
bool		printit(va_list &args)
{
  const char *getStr = va_arg(args, char*);

  std::string str(getStr);



  std::cout << "token [" << str << "]"<< std::endl;
}
/*DEBUG FUNK*/

bool            IO::jarvis(va_list &args)
{
  int	ac = va_arg(args, int);
  char	**av = va_arg(args, char**);

  while (1)
    {
      commandline.clear();
      std::getline(std::cin, commandline);
      if (commandline == ";;")
        break;
      
      exec("parser");

      for_each(commandtab.begin(), commandtab.end(), exec("printit")); // DEBUG

      exec("lexer");

    }
}

int main(int ac, char **av)
{
  /* check ctr+d ?, check ac/av */

  VM	_vm;

  _vm.getModule("IO").exec("jarvis", ac, av);

}
