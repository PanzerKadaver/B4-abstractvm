#ifndef ABSTRACTVM_T_OPERAND
# define ABSTRACTVM_T_OPERAND

# include <cmath>
# include <sstream>
# include <typeinfo>
# include <cstdlib>

# include "IOperand.hpp"
# include "SOperandMaker.hpp"
# include "Trait.hpp"
# include "Exception.hpp"

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

	// STR
	const std::string &toString() const;
	void setString(const std::string &);

	IOperand *operator+(const IOperand &) const;
	IOperand *operator-(const IOperand &) const;
	IOperand *operator*(const IOperand &) const;
	IOperand *operator/(const IOperand &) const;
	IOperand *operator%(const IOperand &) const;

	void	checkOverflow(long double) const;
	void	checkUnderflow(long double) const;

private:
	T				_value;
	eOperandType	_type;
	std::string		_string;

	IOperand	*doAdd(eOperandType, const std::string &, const std::string &) const;
	IOperand	*doLess(eOperandType, const std::string &, const std::string &) const;
	IOperand	*doMul(eOperandType, const std::string &, const std::string &) const;
	IOperand	*doDiv(eOperandType, const std::string &, const std::string &) const;
	IOperand	*doMod(eOperandType, const std::string &, const std::string &) const;
};

template <typename T>
TOperand<T>::TOperand(eOperandType type, T value)
{
	std::ostringstream oss117;

	_value = value;
	_type = type;
	if (typeid(value).name() == typeid(int8).name())
		oss117 << (int)value;
	else
		oss117 << value;
	_string.assign(oss117.str());
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
const std::string &TOperand<T>::toString() const
{
	return _string;
}

template <typename T>
void	TOperand<T>::setString(const std::string &s)
{
	_string = s.c_str();
}

template <typename T>
IOperand *TOperand<T>::operator+(const IOperand &other) const
{
	const std::string &left = this->toString();
	const std::string &right = other.toString();

	if (getPrecision() >= other.getPrecision())
		return doAdd(getType(), left, right);
	else
	{
		IOperand *current = SOperandMaker::createOperand(other.getType(), left);
		IOperand *r = (*current + other);
		delete current;
		return r;
	}
}

template <typename T>
IOperand *TOperand<T>::operator-(const IOperand &other) const
{
	const std::string &left = this->toString();
	const std::string &right = other.toString();

	if (getPrecision() >= other.getPrecision())
		return doLess(getType(), left, right);
	else
	{
		IOperand *current = SOperandMaker::createOperand(other.getType(), left);
		IOperand *r = (*current - other);
		delete current;
		return r;
	}
}

template <typename T>
IOperand *TOperand<T>::operator*(const IOperand &other) const
{
	const std::string &left = this->toString();
	const std::string &right = other.toString();

	if (getPrecision() >= other.getPrecision())
		return doMul(getType(), left, right);
	else
	{
		IOperand *current = SOperandMaker::createOperand(other.getType(), left);
		IOperand *r = (*current * other);
		delete current;
		return r;
	}
}

template <typename T>
IOperand *TOperand<T>::operator/(const IOperand &other) const
{
	const std::string &left = this->toString();
	const std::string &right = other.toString();

	if (getPrecision() >= other.getPrecision())
		return doDiv(getType(), left, right);
	else
	{
		IOperand *current = SOperandMaker::createOperand(other.getType(), left);
		IOperand *r = (*current / other);
		delete current;
		return r;
	}
}

template <typename T>
IOperand *TOperand<T>::operator%(const IOperand &other) const
{
	const std::string &left = this->toString();
	const std::string &right = other.toString();

	if (getPrecision() >= other.getPrecision())
		return doMod(getType(), left, right);
	else
	{
		IOperand *current = SOperandMaker::createOperand(other.getType(), left);
		IOperand *r = (*current % other);
		delete current;
		return r;
	}
}

template <typename T>
void	TOperand<T>::checkOverflow(long double val) const
{
	try
	{
		if (val > std::numeric_limits<T>::max() && val != 0)
			throw Exception("Value Overflow");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x50);
	}
}

template <typename T>
void	TOperand<T>::checkUnderflow(long double val) const
{
	try
	{
		if (val < std::numeric_limits<T>::min() && val != 0)
			throw Exception("Value Underflow");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x51);
	}
}

