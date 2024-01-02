#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT     8080
#define MAXLINE  1024

int calculateSum(int val1, int val2) {
    return val1 + val2;
}

int calculateSubtraction(int val1, int val2) {
    return val1 - val2;
}

int calculateMultiplication(int val1, int val2) {
    return val1 * val2;
}

float calculateDivision(int val1, int val2) {
    return (float) val1 / val2;
}

int main() {
    int mainSocket;
    int backlog = 5;
    char receiveBuffer[MAXLINE];
    char sendBuffer[MAXLINE];

    struct sockaddr_in serverAddress, clientAddress;

    if ((mainSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    memset(&clientAddress, 0, sizeof(clientAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(mainSocket, (const struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(mainSocket, backlog);

    printf("\nServer active...\n");

    while (1) {
        int clientLength = sizeof(clientAddress);

        int newSocket = accept(mainSocket, (struct sockaddr *) &clientAddress, (socklen_t *) &clientLength);

        printf("\nConnection established with client...\n");

        sprintf(sendBuffer, "Hi.");

        send(newSocket, sendBuffer, strlen(sendBuffer), 0);

        printf("Data sent to client: \"%s\"\n", sendBuffer);

        while (1) {
            sprintf(sendBuffer, "\nPlease enter any two numbers (enter number one by one) or type EXIT to exit.\nYour Option: ");

            send(newSocket, sendBuffer, strlen(sendBuffer), 0);

            printf("Data sent to client: \"%s\"\n", sendBuffer);

            int receivedBytes = recv(newSocket, receiveBuffer, MAXLINE, 0);

            receiveBuffer[receivedBytes] = '\0';

            printf("Data received from client: \"%s\"\n", receiveBuffer);

            if (tolower(receiveBuffer[0]) == 'e') {
                sprintf(sendBuffer, "Exiting...\n");

                send(newSocket, sendBuffer, strlen(sendBuffer), 0);

                printf("Data sent to client: \"%s\"\n", sendBuffer);

                break;
            } else {
                int value1 = atoi(receiveBuffer);

                receivedBytes = recv(newSocket, receiveBuffer, MAXLINE, 0);

                receiveBuffer[receivedBytes] = '\0';

                printf("Data received from client: \"%s\"\n", receiveBuffer);

                int value2 = atoi(receiveBuffer);

                printf("Numbers entered: %d, %d\n", value1, value2);

                sprintf(sendBuffer, "Sum: %d + %d = %d\n", value1, value2, calculateSum(value1, value2));

                send(newSocket, sendBuffer, strlen(sendBuffer), 0);

                printf("Data sent to client: \"%s\"\n", sendBuffer);

                sprintf(sendBuffer, "Subtraction: %d - %d = %d\n", value1, value2,
                        calculateSubtraction(value1, value2));

                send(newSocket, sendBuffer, strlen(sendBuffer), 0);

                printf("Data sent to client: \"%s\"\n", sendBuffer);

                sprintf(sendBuffer, "Multiplication: %d * %d = %d\n", value1, value2,
                        calculateMultiplication(value1, value2));

                send(newSocket, sendBuffer, strlen(sendBuffer), 0);

                printf("Data sent to client: \"%s\"\n", sendBuffer);

                sprintf(sendBuffer, "Division: %d / %d = %.2f\n", value1, value2, calculateDivision(value1, value2));

                send(newSocket, sendBuffer, strlen(sendBuffer), 0);

                printf("Data sent to client: \"%s\"\n", sendBuffer);
            }
        }

        printf("\nConnection with client closed...\n");

        close(newSocket);
    }

    return 0;
}
