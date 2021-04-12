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
#include "semlib.h"
#include "getkey.cc"

using namespace std;

char client_message[2000];
char buffer[1024];
//pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

//Sem mutex1;

void * socketThread(void *arg) 
{
    int newSocket = *((int *)arg);
    recv(newSocket, client_message, 2000, 0); //use to get a message from a socket


    //pthread_mutex_lock(&mutex1); // Entrée Section critique
    char *message = (char*) malloc(sizeof(client_message)+20);
    strcpy(message, "Hello Client: ");
    strcat(message, client_message);
    strcat(message, "\n");
    strcpy(buffer, message);
    free(message);
    //pthread_mutex_unlock(&mutex1); // Sortie section critique

    sleep(1);

    send(newSocket, buffer,13, 0);
    cout << "Exit socketThread \n" << endl;
    close(newSocket);
    pthread_exit(NULL);
}

int main() 
{   
    
   /* mutex1 = Sem(getkey("gofp2701"),1);
    char *message = "Hello";
    int i = 1;

    mutex1.P();
    strcpy(message, "Hello Client: ");
    strcat(message, client_message);
    strcat(message, "\n");
    strcpy(buffer, message);
    free(message);
    mutex1.V(); */


    // Pcs(/*Code du serveur à lancer*/)




    /*int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(server != -1) {
        cout << "Socket error" << endl;
    }

    const short port = 9999;
    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    int res = bind(server,(sockaddr*) &addr, sizeof(addr));
    if(res != -1){
        cout << "Binding error" << endl;
    }

    res = listen(server,SOMAXCONN);
    if (res != -1) {
        cout << "Listen error" << endl;
    }

    cout << "Serveur démarre sur le port " << port << endl;

    sockaddr_in from = {0};
    socklen_t addrlen = sizeof(addr);
    int newClient = accept(server, (sockaddr*) &from, &addrlen);
    
    if (newClient != -1) {
        cout << "Connection reussi" << endl;
    }

    close(server);
    return 0;*/


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

        if( pthread_create(&tId[i++], NULL, socketThread, &newSocket) !=0)
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