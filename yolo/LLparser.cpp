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

#define SEP	'\n'

// bool		parser(std::string commandline)
// {
//   int i = 0;
//   std::string			token;
//   std::vector<std::string>	commandtab;

//   // if (!(commandline.length() > 0))
//   //   return commandtab;

//   while (commandline[i])
//     {
//       if (commandline[i] == ';' && commandline[i+1] != ';') // if commentary, copy all from ';' in a token and break
// 	{
// 	  std::cout << "in com cuz of [" << commandline[i] << "]"<< std::endl;
// 	  while (commandline[i])
// 	    token += commandline[i++];
// 	  commandtab.push_back(token);
// 	  break;
// 	}

//       /* push int32(64) */

//       if (commandline[i] != ' ' && commandline[i] != '\t') // if not space nor tab, copy in token
// 	token += commandline[i];

//       if (commandline[i] == ' ' || commandline[i] == '\t' // if end of token, push token in tab
// 	  || commandline[i+1] == '(' || commandline[i] == '('
// 	  || commandline[i+1] == ')' || commandline[i] == ')'
// 	  || commandline[i+1] == '\0')
// 	{
// 	  std::cout << "tokened' success" << std::endl; // DEBUG
// 	  commandtab.push_back(token);
// 	  token.clear();
// 	}
//       i++;
//     }
// }




// /*DEBUG FUNK*/
// void printit(std::string str)
// {
//   std::cout << "token [" << str << "]"<< std::endl;
// }
// /*DEBUG FUNK*/

char		is_digit(char c)
{
  if (c >= '0' && c <= '9')
    return 0;
  else if (c == '.')
    return 1;
  return -1;
}

// bool		check_value(std::string &token)
// {
//   int		i = 0;
//   char		ret;
//   bool		is_dec = false;

//   if (token[i] == '-')
//     i++;

//   for (int j = i; token[j] != '\0'; j++)
//     {
//       ret = is_digit(token[i]);
//       if (ret == -1)
// 	return false; // NON DIGIT VALUE
//       if (ret == 1 && is_dec == false)
// 	is_dec = true;
//       else if (ret == 1 && is_dec == true)
// 	return false; // NON DIGIT VALUE (TOO MUCH '.')
//       i++;
//     }
//   return true;
// }

// bool		token_is_ok(std::string &token)
// {
//   /*check if token, whatever is type, is correct*/
//   bool					is_ok = false;
//   std::map<std::string, bool>::iterator	it;

//   it = instr_map.find(token);
//   if (it != instr.end()) // if token is INSTR
//     {
//       std::cout << "token [" << token << "] found as INSTR" << std::endl; // DEBUG
//       is_ok = true;
//     }
  
//   it = types.find(token);
//   if (it != types.end() && is_ok == false) // if token is TYPE
//     {
//       std::cout << "token [" << token << "] found as TYPE" << std::endl; // DEBUG 
//       is_ok = true;
//     }

//   if (is_ok == false) // if not INSTR nor TYPE, check if VALUE
//     if ((check_value(token)) == true)
//       {
// 	std::cout << "token [" << token << "] found as VALUE" << std::endl; // DEBUG
// 	is_ok = true;
//       }

//   if ((token == "(" || token == ")") && is_ok == false) // if token is PARENTHESIS
//       {
// 	std::cout << "token [" << token << "] found as PARENTHESIS" << std::endl; // DEBUG
// 	is_ok = true;
//       }

//   if (token[0] == ';' && is_ok == false)
//       {
// 	std::cout << "token [" << token << "] found as COMM" << std::endl; // DEBUG
// 	is_ok = true;
//       }


//   if (is_ok == false)
//     std::cout << "token [" << token << "] not found as OK TOKEN" << std::endl; // DEBUG
//      /* exception BAD SYNTAX */
// }

// bool		token_order(std::vector<std::string> commandtab)
// {
//   int	i = 0;
//   std::map<std::string, bool>::iterator	it;
//   static std::map<std::string, bool>	instr = init_instr_map();
//   static std::map<std::string, bool>	types = init_type_map();


//   it = instr.find(commandtab[i++]); // got an iterator to the right INSTR

//   if (commandtab.size() == 1) // it MUST BE an INSTR like PUSH or ASSERT
//     {
//       if (it->second == true)
// 	std::cout << "bad syntax 1 (bad instr (cant be push or assert))" << std::endl; // exception UNEXPECTED TOKEN
//     }
//   else
//     {
//       if (it->second == false)
// 	std::cout << "bad syntax 2 (bad instr, must be push or assert)" << std::endl; // exception UNEXPECTED TOKEN

//       it = types.find(commandtab[i++]); // got an iterator to the right INSTR      
//       if (it == types.end())
// 	std::cout << "bad syntax 3 (type not found)" << std::endl; // exception UNEXPECTED TOKEN	

//       if (commandtab[i++][0] != '(')
// 	std::cout << "bad syntax 4 (must be '(') " << std::endl; // exception UNEXPECTED TOKEN	

//       if ((check_value(commandtab[i++])) == false)
// 	std::cout << "bad syntax 5 (bad value) " << std::endl; // exception UNEXPECTED TOKEN	

//       std::cout << "AV" << std::endl;

//       if (commandtab[i][0] != ')')
// 	std::cout << "bad syntax 6 (must be ')') " << std::endl; // exception UNEXPECTED TOKEN	

//       std::cout << "AF" << std::endl;

//       if (commandtab.size() == 6 && commandtab[i][0] != ';')
// 	std::cout << "bad syntax 6 (must be comm) " << std::endl; // exception UNEXPECTED TOKEN	
//     }

// }

// bool		lexer(std::vector<std::string> commandtab)
// {
//   int len = commandtab.size();

//   if (len != 1 && len != 5 && len != 6)
//     std::cout << "\n***bad syntax CODE ZERO***\n" << std::endl; // DEBUG   /*exception BAD SYNTAX*/

 

//   for_each(commandtab.begin(), commandtab.end(), token_is_ok); /* check if token, whatever is type, is correct */
//   token_order(commandtab);  /* check if token syntax is ok */

// }

// bool		jarvis(int ac, char **av)
// {
//   std::string			commandline;
//   std::vector<std::string>	commandtab;

//   while (1)
//     {
//       commandline.clear();
//       std::getline(std::cin, commandline);
//       if (commandline == ";;")
// 	break;
//       commandtab = parser(commandline);

//       for_each(commandtab.begin(), commandtab.end(), printit); // DEBUG

//       lexer(commandtab);

//       chipset.push(commandtab[0], commandtab[1], commandtab[3]);

//     }

// }

// int main(int ac, char **av)
// {
//   /* check ac, av */
//   jarvis(ac, av);


//   /* check ctrl+d */
//   return 0;
// }
