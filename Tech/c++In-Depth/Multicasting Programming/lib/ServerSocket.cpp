#include <string>
#include <vector>
#include "ServerSocket.h"
#include "SocketException.h"

ServerSocket::ServerSocket(int port){
    if(!Socket::create())
        throw SocketException("Could not create server socket.\n");
    if(!Socket::bind(port))
        throw SocketException("Could not bind server socket.\n");
    if(!Socket::listen())
        throw SocketException("Could not listen to socket.\n");
}

ServerSocket::~ServerSocket(){
    
}

const ServerSocket& ServerSocket::operator<<(const std::string& str) const{
    if(!Socket::send(str))
        throw SocketException("Could not write to socket.\n");
    return *this;
}

const ServerSocket& ServerSocket::operator>>(std::string& str) const{
    if(!Socket::recv(str)){
        throw SocketException("Could not read to socket.\n");
    }
    return *this;
}

void ServerSocket::accept(ServerSocket& new_socket){
    if(!Socket::accept(new_socket))
        throw SocketException("Could not accept socket.\n");
}

const int ServerSocket::getServerFileDescriptor() const{
    int socket_fd;
    if((socket_fd = Socket::getSocketFileDescriptor()) == -1){
        throw SocketException("is not valid socket file descriptor.\n");
    }
    return socket_fd;
}