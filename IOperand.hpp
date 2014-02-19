#ifndef ABSTRACTVM_I_OPERAND_HPP_
# define ABSTRACTVM_I_OPERAND_HPP_

# include <string>

typedef char int8;
typedef short int16;
typedef int int32;


enum eOperandType
{
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
	virtual ~IOperand() {};

	// GETTER
	virtual int getPrecision() const = 0;
	virtual eOperandType getType() const = 0;

	// STR
	virtual const std::string &toString() const = 0;

	// OPERATORS
	virtual IOperand *operator+(const IOperand &) const = 0;
	virtual IOperand *operator-(const IOperand &) const = 0;
	virtual IOperand *operator*(const IOperand &) const = 0;
	virtual IOperand *operator/(const IOperand &) const = 0;
	virtual IOperand *operator%(const IOperand &) const = 0;
};

#endif // !ABSTRACTVM_I_OPERAND_HPP_
