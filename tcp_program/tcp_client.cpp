#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //0. Judging the number of parameters
    if (argc < 3)
    {
        printf("usage: ./tcp_client <server_ip> <server_port>\n");
        return -1;
    }
    //1. create socket
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("create socket failed");
        return -1;
    }

    //2. connect peer socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sockfd, (sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connecting to server failed......\n");
        return -1;
    }
    printf("connecting to server success\n");
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    for (auto index = 1; index <= 10; ++index)
    {
        snprintf(buffer, sizeof(buffer), "this is index: %d message.", index);
        if (write(sockfd, buffer, sizeof(buffer)) <= 0)
        {
            printf("write to server failed\n");
            return -1;
        }

        if (read(sockfd, buffer, sizeof(buffer)) <= 0)
        {
            printf("send to client failed\n");
            return -1;
        }
        printf("%s\n", buffer);
    }
    close(sockfd);
}