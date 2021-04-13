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

#include <iostream>
#include <string>
#include <cstring>

#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <sys/types.h>


#include "getkey.cc"
#include "pcslib.h"
#include "msglib.h"
#include "memlib.h"

#include "msg.h"

using namespace std;

int error = errno;
//short htons(short value); local -> reseau
//short ntohs(short value); reseau -> local


int main() 
{   


    char cip[] = "gofp270"; 
    key_t key = KEY_PORT;
    Port port = Port(key);


    msgbuf msg;

    msg.m_type = 1;

    port.Envoie(&msg, sizeof(msg)); 
    cout << "accepted send ok" << endl; 
    cout << msg.m_texte << endl;
    
    FILE *fd = fopen("file.txt", "rb");

    size_t rret, wret;

    int bytes_read;

    while (!feof(fd)) {

        if ((bytes_read = fread(&msg.m_texte, 1, sizeof(msg), fd)) > 0)
            port.Envoie(&msg, sizeof(msg));
        else
            break;
    }

    fclose(fd);
    
    return 0; 
}