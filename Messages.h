/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/*  Cette classe permet de definir des objets de type port (port   */
/*  de communication) sur lesquels on peut envoyer et recevoir des */
/*  messages.                                                      */
/*                                                                 */
/*  Le message a le format suivant :                               */
/*       - type (mtype) : type du message.  Doit toujours etre >0  */
/*                        si =0 -> des problemes surviennent       */
/*       - contenu      : contenu du message                       */
/*******************************************************************/
/*******************************************************************/
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

const int TAILLE_MAX = 500;

class Port {
   private:
      const int PERM = 0666;
      const int NB_MAX = 10;
      mqd_t  msgqid;
      struct mq_attr attributs ;
   public:
      Port(char * nom);
      int envoie(char *message, size_t dim, unsigned int priorite );
      int recoit(char *message, size_t dim, unsigned int * prio );
      int detruit();
};
