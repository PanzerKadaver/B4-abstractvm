#ifndef ABSTRACTVM_I_MODULE
# define ABSTRACTVM_I_MODULE

# include <string>

class IModule
{
public:
	virtual ~IModule(void) {}

	virtual const std::string &name(void) const = 0;
	virtual bool exec(const char *, ...) = 0;
};


#endif // !ABSTRACTVM_I_MODULE
