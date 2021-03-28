#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
#include <iostream>

using namespace std;

char client_message[2000];
char buffer[1024];
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void * socketThread(void *arg) 
{
    int newSocket = *((int *)arg);
    recv(newSocket, client_message, 2000, 0); //use to get a message from a socket


    pthread_mutex_lock(&mutex1); // Entrée Section critique
    char *message = (char*) malloc(sizeof(client_message)+20);
    strcpy(message, "Hello Client: ");
    strcat(message, client_message);
    strcat(message, "\n");
    strcpy(buffer, message);
    free(message);
    pthread_mutex_unlock(&mutex1); // Sortie section critique

    sleep(1);

    send(newSocket, buffer,13, 0);
    cout << "Exit socketThread \n" << endl;
    close(newSocket);
    pthread_exit(NULL);
}

int main() 
{
    int serverSocket, newSocket;

    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;


    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(7799);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    if(listen(serverSocket, 50)==0)
        cout << "Listening" << endl;
    else
        cout << "Error..." << endl;
    
    pthread_t tId[60];
    int i = 0;

    while(1)
    {
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

        if(pthread_create(&tId[i++], NULL, socketThread, &newSocket) !=0)
            cout << "Faile dto create thread" << endl; 

        if( i >= 50)
        {
          i = 0;
          while(i < 50)
          {
            pthread_join(tId[i++],NULL);
          }
          i = 0;
        }
    }
    return 0;
}