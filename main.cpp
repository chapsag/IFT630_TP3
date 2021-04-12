#include <iostream>
#include <signal.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>


#include "getkey.cc"
#include "pcslib.h"
#include "msglib.h"
#include "memlib.h"
#include "semlib.h"


using namespace std;

typedef void Sigfunc(int);
Sigfunc *signal(int,Sigfunc *);



void fin(int no)
{

static int nb_crtl_c = 0;
cout << "Il y a eu " << nb_crtl_c << " Crtl-c, je ne termine pas " << endl;
nb_crtl_c++;

// Je laisse le 5e Crtl-c détruire le programme
// en remettant l'action par defaut (SIG_DFL)
if (nb_crtl_c > 4) signal(SIGINT, SIG_DFL);
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
 

//char *tab = "gofp2701";
//key_t mdrccajemetue = getkey(tab);
//Port port1 = Port( mdrccajemetue);

Pcs p_server;
Pcs p_client[50];

cout << "Starting";
p_server.Fork("server");

cout << "Starting" << 50 << "clients";

for (int i = 0; i < 50; i++) {
    p_client[i].Fork("client");
}




// on veut empecher l'arret du processus par un crtl-z
signal(SIGTSTP,suspendre) ;
// on veut empecher la destruction du processus par on crtl-c
signal(SIGINT,fin) ;
cout << "Le programme principal démarre ..........." << endl;
// on boucle a l'infini
    while(1);
}

