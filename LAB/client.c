#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE  1024

int main() {
    int mainSocket;
    char receiveBuffer[MAXLINE];
    char sendBuffer[MAXLINE];

    fd_set readFds;
    int maxSd = 0;

    struct sockaddr_in serverAddress;

    if ((mainSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int addressLength = sizeof(serverAddress);

    connect(mainSocket, (struct sockaddr *) &serverAddress, addressLength);

    printf("\nConnection to the server established.\n");

    while (1) {
        int stdinSocket = STDIN_FILENO;
        FD_ZERO(&readFds);
        FD_SET(mainSocket, &readFds);
        FD_SET(stdinSocket, &readFds);

        if (maxSd < mainSocket)
            maxSd = mainSocket;

        if (maxSd < stdinSocket)
            maxSd = stdinSocket;

        select(maxSd + 1, &readFds, NULL, NULL, NULL);

        if (FD_ISSET(mainSocket, &readFds)) {
            int receivedBytes = recv(mainSocket, receiveBuffer, MAXLINE, 0);

            receiveBuffer[receivedBytes] = '\0';

            printf("(Client <-- Server): %s\n", receiveBuffer);
        }

        if (FD_ISSET(stdinSocket, &readFds)) {
            scanf("%s", sendBuffer);

            send(mainSocket, sendBuffer, strlen(sendBuffer), 0);

            printf("(Client --> Server): %s\n", sendBuffer);

            if (sendBuffer[0] == 'e' || sendBuffer[0] == 'E') {
                break;
            } else {
                scanf("%s", sendBuffer);

                send(mainSocket, sendBuffer, strlen(sendBuffer), 0);

                printf("(Client --> Server): %s\n", sendBuffer);
            }
        }
    }

    printf("\nConnection to the server closed.\n");

    close(mainSocket);
    return 0;
}
