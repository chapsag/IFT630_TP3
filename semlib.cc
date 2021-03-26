/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/*  Implantation des operations de la classe semaphore             */    
/*                                                                 */
/*******************************************************************/
/*******************************************************************/
#include "semlib.h"

/*******************************************************************/
/*                                                                 */
/*                   C o n s t r u c t e u r                       */
/*                                                                 */
/*  Cette routine permet de creer un semaphore a partir d'une cle  */
/*  specifiee par l'usager.  Cette cle (qui doit etre numerique ou */
/*  convertit en numerique par la fonction getkey) est unique et   */
/*  est associee a un seul semaphore.  Si la cle specifiee n'est   */
/*  associee a aucun semaphore alors le systeme cree un nouveau    */
/*  semaphore et retourne le nouvel identificateur (semid) associe */
/*  a ce nouveau semaphore.  Si la cle est deja associee a un      */
/*  semaphore alors le systeme retourne le "semid" de ce semaphore.*/
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    key : cle specifiee par l'usager qui permet au systeme de    */
/*          creer un nouveau semaphore et de retourner le nouvel   */
/*          identificateur ou de retourner l'identificateur du     */
/*          semaphore deja associe a cette cle.                    */
/*                                                                 */
/*    valeur : valeur initiale du semaphore (si le semaphore       */
/*             existe deja ce parametre est ignore).               */
/*                                                                 */
/*******************************************************************/
using namespace std;

Sem::Sem(key_t key,int valeur)
{
  union semun arg;
  arg.val = valeur;  
  if ((semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0666)) == -1)
    {   
      if ((semid = semget(key, 1, IPC_CREAT|0666)) == -1)
         perror("Classe Sem Constructeur erreur a la creation");
    }
  else  
    {
      if (semctl(semid, 0, SETVAL, arg) == -1)
         perror("Classe Sem Constructeur erreur a l'initialisation");
    }
}

/*******************************************************************/
/*                                                                 */
/*                   C o n s t r u c t e u r                       */
/*                                                                 */
/*  Cette routine cree un cadre pour un semaphore qui devra etre   */
/*  initialise par la fonction init.                               */
/*                                                                 */
/*******************************************************************/
Sem::Sem()
{}

/*******************************************************************/
/*                                                                 */
/*                                I n i t                          */
/*                                                                 */
/*  Cette routine permet de creer un semaphore a partir d'une cle  */
/*  specifiee par l'usager.  Cette cle (qui doit etre numerique ou */
/*  convertit en numerique par la fonction getkey) est unique et   */
/*  est associee a un seul semaphore.  Si la cle specifiee n'est   */
/*  associee a aucun semaphore alors le systeme cree un nouveau    */
/*  semaphore et retourne le nouvel identificateur (semid) associe */
/*  a ce nouveau semaphore.  Si la cle est deja associee a un      */
/*  semaphore alors le systeme retourne le "semid" de ce semaphore.*/
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    key : cle specifiee par l'usager qui permet au systeme de    */
/*          creer un nouveau semaphore et de retourner le nouvel   */
/*          identificateur ou de retourner l'identificateur du     */
/*          semaphore deja associe a cette cle.                    */
/*                                                                 */
/*    valeur : valeur initiale du semaphore (si le semaphore       */
/*             existe deja ce parametre est ignore).               */
/*                                                                 */
/*******************************************************************/
void Sem::Init(key_t key,int valeur)
{
  union semun arg;
  arg.val = valeur;

  if ((semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0666)) == -1) 
    {  
     if ((semid = semget(key, 1, IPC_CREAT|0666)) == -1)
         perror("Classe Function Init erreur a la creation");
    }
  else
     if (semctl(semid, 0, SETVAL, arg) == -1)
        perror("Classe Function Init erreur a l'initialisation");
}

/*******************************************************************/
/*                                                                 */
/*                  D e t r u i t                                  */
/*                                                                 */
/*  Cette routine detruit le semaphore (libere le "semid")         */
/*  identifie par "semid".                                         */
/*                                                                 */
/*******************************************************************/

void Sem::Detruit()
{
   union semun arg;
      if (semctl(semid, 0, IPC_RMID, 0) == -1)
         perror("Classe Sem Destructeur");
}

/*******************************************************************/
/*                                                                 */
/*                            P                                    */
/*                                                                 */
/*  Cette routine effectue une operation "P" sur le semaphore.     */
/*                                                                 */
/*******************************************************************/
void Sem::P()
{
   struct sembuf cmd;   

   cmd.sem_num = 0;
   cmd.sem_op  = P_OP;
   cmd.sem_flg = 0;

   if (semop(semid, &cmd, 1) == -1)
      perror("Classe Sem function P");
}

/*******************************************************************/
/*                                                                 */
/*                                V                                */
/*                                                                 */
/*  Cette routine effectue une operation "V" sur le semaphore.     */
/*                                                                 */
/*******************************************************************/
void Sem::V()
{
   struct sembuf cmd;   

   cmd.sem_num = 0;
   cmd.sem_op  = V_OP;
   cmd.sem_flg = 0;

   if (semop(semid, &cmd, 1) == -1)
      perror("Classe Sem function V");   
}
/*******************************************************************/
/*                                                                 */
/*                                val                              */
/*                                                                 */
/*  Cette routine retourne la valeur du semaphore.                 */
/*                                                                 */
/*******************************************************************/
int Sem::val()
{
   int temp ;
   
   if ((temp = semctl(semid, 0, GETVAL, 0)) == -1)
      perror("Classe Sem function val"); 
   return temp; 
}