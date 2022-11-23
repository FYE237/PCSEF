#include "cpu.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecran.h"
#include "process.h"
#include "temps.h"
#include <stdlib.h>
#include <tinyalloc.h>

#define N 4


extern  void  traitant_IT_32(void);
extern void  ctx_sw(uint32_t* , uint32_t* );

process* table[TAILLE_PROCESSS_TABLE]  ;



ActivableList *jobs ;
SleepingList *sleeping;
DeadList *dead;


int nb=0;
int NB_INT=49;
int NB_SECONDE=0;


/*********** TP3 *********/
int32_t mon_pid(void){
  // return actif->pid;
  return jobs->premier->pid;
}

char *mon_nom(void){
  return jobs->premier->nom;
}

int nbr_secondes(){
  return NB_SECONDE;
}

//Avant passage à l'horloge qui switch les processus
// process* Extraction(){
//      process *tmp  = malloc(sizeof(process));
//      tmp = jobs->premier;

//     jobs->premier = jobs->premier -> suivant;

//   return tmp;
    
// }


// void inserer(process *nouveau){

//   jobs->dernier->suivant = nouveau;

//    if(jobs->premier->pid == jobs->dernier->pid){
//       jobs->premier->suivant = nouveau; 
//    }

//   jobs->dernier = nouveau;
	
// }

// void ordonnance(void){

//    process *tmp  = malloc(sizeof(process));
//    tmp = Extraction();
//    int a= tmp->pid;
//    inserer(table[a]);
//    free(tmp);

//   table[tmp->pid]->state=activable;

//   table[jobs->premier->pid]->state=elu;

//   ctx_sw(table[a]->savezone, table[jobs->premier->pid]->savezone); 

// }

// void insererSleepingEnTete(process *nouveau){
//   nouveau->suivant = sleeping->tete;
//   sleeping->tete = nouveau;
// }

// void insererSleepingEnQueue(process *nouveau){
//   sleeping->queue->suivant = nouveau;
//   sleeping->queue = nouveau;
  
// }

// void insererSleeping(process *nouveau){

//   if(nouveau->dateReveil < sleeping->tete->pid) insererSleepingEnTete(nouveau);
//   else if (nouveau->dateReveil > sleeping->queue->pid)
//     {
//       insererSleepingEnQueue(nouveau);
//     }
//   else {
//       process * tmp = malloc(sizeof(process*));
//       tmp = sleeping->tete;
//       //Parcours de la liste chainee des processus endormis pour chercher ou inserer le processus (la bonne position de sa date de reveil)
//       while(tmp->suivant != NULL ){
//           if((nouveau->dateReveil < tmp->suivant->pid)){
//             nouveau->suivant = tmp->suivant;
//             tmp->suivant = nouveau;
//             break;
//           }
//         }
//         tmp = tmp->suivant;
//   }

// }


// void dors(int n){
//   jobs->premier->dateReveil =  NB_SECONDE + n;
//   insereSleeping(jobs->premier->dateReveil);
// }

/******Etape Geestion de la terminaison des processus*/






/******Etape Geestion de la terminaison des processus*/


void idle(void)
{
  for (;;) {
    //printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    //ordonnance();  //MOdele statique
    
    /*** Gestion avec l'horloge **/
      // sti();
      // hlt();
      // cli();
    /********/

    //Etape avec liste des processus endormis. On commmente le printf
     sti();
      hlt();
      cli();
    
    }
}
void proc1(void) {
  //Process activables
  // for (;;) {
  //   //printf("[%s] pid = %i\n", mon_nom(), mon_pid());
  //  //ordonnance(); //Modele statique

  //   /*** Gestion avec l'horloge **/
  //     // sti();
  //     // hlt();
  //     // cli();
  //   /********/ 

  //   //Etapes  avec liste des processus endormis!.
  //     printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
  //             mon_nom(), mon_pid());
  //     dors(2);

  //   }

    /****  Liste des processus morts *****/
      for (int32_t i = 0; i < 2; i++) {
          printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
                mon_nom(), mon_pid());
        dors(2);
      }
      //fin_processus();  //On commente ca  pour terminaison automatique
      

    /****  Liste des processus morts *****/
}



