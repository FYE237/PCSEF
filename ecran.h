
#ifndef ECRAN_H
#define ECRAN_H
#include "inttypes.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "ecran.h"
#include "cpu.h"

//C'est une fonction qui renvoie un pointeur sur la case mémoire correspondant aux coordonnées fournies ;
uint16_t *ptr_mem(uint32_t lig,uint32_t col);

//C'est une focntion qui écrit le caractère aux coordonnées spécifiées
void ecrit_car(uint32_t lig,uint32_t col, char c,uint8_t couleur_texte,uint8_t couleur_fond,uint8_t clignote);

void AfficherHorloge(uint32_t lig,uint32_t col, char c,uint8_t couleur_texte,uint8_t couleur_fond,uint8_t clignote);


void efface_ecran(void);

void place_curseur(uint32_t lig, uint32_t col);

void getPositionCouranteCurseur(void);

void traite_car(char c);

void defilement(void);

void console_putbytes(const char *s,int len);

#endif