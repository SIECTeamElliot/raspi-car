#include "../include/communicationSTM.h"

// Messages à envoyer
struct can_frame AngleVolantCommande, VitesseCommandeGauche, VitesseCommandeDroite;


void InitMessage (struct can_frame *frame, int id, int taille)
{
  (*frame).can_id  = id;
  (*frame).can_dlc = taille;
}


#define ANGLEVOLANTCMD 0x21
#define VITESSECMDGAUCHE 0x01
#define VITESSECMDDROITE 0x02

/*********************** Init ******************************
 * Initialisation globale des communications
 * INPUTS :
************************************************************/
void Init ()
{
  // ********************* Creer messages **************************
  
  // Création message AngleVolantCommande
  InitMessage (&AngleVolantCommande, ANGLEVOLANTCMD, 1);

  // Création message VitesseCommandeGauche
  InitMessage (&VitesseCommandeGauche, VITESSECMDGAUCHE, 1);

  // Création message VitesseCommandeDroite
  InitMessage (&VitesseCommandeDroite, VITESSECMDDROITE, 1);



}

/********************** EnvoiMessage ************************
 * Envoi d'un message
 * INPUTS : frame : pointeur vers trame CAN à transmettre
 *          data : donnée à transmettre
 *          socket : id socket 
 * OUTPUT : nbytes : retour de la fonction write
 *********************************************************/

int EnvoiMessage (struct can_frame *frame, char data, Can& can)
{
  char dat[1] = {data}; 
  can.sendFrame(frame, 1, dat);
  return 0;
}



/**************************** Tests *****************************
Teste les envois de messages
INPUTS : socket : 
 ****************************************************************/

void Tests (Can& can)
{
  int nbytes;
  Init();
  
  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)25, can);
  printf("[Test] envoi cmd vitesse : avancer  %d\n",nbytes);
  sleep(3);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)0, can);
  printf("[Test] envoi cmd vitesse : arrêt %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)-25, can);
  printf("[Test] envoi cmd vitesse : reculer %d\n",nbytes);
  sleep(3);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)0, can);
  printf("[Test] envoi cmd vitesse : arrêt %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)-20, can);
  printf("[Test] envoi angle volant: tourner droite %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)25, can);
  printf("[Test] envoi cmd vitesse: avancer %d\n",nbytes);
  sleep(2);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)0, can);
  printf("[Test] envoi angle volant: redresser %d\n",nbytes);
  sleep(1);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)20, can);
  printf("[Test] envoi angle volant: tourner gauche %d\n",nbytes);
  sleep(2);

  nbytes=EnvoiMessage ( &AngleVolantCommande, (char)0, can);
  printf("[Test] envoi angle volant: redresser %d\n",nbytes);
  sleep(2);

  nbytes=EnvoiMessage ( &VitesseCommandeGauche, (char)0, can);
  printf("[Test] envoi cmd vitesse: arrêter %d\n",nbytes);

}