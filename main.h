#define NB_CARA 100
#include <stdio.h>
#define LN_NPV 30
#define LN_CD 7
#define LN_TEL 16
#define LN_MAIL 71
#define LN_TAF 20

struct Entite{
    char prenom[LN_NPV];
    char nom[LN_NPV];
    char ville[LN_NPV];
    char code_postal[LN_CD];
    char numero_tel[LN_TEL];
    char adr_mail[LN_MAIL];
    char metier[LN_TAF];
};
typedef struct Entite Entite;

void charger(FILE *,Entite *pt_personne);
char compte(char*,int);
FILE* name_fichier();
int ligne(FILE*);
void affichage(Entite *pt_personne,int,int);
int ajout(Entite *pt_personne,int);
int suppression(Entite *pt_personne,int);
void remonte(Entite *pt_personne,int,int);
void modifier(Entite *pt_personne,int);
void rempl_mod(Entite *pt_personne,char reponse[],int taille,int type,int ligne);
void filtre(Entite *pt_personne, int taille);
void save(Entite *pt_personne, int taille);
void cpy(Entite *answers, Entite *pt_personne,int ligne, int k);
void tri(Entite *pt_personne, int taille);
void big_cpy(Entite *pt_personne,int,int);
