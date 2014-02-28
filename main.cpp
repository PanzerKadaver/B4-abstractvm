#include <iostream>

#include "VM.hpp"
#include "Exception.hpp"

int main(int ac, char **av)
{
	VM	_vm;

	try
	{
		if (ac == 1 || ac == 2)
		{
			_vm.getModule("IO").exec("jarvis", ac, av);
			//_vm.getModule("Chipset").exec("run");
		}
		else
			throw Exception("Usage : ./avm [file]");
	} catch(Exception ex) {
		std::cerr << ex.what() << std::endl;
	}
	_vm.getModule("Chipset").exec("run");
	system("PAUSE");
	return 0;
}
