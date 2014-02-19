#include <map>
#include <sstream>
#include <stdlib.h>
#include <iostream> // DEBUG

#include "SOperandMaker.hpp"
#include "TOperand.hpp"

std::map<eOperandType, SOperandMaker::func> SOperandMaker::initMap()
{
	std::map<eOperandType, func> map;

	std::cout << "Init map" << std::endl; // DEBUG
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

	if (it == methods.end() && type != it->first)
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

	value = atoi(str.c_str());
	return new TOperand<int8>(Int8, value);
}

IOperand *SOperandMaker::createInt16(const std::string &str)
{
	int16				value;
	std::istringstream	ss(str);

	ss >> value;
	return new TOperand<int16>(Int16, value);
}

IOperand *SOperandMaker::createInt32(const std::string &str)
{
	int32				value;
	std::istringstream	ss(str);

	ss >> value;
	return new TOperand<int32>(Int32, value);
}

IOperand *SOperandMaker::createFloat(const std::string &str)
{
	float				value;
	std::istringstream	ss(str);

	ss >> value;
	return new TOperand<float>(Float, value);
}

IOperand *SOperandMaker::createDouble(const std::string &str)
{
	double				value;
	std::istringstream	ss(str);

	ss >> value;
	return new TOperand<double>(Double, value);
}
