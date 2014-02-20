#ifndef ABSTRACTVM_S_OPERAND_MAKER_HPP_
# define ABSTRACTVM_S_OPERAND_MAKER_HPP_

# include <map>

# include "IOperand.hpp"

class SOperandMaker
{
public:
	// DEF
	typedef IOperand *(*func)(const std::string &);

	// CREATOR
	static IOperand *createOperand(eOperandType, const std::string &);


private:
	// INIT
	static std::map<eOperandType, func> initMap();

	// GETTER
	static func getMethod(eOperandType);

	// SUBFCTS
	static IOperand *createInt8(const std::string &);
	static IOperand *createInt16(const std::string &);
	static IOperand *createInt32(const std::string &);
	static IOperand *createFloat(const std::string &);
	static IOperand *createDouble(const std::string &);
};

#endif // !ABSTRACTVM_SOPERAND_MAKER_HPP_
