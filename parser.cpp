# include <cctype>

#include "parser.hpp"

int	isblank(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	return 0;
}

std::string	epur(std::string &str)
{
	int		i = 0;
	std::string	epur_str;

	while (isblank(str[i]))
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

/* function getline in file */

int		main(int ac, char **av)
{
	int		ret;
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
			else if (str.length() > 0 && (ret = check_str(str)) > 0)
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
					enumInStr = ret_type(str); /* get the known type */
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
