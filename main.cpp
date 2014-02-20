#include <iostream>
#include <sstream>
#include <limits> 

#include "SOperandMaker.hpp"

void		pause();
int			appRun();
void		limitTest();
void		ope8Test();
void		multiopTest();

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
	//limitTest();
	//std::cout << std::endl;
	//ope8Test();
	//std::cout << std::endl;
	multiopTest();

	return (0);
}

void			limitTest()
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
}
void			ope8Test()
{
	IOperand	*pos5 = SOperandMaker::createOperand(Int8, "5");
	IOperand	*pos8 = SOperandMaker::createOperand(Int8, "8");
	IOperand	*pos9 = SOperandMaker::createOperand(Int8, "9");
	IOperand	*pos10 = SOperandMaker::createOperand(Int8, "10");
	IOperand	*pos15 = SOperandMaker::createOperand(Int8, "15");
	IOperand	*pos120 = SOperandMaker::createOperand(Int8, "120");
	IOperand	*neg120 = SOperandMaker::createOperand(Int8, "-120");

	std::cout << "== USER ==" << std::endl;
	std::cout << "Int 8 op :" << std::endl;
	std::cout << "-> 8 + 10   =  " << (*pos8 + *pos10)->toString() << std::endl;
	std::cout << "-> 10 - 5   =  " << (*pos10 - *pos5)->toString() << std::endl;
	std::cout << "-> 5 - 10   = " << (*pos5 - *pos10)->toString() << std::endl;
	std::cout << "-> 120 + 15 = " << (*pos120 + *pos15)->toString() << std::endl;
	std::cout << "-> -120 - 9 =  " << (*neg120 - *pos9)->toString() << std::endl;
	std::cout << "-> 120 * 5 =  " << (*pos120 * *pos5)->toString() << std::endl;
	std::cout << "-> 120 / 5 =  " << (*pos120 / *pos5)->toString() << std::endl;
	std::cout << "-> 120 % 9 =  " << (*pos120 % *pos9)->toString() << std::endl;
	std::cout << std::endl;
	std::cout << "== EXPECTED ==" << std::endl;
	std::cout << "Int 8 op :" << std::endl;
	std::cout << "-> 8 + 10   =  " << (int)(int8)((int8)8 + (int8)10) << std::endl;
	std::cout << "-> 10 - 5   =  " << (int)(int8)((int8)10 - (int8)5) << std::endl;
	std::cout << "-> 5 - 10   = " << (int)(int8)((int8)5 - (int8)10) << std::endl;
	std::cout << "-> 120 + 15 = " << (int)(int8)((int8)120 + (int8)15) << std::endl;
	std::cout << "-> -120 - 9 =  " << (int)(int8)((int8)-120 - (int8)9) << std::endl;
	std::cout << "-> 120 * 5 =  " << (int)(int8)((int8)120 * (int8)5) << std::endl;
	std::cout << "-> 120 / 5 =  " << (int)(int8)((int8)120 / (int8)5) << std::endl;
	std::cout << "-> 120 % 9 =  " << (int)(int8)((int8)120 % (int8)9) << std::endl;
}
void			multiopTest()
{
	IOperand	*pos8 = SOperandMaker::createOperand(Int8, "50");
	IOperand	*neg16 = SOperandMaker::createOperand(Int16, "-750");
	IOperand	*pos32 = SOperandMaker::createOperand(Int32, "870542");
	IOperand	*f = SOperandMaker::createOperand(Float, "27.87");
	IOperand	*d = SOperandMaker::createOperand(Double, "-42.42");
	IOperand	*display;

	std::cout << "== USER ==" << std::endl;
	display = (*pos32 + *pos8);
	std::cout << "<int32>870542 + <int8>50 = " << display->toString() << std::endl;
	delete display;
	display = (*pos32 % *pos8);
	std::cout << "<int32>870542 % <int8>50 = " << display->toString() << std::endl;
	delete display;
	display = (*neg16 - *pos32);
	std::cout << "<int16>-750 - <int32>870542 = " << display->toString() << std::endl;
	delete display;
	display = (*pos32 / *neg16);
	std::cout << "<int32>870542 / <int16>-750 = " << display->toString() << std::endl;
	delete display;
	display = (*pos8 * *pos32);
	std::cout << "<int8>50 * <int32>870542 = " << display->toString() << std::endl;
	delete display;
	display = (*pos8 * *f);
	std::cout << "<int8>50 * <float>27.87 = " << display->toString() << std::endl;
	delete display;
	display = (*neg16 / *d);
	std::cout << "<int16>-750 / <double>-42.42 = " << display->toString() << std::endl;
	delete display;
	display = (*pos32 % *f);
	std::cout << "<int32>870542 % <float>27.87 = " << display->toString() << std::endl;
	delete display;
	display = (*d / *f);
	std::cout << "<double>-42.42 / <float>27.87 = " <<display->toString() << std::endl;
	delete display;
	std::cout << std::endl;
	std::cout << "== EXPECTED ==" << std::endl;
	std::cout << "<int32>870542 + <int8>50 = " << (int32)870542 + (int8)50 << std::endl;
	std::cout << "<int32>870542 % <int8>50 = " << (int32)870542 % (int8)50 << std::endl;
	std::cout << "<int16>-750 - <int32>870542 = " << (int16)-750 - (int32)870542 << std::endl;
	std::cout << "<int32>870542 / <int16>-750 = " << (int32)870542 / (int16)-750 << std::endl;
	std::cout << "<int8>50 * <int32>870542 = " << (int8)50 * (int32)870542 << std::endl;
	std::cout << "<int8>50 * <float>27.87 = " << (int8)50 * (float)27.87 << std::endl;
	std::cout << "<int16>-750 / <double>-42.42 = " << (int16)-750 / (double)-42.42 << std::endl;
	std::cout << "<int32>870542 % <float>27.87 = " << fmod((int32)870542, (float)27.87) << std::endl;
	std::cout << "<double>-42.42 / <float>27.87 = " << (double)-42.42 / (float)27.87 << std::endl;

	delete pos8;
	delete neg16;
	delete pos32;
	delete f;
	delete d;
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
