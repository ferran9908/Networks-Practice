#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

void handle(int check,char *msg){
    if(check<0){
        printf("%s\n",msg);
        exit(0);
}
}

int main(int argc,char **argv){
    int handler;int n;
    char buff[1024];
    struct sockaddr_in server_addr,client_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //Create Socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    handle(sockfd,"Socket Error");

    //Bind Socket
    handler = bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    handle(handler,"Bind Error");

    //Listen for Incoming Connections
    handler = listen(sockfd,1);
    handle(handler,"Listen Error");
    int newfd;
    //Accept Connection
    int len = sizeof(client_addr);
    newfd = accept(sockfd,(struct sockaddr*)&client_addr,&len);
    handle(newfd,"Accept Error");
    

    //Read from client 
    //int n = read(newfd,buff,sizeof(buff));

     n = recv(newfd,buff,sizeof(buff),0);
    printf("%s\n",buff);
    
    close(newfd);
    close(sockfd);
    return 0;
}