/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/*  Cette fichier contient les operations de la classe Port        */
/*                                                                 */
/*******************************************************************/
/*******************************************************************/
#include "msglib.h"
/*******************************************************************/
/*                                                                 */
/*                   P o r t  (constructeur)                       */
/*                                                                 */
/*  Cette routine permet de creer un port a partir d'une cle       */
/*  specifiee par l'usager.  Cette cle (qui doit etre numerique ou */
/*  convertit en numerique par la fonction getkey) est unique et   */
/*  est associee a un seul port.  Si la cle specifiee n'est        */
/*  associee a aucun port alors le systeme cree une nouveau  port  */
/*  et retourne le nouvel identificateur (msgqid) associe a ce     */
/*  nouveau port.  Si la cle est deja associee a un port alors le  */
/*  systeme retourne le "msgqid" de ce port.                       */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    key : cle specifiee par l'usager qui permet au systeme de    */
/*          creer un nouveau port et de retourner le nouvel        */
/*          identificateur ou de retourner l'identificateur du     */
/*          port deja associe a cette cle.                         */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
Port::Port(char * nom)
{
    attributs.mq_flags = 0;  
    attributs.mq_maxmsg = NB_MAX;  
    attributs.mq_msgsize = TAILLE_MAX;  
    attributs.mq_curmsgs = 0;  
   if ((msgqid = mq_open(nom, O_RDWR | O_CREAT | O_EXCL, PERM, &attributs)) == -1)
      if ((msgqid = mq_open(nom, O_RDWR | O_CREAT, PERM, &attributs)) == -1)
         perror("Classe Port Construteur");
}

/*******************************************************************/
/*                                                                 */
/*                   d e t r u i t                                 */
/*                                                                 */
/*  Cette routine permet de detruire le port.                      */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*  RETOUR DE LA FONCTION                                          */
/*                                                                 */
/*    - = 0 (int) s'il n'y a pas d'erreur                          */
/*    - < 0 : code d'erreur (int) si la fonction a echouee.        */
/*                                                                 */
/*******************************************************************/
int Port::detruit()
{

   if (mq_close(msgqid) == -1)
   {
       perror("Classe Port Destructeur");
       return -errno;
   }
   return 0;
}
/*******************************************************************/
/*                                                                 */
/*                       e n v o i e                               */
/*                                                                 */
/*  Cette routine permet d'expedier un message sur le Port.        */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    message : adresse du message a transmettre.                  */
/*              le champs type doit etre >0.                       */
/*                                                                 */
/*    dim : dimension du message a transmettre. Excluant le type   */
/*                                                                 */
/*  RETOUR DE LA FONCTION                                          */
/*                                                                 */
/*    - = 0 : (int) s'il n'y a pas d'erreur                        */
/*    - < 0 : code d'erreur (int) si la fonction a echouee.        */
/* ______________________________________________________________  */
/*            A T T E N T I O N                                    */
/*            __________________                                   */
/*                                                                 */
/* 1. Si type (mtype) n'est pas > 0 -> problemes                   */ 
/* 2. La taille ne doit pas inclure type sinon - problemes         */
/* ______________________________________________________________  */
/*                                                                 */
/*******************************************************************/
int Port::envoie(char *message, size_t dim, unsigned int prio = 0)
{
   if (mq_send(msgqid, message, dim, prio) == -1)
   {
        perror("Classe Port Function Envoie");
        return -errno;
   }
   return 0;
}
/*******************************************************************/
/*                                                                 */
/*                       r e c o i t                               */
/*                                                                 */
/*  Cette routine permet de recevoir un message sur le Port.       */
/*  en parametre.                                                  */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*    message : adresse du tampon qui recevra le message.          */
/*                                                                 */
/*    dim : dimension du message recu.                             */
/*    type : type du message à recevoir (0 par défaut)             */
/*           0 -> recoit le premier message dans la liste          */
/*                                                                 */
/*  RETOUR DE LA FONCTION                                          */
/*                                                                 */
/*    - = 0 (int) s'il n'y a pas d'erreur                          */
/*    - < 0 : code d'erreur (int) si la fonction a echoue.         */
/*    - > 0 : taille effective du message recu                     */
/*                                                                 */
/*******************************************************************/
int Port::recoit(char *message, size_t dim, unsigned int * prio = 0)
{
   int retour;
   retour = mq_receive(msgqid, message, dim, prio);
   if (retour == -1)
   {   
       perror("Classe Msg Function Recoit");
       return -errno;
   }
   return retour;
}