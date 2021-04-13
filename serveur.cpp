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


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main() 
{   
    
    char cip[] = "gofp270"; 
    key_t key = KEY_PORT;
    Port port = Port(key);


    msgbuffer msg;
    msg.m_type = 1;

    while (true) {

        port.Recoit(&msg, sizeof(msg)); 
        cout << "accepted reception ok" << endl; 
        cout << msg.m_texte << endl;

        size_t datasize;
        FILE* fd = fopen("file.txt", "wb");
        
        
        fwrite(&msg.m_texte, 1, sizeof(msg.m_texte), fd);

        fclose(fd);
    }
    
    return 0;
}