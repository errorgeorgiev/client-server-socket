#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>    
#include <sys/types.h>   
#include <arpa/inet.h>  
#include <err.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // create socket info structures
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1337);

    struct sockaddr client_info = {0};
    socklen_t server_info_len = sizeof(server_info);
    socklen_t client_info_len = sizeof(client_info);

    // create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0)
    {
        perror("socket error");
        return -1;
    }

    // bind
    if(bind(sfd, (struct sockaddr*)&server_info, server_info_len) < 0)
    {
        perror("bind error");
        return -1;
    }

    // listen
    if(listen(sfd,0) < 0)
    {
        perror("listen error");
        return -1;
    }

    //accept
    int cfd = accept(sfd, &client_info, &client_info_len);
    if(cfd < 0)
    {
        perror("accept error");
        return -1;
    }

    // do client stuff
    char* hello = "Hello World\n";
    ssize_t sent = send(cfd, (void*)hello, strlen(hello), 0);

    // clean up
    close(cfd);
}   
