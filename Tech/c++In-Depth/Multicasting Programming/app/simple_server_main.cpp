#include "MulticastManager.h"
#include "ClientRoomManager.h"
#include <string>
#include <iostream>
#include <vector>
#include "FdManager.h"
#include "SocketBase.h"
#include "SocketException.h"
#include "ServerSocket.h"
#include <string.h>

int main(int argc, char* argv[]){
    std::cout<<"running... \n";
    char chat[MAXRECV+1]; // 채팅에 사용되는 버퍼
    char announceMent[] = "[chat room #1] [chat room #2]";
    int announceMent_s = sizeof(announceMent);
    int str_len=0;
    int i=0;

    // 클라이언트 채팅방 관리 클래스
    ClientRoomManager clientManager;
    int client_multicast_port=0;
    std::string int_to_string;

    MulticastManager multiManager; // datagram socket create()
    multiManager.set_group_sock_addr(); // multicast address setting..
    multiManager.set_interface_addr(); // interface address setting..

    try{
        ServerSocket server(30000); // create(), bind(), listen()
        ServerSocket new_sock; // client socket

        int server_fd = server.getServerFileDescriptor();
        int client_fd = 0;
        FdManager fdManager(server_fd); // fd_zero(), fd_set()

        while(true){
            if(fdManager.do_select() == -1){
                std::cerr<<"select() error\n";
                break;
            }

            for(i=0; i<fdManager.get_max_fd()+1; ++i){
                if(fdManager.is_set(i)){
                    if(i == server_fd){
                        server.accept(new_sock);
                        client_fd = new_sock.getServerFileDescriptor();
                        std::cout<<"accept socket descriptor : "<<client_fd<<'\n';
                        fdManager.set_reads(client_fd); // 클라이언트 소켓을 읽기 전용 상태로 설정
                        write(client_fd, announceMent, announceMent_s); // 현재 수용 가능한 채팅방 알림 
                        clientManager.set_status_false(client_fd);
                    }
                    else{
                        memset(chat, 0, MAXRECV+1);
                        if((str_len = recv(i, chat, MAXRECV, 0)) < 0){
                            std::cerr<<"recv() error\n";
                            break;
                        }
                        // 방을 아직 배정받지 않았을 경우
                        if(!clientManager.get_client_status(i)){ 
                            clientManager.set_client_room_status(i, chat[0]-'0'); // 클라이언트의 방 번호 선택에 따른 포트 번호 할당
                            clientManager.set_status_true(i); // 포트 배정 완료
                            // 클라이언트의 선택으로부터 할당된 포트를 다시 클라이언트에게 알려주는 부분
                            client_multicast_port = clientManager.get_client_room_port(i);
                            int_to_string = std::to_string(client_multicast_port);
                            std::cout<<"int_to_string : "<<int_to_string<<'\n';
                            send(i, int_to_string.c_str(), int_to_string.size(), 0);
                        }
                        else{ // 방을 이미 배정받았을 경우
                            multiManager.set_group_sock_port(clientManager.get_client_room_port(i));
                            std::cout<<i<<", port : "<<clientManager.get_client_room_port(i)<<'\n';

                            if(!(multiManager.multicast_sendto_process(chat, str_len+1))){
                                std::cerr<<"sendto() fail\n";
                            } 
                        }
                    }
                }
                // end of if_set()
            }
            std::cout<<'\n';
        }
    }
    catch(SocketException& e){
        std::cerr<<"Exception was caught: "<<e.description()<<"\nExiting.\n";
    }
}