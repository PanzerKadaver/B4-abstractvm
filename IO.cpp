#include "IO.hpp"
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Exception.hpp"
#include "IOperand.hpp"
#include "SOperandMaker.hpp"


IO::IO(VM &vm_ref) :
	AModule(vm_ref, "IO")
{
	_components["init_type_map"] = reinterpret_cast<AModule::func>(&IO::init_type_map);
	_components["init_instr_map"] = reinterpret_cast<AModule::func>(&IO::init_instr_map);	
	_components["parser"] = reinterpret_cast<AModule::func>(&IO::parser);
	_components["jarvis"] = reinterpret_cast<AModule::func>(&IO::jarvis);
	_components["lexer"] = reinterpret_cast<AModule::func>(&IO::lexer);
	_components["token_is_ok"] = reinterpret_cast<AModule::func>(&IO::token_is_ok);
	_components["is_digit"] = reinterpret_cast<AModule::func>(&IO::is_digit);
	_components["check_value"] = reinterpret_cast<AModule::func>(&IO::check_value);
	_components["token_order"] = reinterpret_cast<AModule::func>(&IO::token_order);

	exec("init_instr_map");
	exec("init_type_map");
}

bool	IO::init_instr_map(va_list *args)
{
	(void)args;
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

	return true;
}

bool IO::init_type_map(va_list *args)
{
	(void)args;
	types_map["int8"] = false;
	types_map["int16"] = false;
	types_map["int32"] = false;
	types_map["float"] = true;
	types_map["double"] = true;

	return true;
}

bool		IO::is_digit(va_list *args)
{
	int	c = va_arg(*args, int);
	int	*p = va_arg(*args, int*);

	if (c >= '0' && c <= '9')
		*p = 0;
	else if (c == '.')
		*p = 1;
	else
		*p = -1;
	return true;
}



bool IO::check_value(va_list *args)
{
	int i = 0;
	int		ret = 0;
	bool is_dec = false;
	const char	*token = va_arg(*args, char *);

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

bool IO::token_is_ok(va_list *args)
{
	/*check if token, whatever is type, is correct*/

	const char *getToken = va_arg(*args, const char *);
	std::string token(getToken);
	bool is_ok = false;
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
			return false;
		return true;
}

bool IO::token_order(va_list *args)
{
	int i = 0;
	int s = commandtab.size();
	// std::vector<std::string> commandtab = va_arg(args, std::string); // seems not to be usefull anymore with the class
	std::map<std::string, bool>::iterator it;

	(void)args;
	if (!(s == 1 || s == 2 || s == 5 || s == 6))
		return false;
	it = instr_map.find(commandtab[i++]); // got an iterator to the right INSTR

	if (s == 1 && it == instr_map.end() && commandtab[0][0] == ';')
		return true;

	if (s == 1 || s == 2) // it MUST BE an INSTR like PUSH or ASSERT
	{
		if (it->second == true)
			return false;
			//std::cout << "bad syntax 1 (bad instr (cant be push or assert))" << std::endl; // exception UNEXPECTED TOKEN
		if (s == 2 && commandtab[1][0] != ';')
			return false;
	}
	else
	{
		if (it->second == false)
			return false;
			//std::cout << "bad syntax 2 (bad instr, must be push or assert)" << std::endl; // exception UNEXPECTED TOKEN 

		it = types_map.find(commandtab[i++]); // got an iterator to the right INSTR 
		if (it == types_map.end())
			return false;
			//std::cout << "bad syntax 3 (type not found)" << std::endl; // exception UNEXPECTED TOKEN 

		if (commandtab[i++][0] != '(')
			return false;
			//std::cout << "bad syntax 4 (must be '(') " << std::endl; // exception UNEXPECTED TOKEN 

		if ((exec("check_value", commandtab[i++].c_str())) == false)
			return false;
			//std::cout << "bad syntax 5 (bad value) " << std::endl; // exception UNEXPECTED TOKEN

		if (commandtab[i][0] != ')')
			return false;
			//std::cout << "bad syntax 6 (must be ')') " << std::endl; // exception UNEXPECTED TOKEN 

		if (commandtab.size() == 6 && commandtab[i][0] != ';')
			return false;
			//std::cout << "bad syntax 6 (must be comm) " << std::endl; // exception UNEXPECTED TOKEN 
	}
	return true;
}

bool IO::lexer(va_list *args)
{
	int len = commandtab.size();
	std::vector<std::string>::iterator first = commandtab.begin();
	std::vector<std::string>::iterator end = commandtab.end();

	(void)args;
	if (len == 0)
		return true;
	while (first != end)
	{
		try
		{
			if (!exec("token_is_ok", (*first).c_str()))
				throw Exception("Invalid token");
		}
		catch (Exception ex)
		{
			std::cerr << ex.what() << std::endl;
			exit(1);
		}
		++first;
	}
	try
	{
		if (!exec("token_order"))
			throw Exception("Unexpected token");
	}
	catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
	return true;
}

bool IO::parser(va_list *args)
{
	size_t		i = 0;
	std::string token;

	(void)args;
	if (commandline.length() == 0) 
		return false;

	while (commandline[i])
	{
		if (commandline[i] == ';' && commandline[i+1] != ';') // if commentary, copy all from ';' in a token and break
		{
			while (commandline[i])
				token += commandline[i++];
			commandtab.push_back(token);
			break;
		}

		if (commandline[i] != ' ' && commandline[i] != '\t') // if not space nor tab, copy in token 
			token += commandline[i];

		if (commandline[i] == ' ' || commandline[i] == '\t' // if end of token, push token in tab 
			|| commandline[i+1] == '(' || commandline[i] == '('
			|| commandline[i+1] == ')' || commandline[i] == ')'
			|| commandline[i+1] == '\0')
		{
			if (token.length() != 0)
				commandtab.push_back(token);
			token.clear();
		}
		i++;
	}
	return true;
}

bool IO::jarvis(va_list *args)
{
	int		ac = va_arg(*args, int);
	char	**av = va_arg(*args, char**);
	std::ifstream file;

	if (ac == 2)
	{
		std::cout << av[1] << std::endl;
		file.open(av[1]);
		try
		{
			if (!file.is_open() || !file.good())
				throw Exception("Fatal error : Unable to open input file");
		}
		catch (Exception ex)
		{
			std::cerr << ex.what() << std::endl;
			exit(1);
		}
	}

	while (1)
	{
		commandline.clear();
		if (ac == 1)
		{
			std::getline(std::cin, commandline);
			if (std::cin.eof() == 1 || commandline == ";;")
				break;
			else if (commandline == "")
				continue;
		}
		else
		{
			if (file.is_open() && file.good())	
				std::getline(file, commandline);
			else
				break;
		}

		exec("parser");
		exec("lexer");
		if ((commandtab.size() == 1 || commandtab.size() == 2) && commandtab[0][0] != ';')
			_vm.getModule("Chipset").exec("push", commandtab[0].c_str(), "", "");
		else if (commandtab.size() == 5 ||commandtab.size() == 6)
			_vm.getModule("Chipset").exec("push", commandtab[0].c_str(), commandtab[1].c_str(), commandtab[3].c_str());
		commandtab.clear();
	}
	return true;
}
