#include <iostream>
#include <sstream>
#include <limits> 

#include "SOperandMaker.hpp"

void		pause();
int			appRun();

int			main()
{
	int		err_code = 0;

	err_code = appRun();
	std::cout << std::endl;
	pause();
	return (err_code);
}

int			appRun()
{
	IOperand *max8;
	IOperand *min8;
	IOperand *max16;
	IOperand *min16;
	IOperand *max32;
	IOperand *min32;
	IOperand *maxF;
	IOperand *minF;
	IOperand *maxD;
	IOperand *minD;
	std::ostringstream oss;

	oss << (int)std::numeric_limits<int8>::max();
	max8 = SOperandMaker::createOperand(Int8, oss.str());
	oss.str("");
	oss << (int)std::numeric_limits<int8>::min();
	min8 = SOperandMaker::createOperand(Int8, oss.str());
	oss.str("");
	oss << std::numeric_limits<int16>::max();
	max16 = SOperandMaker::createOperand(Int16, oss.str());
	oss.str("");
	oss << std::numeric_limits<int16>::min();
	min16 = SOperandMaker::createOperand(Int16, oss.str());
	oss.str("");
	oss << std::numeric_limits<int32>::max();
	max32 = SOperandMaker::createOperand(Int32, oss.str());
	oss.str("");
	oss << std::numeric_limits<int32>::min();
	min32 = SOperandMaker::createOperand(Int32, oss.str());
	oss.str("");
	oss << std::numeric_limits<float>::max();
	maxF = SOperandMaker::createOperand(Float, oss.str());
	oss.str("");
	oss << std::numeric_limits<float>::min();
	minF = SOperandMaker::createOperand(Float, oss.str());
	oss.str("");
	oss << std::numeric_limits<double>::max();
	maxD = SOperandMaker::createOperand(Double, oss.str());
	oss.str("");
	oss << std::numeric_limits<double>::min();
	minD = SOperandMaker::createOperand(Double, oss.str());

	std::cout << "== USER ==" << std::endl;
	std::cout << "Maximum of Int8    :  " << max8->toString() << std::endl;
	std::cout << "Minimum of Int8    : " << min8->toString() << std::endl;
	std::cout << "Maximum of Int16   :  " << max16->toString() << std::endl;
	std::cout << "Minimum of Int16   : " << min16->toString() << std::endl;
	std::cout << "Maximum of Int32   :  " << max32->toString() << std::endl;
	std::cout << "Minimum of Int32   : " << min32->toString() << std::endl;
	std::cout << "Maximum of Float   :  " << maxF->toString() << std::endl;
	std::cout << "Minimum of Float   :  " << minF->toString() << std::endl;
	std::cout << "Maximum of Double  :  " << maxD->toString() << std::endl;
	std::cout << "Minimum of Double  :  " << minD->toString() << std::endl;
	std::cout << std::endl;
	std::cout << "== EXPECTED ==" << std::endl;
	std::cout << "Maximum of Int8   :  " << (int)std::numeric_limits<int8>::max() << std::endl;
	std::cout << "Minimum of Int8   : " << (int)std::numeric_limits<int8>::min() << std::endl;
	std::cout << "Maximum of Int16  :  " << std::numeric_limits<int16>::max() << std::endl;
	std::cout << "Minimum of Int16  : " << std::numeric_limits<int16>::min() << std::endl;
	std::cout << "Maximum of Int32  :  " << std::numeric_limits<int32>::max() << std::endl;
	std::cout << "Minimum of Int32  : " << std::numeric_limits<int32>::min() << std::endl;
	std::cout << "Maximum of Float  :  " << std::numeric_limits<float>::max() << std::endl;
	std::cout << "Minimum of Float  :  " << std::numeric_limits<float>::min() << std::endl;
	std::cout << "Maximum of Double :  " << std::numeric_limits<double>::max() << std::endl;
	std::cout << "Minimum of Double :  " << std::numeric_limits<double>::min() << std::endl;

	return 0;
}

void		pause()
{
#if defined(_MSC_VER)
	system("PAUSE");
#else
	std::cout << "Press key to continue..." <<std::endl;
	std::cin.get();
#endif
}