/*****  Etape avec Liste des processus endormis   *****/
 

 void proc2(void)
  {
    for (;;) {
      printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
      mon_nom(), mon_pid());
      dors(3);

    }
  }

void proc3(void)
  {
    for (;;) {
      printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
      mon_nom(), mon_pid());
      dors(5);

    }
  }
  
/************/



void initialisation(process *nouveau){

  jobs->premier = nouveau;

  jobs->dernier = nouveau;

}


void init_idle(void){

   table[0] = (process*)malloc(sizeof(process));
   table[0]->nom ="idle";
   table[0]->pid=0;
   table[0]->state=elu;

  //Test
 
    initialisation(table[0]);
} 

void init_proc(void){
   
    //  table[nb]->pid=nb;
    //  table[nb]->state=activable;
    //  table[nb]->stack = (uint32_t *)(malloc(512*sizeof(uint32_t)));
    //  table[nb]->stack[511]= (uint32_t)(proc1);
    //  table[nb]->savezone[1]= (uint32_t)(&(table[nb]->stack[511]));

    /****   Cas des 04 processus pour la liste des processus endormis  ****/

    //  table[nb]->pid=nb;
    //  table[nb]->state=activable;
    //  table[nb]->stack = (uint32_t *)(malloc(512*sizeof(uint32_t)));
    //  table[nb]->stack[0] = (uint32_t *)(fin_processus);
    // switch (nb)
    // {
    //   case 1 :
    //     table[nb]->stack[511]= (uint32_t)(proc1);
    //     break;
    //   case 2 :
    //     table[nb]->stack[511]= (uint32_t)(proc2);
    //     break;;
    //   case 3 :
    //     table[nb]->stack[511]= (uint32_t)(proc3);
    //     break;
    //   default:
    //     break;
    // }

    //  table[nb]->savezone[1]= (uint32_t)(&(table[nb]->stack[511]));

    /****   Cas des 04 processus pour la liste des processus endormis  ****/


    /**** Terminsaison automatique des processus ****/
     table[nb]->pid=nb;
     table[nb]->state=activable;
     table[nb]->stack = (uint32_t *)(malloc(512*sizeof(uint32_t)));
     table[nb]->stack[511] = (uint32_t)(fin_processus);
    switch (nb)
    {
      case 1 :
        table[nb]->stack[510]= (uint32_t)(proc1);
        break;
      case 2 :
        table[nb]->stack[510]= (uint32_t)(proc2);
        break;;
      case 3 :
        table[nb]->stack[510]= (uint32_t)(proc3);
        break;
      default:
        break;
    }

     table[nb]->savezone[1]= (uint32_t)(&(table[nb]->stack[510]));

    /**** Terminsaison automatique des processus ****/


   }



 int32_t cree_processus(void(*code)(void),char *nom){
    if(nb<N){
        if(nb==0){
            code();
            nb++;
            return table[nb-1]->pid;
            
        }
        else {
  
          table[nb] = (process*)malloc(sizeof(process));
          table[nb]->nom = nom;
          code();
          nb++;
          return table[nb-1]->pid;
        }
  }
  else return -1;
 }




// void idle(void)
// {
//    /**** SEANCE 1 ****/
// // printf("[idle] je tente de passer la main a proc1...\n");
// // ctx_sw(table[0].savezone, table[1].savezone);
//   /**** SEANCE 1 ****/

//   /**** SEANCE 2 *****/
//   //   for (int i = 0; i < 3; i++) {
//   // printf("[idle] je tente de passer la main a proc1...\n");
//   // ctx_sw(table[0].savezone, table[1].savezone);
//   // printf("[idle] proc1 m’a redonne la main\n");
//   // }
//   // printf("[idle] je bloque le systeme\n");
//   // hlt();
//   /***** SEANCE 2******/

