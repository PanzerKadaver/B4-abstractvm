#ifndef ABSTRACTVM_I_OPERAND_HPP_
# define ABSTRACTVM_I_OPERAND_HPP_

# include <string>

typedef char int8;
typedef short int16;
typedef int int32;


enum eOperandType
{
	Unknow = 0,
	Int8 = 1,
	Int16 = 2,
	Int32 = 3,
	Float = 4,
	Double = 5
};

class IOperand
{
public:
	// DTOR
	virtual ~IOperand(void) {};

	// GETTER
	virtual int getPrecision(void) const = 0;
	virtual eOperandType getType(void) const = 0;

	// DISPLAY
	virtual const std::string &toString(void) const = 0;

	// OPERATORS
	virtual IOperand *operator+(const IOperand &) const = 0;
	virtual IOperand *operator-(const IOperand &) const = 0;
	virtual IOperand *operator*(const IOperand &) const = 0;
	virtual IOperand *operator/(const IOperand &) const = 0;
	virtual IOperand *operator%(const IOperand &) const = 0;
};

#endif // !ABSTRACTVM_I_OPERAND_HPP_
