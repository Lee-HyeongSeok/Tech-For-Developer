#ifndef SOCKETBASE_H
#define SOCKETBASE_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>


const int MAXCONNECTIONS=10;
const int MAXRECV=500;

class Socket{
public:
    Socket();
    virtual ~Socket();

    bool create();
    bool bind(const int);
    bool listen() const;
    bool accept(Socket&) const;

    // client
    bool connect(const std::string, const int);

    // input output
    bool send(const std::string) const;
    int recv(std::string&) const;

    // socket set
    void set_non_blocking(const bool);
    
    // checking validation(socket file descriptor)
    // if socket fd is not empty, return true, otherwise return false
    bool is_valid() const{ return m_sock != -1; }
    const int getSocketFileDescriptor() const;
private:
    int m_sock; // socket fd
    sockaddr_in m_addr; // socket address information
};

#endif