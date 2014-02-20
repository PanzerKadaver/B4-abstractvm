#ifndef ABSTRACTVM_S_COMMAND_MAKER
# define ABSTRACTVM_S_COMMAND_MAKER

# include <map>

class SCommandMaker
{
public:
	// DEF
	typedef void (*func)(void);

	// GETTER
	static func getCommand(const std::string &);

private:
	// INIT
	static std::map<const char *, func> initMap();
};


#endif // !ABSTRACTVM_S_COMMAND_MAKER
