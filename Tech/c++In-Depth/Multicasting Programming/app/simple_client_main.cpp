#include <string>
#include <iostream>
#include "MulticastManager.h"
#include "SocketBase.h"
#include "SocketException.h"
#include "ClientSocket.h"
#include <sys/select.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char* argv[]){
    std::string client_msg;
    int user_room_number=0;
    char databuf[1024];

    // multicast group, interface group set
    MulticastManager multiManager;
    multiManager.set_client_multi_fd_option();
    multiManager.set_localSock_addr();

    multiManager.set_group_multi_addr();
    multiManager.set_group_interface_addr();
    multiManager.set_client_multi_fd_membership();

    try{
        ClientSocket client_socket("localhost", 30000); // create(), bind(), connect()

        client_socket>>client_msg;   // 채팅방 공지받음
        std::cout<<"client_msg size : "<<client_msg.size()<<'\n';
        std::cout<<client_msg<<'\n'<<"채팅방 선택 : "; // 서버의 공지 출력
        std::cin>>user_room_number; // 사용자 채팅방 번호 입력

        client_socket<<std::to_string(user_room_number); // 클라가 선택한 방번호를 서버에 전송
        client_socket>>client_msg; // 서버로부터 포트를 수신

        // local address를 UDP 포트에 바인딩
        multiManager.set_localSock_port(std::stoi(client_msg));
        multiManager.bind_localSock();

        
        switch(fork()){
            case -1:
                std::cerr<<"fork() error\n";
                break;
            case 0: // 자식
                for(;;){
                    // write
                    std::cin>>client_msg;
                    client_socket<<client_msg;
                }
                break;
            default: // 부모
                for(;;){
                    if(!(multiManager.multicast_receive_process(databuf))){
                        std::cerr<<"receive error()\n";
                        exit(1);
                    }
                    std::cout<<"from server : "<<databuf<<'\n';     
                }
                break;
        }
    }
    catch(SocketException& e){
        std::cout<<"Exception was caught: "<<e.description()<<'\n';
    }
    return 0;
}