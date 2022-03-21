#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

class SocketException{
public:
    SocketException(){}
    SocketException(std::string str) : m_s(str){ }
    ~SocketException(){ }

    std::string description(){ return m_s; }
private:
    std::string m_s;
};

#endif