#include <map>
#include <sstream>
#include <cstdlib>
#include <iostream> // DEBUG

#include "SOperandMaker.hpp"
#include "TOperand.hpp"

std::map<eOperandType, SOperandMaker::func> SOperandMaker::initMap()
{
	std::map<eOperandType, func> map;

	//std::cout << "Init map IN SOPERAND" << std::endl; // DEBUG
	map[Int8] = &SOperandMaker::createInt8;
	map[Int16] = &SOperandMaker::createInt16;
	map[Int32] = &SOperandMaker::createInt32;
	map[Float] = &SOperandMaker::createFloat;
	map[Double] = &SOperandMaker::createDouble;

	return map;
}

SOperandMaker::func SOperandMaker::getMethod(eOperandType type)
{
	static std::map<eOperandType, func> methods = SOperandMaker::initMap();
	std::map<eOperandType, func>::iterator it = methods.find(type);

	if (it == methods.end())
		return NULL;
	else
		return it->second;
}

IOperand *SOperandMaker::createOperand(eOperandType type, const std::string &value)
{
	func fctPtr = NULL;

	if ((fctPtr = getMethod(type)) == NULL)
		return NULL;
	else
		return (fctPtr)(value);
}

IOperand *SOperandMaker::createInt8(const std::string &str)
{
	int8				value;
	long double			check;
	TOperand<int8>		*t;

	if (str.empty())
	{
		t = new TOperand<int8>(Int8, 0);
		t->setString("");
		return t;
	}
	value = atoi(str.c_str());
	check = atoi(str.c_str());
	t = new TOperand<int8>(Int8, value);
	t->checkOverflow(check);
	t->checkUnderflow(check);

	return t;
}

IOperand *SOperandMaker::createInt16(const std::string &str)
{
	int16				value;
	long double			check;
	std::istringstream	ss(str);
	std::istringstream	c_ss(str);
	TOperand<int16>		*t;

	ss >> value;
	c_ss >> check;
	t = new TOperand<int16>(Int16, value);
	t->checkOverflow(check);
	t->checkUnderflow(check);

	return t;
}

IOperand *SOperandMaker::createInt32(const std::string &str)
{
	int32				value;
	long double			check;
	std::istringstream	ss(str);
	std::istringstream	c_ss(str);
	TOperand<int32>		*t;

	ss >> value;
	c_ss >> check;
	t = new TOperand<int32>(Int32, value);
	t->checkOverflow(check);
	t->checkUnderflow(check);

	return t;
}

IOperand *SOperandMaker::createFloat(const std::string &str)
{
	float				value;
	long double			check;
	std::istringstream	ss(str);
	std::istringstream	c_ss(str);
	TOperand<float>		*t;

	ss >> value;
	c_ss >> check;
	t = new TOperand<float>(Float, value);
	t->checkOverflow(check);
	t->checkUnderflow(check);

	return t;
}

IOperand *SOperandMaker::createDouble(const std::string &str)
{
	double				value;
	long double			check;
	std::istringstream	ss(str);
	std::istringstream	c_ss(str);
	TOperand<double>	*t;

	ss >> value;
	c_ss >> check;
	t = new TOperand<double>(Double, value);
	t->checkOverflow(check);
	t->checkUnderflow(check);

	return t;
}
