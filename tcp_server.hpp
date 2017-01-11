#ifndef _VARLIB_TCP_SERVER_HPP
#define _VARLIB_TCP_SERVER_HPP

#include <string>

namespace varlib {

class tcp_server {

public:
    tcp_server();
    tcp_server(const short& port);
    bool start();

private:
    const short& m_lis_port;
};

}

#endif
