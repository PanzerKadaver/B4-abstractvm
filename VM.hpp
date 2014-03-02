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
	void	exit() const;

private:
	std::map<const std::string, IModule *> _modules;
};

#endif // !ABSTRACTVM_VM
