#include "inet.h"

int main(int argc, char *argv[])
{
	int sockfd, new_sockfd, clilen;
	struct sockaddr_in serv_addr, cli_addr;
	char buffermax[1025];
	time_t timeval;
	int n=0;
	int pid;
	

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		perror("SERVER : socket() error\n");
		exit(1);
	}
	
	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	//serv_addr.sin_addr.s_addr = htonl("10.0.2.15");
	serv_addr.sin_port = htons(SERV_TCP_PORT);
	serv_addr.sin_addr.s_addr= inet_addr("10.0.2.15");
	

	bind(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));

	char *buf; 
	buf=(char *)malloc(10*sizeof(char)); 
	buf=getlogin(); 
	
	char place[30]; 
	strcpy(place, "/home/"); 
	strcat(place, buf); 
	strcat(place, "/serv_file/");

	struct stat st; 
	if(stat(place, &st) == -1){ 
	mkdir(place, 0700); }	

	listen(sockfd, 5);
	
	while(1)
	{
		printf("---------------Waiting connection from client---------------");
		clilen = sizeof(cli_addr);
		new_sockfd=accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
		printf("\n Client connected now. \n");
		printf("\nServer: Get connection from client %s\n",inet_ntoa(cli_addr.sin_addr));
		
		pid=fork();
		if(pid==0){
			strcat(buffermax, "\n1)Create\n2)File List\n3)Delete\n4)Upload\n5)Download\nEnter(1,2,3,4,5) :");
			send(new_sockfd, buffermax, 1025,0);
			
			bzero( buffermax, sizeof(buffermax));
			recv(new_sockfd, buffermax, 1025, 0);
				 if(!strcmp(buffermax, "1"))
				{
		
				bzero( buffermax, sizeof(buffermax));
				recv(new_sockfd, buffermax, 1025, 0);
				printf("filename:%s\n",buffermax);
				
				}


				else if(!strcmp(buffermax, "4"))
				{	
					/*

					DIR *dir;
					struct dirent *ent;

					char directory_name[30];
			   		strcpy(directory_name, "/home/"); 
			    		strcat(directory_name, buf); 
			    		strcat(directory_name, "/ser_file/");

					if ((dir = opendir (directory_name)) != NULL)
						 {
		
						 
			 			while ((ent = readdir (dir)) != NULL) 
							{

								strcat(buffermax, ent->d_name);
								strcat(buffermax, "\n");
			 				}
			 		 	closedir (dir);
						send(new_sockfd, buffermax, 1025, 0);
					 
						}
					
					else 
					{

			  		
			 		 perror ("Directory does not exist...");
			  		exit(0);
					}

					*/

		
					bzero( buffermax, sizeof(buffermax));
					recv(new_sockfd,buffermax, 1025, 0);


				    	strcat(place, buffermax);
				    //printf("%s\n",place);
					FILE *fp;
			   	 	fp = fopen(place, "wb+"); 
					int length=0;
					while(length=recv(new_sockfd,buffermax,1025,0))
					{
							if(length<0)
							{
								perror("recv");
								exit(1);
							}
						int writelen=fwrite(buffermax,sizeof(char),length,fp);
						if(writelen<length)
						{
							perror("write");
							exit(1);
						}
						bzero( buffermax, sizeof(buffermax));
					}
					
					bzero( buffermax, sizeof(buffermax));
					recv(new_sockfd, buffermax, 1025, 0);
					printf("successful reveived\n");
					strcat(buffermax,place);
					fwrite(buffermax,1,n,fp);
					fclose(fp);
					
					

					
					}

				
				else if(!strcmp(buffermax, "3"))
				{
					bzero( buffermax, sizeof(buffermax));
					strcat(buffermax,"Managed to delete Directory... [/q to quit]");
				}

			else if(!strcmp(buffermax, "5"))
		{
			bzero( buffermax, sizeof(buffermax));
			recv(new_sockfd,buffermax, 1025, 0);
			strcat(place,buffermax);
			//printf("%s\n",place);
			FILE *fp=fopen(place,"rb");
			
			bzero(buffermax,sizeof(buffermax));
			int file_block_length=0;
			while((file_block_length=fread(buffermax,sizeof(char),1025,fp))>0)
			{
			printf("file_block_length:%d\n",file_block_length);
			if(send(new_sockfd,buffermax,file_block_length,0)<0)
			{
			perror("Send");
			exit(1);
			}
			bzero(buffermax,sizeof(buffermax));
			}
			fclose(fp);
			printf("Transfer file finished !\n");
			
		}





				if(n==0)
				{
				close(new_sockfd);
				break;
				}
				//buf[n]=0;
				//send(new_sockfd,buf,1025,0); 
			
			//exit(0);
		
		else
		{
		close(new_sockfd);//sock is closed BY PARENT
		}
		}//close exterior while

		
	}
return 0;		
}