//   //Ordonnannce
//   for (;;) {
//   printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//   ordonnance();
//   }
  
// }
// hlt();
// void proc1(void){
//   /**** SEANCE 1 ****/

//   /**** SEANCE 2*****/
//   //   for (;;) {
//   // printf("[proc1] idle m’a donne la main\n");
//   // printf("[proc1] je tente de lui la redonner...\n");
//   // ctx_sw(table[1].savezone, table[0].savezone);
//   // }
//   /**** SEANCE 2 *****/
//   //Ordonnance
//   for (;;) {
//   printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//   ordonnance();
//   }
// }
/*********** TP3 *********/


void kernel_start(void)
{
        //*****TP 1 *****//////
        //ecrit_car(10,5,'A',15,0,0);
        //traite_car('a');
        //defilement();
         efface_ecran();

         place_curseur(0,0);
        // for(;;){
        //   printf("Bonjour");
        // }
       // console_putbytes("Hello! TP1 reussi avec succes",29);
        // ****** FIN TP1 *****///

	////******TP2*******////        
	  //Initialisation
	// cli();

	//   frequence_horloge();
	//   masque_IRQ(0,0);
	//   init_traitant_IT(32, traitant_IT_32);

     
        // démasquage des interruptions externes
        //sti();


  ////////******TP2*******//// 

    // uint32_t x = fact(5);
    // // quand on saura gerer l'ecran, on pourra afficher x
    // (void)x;
    // on ne doit jamais sortir de kernel_start
    
    ///RUN TP1 et TP2
    /*while (1) {
        // cette fonction arrete le processeur
        hlt();
    }*/


  ///////******TP3*******//// 

  //   strcpy(table[0].nom,"idle");
  //   table[0].pid=0;
  //   table[0].state=elu;

  //   actif=&table[0];

  jobs = malloc(sizeof(ActivableList));
  sleeping = malloc(sizeof(SleepingList));
  dead = malloc(sizeof(DeadList));
//int i=1;

 char nom[N][6]; //Un tableau des noms de longueur 6 de nos 8=N processurs

  // char *nom[]={"proc1","proc2","proc3","proc4","proc5","proc6","proc7"};

  //   strcpy(table[1].nom,"proc1");
  //   table[1].pid=12;
  //   table[1].state=activable;
  //   table[1].savezone[1]= (uint32_t)(&(table[1].stack[511]));
  //   table[1].stack[511]= (uint32_t)(proc1);
  
  // strcpy(nom[0],"idle");
  // cree_processus(init_idle,"idle");

  // nb=1;
  //   for(i=1;i<8;i++){

  //   sprintf(nom[i],"proc%d",i);

  //    if ( cree_processus(init_proc,nom[i])== -1  ) printf("Echec : %d ",i) ;

  //  }
  

    

  // actif =table;
 

    /**** Modele Dynamique ***/
     strcpy(nom[0],"idle");
  cree_processus(init_idle,"idle");

  nb=1;
  //   for(i=1;i<N;i++){

  //   sprintf(nom[i],"proc%d",i);

  //    if ( cree_processus(init_proc,nom[i])== -1  ) printf("Echec : %d ",i) ;

  //     //Pour le cas avec la liste des processus endormis  on commente cette ligne
  //     inserer(table[i]);

  //  }
  cree_processus(init_proc,"proc1");
  inserer(table[1]);

  cree_processus(init_proc,"proc2");
  inserer(table[2]);

  cree_processus(init_proc,"proc3");
  inserer(table[3]);
  
    //Gestion par l'horloge : 
      cli();

	    frequence_horloge();
	     masque_IRQ(0,0);
	    init_traitant_IT(32, traitant_IT_32);

      idle();
   /**** Modele Dynamique ***/


  ///////******TP3*******//// 
    


}

