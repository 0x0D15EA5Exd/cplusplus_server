#include <iostream>
#include <cstring>
#include <strings.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define  PORT 5896


int main()
{
    struct sockaddr_in addr_srv;
    struct sockaddr_in src_addr;
    socklen_t addr_len;


    int sock;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock == -1 )
    {
        std::cout << "Erreur socket " << std::endl;
        exit(1);
    }

    bzero(&addr_srv, sizeof(addr_srv));

    addr_srv.sin_family = AF_INET;
    addr_srv.sin_port = htons(PORT);
    addr_srv.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr*) &addr_srv, sizeof(addr_srv)) == -1)
    {
        std::cout << "bind error" << std::endl;
        close(sock);
        exit(1);
    }

    char buff[256];

    int msgCout;


    while( msgCout < 50)
    {
        memset(buff,0,sizeof(buff));



    }










    memset(buff,0,sizeof(buff));

    bzero(&src_addr, sizeof(src_addr));
    if(recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr*) &src_addr, &addr_len) == -1)
    {
        std::cout << "recvfrom error" << std::endl;
        close(sock);
        exit(1);
    }

    std::cout << "receive from :" << inet_ntoa(src_addr.sin_addr) <<"\n"<< "Message receive :" << buff << std::endl;

    if(sendto(sock, buff, strlen(buff), 0, (struct sockaddr*) &src_addr, sizeof(src_addr)) ==-1)
    {
        std::cout << "Send to error" << std::endl;
        close(sock);
        exit(1);
    }
    close(sock);
}
