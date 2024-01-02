// Server side implementation of TCP client-server model 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    int arr[MAXLINE]={};
    char *hello = "!!!!!!!!!!!!!!DONE!!!!!!!!!!!!!!!!!!\n";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len = sizeof(cliaddr);
    int n = recvfrom(sockfd, (int *)arr, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
    // buffer[n] = '\0';
    //write(1, arr, 22);

    for (int i = 0; i < 15; i++)
    {
        printf(" %d", arr[i]);
    }

    int max = arr[0];
    int min = arr[0];

    // Loop through the array
    for (int i = 0; i < 15; i++)
    {
        // Compare elements of array with max
        if (arr[i] > max)
        {
            max = arr[i];
        }
        else if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    int rep_max = 0, rep_min = 0;


    for (int i = 0; i < 22; i++)
    {
       if(max==arr[i]){
        rep_max++;
       }
       else if(min==arr[i]){
        rep_min++;
       }
    }

    printf("\nMax number is = %d and it repeated = %d\n",max,rep_max);
     printf("Min number is = %d and it repeated = %d\n",min,rep_min);
    

    sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));

    return 0;
}

