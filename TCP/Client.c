// Client side implementation of TCP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 
#define size 15

// Driver code 
int main() { 
	int sockfd; 
	int buffer[MAXLINE]; 
	int arr[15]= {1,2,3,21,32,4,36,543,54,64,75,234,567,4324,675};
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len=sizeof(servaddr); 
	
	sendto(sockfd, (const int*)arr, 15*sizeof(int), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
	printf("Array send to server!!!!!!.\n"); 
		
	n = recvfrom(sockfd, (int *)buffer, MAXLINE, 0, (struct sockaddr *) &servaddr, &len); 
	//buffer[n] = '\0'; 
	write(1,buffer,size); 
	
	
	close(sockfd); 
	return 0; 
} 
