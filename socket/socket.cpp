
#include <socket.hpp>
#include <varlib.h>
#include <string>
#include <iostream>
#include <unistd.h>

BEGIN_NAMESPACE(varlib)
BEGIN_NAMESPACE(socket)

int socket::bind()
{
	int nRet = 0;
	return nRet;	
}

int socket::listen()
{
	int nRet = 0;
	return nRet;
}

int socket::accept()
{
	int nRet = 0;
	return nRet;
}

int socket::connect()
{
	int nRet = 0;
	return nRet;
}

int socket::close()
{
	return ::close(m_socket);
}

END_NAMESPACE
END_NAMESPACE

