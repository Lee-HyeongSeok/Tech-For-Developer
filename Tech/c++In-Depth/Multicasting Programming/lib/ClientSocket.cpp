#include <string>
#include "ClientSocket.h"
#include "SocketException.h"

ClientSocket::ClientSocket(std::string host, int port){
    if(!Socket::create())
        throw SocketException("Could not create client socket.\n");
    if(!Socket::connect(host, port))
        throw SocketException("Could not bind to port.\n");
}

const ClientSocket& ClientSocket::operator<<(const std::string& str) const{
    if(!Socket::send(str)){
        throw SocketException("Could not write to socket.\n");
    }
    return *this;
}

const ClientSocket& ClientSocket::operator>>(std::string& str) const{
    if(!Socket::recv(str)){
        throw SocketException("Could not read to socket.\n");
    }
    return *this;
}

const int ClientSocket::getClientFileDescriptor() const{
    int socket_fd;

    if((socket_fd = Socket::getSocketFileDescriptor()) == -1){
        throw SocketException("is not valid socket file descriptor.\n");
    }
    return socket_fd;
}