#ifndef MULTICASTMANAGER_H
#define MULTICASTMANAGER_H

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

class MulticastManager{
public:
    // common
    MulticastManager(); // socket()
    ~MulticastManager();
    bool multicast_sendto_process(char*, int);
    bool multicast_receive_process(char*); 

    // server multicast configuration
    void set_group_sock_addr();
    void set_group_sock_port(int);
    void set_interface_addr();

    // client multicast configuration
    void set_client_multi_fd_option();
    void set_client_multi_fd_membership();
    void set_client_multi_fd_drop_membership();

    void set_localSock_addr();
    void set_localSock_port(int);
    void set_group_multi_addr();
    void set_group_interface_addr();
    void bind_localSock();

private:
    // server multicast configuration
    struct in_addr localInterface;
    struct sockaddr_in groupSock;

    // client multicast configuration
    struct sockaddr_in localSock;
    struct ip_mreq group;

    //common
    int multi_fd;
};

#endif