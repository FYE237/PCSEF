//  **************** TP1 ******************//


#include "ecran.h"



#define COL 80
#define LINE 25

uint8_t col_courant;
uint8_t line_courant;
uint8_t coleur_texte_courant=15;
uint8_t couleur_fond_courant=0;

uint16_t *ptr_mem(uint32_t lig,uint32_t col){

    uint16_t * pos=NULL;
    pos = (uint16_t *) (0xB8000 + 2*(col + lig * 80));
    return pos;
}

void ecrit_car(uint32_t lig,uint32_t col, char c,uint8_t couleur_texte,uint8_t couleur_fond,uint8_t clignote)
{
    *ptr_mem(lig,col) = c|(clignote << 15) | (couleur_fond <<12) |(couleur_texte<<8); 
    col_courant=(col +1)%80;
    if(col_courant==79){
        line_courant = (lig +1)%25;
        col_courant = 0;
    }

}

void AfficherHorloge(uint32_t lig,uint32_t col, char c,uint8_t couleur_texte,uint8_t couleur_fond,uint8_t clignote)
{
    *ptr_mem(lig,col) = c|(clignote << 15) | (couleur_fond <<12) |(couleur_texte<<8); 

}

void efface_ecran(void) {
    int i ,j;
    for(i = 0;i<LINE;i++)
        {
            for(j=0;j<COL;j++)
                {
                    ecrit_car(i,j,' ',15,0,0);
                }
        }
}

void place_curseur(uint32_t lig, uint32_t col)
{
    uint16_t pos = (uint16_t)(col + lig * 80);
    uint8_t lower = (uint8_t) pos;
    uint8_t upper = (uint8_t) (pos>>8);
    outb(0x0F,0x3D4);
    outb(lower,0x3D5);
    outb(0x0E,0x3D4);
    outb(upper,0x3D5);

    line_courant = lig;
    col_courant = col;
}



void traite_car(char c)
{
    uint16_t code = c;
    if(code >=0 && code <=127){
       if(code >=32 && code <=126){
        ecrit_car(line_courant,col_courant,c,15,0,0);
        
        }
     else
        {
            switch (code)
            {
            case 8: /* constant-expression */
                /* code */
                col_courant = (col_courant -1) % 80;
                place_curseur(line_courant,col_courant);

                break;
            case 9:
                col_courant = (col_courant + 4)%80;
                place_curseur(line_courant,col_courant);
                break;
            case 10:
                col_courant = 0;
                line_courant = (line_courant + 1)%25 ;
                place_curseur(line_courant,col_courant);
                break;
            case 12:
                efface_ecran();
                col_courant = 0;
                line_courant = 0;
                place_curseur(0,0);
                break;
            case 13:
                col_courant =0 ;
                place_curseur(line_courant,col_courant);
                break;
            default:
                break;
            }
        } 

    } 
   
}

void defilement(void){
    // int i=1;
    // while(i<LINE){
    //     int j=0;
    //     for(j=0;j<COL;j++){

            memmove(ptr_mem(line_courant,col_courant),ptr_mem(line_courant-1,col_courant),COL*LINE*16);
            col_courant = 0;
            line_courant -= 1;
    //     }
    // }
}

void console_putbytes(const char *s,int len){
        int i=0;
        while(i<len)
            {   
                traite_car(s[i]);
                i++;
            }
}
