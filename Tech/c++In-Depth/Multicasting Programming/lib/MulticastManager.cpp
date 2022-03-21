#include "MulticastManager.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

MulticastManager::MulticastManager(){
    if((multi_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        std::cerr<<"MulticastManager :: socket() error\n";
        close(multi_fd);
        exit(1);
    }
}

MulticastManager::~MulticastManager(){
    std::cout<<"~multi destructor\n";
    close(multi_fd);
}

void MulticastManager::set_group_sock_addr(){
    memset((char*)&groupSock, 0, sizeof(groupSock));
    groupSock.sin_family = AF_INET;
    groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");
}

void MulticastManager::set_group_sock_port(int port){
    groupSock.sin_port = htons(port);
}

void MulticastManager::set_interface_addr(){
    localInterface.s_addr = inet_addr("10.99.0.89");
    if(setsockopt(multi_fd, IPPROTO_IP, IP_MULTICAST_IF, (char*)&localInterface, sizeof(localInterface)) < 0){
        std::cerr<<"MulticastManager :: setting local interface error\n";
        exit(1);
    }
}

bool MulticastManager::multicast_sendto_process(char* msg, int msg_len){
    if(sendto(multi_fd, msg, msg_len, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0){
        std::cerr<<"MulticastManager :: sendto() error\n";
        return false;
    }
    return true;
}

bool MulticastManager::multicast_receive_process(char* msg){
    if(recv(multi_fd, msg, 1024, 0) < 0){
        std::cerr<<"MulticastManager :: recv() error\n";
        close(multi_fd);
        return false;
    }
    return true;
}

void MulticastManager::set_client_multi_fd_option(){
    int reuse=1;
    if(setsockopt(multi_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0){
        std::cerr<<"MulticastManager :: setting SO_REUSEADDR error\n";
        close(multi_fd);
        exit(1);
    }
}

void MulticastManager::set_client_multi_fd_membership(){
    if(setsockopt(multi_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&group, sizeof(group)) < 0){
        std::cerr<<"MulticastManager :: IP_ADD_MEMBERSHIP setsockopt() error\n";
        close(multi_fd);
        exit(1);
    }
}

void MulticastManager::set_client_multi_fd_drop_membership(){
    if(setsockopt(multi_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&group, sizeof(group)) < 0){
        std::cerr<<"MulticastManager :: IP_DROP_MEMBERSHIP setsockopt() error\n";
    }
    close(multi_fd);
}

void MulticastManager::set_localSock_addr(){
    memset((char*)&localSock, 0, sizeof(localSock));
    localSock.sin_family = AF_INET;
    localSock.sin_addr.s_addr = INADDR_ANY;
}

void MulticastManager::set_localSock_port(int port){
    localSock.sin_port = htons(port);
}

// 원형 : set_group_multi_addr()
void MulticastManager::set_group_multi_addr(){
    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
}

void MulticastManager::set_group_interface_addr(){
    group.imr_interface.s_addr = inet_addr("10.99.0.89");
}

void MulticastManager::bind_localSock(){
    if(bind(multi_fd, (struct sockaddr*)&localSock, sizeof(localSock))){
        std::cerr<<"MulticastManager :: bind() error\n";
        close(multi_fd);
        exit(1);
    }
}