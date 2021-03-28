#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
#include <iostream>

using namespace std;

void * clientThread(void * arg) 
{

    cout << "In thread" << endl;

    char message[1000];
    char buffer[1024];
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7799);
    serverAddr.sin_addr.s_addr = inet_addr("localhost");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    strcpy(message, "Hello");

    if( send(clientSocket, message, strlen(message), 0) < 0)
        cout << "send failed" << endl;
    
    if ( recv(clientSocket, buffer, 1024, 0) < 0)
        cout << "receive failed" << endl;
    
    cout << "Data received" << buffer << endl;

    close(clientSocket);
    pthread_exit(NULL);
}

int main() 
{
    int i = 0;
    pthread_t tId[51];

    while(i < 50) 
    {
        if( pthread_create(&tId[i], NULL, clientThread, NULL) != 0)
            cout << "Failed to create thread" << endl;
            i++;
    }
     
    sleep(20);
    i = 0;

    while (i<50)
    {
        pthread_join(tId[i++], NULL);
        cout << i << endl;
    }
    
    return 0; 
}