#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "SocketBase.h"

class ServerSocket : private Socket{
public:
    ServerSocket(){}
    ServerSocket(int);
    virtual ~ServerSocket();
    const ServerSocket& operator<<(const std::string&) const;
    const ServerSocket& operator>>(std::string&) const;
    int recv_target(int, std::vector<std::string>&);
    void accept(ServerSocket&);
    const int getServerFileDescriptor() const;
};

#endif