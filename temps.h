#ifndef DEF_NOMDUFICHIER 

#define DEF_NOMDUFICHIER 


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "process.h"


// void initialisation(process nouveau);


// process * Extraction();


// void inserer(process nouveau);


//Gestion horloge
void afficherChaine(char *chaine);
void masque_IRQ(uint32_t num_IRQ, bool masque);

void tic_PIT(void);
void init_traitant_IT(int32_t num_IT, void (*traitant)(void));
void frequence_horloge();
void masque_IRQ(uint32_t num_IRQ, bool masque);

//Gestion liste des processus activablees
process* Extraction(void);
void ordonnance(void);
void inserer(process *p);

//GesTion liste des processus endormis
void dors(int n);
void insererSleeping(process *nouveau);
void insererSleepingEnQueue(process *nouveau);
void insererSleepingEnTete(process *nouveau);

//Gestion liste des processus morts
process *ExtractionDead();
void initialisationDeadList(process *nouveau);
void insererDead(process *nouveau);
void fin_processus();


#endif