#ifndef INSTR_HPP_
# define INSTR_HPP_

# include <map>
# include <string>
# include <iostream>
# include <algorithm>
# include "IOperand.hpp"
# include "SCommandMaker.hpp"

std::string		ret_value(const std::string &);
eOperandType		get_type(std::string &);
eOperandType		ret_type(std::string &);
SCommandMaker::func	ret_cmd(std::string &);
std::map<std::string, eOperandType>	init_type_map();

#endif /* INSTR_HPP_ */
