#ifndef ABSTRACTVM_VM
# define ABSTRACTVM_VM

# include <map>
# include <string>
# include "IModule.hpp"

class VM
{
public:
	VM(void);
	~VM(void) {};

	IModule &getModule(const char *) const;

private:
	std::map<const char *, IModule *> _modules;
};

#endif // !ABSTRACTVM_VM
