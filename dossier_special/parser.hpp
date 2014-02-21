#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <iostream>
# include <string>
# include <queue>
# include <cctype>
# include <algorithm>
# include <map>
# include <utility>
# include "TOperand.hpp"
# include "Commands.hpp"
# include "IOperand.hpp"
# include "SCommandMaker.hpp"
# include "SOperandMaker.hpp"
# include "Trait.hpp"
# include "instr.hpp"

std::string	epur(std::string &);
int		check_syntax(std::string &);
int		check_str(std::string &);

#endif /* PARSER_HPP_*/
