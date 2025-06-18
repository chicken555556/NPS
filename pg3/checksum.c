#include <stdio.h>

unsigned fields[11];

unsigned short checksum(int n) {
    int i;
    int sum = 0;
    printf("Enter %d 16-bit words in hex:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%x", &fields[i]);
        sum += fields[i];
        while (sum >> 16) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
    }
    sum = ~sum;
    return (unsigned short) sum;
}

int main() {
    unsigned short sender_checksum, receiver_checksum;

    
    sender_checksum = checksum(10);
    printf("\nSender Checksum: %04X\n", sender_checksum);

    
    receiver_checksum = checksum(11);
    printf("\nReceiver checksum result: %04X\n", receiver_checksum);

    if(receiver_checksum == 0x0000)
        printf(" No error in data\n");
    else
        printf("Error in received data\n");

    return 0;
}

