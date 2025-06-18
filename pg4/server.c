#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>       // for close()

#define PORT 12345
#define GROUP "225.0.0.37"
#define BUFSIZE 256

int main() {
    int sock;
    struct sockaddr_in addr;
    struct ip_mreq mreq;
    char buf[BUFSIZE];

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Listen on all interfaces
    addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    mreq.imr_multiaddr.s_addr = inet_addr(GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    while (1) {
        int n = recv(sock, buf, BUFSIZE, 0);
        if (n < 0) {
            perror("recv");
            exit(1);
        }
        buf[n] = '\0';
        printf("Received: %s\n", buf);
    }
}

