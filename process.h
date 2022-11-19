#ifndef DEF_NOMDUFICHIER1 
#define DEF_NOMDUFICHIER1 


#define TAILLE 259867
#define TAILLE_PROCESSS_TABLE 90


enum state_process{elu,activable,endormi};

typedef struct process process;
struct process
{
    /* data */
    int pid;
    //char nom[TAILLE];
    char *nom;
    enum state_process state;
    uint32_t savezone[5];
    uint32_t *stack;
    process * suivant;
    int dateReveil;
    process *next;

};



   //Pointeur sur le processus actif


typedef struct ActivableList ActivableList;
struct  ActivableList
{
	process *premier;	//Pointeur sur le premier element
	process *dernier; //Pointeur sur le dernier element
};

typedef struct SleepingList SleepingList;
struct  SleepingList
{
	process *tete;	//Pointeur sur le premier element
	process *queue; //Pointeur sur le dernier element
};




// extern process* actif;
// extern ActivableList *jobs;
// extern process table[TAILLE_PROCESSS_TABLE];

// ActivableList *jobs=(ActivableList*)malloc(sizeof(ActivableList));

#endif
