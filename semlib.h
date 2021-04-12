/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/*  Cette classe permet de creer des objet de type semaphore et    */
/*  definit cinq operations sur ces objet: creation,initialisation,*/
/*  destruction, P et V.                                           */
/*                                                                 */
/*******************************************************************/
/*******************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define P_OP -1
#define V_OP 1


union semun {
             int             val;
             struct semid_ds *buf;
             unsigned short  *array;
     };

class Sem {
   private:
      int semid;
   public:
      Sem();
      Sem(key_t key,int valeur);
      void Init(key_t key,int valeur);
      void P();
      void V();
      int val();
      void Detruit();
};