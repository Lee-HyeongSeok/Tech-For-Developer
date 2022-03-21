#include "SocketBase.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string>

Socket::Socket(){
    m_sock = -1;
    memset(&m_addr, 0, sizeof(m_addr));
}

Socket::~Socket(){
    if(is_valid()) {
        std::cout<<"close socket fd : "<<m_sock<<'\n';
        ::close(m_sock);
    }
}

// create socket
bool Socket::create(){
    m_sock = socket(PF_INET, SOCK_STREAM, 0);

    if(!is_valid()){
        return false;
    }

    int on = 1;
    if(setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) == -1){ 
        return false;
    }

    return true;
}

// socket binding
bool Socket::bind(const int port){
    if(!is_valid()) 
        return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    if(::bind(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr)) == -1) 
        return false;

    return true;
}

bool Socket::listen() const{
    if(!is_valid()){
        return false;
    }

    // set syn queue, accept queue size
    if(::listen(m_sock, MAXCONNECTIONS) == -1){
        std::cout<<"m_sock : "<<m_sock<<std::endl;
        return false;
    }

    return true;
}

bool Socket::accept(Socket& new_socket) const{
    int addr_length = sizeof(m_addr);

    new_socket.m_sock = ::accept(m_sock, (struct sockaddr*)&m_addr, (socklen_t *)&addr_length);

    if(new_socket.m_sock <= 0) 
        return false;
    else 
        return true;
}

bool Socket::send(const std::string str) const{
    int status = ::send(m_sock, str.c_str(), str.size(), MSG_NOSIGNAL);
   
    if(status){
        return true;
    }
    else{   
        return false;
    }
}

int Socket::recv(std::string &str) const{
    char buf[MAXRECV + 1];
    str = "";

    memset(buf, 0, MAXRECV+1);

    int status = ::recv(m_sock, buf, MAXRECV, 0);

    if(status == -1){
        std::cout<<"status == -1 errno =="<<errno<<" in Socket::recv\n";
        return 0;
    }
    else if(status == 0){
        std::cout<<"call zero in server \n";
        return 0;
    }
    else{
        str = buf;
        return status;
    }
}

bool Socket::connect(const std::string host, const int port){
    if(!is_valid())
        return false;

    m_addr.sin_family = AF_INET;
    //m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

    if(errno == EAFNOSUPPORT)
        return false;
    
    status = ::connect(m_sock, (struct sockaddr *)&m_addr, sizeof(m_addr));

    if(status)
        return false;
    else   
        return true;
}

void Socket::set_non_blocking(const bool status){
    int opts = fcntl(m_sock, F_GETFL);

    if(opts < 0)
        return;
    if(status)
        opts = (opts | O_NONBLOCK);
    else
        opts = (opts & ~O_NONBLOCK);
    
    fcntl(m_sock, F_SETFL, opts);
}

const int Socket::getSocketFileDescriptor() const{
    if(is_valid()){
        return m_sock;
    }
    return -1;
}