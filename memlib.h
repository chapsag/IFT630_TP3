/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/* Cette classe permet de definir des zones de memoire commune a   */
/* plusieurs processus.                                            */
/* Quatre operations permettent de manipuler cette memoire.        */
/* On peut d'abord creer des zones de memoire commune dans le      */
/* systeme. Lorsqu'une zone de memoire est creee on peut l'attacher*/
/* a notre programme (initialiser un pointeur vers cette zone).    */
/* Lorsque l'on veut liberer la zone, on doit d'abord la detacher  */
/* de notre programme. Le processus en charge de la liberation peut*/
/* ensuite liberer la zone de memoire commune.                     */  
/*                                                                 */
/*******************************************************************/
/*******************************************************************/
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

class Mem {
   private:
        int memid;
   public:
         Mem(key_t key, int dimension);
         void Attache(void **adresse);
         void Detache(char *adresse);
         void Libere();
};