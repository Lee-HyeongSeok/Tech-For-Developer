## C++: Network Programming

***

<br>



### :pushpin: 기본 소켓 생성 및 연결(Socket.h)

```c++
#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

const int MAXHOSTNAME=200;
const int MAXCONNECTIONS=5;
const int MAXRECV=500;

class Socket{
public:
    Socket();
    virtual ~Socket();
    
    bool create();
    bool bind(const int port);
    bool listen() const;
    bool accept(Socket&) const;
    
    bool connect(const std::string host, const int port);
    
    bool send(const std::string) const;
    int recv(std::string&) const;
    
    void set_non_blocking(const bool);
    bool is_valid() const{ return m_sock != -1}
private: 
    int m_sock;
    sockaddr_in m_addr;
};

#endif
```

<br>

### :pushpin: 기본 소켓 생성 및 연결(Socket.cpp)

```c++
#include "Socket.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>

Socket::Socket(): m_sock(-1){ memset(&m_addr, 0, sizeof(m_addr)); }

Socket::~Socket(){ if(is_valid())::close(m_sock); }

bool Socket::create(){
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(!is_valid()) return false;
    
    int on = 1;
    if(setsockopt(m_sock, SQL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on) == -1))
        return false;
    
    return true;
}

bool Socket::bind(const int port){
    if(!is_valid()) return false;
    
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);
    
    if(::bind(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr)) == -1)
        return false;
    return true;
}

bool Socket::listen() const{
    if(!is_valid()) return false;
    
    if(::listen(m_sock, MAXCONNECTIONS) == -1)
        return false;
    return true;
}

bool Socket::accept(Socket& new_socket) const{
    int addr_length = sizeof(m_addr);
    new_socket.m_sock = ::accept(m_sock, (sockaddr*)&m_addr, (socklen_t *)&addr_length);
    
    if(new_sock.m_sock <= 0) return false;
    else return true;
}

bool Socket::send(const std::string str) const{
    int status = ::send(m_sock, str.c_str(), str.size(), MSG_NOSIGNAL);
    if(status == -1) return false;
    else return true;
}

int Socket::recv(std::string &str) const{
    char buf[MAXRECV + 1];
    str=" ";
    
    memset(buf, 0, MAXRECV+1);
    
    int status = ::recv(m_sock, buf, MAXRECV, 0);
    
    if(status == -1){
        std::cout<<"status == -1 errno == "<<errno<<" in Socket::recv\n";
        return 0;
    }
    else if(status == 0){
        return 0;
    }
    else{
        str = buf;
        return status;
    }
}

bool Socket::connect(const std::string host, const int port){
    if(!is_valid()) return false;
    
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    
    int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
    
    if(errno == EAFNOSUPPORT) return false;
    
    status = ::connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));
    
    if(status == 0) return true;
    else return false;
}

void Socket::set_non_blocking(const bool status){
    int opts;
    
    opts = fcntl(m_sock, F_GETFL);
    
    if(opts < 0) return;
    if(status) opts = (opts | O_NONBLOCK);
    else opts = (opts & ~O_NONBLOCK);
    fcntl(m_sock, F_SETFL, opts);
}
```

<br>

### :pushpin: 서버 소켓 생성 및 연결(ServerSocket.h)

```c++
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "Socket.h"

class ServerSocket : private Socket{
public:
    ServerSocket(int);
    ServerSocket(){}
    virtual ~ServerSocket();
    const ServerSocket& operator<<(const std::string&) const;
    const ServerSocket& operator>>(std::string&) const;
    void accept(ServerSocket&);
};

#endif
```



### :pushpin: 서버 소켓 생성 및 연결(ServerSocket.cpp)

```c++
#include <string>
#include "ServerSocket.h"
#include "SocketException.h" // socket 에러 처리 클래스

ServerSocket::ServerSocket(int port){
    if(!Socket::create()) // socket 생성
        throw SocketException("Could not create server socket.\n");
    if(!Socket::bind(port)) // socket 주소 및 설정 바인딩
        throw SocketException("Could not bind to port\n");
    if(!Socket::listen()) // 클라이언트 연결 대기
        throw SocketException("Could not listen to socket\n");
}

const ServerSocket& ServerSocket::operator<<(const std::string& str) const{
    if(!Socket::send(str))
        throw SocketException("Could not write to socket.\n");
    return *this;
}

const ServerSocket& ServerSocket::operator>>(std::string& str) const{
    if(!Socket::recv(str))
        throw SocketException("Could not read from socket.\n");
    return *this;
}

void ServerSocket::accept(ServerSocket& sock){
    if(!Socket::accept(sock))
        throw SocketException("Could not accept socket.\n");
}
```

