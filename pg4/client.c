#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>       // for sleep()
#include <arpa/inet.h>    // for inet_addr(), htons()

#define PORT 12345
#define GROUP "225.0.0.37"

int main() {
    int sock;
    struct sockaddr_in addr;
    const char *msg = "RVCE-CSE";

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(GROUP);
    addr.sin_port = htons(PORT);

    while (1) {
        if (sendto(sock, msg, strlen(msg) + 1, 0, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("sendto");
            exit(1);
        }
        sleep(1);
    }
}

