/*******************************************************************/
/*                                                                 */
/*                       G E T K E Y                               */
/*                                                                 */
/*  Cette routine permet de convertir une cle alphanumerique en    */
/*  une cle numerique.                                             */
/*                                                                 */
/*  PARAMETRES                                                     */
/*                                                                 */
/*   p : ce pointeur contient l'adresse de la chaine de caracteres */
/*       a convertir.                                              */
/*                                                                 */
/*  RETOUR DE LA FONCTION                                          */
/*                                                                 */
/*    - cle numerique ("long int")                                 */
/*                                                                 */
/*******************************************************************/
#include <ctype.h>
#include <sys/types.h>
#include <iostream>



using namespace std;

bool isnumber(register char *p)
{

  for (; *p && isdigit(*p); p++);
  return(*p ? 0:1);
}


key_t getkey(register char *p)
{
  key_t key;
  register int i;

  if (isnumber(p)) {
    cout << "nombre     ";
    key = (key_t) atol(p);
  } else {
    key = (key_t) 0;
    for (i=0; i< (2 * sizeof(key_t)) && p[i]; i++) {
      key = (key << 8) | p[i];
    }
  }
  return(key);
}