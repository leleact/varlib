
#ifndef _SOCKET_H
#define _SOCKET_H

#include <varlib.h>
#include <string>

BEGIN_NAMESPACE(varlib)
BEGIN_NAMESPACE(socket)
class socket {
public:
	socket(char *ipaddr, unsigned short port) 
		: m_ipaddr(ipaddr), m_port(port), m_socket(-1) {};

	socket(std::string &ipaddr, unsigned short port) 
		: m_ipaddr(ipaddr), m_port(port), m_socket(-1) {};

	~socket()
	{};

	socket(const socket &);
	socket &operator=(const socket &);

	int bind();
	int listen();
	int accept();
	int connect();
	int close();

private:
	std::string m_ipaddr;
	unsigned short m_port;
	int m_socket;
};
END_NAMESPACE
END_NAMESPACE

#endif // end of socket.hpp
