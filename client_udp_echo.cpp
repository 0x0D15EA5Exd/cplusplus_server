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



#define IP_SERVER 10.0.200


using namespace std;

int main(){


    struct sockaddr_in dest_addr;

    struct sockaddr_in src_addr;
    socklen_t addr_len;

    std::string message;
    std::cin >> message;
    // creation socket
    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        cout << " Erreur creation socket, sock retured -1"<< endl;
        exit(1);
    }

    bzero(&dest_addr, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(4576);
    inet_aton("10.0.200.160", &dest_addr.sin_addr);


    const char * msg = message.c_str();
    for(int i; i<500 ; i++){
        if (sendto(sock,msg,strlen(msg), 0, (struct sockaddr*) &dest_addr, sizeof(dest_addr)) == -1) {
            cout << " Echec envoi" << endl;
            exit(1);
        }
    }

    if (sock == -1){
        std::cerr << " Socket creation ERROR" << std::endl;
        exit(1);
    }

    
    char buffer[256];
    
    bzero(&buffer,sizeof(buffer));

    if(recvfrom(sock, buffer, sizeof(buffer) , 0, (struct sockaddr*) &src_addr, &addr_len) == -1) {
        std::cout << "Echec récéption"<< endl;
        exit(1);
    }

    close(sock);




}
