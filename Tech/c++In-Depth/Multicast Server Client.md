## Multicast Server Client

***

<br>

### :pushpin: Server

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define INADDR_RIP_GROUP   0xe0000009    /* 224.0.0.9 */
#define INADDR_RIP_PORT    520
#define MAX_MESSAGE_LENGTH 4096

int   gMulticastSock;
void SetMulticastSocket(struct in_addr gMulticastGroup, unsigned short gMulticastPort)
{
  struct in_addr group;
  struct sockaddr_in servaddr;
  struct in_addr ifAddr0; //eth0
  struct in_addr ifAddr1; //eth1
  struct in_addr ifAddr2; // eth2

  printf("==> mAddr = %s\n", inet_ntoa(gMulticastGroup));
  printf("==> mPort = %d\n", gMulticastPort);
    
  gMulticastSock = socket(AF_INET, SOCK_DGRAM, 0);
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(gMulticastPort);

  bind(gMulticastSock, (struct sockaddr *)&servaddr,sizeof(servaddr));

  group.s_addr  = gMulticastGroup.s_addr;
  ifAddr0.s_addr = inet_addr("129.254.73.196"); // installed IP Address on eth0
  ifAddr1.s_addr = inet_addr("1.1.1.1"); // installed IP Address on eth1
  ifAddr2.s_addr = inet_addr("3.3.3.2"); // installed IP Address on eth2

 struct ip_mreqn mreqn;
 mreqn.imr_multiaddr.s_addr = group.s_addr;
 mreqn.imr_address = ifAddr0;
 mreqn.imr_ifindex = 2;  // should check interface index

    // add memership on eth0
int ret = setsockopt(gMulticastSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mreqn, sizeof(mreqn));

if(ret < 0)
{
    perror("setsockopt");
}


  // add memership on eth1
  mreqn.imr_address = ifAddr1;
  mreqn.imr_ifindex = 3;  // should check interface index
  ret = setsockopt(gMulticastSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mreqn, sizeof(mreqn));
  if(ret < 0)
  {
    perror("setsockopt");
  }

  // add memership on eth2
  mreqn.imr_address = ifAddr2;
  mreqn.imr_ifindex = 4;  // should check interface index
  ret = setsockopt(gMulticastSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mreqn, sizeof(mreqn));
  if(ret < 0)
  {
    perror("setsockopt");
  }
}
int main(int argc, char ** argv)
{
  struct in_addr group;
  unsigned short port;
  if(argc != 3)
  {
     printf("usage: mcast-server <Multicast IP> <Udp Port>");
     exit(1);
  }

  group.s_addr = inet_addr(argv[1]);
  port = atoi(argv[2]);

  SetMulticastSocket(group, port);
  while(1)
  {
    char  msgBuf[MAX_MESSAGE_LENGTH] = {};
    int n = recvfrom(gMulticastSock, msgBuf, MAX_MESSAGE_LENGTH, 0, NULL, NULL);
    printf("receive message n=%d, data=%s\n", n, msgBuf);
  }
  return 0;
}
```



```c++
#include <sys/socket.h>

#include <netinet/in.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

 

#define SOCKET_RIP_PORT 520

 

int main(int argc, char**argv)

{

   int sockfd, n, port;

   struct sockaddr_in groupAddr;

   char msgBuff[1000]={};

 

   if (argc != 3)

   {   

      printf("usage:  mcast-client <IP Address> <Udp Port>\n");

      exit(1);

   }   

 

   sockfd=socket(AF_INET, SOCK_DGRAM, 0); 

 

   bzero(&groupAddr, sizeof(groupAddr));

   groupAddr.sin_family = AF_INET;

   groupAddr.sin_addr.s_addr = inet_addr(argv[1]);

   groupAddr.sin_port = htons(atoi(argv[2]));

 

   // Multicast Socket  

   // This Socket Option is Optional...

#if 0

   struct in_addr localIf;

   //localIf.s_addr = inet_addr("129.254.73.196");

   localIf.s_addr = inet_addr("129.254.73.196");

   if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF,

                  (char *)&localIf, sizeof(localIf)) < 0) {

     perror("setting local interface");

     exit(1);

   }

#endif

  

   // send message

   strcpy(msgBuff, "Hello N2os Message");

   sendto(sockfd, msgBuff, strlen(msgBuff),0, 

          (struct sockaddr *)&groupAddr,sizeof(groupAddr));

    

   return 0;

}
```



```netstat -gn``` 명령으로 각 인터페이스에 해당 멀티캐스트 그룹 정보가 설정됨을 확인해야 한다.