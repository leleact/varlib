

#include <varlib.h>
#include <string>

#ifndef _SOCKET_H
#define _SOCKET_H

BEGIN_NAMESPACE(varlib)
BEGIN_NAMESPACE(socket)
class socket {
public:
	socket(char *ipaddr, unsigned short port) : m_ipaddr(ipaddr), m_port(port), m_socket(-1) {};
	socket(std::string &ipaddr, unsigned short port) : m_ipaddr(ipaddr), m_port(port), m_socket(-1) {};

	int bind();
	int listen();
	int connect();
	int close();

private:
	std::string m_ipaddr;
	unsigned short m_port;
	int m_socket;
};
END_NAMESPACE
END_NAMESPACE
#endif
