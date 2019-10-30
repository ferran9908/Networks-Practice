#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<sys/socket.h> 
#include<sys/types.h> 
#include<netinet/in.h> 
#include<unistd.h>
#include<arpa/inet.h> 

void handle(int check,char *msg){
	if(check<0){
		printf("%s\n",msg);
		exit(0);
	}
}

int main(){
    char name[30];
    char buff[1024];
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(1241);
	server.sin_addr.s_addr = INADDR_ANY;
	
	//Create Socket
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	handle(sockfd,"Cannot Create Socket");

    //Connect to Server
    int handler = connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    handle(handler,"Connect Error");

    printf("Connected!\n");

    //Send filename to client
    printf("Enter File Name:");
    scanf("%s",name);
    write(sockfd,name,sizeof(name));


    //Receive contents from server
    handler = read(sockfd,buff,sizeof(buff));
    handle(handler,"read error");
    buff[handler+1] = EOF;
    printf("%s",buff);


    //Create new file to store contents of server file
    char fname[30];
    printf("Enter file name to save:");
    scanf("%s",fname);
    FILE *fptr;
    fptr = fopen(fname,"w");
    if(fptr==NULL){
        printf("Try Again!");
        exit(0);
        }
    

    // read(sockfd,buff,sizeof(buff));

    // printf("%s",buff);

    //fprintf(fptr,"%s",buff);
    fwrite(buff,sizeof(buff)+1,1,fptr);

    printf("File Transfer Successful!");

    close(sockfd);
    fclose(fptr);


return 0;

}