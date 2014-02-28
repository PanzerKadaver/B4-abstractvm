#ifndef ABSTRACTVM_EXCEPTION_HPP_
# define ABSTRACTVM_EXCEPTION_HPP_

# include <exception>

struct Exception : public std::exception
{
	const char *msg;
	Exception(const char *msg_) : msg(msg_) {}
	~Exception() throw () {}
	const char *what() const throw() { return msg; }
};

#endif // !ABSTRACTVM_EXCEPTION_HPP_
