#include <exception>
#include <errno.h>
#include <string.h>
#include <varlib.h>

BEGIN_NAMESPACE(varlib)
class socketException : public std::exception {
public:
	socketException(int errno) : m_errno(errno) { }

	virtual const char *what() const noexcept {
		return strerror(m_errno);
	}
private:
	int m_errno;
};


END_NAMESPACE
