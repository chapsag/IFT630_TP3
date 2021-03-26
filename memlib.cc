/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/* Implantation des fonction de la classe Memoire commune          */
/*                                                                 */
/*******************************************************************/
/*******************************************************************/
#include "memlib.h"
/*******************************************************************/
/*                                                                 */
/*               C o n s t r u c t e u r                           */
/*                                                                 */
/*  Cette routine permet de creer un segment de memoire partage    */
/*  a partir d'une cle specifiee par l'usager.  Cette cle (qui     */
/*  doit etre numerique ou convertit en numerique par la fonction  */
/*  getkey) est unique et est associee a un seul segment de        */
/*  memoire.  Si la cle specifiee n'est associee a aucun segment   */
/*  de memoire alors le systeme cree un nouveau segment et retourne*/
/*  le nouvel identificateur (memid) associe a ce nouveau segment  */
/*  de memoire.  Si la cle est deja associee a un segment de       */
/*  memoire alors le systeme retourne le "memid" de ce segment de  */
/*  memoire.                                                       */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    key : cle specifiee par l'usager qui permet au systeme de    */
/*          creer un nouveau segment de memoire et de retourner le */
/*          nouvel identificateur ou de retourner l'identificateur */
/*          du segment de memoire deja associe a cette cle.        */
/*                                                                 */
/*    dimension : dimension desiree du nouveau segment (si le      */
/*                segment existe deja ce parametre est ignore).    */
/*                                                                 */
/*******************************************************************/

Mem::Mem(key_t key, int dimension)
{
   if ((memid = shmget(key, dimension, IPC_CREAT|0666)) == -1)
      perror("Classe Mem constructeur");
}

/*******************************************************************/
/*                                                                 */
/*                    D e t a c h e                                */
/*                                                                 */
/*  Cette routine detache le segment de memoire partage du         */
/*  processus appelant mais ne le detruit pas (il reste encore     */
/*  valide pour tous les autres processus qui desirent l'utiliser) */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    adresse : adresse du segment de memoire a detacher (cette    */
/*              adresse a ete obtenue lors du attache_mem).        */
/*                                                                 */
/*******************************************************************/

void Mem::Detache(char *adresse)
{
   if (shmdt(adresse) == -1)
      perror("Classe Mem function Detache");
}

/*******************************************************************/
/*                                                                 */
/*                      A t t a c h e                              */
/*                                                                 */
/*  Cette routine permet d'attacher a un processus un segment de   */
/*  memoire deja alloue.                                           */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    adresse : ce pointeur contiendra l'adresse de la memoire     */
/*              partagee.                                          */
/*                                                                 */
/*******************************************************************/
void Mem::Attache(void **adresse)
{
   *adresse = NULL;
   if ((*adresse = shmat(memid, *adresse, 0)) == (void *) -1)
      perror("Classe Mem function Attache");
}

/*******************************************************************/
/*                                                                 */
/*                    L i b e r e                                  */
/*                                                                 */
/*  Cette routine libere le segment de memoire partage.            */
/*                                                                 */
/*******************************************************************/
void Mem::Libere()
{
   if (shmctl(memid, IPC_RMID,0) == -1)
      perror("Classe Mem Destructeur");
}