<br>

### :pushpin: 클라이언트 소켓 생성 및 연결(ClientSocket.h)

```c++
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "Socket.h"

class ClientSocket : private Socket{
public:
    ClientSocket(std::string, int);
    virtual ~ClientSocket(){}
    
    const ClientSocket& operator<<(const std::string&) const;
    const ClientSocket& operator>>(std::string&) const;
};

#endif
```



### :pushpin: 클라이언트 소켓 생성 및 연결(ClientSocket.cpp)

```c++
#include "ClientSocket.h"
#include "SocketException.h"

ClientSocket::ClientSocket(std::string host, int port){
    if(!Socket::create()) // 소켓 생성
        throw SocketException("Could not create client socket.\n");
    if(!Socket::connect(host, port))
        throw SocketException("Could not bind to port.\n");
}

const ClientSocket& ClientSocket::operator<<(const std::string& str) const{
    if(!Socket::send(str))
        throw SocketException("Could not write to socket.\n");
    return *this;
}

const ClientSocket& ClientSocket::operator>>(std::string& str) const{
    if(!Socket::recv(str))
        throw SocketException("Could not read from socket.\n");
    return *this;
}
```

<br>

### :pushpin: 소켓 예외처리 클래스(SocketException.h)

```c++
#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

class SocketException{
public:
    SocketException(){ }
    SocketException(std::string str) : m_s(str){ }
    ~SocketException(){ }
    
    std::string description(){ return m_s; }
private:
    std::string m_s;
};

#endif
```

<br>

### :pushpin: 서버 프로그램(simple_server_main.cpp)

```c++
#include "ServerSocket.h"
#include <string>
#include <iostream>
#include "SocketException.h"

int main(int argc, char* argv[]){
    std::cout<<"running... \n";
    
    try{
        ServerSoket server(30000); // 서버 소켓 생성, 바인딩, 연결 대기
        
        while(true){
            ServerSocket new_sock; // 새로운 소켓 생성(클라이언트의 FD를 저장할 소켓)
            server.accept(new_sock); // 연결 허용과 동시에 내부에서는 클라이언트의 소켓 정보를 저장
            
            try{ // 데이터 송수신
                while(true){
                    std::string data;
                    new_sock>>data; // 클라이언트의 입력 읽기
                    new_sock<<data; // 클라이언트로 출력
                }
            }
            catch(SocketException& e){
                
            }
        }
    }
    catch(SocketException &e){
        std::cout<<"Exception was caught : "<<e.description()<<"\nExiting.\n";
    }
    return 0;
}
```

<br>

### :pushpin: 클라이언트 프로그램(simple_client_main.cpp)

```c++
#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
    try{
        clientSocket client_socket("localhost", 30000);
        
        std::string reply;
        
        try{
            client_socket<<"Test message: ";
            client_socket<<reply;
        }
        catch(SocketException& e){
            
        }
        
        std::cout<<"We received this response from the server: \n"<<reply<<'\n';
    }
    catch(SocketException& e){
        std::cout<<"Exception was caught: "<<e.description()<<'\n';
    }
    
    return 0;
}
```

<br>

### :pushpin: Makefile

```bash
CC=clang++
CFLAGS=-m64 -Wall -std=c++1z -stdlib=libstdc++
simple_server_objects=ServerSocket.o Socket.o simple_server_main.o
simple_client_objects=ClientSocket.o Socket.o simple_client_main.o

all: simple_server simple_client

simple_server: $(simple_server_objects)
	$(CC) -o simple_server $(simple_server_objects)
simple_client: $(simple_client_objects)
	$(CC) -o simple_client $(simple_client_objects)
	
Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
simple_server_main: simple_server_main.cpp
simple_client_main: simple_client_main.cpp

clean:
	rm -f *.o simple_server simple_client
```

<br>

### :pushpin: 전체 구조

![Untitled Diagram drawio](https://user-images.githubusercontent.com/55940552/154842829-2ae6502e-05b6-40c2-b84f-5e8a303cfbef.png) 





***

<br>

### :round_pushpin: 출처

[블로그](http://coffeenix.net/doc/lg/issue74/tougher.html) 