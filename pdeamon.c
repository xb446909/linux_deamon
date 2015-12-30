/* xiong-bin@live.com
   compile command: gcc pdeamon.c -o pdeamon */

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

void executeShell(const char *shell, char* buf);

int main(int argc, char** argv)
{
    int socket_fd;
    char recv_buf[BUFFER_SIZE];
    char ret_buf[BUFFER_SIZE];
    int len, ret;
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in srv_addr, client_addr;
    if(socket_fd < 0)
    {
        perror("Can not create socket");
        return 1;
    }
    
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(PORT);
    srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ret = bind(socket_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if(ret < 0)
    {
        perror("Can not bind socket");
        close(socket_fd);
        return 1;
    }
    len = sizeof(client_addr);
    while(1)
    {
        memset(recv_buf, '\0', BUFFER_SIZE);
        recvfrom(socket_fd, recv_buf, BUFFER_SIZE, 0,
                (struct sockaddr*)&client_addr, &len);
        executeShell(recv_buf, ret_buf);
        printf("shell: %s\n%s", recv_buf, ret_buf);
        usleep(10000);
        sendto(socket_fd, ret_buf, strlen(ret_buf) + 1, 0,
                (struct sockaddr*)&client_addr, len);
    }
    close(socket_fd);
    return 0;
    
}

void executeShell(const char *shell, char* buf)
{
    FILE *stream;
    memset( buf, '\0', BUFFER_SIZE );
    stream = popen( shell , "r" );
    fread( buf, sizeof(char), BUFFER_SIZE, stream);
    pclose( stream );
}
