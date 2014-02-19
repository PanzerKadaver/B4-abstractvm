#ifndef ABSTRACTVM_T_OPERAND
# define ABSTRACTVM_T_OPERAND

# include <math.h>
# include <sstream>
# include <typeinfo>

# include "IOperand.hpp"

template <typename T>
class TOperand : public IOperand
{
public:
	// CTOR / DTOR
	TOperand(eOperandType, T);
	~TOperand(void) {};

	// GETTER
	int				getPrecision() const;
	eOperandType	getType() const;
	T				getValue() const;

	// CAST
	IOperand		*makeBy(T) const;

	// STR
	const std::string &toString() const;

	IOperand *operator+(const IOperand &) const;
	IOperand *operator-(const IOperand &) const;
	IOperand *operator*(const IOperand &) const;
	IOperand *operator/(const IOperand &) const;
	IOperand *operator%(const IOperand &) const;

private:
	T				_value;
	eOperandType	_type;
	std::string		_string;
};

template <typename T>
TOperand<T>::TOperand(eOperandType type, T value)
{
	std::ostringstream oss;

	_value = value;
	_type = type;
	if (typeid(value).name() == typeid(int8).name())
		oss << (int)value;
	else
		oss << value;
	_string.assign(oss.str());
}

template <typename T>
int	TOperand<T>::getPrecision() const
{
	return  (int)_type;
}

template <typename T>
eOperandType TOperand<T>::getType() const
{
	return _type;
}

template <typename T>
T TOperand<T>::getValue() const
{
	return _value;
}

template <typename T>
IOperand *TOperand<T>::makeBy(T value) const
{
	return new TOperand<T>(getType(), value);
}

template <typename T>
const std::string &TOperand<T>::toString() const
{
	return _string;
}

template <typename T>
IOperand *TOperand<T>::operator+(const IOperand &other) const
{
	if (getPrecision() >= other.getPrecision())
		return new TOperand<T>(getType(), getValue() + ((TOperand &)other).getValue());
	else
		return ((TOperand &)other).makeBy(getValue() + ((TOperand &)other).getValue());
}

template <typename T>
IOperand *TOperand<T>::operator-(const IOperand &other) const
{
	if (getPrecision() >= other.getPrecision())
		return new TOperand<T>(getType(), getValue() - ((TOperand &)other).getValue());
	else
		return ((TOperand &)other).makeBy(getValue() - ((TOperand &)other).getValue());
}

template <typename T>
IOperand *TOperand<T>::operator*(const IOperand &other) const
{
	if (getPrecision() >= other.getPrecision())
		return new TOperand<T>(getType(), getValue() * ((TOperand &)other).getValue());
	else
		return ((TOperand &)other).makeBy(getValue() * ((TOperand &)other).getValue());
}

template <typename T>
IOperand *TOperand<T>::operator/(const IOperand &other) const
{
	if (((TOperand &)other).getValue() == 0)
		return NULL;
	else if (getPrecision() >= other.getPrecision())
		return new TOperand<T>(getType(), getValue() / ((TOperand &)other).getValue());
	else
		return ((TOperand &)other).makeBy(getValue() / ((TOperand &)other).getValue());
}

template <typename T>
IOperand *TOperand<T>::operator%(const IOperand &other) const
{
	if (((TOperand &)other).getValue() == 0)
		return NULL;
	else if (getPrecision() >= other.getPrecision())
		return new TOperand<T>(getType(), fmod(getValue(), ((TOperand &)other).getValue()));
	else
		return ((TOperand &)other).makeBy(fmod(getValue(), ((TOperand &)other).getValue()));
}

#endif // !ABSTRACTVM_T_OPERAND
