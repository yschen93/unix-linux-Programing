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
    if (argc < 2)
    {
        printf("usage: ./tcp_server <port>\n");
        return -1;
    }
    //1. create socket
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("create socket failed");
        return -1;
    }

    //2. bind local address
    //2.0 construct sockaddr_in struct
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    
    //2.1 bind address
    if (bind(sockfd, (sockaddr *)(&server_addr), sizeof(server_addr)) < 0)
    {
        perror("bind local address failed");
        return -1;
    }

    //3. listen
    if (listen(sockfd, 5) < 0)
    {
        perror("server listen failed");
        return -1;
    }
    while (1);
    //4. accept client connection
    sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t addr_len = sizeof(client_addr);
    printf("wating for connecting......\n");
    int clientfd = accept(sockfd, (sockaddr *)&client_addr, &addr_len);
    if (clientfd < 0)
    {
        perror("server accept failed");
        return -1;
    }
    printf("accept client: %s : %d connection!\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

    close(sockfd);
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    while (true)
    {
        if (read(clientfd, buffer, sizeof(buffer)) <= 0)
        {
            printf("recv from client failed\n");
            return -1;
        }
        printf("recv from client: %s\n", buffer);
        
        strcpy(buffer, "send to server success");
        if (write(clientfd, buffer, sizeof(buffer)) <= 0)
        {
            printf("send to client failed\n");
            return -1;
        }
    }
    close(clientfd);
}