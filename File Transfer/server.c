#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void handle(int check,char *msg){
	if(check<0){
		printf("%s\n",msg);
		exit(0);
	}
}
int main(int argc,char **argv){
	char name[30];
	char buff[1024];

	struct sockaddr_in server,client;
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(1241);
	server.sin_addr.s_addr = INADDR_ANY;
	
	//Create Socket
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	handle(sockfd,"Cannot Create Socket");

	//Bind Socket
	int handler = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	handle(handler,"Bind Error");

	//Listen for incoming connections
	handler = listen(sockfd,1);
	handle(handler,"Listen Error");

	//Accept connection
	int len = sizeof(client);
	int newfd = accept(sockfd,(struct sockaddr*)&client,&len);
	handle(newfd,"Accept Error");

	printf("Connected!\n");
	
	//Get filename from client
	read(newfd,name,sizeof(name));

	printf("\nname:%s\n",name);

	FILE *fptr;
	if((fptr=fopen(name,"r"))==NULL)
		{
			printf("File Does not exist\n");
			exit(0);
		}
	memset(&buff,0,sizeof(buff));
//	fscanf(fptr,"%s",buff);
	fread(buff,sizeof(buff)+1,1,fptr);

	printf("Buffer: %s\n",buff);
	
	write(newfd,buff,sizeof(buff));

	printf("File Transfered");
	close(newfd);
	close(sockfd);
	fclose(fptr);
	return 0;

}