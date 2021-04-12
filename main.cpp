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

//#include "semlib.h"


using namespace std;

typedef void Sigfunc(int);
Sigfunc *signal(int,Sigfunc *);




void fin(int no)
{

static int nb_crtl_c = 0;
nb_crtl_c++;

// Je laisse le 5e Crtl-c détruire le programme
// en remettant l'action par defaut (SIG_DFL)
if (nb_crtl_c > 1) signal(SIGINT, SIG_DFL);
}
//
// Routine qui traite les signaux de type CRTL-z
//
void suspendre(int no)
{
cout << "Non-- je ne veux pas etre suspendu" << endl;
}
//
// Programme qui attend les signaux...
//


int main()
{
 

char tab[] = "gofp2701";
key_t key = 12312323;
Port port = Port(key);

Pcs p_server;
Pcs p_client;

char c[] = "client";
char s[] = "server";

cout << "Starting" << endl;
p_server.Fork(s);

cout << "Starting " << 50 << " clients" << endl;

p_client.Fork(c);




// on veut empecher l'arret du processus par un crtl-z
signal(SIGTSTP,suspendre) ;
// on veut empecher la destruction du processus par on crtl-c
signal(SIGINT, fin) ;
signal(SIGQUIT, fin);
signal(SIGILL, fin);
signal(SIGBUS, fin);
signal(SIGFPE, fin);
signal(SIGSEGV,fin);
signal(SIGTERM, fin);
signal(SIGTSTP, fin);
signal(SIGXCPU, fin);
signal(SIGXFSZ, fin);
signal(SIGSYS, fin); 

// on boucle a l'infini
    while(1);
}

