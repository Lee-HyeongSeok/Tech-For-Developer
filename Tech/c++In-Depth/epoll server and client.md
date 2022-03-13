## epoll server & client

***



간단한 에코 epoll 서버&클라이언트

서버는 클라이언트의 메시지를 받아서 반환하는 작업

클라이언트는 사용자에게 입력받은 메시지를 서버에 전송하고 다시 반환받는 작업

<br>

### :pushpin: server

```c++
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 100
#define EPOLL_SIZE 50

int main(){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];
    
    struct epoll_event ep_events[1024];
    struct epoll_event event;
    
    int epfd, event_cnt;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_adr.sin_port = htons(30000);
    
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(*serv_adr)) == -1){
        std::cerr<<"에러처리";
    }
    
    if(listen(serv_sock, 5) == -1){
        std::cerr<<"에러처리";
    }
    
    epfd = epoll_create(EPOLL_SIZE);
    memset(&ep_events, 0, 1024);
    event.events = EPOLLIN;
    event.data.fd=serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
    
    while(true){
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        
        if(event_cnt == -1)
            break;
        
        for(i=0; i<event_cnt; ++i){
            if(ep_events[i].data.fd == serv_sock){
                adr_sz = sizeof(clnt_adr);
                clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
                
                event.events=EPOLLIN;
                event.data.fd= clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                std::cout<<"connect clnt"<<clnt_sock<<'\n';
            }
            else{
                std_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                if(str_len == 0){
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                }
                else{
                    write(ep_events[i].data.fd, buf, str_len);
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}
```



<br>

### :pushpin: client

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

int main(){
    char buf[BUF_SIZE];
    
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        std::cerr<<"에러처리";
    }
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(30000);
    
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        std::cerr<<"에러처리";
    
    while(true){
        memset(buf, 0x00, BUF_SIZE);
        read(0, buf, BUF_SIZE);
        
        if(write(sock, buf, BUF_SIZE) <= 0)
            std::cerr<<"에러처리";
        int str_len;
        str_len = read(sock, buf, BUF_SIZE);
        if(str_len == 0)
            std::cerr<<"에러처리";
        std::cout<<"server : "<<buf<<'\n';
    }
    
    close(sock);
    return 0;
}
```

