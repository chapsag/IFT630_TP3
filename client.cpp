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
#include <errno.h>

using namespace std;

int error = errno;
//short htons(short value); local -> reseau
//short ntohs(short value); reseau -> local

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

    /*int clientSocket;
    int port = 6666;
    const char* ipadrress = "127.0.0.1";


    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ipadrress);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    sockaddr_in addr = {0};
    socklen_t len = sizeof(addr);
    
    // int newClient = accept(server, (sockaddr*)&addr, &len);

    if (connect(clientSocket, (struct sockaddr *) &server, sizeof(server)) != 0) {
        cout << "This is a problem" << endl;
    }

    cout << "Socket connected" << endl;
    close(clientSocket); */



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