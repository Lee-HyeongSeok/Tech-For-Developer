#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "SocketBase.h"

class ClientSocket : private Socket{
public:
    ClientSocket(std::string, int);
    virtual ~ClientSocket(){}

    const ClientSocket& operator<<(const std::string&) const;
    const ClientSocket& operator>>(std::string&) const;
    const int getClientFileDescriptor() const;
};

#endif
