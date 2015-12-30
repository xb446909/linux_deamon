/* xiong-bin@live.com
   compile command: gcc client.c -o client */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>

#define PORT 10000

#define BUFFER_SIZE 1024

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        printf("Usage: %s <command>.\nsuch as: %s \"ls\"\n", 
                argv[0], argv[0]);
        return 0;
    }

    struct sockaddr_in srv_addr;
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd < 0)
    {
        perror("Can not create socket");
        return 1;
    }

    char ret_buf[BUFFER_SIZE] = {0};
    int len = sizeof(srv_addr);

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(PORT);
    srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendto(socket_fd, argv[1], strlen(argv[1]) + 1, 0,
            (struct sockaddr*)&srv_addr, len);
    recvfrom(socket_fd, ret_buf, BUFFER_SIZE, 0,
             (struct sockaddr*)&srv_addr, &len);
    printf("%s", ret_buf);
    close(socket_fd);
    return 0;
}
