#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void handle(int check,char *msg){
    if(check<0){
        printf("%s\n",msg);
        exit(0);
}
}
int main(int argc,char **argv){
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(1234);
    server_addr.sin_family = AF_INET;
    //Create Socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    handle(sockfd,"Socket Error");
    //Connect socket with server
    int handler = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    handle(handler,"Connect Error");
    printf("%d\n",handler);
    char buff[1024];
    printf("Enter a message to send to server:");
    scanf("%s",buff);

   // int n = write(sockfd,buff,sizeof(buff));
    int n = send(sockfd,buff,sizeof(buff),0);
    close(sockfd);

    return 0;
}