template <typename T>
IOperand *TOperand<T>::doAdd(eOperandType type, const std::string &left, const std::string &right) const
{
	T l_value;
	T r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;
	checkOverflow(l_value + r_value);
	checkUnderflow(l_value + r_value);

	return new TOperand<T>(type, (l_value + r_value));
}

template <>
IOperand *TOperand<int8>::doAdd(eOperandType type, const std::string &left, const std::string &right) const
{
	int l_value;
	int	r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;
	checkOverflow(l_value + r_value);
	checkUnderflow(l_value + r_value);

	return new TOperand<int8>(type, (l_value + r_value));
}

template <typename T>
IOperand *TOperand<T>::doLess(eOperandType type, const std::string &left, const std::string &right) const
{
	T l_value;
	T r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;
	checkOverflow(l_value - r_value);
	checkUnderflow(l_value - r_value);

	return new TOperand<T>(type, (l_value - r_value));
}

template <>
IOperand *TOperand<int8>::doLess(eOperandType type, const std::string &left, const std::string &right) const
{
	int l_value;
	int r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;
	checkOverflow(l_value - r_value);
	checkUnderflow(l_value - r_value);

	return new TOperand<int8>(type, (l_value - r_value));
}

template <typename T>
IOperand *TOperand<T>::doMul(eOperandType type, const std::string &left, const std::string &right) const
{
	T l_value;
	T r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;
	checkOverflow(l_value * r_value);
	checkUnderflow(l_value * r_value);

	return new TOperand<T>(type, (l_value * r_value));
}

template <>
IOperand *TOperand<int8>::doMul(eOperandType type, const std::string &left, const std::string &right) const
{
	int l_value;
	int r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;
	checkOverflow(l_value * r_value);
	checkUnderflow(l_value * r_value);

	return new TOperand<int8>(type, (l_value * r_value));
}

template <typename T>
IOperand *TOperand<T>::doDiv(eOperandType type, const std::string &left, const std::string &right) const
{
	T l_value;
	T r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;

	try
	{
		if (r_value == 0)
			throw Exception("Floating exception (Divide by 0)");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x52);
	}
	checkOverflow(l_value / r_value);
	checkUnderflow(l_value / r_value);

	return new TOperand<T>(type, (l_value / r_value));
}

template <>
IOperand *TOperand<int8>::doDiv(eOperandType type, const std::string &left, const std::string &right) const
{
	int l_value;
	int r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;

	try
	{
		if (r_value == 0)
			throw Exception("Floating exception (Divide by 0)");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x52);
	}
	checkOverflow(l_value / r_value);
	checkUnderflow(l_value / r_value);

	return new TOperand<int8>(type, (l_value / r_value));
}

template <typename T>
IOperand *TOperand<T>::doMod(eOperandType type, const std::string &left, const std::string &right) const
{
	T l_value;
	T r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;

	try
	{
		if (r_value == 0)
			throw Exception("Floating exception (Modulo by 0)");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x53);
	}
	if (TRAIT::is_float<T>::value || TRAIT::is_double<T>::value)
	{
		checkOverflow(fmod(l_value, r_value));
		checkUnderflow(fmod(l_value, r_value));
		return new TOperand<T>(type, fmod(l_value, r_value));
	}
	else
	{
		checkOverflow((l_value - ((l_value / r_value) * r_value)));
		checkUnderflow((l_value - ((l_value / r_value) * r_value)));
		return new TOperand<T>(type, (l_value - ((l_value / r_value) * r_value)));
	}
}

template <>
IOperand *TOperand<int8>::doMod(eOperandType type, const std::string &left, const std::string &right) const
{
	int l_value;
	int r_value;
	std::istringstream l_ss(left);
	std::istringstream r_ss(right);

	l_ss >> l_value;
	r_ss >> r_value;

	try
	{
		if (r_value == 0)
			throw Exception("Floating exception (Modulo by 0)");
	} catch (Exception ex)
	{
		std::cerr << ex.what() << std::endl;
		exit(0x53);
	}
	checkOverflow((l_value % r_value));
	checkUnderflow((l_value % r_value));

	return new TOperand<int8>(type, (l_value % r_value));
}

#endif // !ABSTRACTVM_T_OPERAND
