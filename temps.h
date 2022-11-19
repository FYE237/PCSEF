#ifndef DEF_NOMDUFICHIER 

#define DEF_NOMDUFICHIER 


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "process.h"


// void initialisation(process nouveau);


// process * Extraction();


// void inserer(process nouveau);

void afficherChaine(char *chaine);
void masque_IRQ(uint32_t num_IRQ, bool masque);

void tic_PIT(void);
void init_traitant_IT(int32_t num_IT, void (*traitant)(void));
void frequence_horloge();
void masque_IRQ(uint32_t num_IRQ, bool masque);

process* Extraction(void);
void ordonnance(void);
void inserer(process *p);

void dors(int n);
void insererSleeping(process *nouveau);
void insererSleepingEnQueue(process *nouveau);
void insererSleepingEnTete(process *nouveau);

#endif