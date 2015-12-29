/* xiong-bin@live.com
   compile command: gcc client.c -o client */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_DOMAIN "/tmp/UNIX.domain"

#define BUFFER_SIZE 1024

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        printf("Usage: %s <command>.\nsuch as: %s \"ls\"\n", 
                argv[0], argv[0]);
        return 0;
    }

    struct sockaddr_un srv_addr;
    int socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(socket_fd < 0)
    {
        perror("Can not create socket");
        return 1;
    }

    int len = sizeof(srv_addr);

    srv_addr.sun_family = AF_UNIX;
    strcpy(srv_addr.sun_path, UNIX_DOMAIN);
    sendto(socket_fd, argv[1], strlen(argv[1]) + 1, 0,
            (struct sockaddr*)&srv_addr, len);
    close(socket_fd);
    return 0;
}
