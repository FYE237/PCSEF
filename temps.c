//  ****************************** SEANCE 2  ***********************
#define COL 80
#define LINE 25
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "ecran.h"
#include "cpu.h"
#include "segment.h"
#include "temps.h"
#include  "process.h"
#include <tinyalloc.h>


extern void  ctx_sw(uint32_t* , uint32_t* );

#define QUARTZ 0x1234DD
#define CLOCKFREQ  50  

extern ActivableList *jobs;
extern process *table[TAILLE_PROCESSS_TABLE];
extern SleepingList *sleeping;
extern int NB_INT;
extern int  NB_SECONDE;
extern  void  traitant_IT_32(void);

void afficherChaine(char *chaine)
{
    int i=0,pos=COL-8;
    while(pos<=COL)
    {   
        //On choisir d'écrir sur la ligne numéro 1
        ecrit_car(1,pos,chaine[i],15,0,0);
        i++;
        pos++;
    }
} 

// //Extraire un processus dans la liste des processus activables
// process* Extraction(){
//      process *tmp  = malloc(sizeof(process));
//      tmp = jobs->premier;

//     jobs->premier = jobs->premier -> suivant;

//   return tmp;
    
// }


void inserer(process *nouveau){

  if(jobs->premier == NULL ) {
     jobs->premier = nouveau;

  jobs->dernier = nouveau;
  }

  else {
  jobs->dernier->suivant = nouveau;

   if(jobs->premier->pid == jobs->dernier->pid){
      jobs->premier->suivant = nouveau; 
   }

  jobs->dernier = nouveau;
  }
	
}

void insererSleepingEnTete(process *nouveau){
  nouveau->next = sleeping->tete;
  sleeping->tete = nouveau;
}

void insererSleepingEnQueue(process *nouveau){
  sleeping->queue->next = nouveau;
  sleeping->queue = nouveau;
  
}

void initialisationSleeping(process *nouveau){

  sleeping->tete = nouveau;

  sleeping->queue = nouveau;

}

void insererSleeping(process *nouveau){

  if( sleeping->tete == NULL ) {
    initialisationSleeping(nouveau);
  }
  else {

          if(nouveau->dateReveil <= sleeping->tete->dateReveil ) 
                insererSleepingEnTete(nouveau);
          else if (nouveau->dateReveil >= sleeping->queue->dateReveil)
            {
              insererSleepingEnQueue(nouveau);
            }
          else {
              process * tmp = malloc(sizeof(process*));
              tmp = sleeping->tete;
              //Parcours de la liste chainee des processus endormis pour chercher ou inserer le processus (la bonne position de sa date de reveil)
              while(tmp->next != NULL ){
                  if((nouveau->dateReveil <= tmp->next->dateReveil)){
                    nouveau->next = tmp->next;
                    tmp->next = nouveau;
                    break;
                  }
                  tmp = tmp->next;
                }
                
          }

  }
}




//Extraire un processus de la liste des processus endormis
process* ExtractionSleeping(){
   process *tmp  = malloc(sizeof(process));
     tmp = sleeping->tete;
         

    sleeping->tete = sleeping->tete -> next;

  return tmp;
}



//Je parcours la liste des processsus activables pour retier celui dont la date de reveil est < au temps courant et je les ajoute à la liste des processus
//activables
void GestionSleeping(){
     process * tmp = malloc(sizeof(process*));
     tmp = sleeping->tete;
     //int  t = 0;
     if(tmp != NULL ){
        while(NB_SECONDE > tmp->dateReveil && tmp != NULL){
            inserer(ExtractionSleeping());
            tmp = tmp->next;
            break;
            //t = 1;
        }
        //if(t != 0) inserer(table[0]);
     }
     
}



//Extraire un processus dans la liste des processus activables
process* Extraction(){
     process *tmp  = malloc(sizeof(process));
     tmp = jobs->premier;

 // test
    
   jobs->premier = jobs->premier -> suivant;

    ///Cas avec liste des processus endormis

  return tmp;
    
}

//Il faut checker la liste des processus endormis apres chaque opération
void ordonnance(void){
  
  GestionSleeping(); // On check avant de changer le procéssus actif
   process *tmp  = malloc(sizeof(process));
   tmp = Extraction();
    

   int a= tmp->pid;
    inserer(table[0]);   //Ici on reinserait un processus qu'on avait elu en fin de liste. Mais plus besoin vu qu'il passe à endormi.
     // !!!!!!!!!!!!!!    On rajoute  idle car il faut incrementer le temps à chaque action


   GestionSleeping(); //On check après avoir rajouter le processus idle 

  
  table[a]->state=activable;

  table[jobs->premier->pid]->state=elu;

  ctx_sw(table[a]->savezone, table[jobs->premier->pid]->savezone); 

}

void dors(int n){
  jobs->premier->dateReveil =  NB_SECONDE + n;
  if(jobs->premier->pid != 0) insererSleeping(jobs->premier);
  ordonnance();


}

void tic_PIT(void)
{
    outb(0x20,0x20);
    NB_INT++;
    if(NB_INT == 50) 
        {
            NB_INT =40; //NB_INT =0  //Ca prenait trop de temps //test
            NB_SECONDE++;
        }
    char timer[8];
    int heure = NB_SECONDE/3600;
    int minute = (NB_SECONDE -heure*3600)/60;
    int seconde =NB_SECONDE- minute*60 - heure*3600;

    sprintf(timer,"%d:%d:%d",heure,minute,seconde);
    //sprintf(timer,"%d",NB_SECONDE);
    afficherChaine(timer);
    ordonnance();
}




void init_traitant_IT(int32_t num_IT, void (*traitant)(void))
{

    uint32_t mot1,mot2;
    mot1=KERNEL_CS<<16|(((uint32_t) traitant) & 0xffff); //POur avoir les 16 bits de poids forts on décale vers la gauche de 16 bits
    mot2 = ((uint32_t)traitant & 0xffff0000 ) | 0x8E00 ;
    //mot1 = (uint32_t)(KERNEL_CS>>16|(((uint32_t) traitant) & 0xffff0000)); 
    //mot2 = (uint32_t)(((uint32_t)traitant & 0xffff)| (uint32_t)0x8E00);

    uint32_t *table =  (uint32_t *)0x1000;
    *(table + num_IT*2) = mot1; //On fait *2 car chaque entrée du tableau d'intérruption est en fait composée de deux lignes de notre tableau table
    *(table + num_IT*2 +1) = mot2;
}

void frequence_horloge(){
    outb(0x34,0x43);
    outb((QUARTZ / CLOCKFREQ) % 256, 0x40); 
    outb((QUARTZ / CLOCKFREQ) / 256, 0x40);

}


void masque_IRQ(uint32_t num_IRQ, bool masque)
{
    uint8_t valeur_masque =  inb(0x21);
    //Masquage de l'irq N
    if(masque == false) // Si masque vaut 1
        
             valeur_masque &= ~(1<< num_IRQ);
            // valeur_masque |= 1<< num_IRQ; 
            // outb(valeur_masque,0x21);
        
    else
        // valeur_masque &= ~(1<< num_IRQ);
        // outb(valeur_masque,0x21);
          valeur_masque |= 1<< num_IRQ; 
    
    outb(valeur_masque,0x21);
}

