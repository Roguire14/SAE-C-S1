/**
 * \file main.
 * \brief fichier pour la sae de c
 * \author {Romain.G,Loïc.W}
 * \version 1
 * \date 16/12/21
 *
 * Ce programme correspond à une version pour la sae de C
 *
 */

#include "main.h"

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <time.h>

/**
 * \fn int main ()
 * \brief Entrée de la fonction principale qui gère l'application
 * \referant Baptiste BOISMENU a aidé afin de mettre en place le tableau de structure
 *
 * \return 0 - succès du programme.
 */
int main() {
    //debut = clock();
    //fin = clock();
    //printf("duree: %d", fin-debut);
    clock_t debut,fin;
    int choix, opt;
    FILE * pointeur;
    pointeur = name_fichier();
    int taille_fichier = ligne(pointeur);
    //création du pointeur du tableau et allocation dynamique du tableau
    Entite * pt_personne;
    pt_personne = (Entite * ) malloc(taille_fichier * sizeof(Entite));
    //on charge le fichier csv dans la mémoire
    charger(pointeur, pt_personne);
    printf("Pour certaine.s fonction.s, les entrees sont case-sensitives.\nC'est a dire qu'une majuscule suffit pour ne pas faire aboutir votre recherche correctement, comme par exemple, le nom des villes\n");
    do {
        printf("Que voulez vous faire avec ce fichier: \n  - Afficher le contenu du document actuel    (0)\n  - Donner son nombre de lignes               (1)\n  - Ouvrir un autre fichier                   (2)\n  - Ajout de donnees                          (3)\n");
        printf("  - Effacer les informations de quelqu'un     (4)\n  - Modifier les donnees de quelqu'un         (5)\n  - Faire un affichage selon un filtre        (6)\n  - Enregistrer le fichier                    (7)\n  - Trier le tableau                          (8)\n  - Quitter le programme                      (9)\n");
        printf("Votre choix: ");
        scanf("%d", & choix);
        switch (choix) {
        case 0:
            do {
                printf("Voulez vous:\n  - Charger les donnees valides/pleines                  (0)\n  - Charger les donnees dont il manque des informations  (1)\n  - Charger toutes les donnnes sans aucune distinction   (2)\nVotre choix: ");
                scanf("%d", & opt);
                switch (opt) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                default:
                    printf("Veuillez inserez une valeur valide\n");
                }
            } while (opt > 2 && opt < 0);
            debut = clock();
            affichage(pt_personne, taille_fichier, opt);
            fin=clock();
            printf("Temps d'execution: %ldms\n\n",fin-debut);
            break;
        case 1:
            printf("Il y a %d ligne.s dans le fichier\n",taille_fichier);
            break;
        case 2:
            fclose(pointeur);
            free(pt_personne);
            pt_personne=NULL;
            pointeur = name_fichier();
            taille_fichier = ligne(pointeur);
            pt_personne = (Entite * ) malloc(taille_fichier * sizeof(Entite));
            charger(pointeur, pt_personne);
            break;
        case 3:
            taille_fichier = ajout(pt_personne, taille_fichier);
            break;
        case 4:
            taille_fichier = suppression(pt_personne, taille_fichier);
            break;
        case 5:
            modifier(pt_personne, taille_fichier);
            break;
        case 6:
            filtre(pt_personne,taille_fichier);
            break;
        case 7:
            save(pt_personne, taille_fichier);
            break;
        case 8:
            tri(pt_personne,taille_fichier);
            break;
        case 9:
            break;
        default:
            printf("\nVeuillez inserez un chiffre valide\n\n");
            break;
            }
    } while (choix != 9);
    fclose(pointeur);
    free(pt_personne);
    pt_personne=NULL;
    return 0;
}

/**
 * \fn FILE* name_fichier()
 * \brief fonction qui permet d'obtenir le pointeur sur un fichier demandé dans la fonction
 *
 * \param NONE
 * \return FILE* pointeur
 */
FILE * name_fichier() {
    char fichier[NB_CARA];
    FILE * pointeur;
    do {
        printf("Inserer le nom du fichier dont vous voulez travailler dessus: ");
        scanf("%s", fichier);
        printf("\n");
        pointeur = fopen(fichier, "r");
        if (pointeur == NULL) {
            printf("Echec de l'ouverture. :')\n");
        }
    } while (pointeur == NULL);
    printf("Succes de l'ouverture du fichier %s", fichier);
    return pointeur;
}

/**
 * \fn int ligne(FILE * pointeur)
 * \brief fonction qui compte le nombre de ligne, utilisé dans le main
 *
 * \param FILE* pointeur ; permet de chercher dans le bon fichier
 * \return int - nb ; correspond au nombre de ligne
 */
int ligne(FILE * pointeur) {
    char cara_lu;
    int nb = 0;
    rewind(pointeur);
    do {
        cara_lu = fgetc(pointeur);
        if (cara_lu == '\n')
            nb++;
    } while (cara_lu != EOF);
    return nb;
}

/**
 * \fn void charger(FILE * pointeur,Entite (*pt_personne))
 * \brief fonction procédure qui permet de faire charger le fichier csv dans le tableau précedemment alloué dynamiquement
 *
 * \param FILE* pointeur ; permet de chercher dans le bon fichier - Entite (*pt_personnel) ; pointeur vers le tableau de notre structure
 * \return rien
 */
void charger(FILE * pointeur, Entite * pt_personne) {
    //permet de mettre le pointeur au début du fichier
    rewind(pointeur);
    clock_t debut,fin;
    int i, j;
    int catego = 0, caractere = 0;
    int ligne = 0;
    char cara_lu;
    char temp[NB_CARA];
    debut = clock();
    do {
        cara_lu = fgetc(pointeur);
        if (cara_lu == '\n') {
            strcpy(pt_personne[ligne].metier, temp);
            for (j = 0; temp[j] != '\0'; j++);
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            caractere = 0;
            catego = 0;
            ligne++;
        } else if (cara_lu == ',') {
            temp[caractere] = '\0';
            //ici on copie dans la ligne correspondante toutes les catégories de notre entrée
            switch (catego) {
            case 0:
                strcpy(pt_personne[ligne].prenom, temp);
                for (j = 0; temp[j] != '\0'; j++);
                for (i = 0; i < j; i++) {
                    temp[i] = '\0';
                }
                caractere = 0;
                break;
            case 1:
                strcpy(pt_personne[ligne].nom, temp);
                for (j = 0; temp[j] != '\0'; j++);
                for (i = 0; i < j; i++) {
                    temp[i] = '\0';
                }
                caractere = 0;
                break;
            case 2:
                strcpy(pt_personne[ligne].ville, temp);
                for (j = 0; temp[j] != '\0'; j++);
                for (i = 0; i < j; i++) {
                    temp[i] = '\0';
                }
                caractere = 0;
                break;
            case 3:
                strcpy(pt_personne[ligne].code_postal, temp);
                for (j = 0; temp[j] != '\0'; j++);
                for (i = 0; i < j; i++) {
                    temp[i] = '\0';
                }
                caractere = 0;
                break;
            case 4:
                strcpy(pt_personne[ligne].numero_tel, temp);
                for (j = 0; temp[j] != '\0'; j++);
                for (i = 0; i < j; i++) {
                    temp[i] = '\0';
                }
                caractere = 0;
                break;
            case 5:
                strcpy(pt_personne[ligne].adr_mail, temp);
                for (j = 0; temp[j] != '\0'; j++);
                for (i = 0; i < j; i++) {
                    temp[i] = '\0';
                }
                caractere = 0;
                break;

            }
            catego++;
        } else {
            temp[caractere] = cara_lu;
            caractere++;
        }
    } while (!feof(pointeur));
    fin = clock();
    printf(" en : %ld millisecondes.\n\n", fin-debut);
}

/**
 * \fn void affichage(Entite (*pt_personne),int taille, int option)
 * \brief fonction procédure qui permet d'afficher le tableau selon une option rentrée en paramètre
 * \param Entite (*pt_personnel) : pointeur vers le tableau de notre structure -  int taille : correspond à la taille du tableau - int option : correspond à l'option choisie pour l'affichage
 * \return rien
 */
void affichage(Entite * pt_personne, int taille, int option) {
    int ligne = 0;
    clock_t debut,fin;
    debut = clock();
    printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
    while (ligne < taille) {
        if (option == 0) {
            if (strcmp(pt_personne[ligne].nom, "") != 0 && strcmp(pt_personne[ligne].prenom, "") != 0 && strcmp(pt_personne[ligne].ville, "") != 0 && strcmp(pt_personne[ligne].code_postal, "") != 0 && strcmp(pt_personne[ligne].numero_tel, "") != 0 && strcmp(pt_personne[ligne].adr_mail, "") != 0 && strcmp(pt_personne[ligne].metier, "") != 0) {
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", pt_personne[ligne].prenom, pt_personne[ligne].nom, pt_personne[ligne].ville, pt_personne[ligne].code_postal, pt_personne[ligne].numero_tel, pt_personne[ligne].adr_mail, pt_personne[ligne].metier);
            }
        } else if (option == 1) {
            if (strcmp(pt_personne[ligne].nom, "") == 0 || strcmp(pt_personne[ligne].prenom, "") == 0 || strcmp(pt_personne[ligne].ville, "") == 0 || strcmp(pt_personne[ligne].code_postal, "") == 0 || strcmp(pt_personne[ligne].numero_tel, "") == 0 || strcmp(pt_personne[ligne].adr_mail, "") == 0 || strcmp(pt_personne[ligne].metier, "") == 0) {
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", pt_personne[ligne].prenom, pt_personne[ligne].nom, pt_personne[ligne].ville, pt_personne[ligne].code_postal, pt_personne[ligne].numero_tel, pt_personne[ligne].adr_mail, pt_personne[ligne].metier);
            }
        } else {
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", pt_personne[ligne].prenom, pt_personne[ligne].nom, pt_personne[ligne].ville, pt_personne[ligne].code_postal, pt_personne[ligne].numero_tel, pt_personne[ligne].adr_mail, pt_personne[ligne].metier);}
        ligne++;
    }
    fin = clock();
    printf("Affichage du fichier en  : %ld millisecondes.\n\n", fin-debut);
}

/**
 * \fn int ajout(Entite( * pt_personne), int taille)
 * \brief fonction qui permet d'ajouter une entree dans le tableau et d'augmenter en conséquent la taille tout en passant par une réallocation de la taille du tableau
 * \param Entite (*pt_personne) : accès au tableau ; int taille
 * \return taille : correspond à la nouvelle taille soit taille+1
 */
int ajout(Entite * pt_personne, int taille) {
    char temp[NB_CARA], bug[NB_CARA];
    int compteur = 0, i, j;
    clock_t debut,fin;
    debut = clock();
    //reallocation dynamique du tableau
    pt_personne = (Entite * ) realloc(pt_personne, (taille + 1) * sizeof( * pt_personne));
    while (compteur < 8) {
        switch (compteur) {
            //ici ce n'est pas un bug mais bel et bien une feature: le case 0 permet de catch un bug qui faisait fonctionner le case 1 sans faire fonctionner
            //les interractions
            //je crois que je peux y changer par un getchar() mais pas sûr faudrait que je vérifie
        case 0:
            fgets(bug, NB_CARA, stdin);
            break;
        case 1:
            printf("Indiquez le prenom de la personne a inserer: ");
            fgets(temp, LN_NPV, stdin);
            //permet de compter le réel nombre de caractere de temp, strlen ne faisant pas le taff correctement
            for (j = 0; temp[j] != '\0'; j++);
            //permet de remplacer le dernier caractere qui est un \n par défaut par le \0 habituel
            temp[j - 1] = '\0';
            strcpy(pt_personne[taille].prenom, temp);
            //permet de completement réinitialisé la variable temp, vu qu'il y avait un bug et/ou que ça ne fonctionnait pas correctement avec juste temp[0]='\0'
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            break;
        case 2:
            printf("Indiquez le nom de la personne a inserer: ");
            fgets(temp, LN_NPV, stdin);
            for (j = 0; temp[j] != '\0'; j++);
            temp[j - 1] = '\0';
            strcpy(pt_personne[taille].nom, temp);
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            break;
        case 3:
            printf("Indiquez la ville de la personne a inserer: ");
            fgets(temp, LN_NPV, stdin);
            for (j = 0; temp[j] != '\0'; j++);
            temp[j - 1] = '\0';
            strcpy(pt_personne[taille].ville, temp);
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            break;
        case 4:
            printf("Indiquez le code postal de la personne a inserer: ");
            fgets(temp, LN_CD, stdin);
            for (j = 0; temp[j] != '\0'; j++);
            temp[j - 1] = '\0';
            strcpy(pt_personne[taille].code_postal, temp);
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            break;
        case 5:
            printf("Indiquez le numero de telephone de la personne a inserer: ");
            fgets(temp, LN_TEL, stdin);
            for (j = 0; temp[j] != '\0'; j++);
            temp[j - 1] = '\0';
            strcpy(pt_personne[taille].numero_tel, temp);
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            break;
        case 6:
            printf("Indiquez l'adresse mail de la personne a inserer: ");
            fgets(temp, LN_MAIL, stdin);
            for (j = 0; temp[j] != '\0'; j++);
            temp[j - 1] = '\0';
            strcpy(pt_personne[taille].adr_mail, temp);
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            break;
        case 7:
            printf("Indiquez le metier de la personne a inserer: ");
            fgets(temp, LN_TAF, stdin);
            for (j = 0; temp[j] != '\0'; j++);
            temp[j - 1] = '\0';
            strcpy(pt_personne[taille].metier, temp);
            for (i = 0; i < j; i++) {
                temp[i] = '\0';
            }
            break;
        }
        compteur++;
    }
    printf("\n");
    //return la nouvelle taille
    fin = clock();
    printf("L'ajout de la ligne a pris : %ld millisecondes. \n(A noter que cette fonction comprend des demandes d'entrees d'ou un temps si eleve)\n\n", fin-debut);
    return taille + 1;
}

/**
 * \fn int suppression(Entite( * pt_personne), int taille)
 * \brief fonction qui permet de supprimer une entree dans le tableau et de diminuer en conséquent la taille tout en passant par une réallocation de la taille du tableau
 * \param Entite (*pt_personne) : accès au tableau ; taille
 * \return taille : correspond à la nouvelle taille soit taille-1
 */
int suppression(Entite * pt_personne, int taille) {
    int choix=0, ligne = 0, i=0, j=0, c = 0, k=0;
    char pers[LN_NPV], perso[LN_NPV], mail[LN_MAIL], num[LN_TEL];
    clock_t debut,fin;
    debut = clock();
    Entite * to_del;
    to_del = (Entite * ) malloc(taille * sizeof(Entite));

    do {
        printf("Par rapport a quoi souhaitez vous supprimer une entree ?\n");
        printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Adresse mail        (2)\n  - Numero de telephone (3)\n  - Annuler             (4)\nVotre choix: ");
        scanf("%d", & choix);
    } while (choix > 4 || choix < 0);
    getchar();
    switch (choix) {
    case 0:
        k=0;
        //boucle do-while pour être sûr que la valeur que l'on veut supprimer soit bien dans le tableau
        do {
            printf("Veuillez, s'il vous plait, indiquez le prenom de la personne: ");
            fgets(pers, LN_NPV, stdin);
            for (j = 0; pers[j] != '\0'; j++);
            pers[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                //calcul le nombre d'occurence pour savoir s'il faut spécifier le prénom en compplément
                if (strcmp(pt_personne[ligne].prenom, pers) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        if (c > 1) {
            to_del= (Entite* ) realloc(to_del, c*sizeof(Entite));
            printf("Plusieurs personnes ont ete trouvees:\n");
            printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0) {
                    cpy(to_del,pt_personne,ligne,k);
                    printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", to_del[k].prenom, to_del[k].nom, to_del[k].ville, to_del[k].code_postal, to_del[k].numero_tel, to_del[k].adr_mail, to_del[k].metier);
                    k++;
                }
            }
            printf("Veuillez desormais indiquez le nom de la personne que vous voulez supprimer: ");
            fgets(perso, LN_NPV, stdin);
            for (j = 0; perso[j] != '\0'; j++);
            perso[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, perso) == 0 && strcmp(pt_personne[ligne].prenom, pers) == 0) {
                    remonte(pt_personne, taille, i);
                } else i++;
            }
        } else {
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0) {
                    remonte(pt_personne, taille, i);
                } else i++;
            }
        }

        break;
    case 1:
        k=0;
        //globalement même fonctionnement que le case 0
        do {
            printf("Veuillez, s'il vous plait, indiquez le nom de la personne: ");
            fgets(perso, LN_NPV, stdin);
            for (j = 0; perso[j] != '\0'; j++);
            perso[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, perso) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        if (c > 1) {
            to_del= (Entite* ) realloc(to_del, c*sizeof(Entite));
            printf("Plusieurs personnes ont ete trouvees:\n");
            printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, perso) == 0) {
                    cpy(to_del,pt_personne,ligne,k);
                    printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", to_del[k].prenom, to_del[k].nom, to_del[k].ville, to_del[k].code_postal, to_del[k].numero_tel, to_del[k].adr_mail, to_del[k].metier);
                    k++;
                }
            }
            printf("Veuillez desormais indiquez le prenom de la personne que vous voulez supprimer: ");
            fgets(pers, LN_NPV, stdin);
            for (j = 0; pers[j] != '\0'; j++);
            pers[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0 && strcmp(pt_personne[ligne].nom, perso) == 0) {
                    remonte(pt_personne, taille, i);
                } else i++;
            }
        } else {
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, perso) == 0) {
                    remonte(pt_personne, taille, i);
                } else i++;
            }
        }
        break;
    case 2:
        k=0;
        do {
            printf("Veuillez, s'il vous plait, indiquez l'adresse mail de la personne: ");
            fgets(mail, LN_MAIL, stdin);
            for (j = 0; mail[j] != '\0'; j++);
            mail[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].adr_mail, mail) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].adr_mail, mail) == 0) {
                    remonte(pt_personne, taille, i);
                } else i++;
        }
        break;
    case 3:
        k=0;
        do {
            printf("Veuillez, s'il vous plait, indiquez le numero de telephone de la personne: ");
            fgets(num, LN_TEL, stdin);
            for (j = 0; num[j] != '\0'; j++);
            num[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].numero_tel, num) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].numero_tel, num) == 0) {
                    remonte(pt_personne, taille, i);
                } else i++;
        }
        break;
    case 4:
        break;
    }
    free(to_del);
    to_del=NULL;
    printf("\n");
    fin = clock();
    printf("La suppression a pris : %ld millisecondes\n(A noter que cette fonction comprend des demandes d'entrees d'ou un temps si eleve)\n\n", fin-debut);
    return taille - 1;
}

/**
 * \fn void remonte(Entite( * pt_personne), int taille, int i)
 * \brief fonction procédure utile a la fonction suppression qui permet d'écraser la ligne que l'on veut supprimer et fait remonter le reste des lignes
 * \param Entite (*pt_personne) : accès au tableau ; int taille ; int i : permet de savoir à partir de quelle ligne on fait remonter puis fais remonter les lignes d'après
 * \return rien
 */
void remonte(Entite * pt_personne, int taille, int i) {
    while (i < taille-1) {
        strcpy(pt_personne[i].nom, pt_personne[i + 1].nom);
        strcpy(pt_personne[i].prenom, pt_personne[i + 1].prenom);
        strcpy(pt_personne[i].ville, pt_personne[i + 1].ville);
        strcpy(pt_personne[i].code_postal, pt_personne[i + 1].code_postal);
        strcpy(pt_personne[i].numero_tel, pt_personne[i + 1].numero_tel);
        strcpy(pt_personne[i].adr_mail, pt_personne[i + 1].adr_mail);
        strcpy(pt_personne[i].metier, pt_personne[i + 1].metier);
        i++;
    }
}

/**
 * \fn modifier(Entite( * pt_personne), int taille)
 * \brief fonction procédure qui correspond à la modification d'une ou de plusieurs valeurs dans un tableau à partir de différentes possibilités
 * \param Entite (*pt_personne) : accès au tableau ; int taille
 * \return rien
 */
void modifier(Entite * pt_personne, int taille) {
    int choix, donnee, ligne = 0, j, c=0,k=0;
    char reponse[NB_CARA], pers[NB_CARA], perso[NB_CARA];
    Entite * temp;
    clock_t debut,fin;
    debut = clock();

    do {
        printf("Choississez la methode de recherche pour la personne a qui vous voulez modifier ses donnees:\n");
        printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Adresse mail        (2)\n  - Numero de telephone (3)\n  - Annuler             (4)\nVotre choix: ");
        scanf("%d", & choix);
        getchar();
    } while (choix > 4 || choix < 0);
    temp = (Entite * ) malloc(taille * sizeof(Entite));
    switch (choix) {
    case 0:
        do {
            printf("Veuillez, s'il vous plait, indiquez le prenom de la personne: ");
            fgets(pers, LN_NPV, stdin);
            for (j = 0; pers[j] != '\0'; j++);
            pers[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        temp=(Entite *)realloc(temp, c*sizeof(Entite));
        if (c > 1) {
            printf("Plusieurs personnes ont ete trouvees:\n");
            printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0) {
                    cpy(temp,pt_personne,ligne,k);
                    printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", temp[k].prenom, temp[k].nom, temp[k].ville, temp[k].code_postal, temp[k].numero_tel, temp[k].adr_mail, temp[k].metier);
                    k++;
                }
            }
            printf("Veuillez desormais indiquez le nom de la personne dont vous voulez modifier ces donnees: ");
            fgets(perso, LN_NPV, stdin);
            for (j = 0; perso[j] != '\0'; j++);
            perso[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0 && strcmp(pt_personne[ligne].nom, perso) == 0) {
                    do {
                        printf("Quelle donnee voulez modifier ?\n");
                        printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Ville               (2)\n  - Code postal         (3)\n  - Numero de telephone (4)\n  - Adresse mail        (5)\n  - Metier              (6)\n  - Quitter le menu     (7)\n");
                        printf("Votre choix: ");
                        scanf("%d", & donnee);
                        getchar();
                        switch (donnee) {
                        case 0:
                            printf("Ancien prenom: %s\n", pt_personne[ligne].prenom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 1:
                            printf("Ancien nom: %s\n", pt_personne[ligne].nom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 2:
                            printf("Ancienne ville: %s\n", pt_personne[ligne].ville);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 3:
                            printf("Ancien code postal: %s\n", pt_personne[ligne].code_postal);
                            rempl_mod(pt_personne, reponse, LN_CD, donnee, ligne);
                            break;
                        case 4:
                            printf("Ancien numero de telephone: %s\n", pt_personne[ligne].numero_tel);
                            rempl_mod(pt_personne, reponse, LN_TEL, donnee, ligne);
                            break;
                        case 5:
                            printf("Ancienne adresse mail: %s\n", pt_personne[ligne].adr_mail);
                            rempl_mod(pt_personne, reponse, LN_MAIL, donnee, ligne);
                            break;
                        case 6:
                            printf("Ancien metier: %s\n", pt_personne[ligne].metier);
                            rempl_mod(pt_personne, reponse, LN_TAF, donnee, ligne);
                            break;
                        case 7:
                            break;
                        default:
                            printf("Erreur de saisie :/\n");
                        }
                    } while (donnee != 7);
                }
            }
        } else {
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0) {
                    do {

                        printf("Quelle donnee voulez modifier ?\n");
                        printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Ville               (2)\n  - Code postal         (3)\n  - Numero de telephone (4)\n  - Adresse mail        (5)\n  - Metier              (6)\n  - Quitter le menu     (7)\n");
                        printf("Votre choix: ");
                        scanf("%d", & donnee);
                        getchar();
                        switch (donnee) {
                        case 0:
                            printf("Ancien prenom: %s\n", pt_personne[ligne].prenom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 1:
                            printf("Ancien nom: %s\n", pt_personne[ligne].nom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 2:
                            printf("Ancienne ville: %s\n", pt_personne[ligne].ville);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 3:
                            printf("Ancien code postal: %s\n", pt_personne[ligne].code_postal);
                            rempl_mod(pt_personne, reponse, LN_CD, donnee, ligne);
                            break;
                        case 4:
                            printf("Ancien numero de telephone: %s\n", pt_personne[ligne].numero_tel);
                            rempl_mod(pt_personne, reponse, LN_TEL, donnee, ligne);
                            break;
                        case 5:
                            printf("Ancienne adresse mail: %s\n", pt_personne[ligne].adr_mail);
                            rempl_mod(pt_personne, reponse, LN_MAIL, donnee, ligne);
                            break;
                        case 6:
                            printf("Ancien metier: %s\n", pt_personne[ligne].metier);
                            rempl_mod(pt_personne, reponse, LN_TAF, donnee, ligne);
                            break;
                        case 7:
                            break;
                        default:
                            printf("Erreur de saisie :/\n");
                        }
                    } while (donnee != 7);
                }
            }
        }
        break;

    case 1:
        k=0;
         do {
            printf("Veuillez, s'il vous plait, indiquez le nom de la personne: ");
            fgets(perso, LN_NPV, stdin);
            for (j = 0; perso[j] != '\0'; j++);
            perso[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, perso) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        temp=(Entite *)realloc(temp, c*sizeof(Entite));
        if (c > 1) {
            printf("Plusieurs personnes ont ete trouvees:\n");
            printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, perso) == 0) {
                    cpy(temp,pt_personne,ligne,k);
                    printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", temp[k].prenom, temp[k].nom, temp[k].ville, temp[k].code_postal, temp[k].numero_tel, temp[k].adr_mail, temp[k].metier);
                    k++;
                }
            }
            printf("Veuillez desormais indiquez le prenom de la personne dont vous voulez modifier ces donnees: ");
            fgets(pers, LN_NPV, stdin);
            for (j = 0; pers[j] != '\0'; j++);
            pers[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, pers) == 0 && strcmp(pt_personne[ligne].nom, perso) == 0) {
                    do {
                        printf("Quelle donnee voulez modifier ?\n");
                        printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Ville               (2)\n  - Code postal         (3)\n  - Numero de telephone (4)\n  - Adresse mail        (5)\n  - Metier              (6)\n  - Quitter le menu     (7)\n");
                        printf("Votre choix: ");
                        scanf("%d", & donnee);
                        getchar();
                        switch (donnee) {
                        case 0:
                            printf("Ancien prenom: %s\n", pt_personne[ligne].prenom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 1:
                            printf("Ancien nom: %s\n", pt_personne[ligne].nom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 2:
                            printf("Ancienne ville: %s\n", pt_personne[ligne].ville);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 3:
                            printf("Ancien code postal: %s\n", pt_personne[ligne].code_postal);
                            rempl_mod(pt_personne, reponse, LN_CD, donnee, ligne);
                            break;
                        case 4:
                            printf("Ancien numero de telephone: %s\n", pt_personne[ligne].numero_tel);
                            rempl_mod(pt_personne, reponse, LN_TEL, donnee, ligne);
                            break;
                        case 5:
                            printf("Ancienne adresse mail: %s\n", pt_personne[ligne].adr_mail);
                            rempl_mod(pt_personne, reponse, LN_MAIL, donnee, ligne);
                            break;
                        case 6:
                            printf("Ancien metier: %s\n", pt_personne[ligne].metier);
                            rempl_mod(pt_personne, reponse, LN_TAF, donnee, ligne);
                            break;
                        case 7:
                            break;
                        default:
                            printf("Erreur de saisie :/\n");
                        }
                    } while (donnee != 7);
                }
            }
        } else {
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, perso) == 0) {
                    do {

                        printf("Quelle donnee voulez modifier ?\n");
                        printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Ville               (2)\n  - Code postal         (3)\n  - Numero de telephone (4)\n  - Adresse mail        (5)\n  - Metier              (6)\n  - Quitter le menu     (7)\n");
                        printf("Votre choix: ");
                        scanf("%d", & donnee);
                        getchar();
                        switch (donnee) {
                        case 0:
                            printf("Ancien prenom: %s\n", pt_personne[ligne].prenom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 1:
                            printf("Ancien nom: %s\n", pt_personne[ligne].nom);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 2:
                            printf("Ancienne ville: %s\n", pt_personne[ligne].ville);
                            rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                            break;
                        case 3:
                            printf("Ancien code postal: %s\n", pt_personne[ligne].code_postal);
                            rempl_mod(pt_personne, reponse, LN_CD, donnee, ligne);
                            break;
                        case 4:
                            printf("Ancien numero de telephone: %s\n", pt_personne[ligne].numero_tel);
                            rempl_mod(pt_personne, reponse, LN_TEL, donnee, ligne);
                            break;
                        case 5:
                            printf("Ancienne adresse mail: %s\n", pt_personne[ligne].adr_mail);
                            rempl_mod(pt_personne, reponse, LN_MAIL, donnee, ligne);
                            break;
                        case 6:
                            printf("Ancien metier: %s\n", pt_personne[ligne].metier);
                            rempl_mod(pt_personne, reponse, LN_TAF, donnee, ligne);
                            break;
                        case 7:
                            break;
                        default:
                            printf("Erreur de saisie :/\n");
                        }
                    } while (donnee != 7);
                }
            }
        }
        break;

    case 2:
        do {
            printf("Veuillez, s'il vous plait, indiquez l'adresse mail de la personne: ");
            fgets(perso, LN_MAIL, stdin);
            for (j = 0; perso[j] != '\0'; j++);
            perso[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].adr_mail, perso) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].adr_mail, perso) == 0) {
                do {
                    printf("Quelle donnee voulez modifier ?\n");
                    printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Ville               (2)\n  - Code postal         (3)\n  - Numero de telephone (4)\n  - Adresse mail        (5)\n  - Metier              (6)\n  - Quitter le menu     (7)\n");
                    printf("Votre choix: ");
                    scanf("%d", & donnee);
                    getchar();
                    switch (donnee) {
                    case 0:
                        printf("Ancien prenom: %s\n", pt_personne[ligne].prenom);
                        rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                        break;
                    case 1:
                        printf("Ancien nom: %s\n", pt_personne[ligne].nom);
                        rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                        break;
                    case 2:
                        printf("Ancienne ville: %s\n", pt_personne[ligne].ville);
                        rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                        break;
                    case 3:
                        printf("Ancien code postal: %s\n", pt_personne[ligne].code_postal);
                        rempl_mod(pt_personne, reponse, LN_CD, donnee, ligne);
                        break;
                    case 4:
                        printf("Ancien numero de telephone: %s\n", pt_personne[ligne].numero_tel);
                        rempl_mod(pt_personne, reponse, LN_TEL, donnee, ligne);
                        break;
                    case 5:
                        printf("Ancienne adresse mail: %s\n", pt_personne[ligne].adr_mail);
                        rempl_mod(pt_personne, reponse, LN_MAIL, donnee, ligne);
                        break;
                    case 6:
                        printf("Ancien metier: %s\n", pt_personne[ligne].metier);
                        rempl_mod(pt_personne, reponse, LN_TAF, donnee, ligne);
                        break;
                    case 7:
                        break;
                    default:
                        printf("Erreur de saisie :/\n");
                    }
                } while (donnee != 7);
            }
        }
        break;

    case 3:
        do {
            printf("Veuillez, s'il vous plait, indiquez le numero de telephone de la personne: ");
            fgets(pers, LN_TEL, stdin);
            for (j = 0; pers[j] != '\0'; j++);
            pers[j - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].numero_tel, pers) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].numero_tel, pers) == 0) {
                do {
                    printf("Quelle donnee voulez modifier ?\n");
                    printf("  - Prenom              (0)\n  - Nom                 (1)\n  - Ville               (2)\n  - Code postal         (3)\n  - Numero de telephone (4)\n  - Adresse mail        (5)\n  - Metier              (6)\n  - Quitter le menu     (7)\n");
                    printf("Votre choix: ");
                    scanf("%d", &donnee);
                    getchar();
                    switch (donnee) {
                    case 0:
                        printf("Ancien prenom: %s\n", pt_personne[ligne].prenom);
                        rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                        break;
                    case 1:
                        printf("Ancien nom: %s\n", pt_personne[ligne].nom);
                        rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                        break;
                    case 2:
                        printf("Ancienne ville: %s\n", pt_personne[ligne].ville);
                        rempl_mod(pt_personne, reponse, LN_NPV, donnee, ligne);
                        break;
                    case 3:
                        printf("Ancien code postal: %s\n", pt_personne[ligne].code_postal);
                        rempl_mod(pt_personne, reponse, LN_CD, donnee, ligne);
                        break;
                    case 4:
                        printf("Ancien numero de telephone: %s\n", pt_personne[ligne].numero_tel);
                        rempl_mod(pt_personne, reponse, LN_TEL, donnee, ligne);
                        break;
                    case 5:
                        printf("Ancienne adresse mail: %s\n", pt_personne[ligne].adr_mail);
                        rempl_mod(pt_personne, reponse, LN_MAIL, donnee, ligne);
                        break;
                    case 6:
                        printf("Ancien metier: %s\n", pt_personne[ligne].metier);
                        rempl_mod(pt_personne, reponse, LN_TAF, donnee, ligne);
                        break;
                    case 7:
                        break;
                    default:
                        printf("Erreur de saisie :/\n");
                    }
                } while (donnee != 7);
            }
        }
        break;

    case 4:
        break;

    }
    free(temp);
    temp=NULL;
    fin = clock();
    printf("La modification a duree au total : %ld millisecondes.\n(A noter que cette fonction comprend des demandes d'entrees d'ou un temps si eleve)\n\n", fin-debut);
}

/**
 * \fn rempl_mod(Entite( * pt_personne), char reponse[], int taille, int type, int ligne)
 * \brief fonction procédure qui permet de remplir la le critère d'une ligne blablabla je suis fatigué ça commence à faire long à partir de ces paramètres
 * \param Entite (*pt_personne) : accès au tableau ; char reponse[] : pour pouvoir répondre ; int taille : c'est la taille du tableau ; int type : permet au programme de savoir quelle catégorie il faut remplir ; int ligne : le nombre de ligne mdr
 * \return rien
 */
void rempl_mod(Entite * pt_personne, char reponse[], int taille, int type, int ligne) {
    int j;
    clock_t debut,fin;
    printf("Votre modification: ");
    fgets(reponse, taille, stdin);
    debut = clock();
    for (j = 0; reponse[j] != '\0'; j++);
    reponse[j - 1] = '\0';
    switch (type) {
    case 0:
        strcpy(pt_personne[ligne].prenom, reponse);
        break;
    case 1:
        strcpy(pt_personne[ligne].nom, reponse);
        break;
    case 2:
        strcpy(pt_personne[ligne].ville, reponse);
        break;
    case 3:
        strcpy(pt_personne[ligne].code_postal, reponse);
        break;
    case 4:
        strcpy(pt_personne[ligne].numero_tel, reponse);
        break;
    case 5:
        strcpy(pt_personne[ligne].adr_mail, reponse);
        break;
    case 6:
        strcpy(pt_personne[ligne].metier, reponse);
        break;
    }fin=clock();
    printf("Temps d'execution de la procedure : %ldms\n\n",fin-debut);

}

/**
 * \fn void filtre(Entite *pt_personne,int taille)
 * \brief fonction procédure qui permet de filtrer le tableau pour n'afficher que certaines personnes selon un paramètre (filtre)
 * \param Entite (*pt_personne) : accès au tableau ; int taille :nombre de lignes totale
 * \return rien
 */
void filtre(Entite *pt_personne,int taille){
    clock_t debut, fin;
    int choix,ligne,i,c=0,k=0;
    char filter[NB_CARA];
    printf("Quel filtre voulez-vous utiliser pour votre recherche ?\n");
    printf(" (0) - Prenom\n (1) - Nom\n (2) - Ville\n (3) - Code postal\n (4) - Numero de telephone\n (5) - Adresse mail\n (6) - Metier\n (7) - Annuler\n");
    Entite * answers;
    answers = (Entite * ) malloc(taille * sizeof(Entite));
    do{
        printf("Votre choix: ");
        scanf("%d",&choix);
    }while(choix > 7 || choix < 0);
    getchar();
    debut=clock();
    switch(choix){
    case 0:
        do{
            printf("Veuillez, s'il vous plait, indiquer le prenom: ");
            fgets(filter,NB_CARA,stdin);
            debut=clock();
            for (i = 0; filter[i] != '\0'; i++);
            filter[i - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].prenom, filter) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        answers = (Entite *) realloc(answers, c*sizeof(Entite));
        printf("Voici les personnes correspondantes a votre recherche:\n");
        printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].prenom, filter) == 0) {
                cpy(answers,pt_personne,ligne,k);
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", answers[k].prenom, answers[k].nom, answers[k].ville, answers[k].code_postal, answers[k].numero_tel, answers[k].adr_mail, answers[k].metier);
                k++;
            }
        }
        break;
    case 1:
        do{
            printf("Veuillez, s'il vous plait, indiquer le nom: ");
            fgets(filter,NB_CARA,stdin);
            debut=clock();
            for (i = 0; filter[i] != '\0'; i++);
            filter[i - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].nom, filter) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        answers = (Entite *) realloc(answers, c*sizeof(Entite));
        printf("Voici les personnes correspondantes a votre recherche:\n");
        printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].nom, filter) == 0) {
                cpy(answers,pt_personne,ligne,k);
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", answers[k].prenom, answers[k].nom, answers[k].ville, answers[k].code_postal, answers[k].numero_tel, answers[k].adr_mail, answers[k].metier);
                k++;
            }
        }
        break;
    case 2:
        do{
            printf("Veuillez, s'il vous plait, indiquer la ville: ");
            fgets(filter,NB_CARA,stdin);
            debut=clock();
            for (i = 0; filter[i] != '\0'; i++);
            filter[i - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].ville, filter) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        answers = (Entite *) realloc(answers, c*sizeof(Entite));
        printf("Voici les personnes correspondantes a votre recherche:\n");
        printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].ville, filter) == 0) {
                cpy(answers,pt_personne,ligne,k);
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", answers[k].prenom, answers[k].nom, answers[k].ville, answers[k].code_postal, answers[k].numero_tel, answers[k].adr_mail, answers[k].metier);
                k++;}
        }
        break;
    case 3:
        do{
            printf("Veuillez, s'il vous plait, indiquer le code postal: ");
            fgets(filter,NB_CARA,stdin);
            debut=clock();
            for (i = 0; filter[i] != '\0'; i++);
            filter[i - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].code_postal, filter) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        answers = (Entite *) realloc(answers, c*sizeof(Entite));
        printf("Voici les personnes correspondantes a votre recherche:\n");
        printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].code_postal, filter) == 0) {
                cpy(answers,pt_personne,ligne,k);
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", answers[k].prenom, answers[k].nom, answers[k].ville, answers[k].code_postal, answers[k].numero_tel, answers[k].adr_mail, answers[k].metier);
                k++;}
        }
        break;
    case 4:
        do{
            printf("Veuillez, s'il vous plait, indiquer le numero de telephone: ");
            fgets(filter,NB_CARA,stdin);
            debut=clock();
            for (i = 0; filter[i] != '\0'; i++);
            filter[i - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].numero_tel, filter) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        answers = (Entite *) realloc(answers, c*sizeof(Entite));
        printf("Voici les personnes correspondantes a votre recherche:\n");
        printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].numero_tel, filter) == 0) {
                cpy(answers,pt_personne,ligne,k);
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", answers[k].prenom, answers[k].nom, answers[k].ville, answers[k].code_postal, answers[k].numero_tel, answers[k].adr_mail, answers[k].metier);
                k++;}
        }
        break;
    case 5:
        do{
            printf("Veuillez, s'il vous plait, indiquer l'adresse mail: ");
            fgets(filter,NB_CARA,stdin);
            debut=clock();
            for (i = 0; filter[i] != '\0'; i++);
            filter[i - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].adr_mail, filter) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        answers = (Entite *) realloc(answers, c*sizeof(Entite));
        printf("Voici les personnes correspondantes a votre recherche:\n");
        printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].adr_mail, filter) == 0) {
                cpy(answers,pt_personne,ligne,k);
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", answers[k].prenom, answers[k].nom, answers[k].ville, answers[k].code_postal, answers[k].numero_tel, answers[k].adr_mail, answers[k].metier);
                k++;}
        }
        break;
    case 6:
        do{
            printf("Veuillez, s'il vous plait, indiquer le metier: ");
            fgets(filter,NB_CARA,stdin);
            debut=clock();
            for (i = 0; filter[i] != '\0'; i++);
            filter[i - 1] = '\0';
            for (ligne = 0; ligne < taille; ligne++) {
                if (strcmp(pt_personne[ligne].metier, filter) == 0) {
                    c++;
                }
            }
        } while (c == 0);
        answers = (Entite *) realloc(answers, c*sizeof(Entite));
        printf("Voici les personnes correspondantes a votre recherche:\n");
        printf("           Prenom             |             Nom              |          Ville          |C Post|    Num Tel    |                  Adresse Mail                    |         Metier\n");
        for (ligne = 0; ligne < taille; ligne++) {
            if (strcmp(pt_personne[ligne].metier, filter) == 0) {
                cpy(answers,pt_personne,ligne,k);
                printf("%30s|%30s|%25s|%6s|%15s|%50s|%20s\n", answers[k].prenom, answers[k].nom, answers[k].ville, answers[k].code_postal, answers[k].numero_tel, answers[k].adr_mail, answers[k].metier);
                k++;}
        }
        break;
    }fin=clock();
    printf("Temps d'execution : %ld millisecondes.\n\n",fin-debut);
}

/**
 * \fn void save(Entite *pt_personne, int taille)
 * \brief fonction procédure qui permet de sauvegarder le tableau ouvert précedement en variable dans un fichier au nom choisit.
 * \param Entite (*pt_personne) : accès au tableau ; int taille :nombre de lignes totale
 * \return rien
 * \referent : https://www.exelib.net/langage-c/sauvegarde-et-lecture-d-un-tableau-d-etudiants-dans-un-fichier-texte.html#solution-tab
 */
void save(Entite *pt_personne, int taille){
    int ligne,i,choix;
    clock_t debut,fin;
    char name[NB_CARA];
    getchar();
    printf("Veuillez indiquer sous quel nom vous voulez sauvegarder (pensez a inclure le .csv a la fin): ");
    fgets(name,NB_CARA,stdin);
    do{
        printf("Que voulez-vous sauvegarder ?\n (0) - Toutes les entrees\n (1) - Seulement les entrees completes\n (2) - Seulement les entrees incompletes\n Votre choix: ");
        scanf("%d",&choix);
    }while(choix>2||choix<0);
    debut=clock();
    for(i=0;name[i]!='\0';i++);
    name[i-1]='\0';
    FILE * sauvegarde = fopen(name,"w");
    switch(choix){
    case 0:
        for(ligne = 0; ligne < taille; ligne ++){
            fprintf(sauvegarde,"%s,%s,%s,%s,%s,%s,%s\n",pt_personne[ligne].prenom, pt_personne[ligne].nom, pt_personne[ligne].ville, pt_personne[ligne].code_postal, pt_personne[ligne].numero_tel, pt_personne[ligne].adr_mail, pt_personne[ligne].metier);
        }break;
    case 1:
        for(ligne = 0; ligne < taille; ligne ++){
            if (strcmp(pt_personne[ligne].nom, "") != 0 && strcmp(pt_personne[ligne].prenom, "") != 0 && strcmp(pt_personne[ligne].ville, "") != 0 && strcmp(pt_personne[ligne].code_postal, "") != 0 && strcmp(pt_personne[ligne].numero_tel, "") != 0 && strcmp(pt_personne[ligne].adr_mail, "") != 0 && strcmp(pt_personne[ligne].metier, "") != 0) {
                fprintf(sauvegarde,"%s,%s,%s,%s,%s,%s,%s\n",pt_personne[ligne].prenom, pt_personne[ligne].nom, pt_personne[ligne].ville, pt_personne[ligne].code_postal, pt_personne[ligne].numero_tel, pt_personne[ligne].adr_mail, pt_personne[ligne].metier);}
        }break;
    case 2:
        for(ligne = 0; ligne < taille; ligne ++){
            if (strcmp(pt_personne[ligne].nom, "") == 0 || strcmp(pt_personne[ligne].prenom, "") == 0 || strcmp(pt_personne[ligne].ville, "") == 0 || strcmp(pt_personne[ligne].code_postal, "") == 0 || strcmp(pt_personne[ligne].numero_tel, "") == 0 || strcmp(pt_personne[ligne].adr_mail, "") == 0 || strcmp(pt_personne[ligne].metier, "") == 0) {
                fprintf(sauvegarde,"%s,%s,%s,%s,%s,%s,%s\n",pt_personne[ligne].prenom, pt_personne[ligne].nom, pt_personne[ligne].ville, pt_personne[ligne].code_postal, pt_personne[ligne].numero_tel, pt_personne[ligne].adr_mail, pt_personne[ligne].metier);}
        }break;
    default:
        printf("Valeur incorrect :/\n");
        break;
    }
	fclose(sauvegarde);
	fin=clock();
	printf("Le fichier a bien ete enregistre sous le nom de %s\n",name);
	printf("Temps pris pour la sauvegarde du fichier est de : %ld millisecondes.\n\n",fin-debut);
}

/**
 * \fn void cpy(Entite *receveur, Entite *emetteur,int ligne, int k)
 * \brief fonction procédure qui a pour but d'optimiser le code afin d'éviter une trop grosse répétition
 * \param Entite *receveur : accès à la mémoire du tableau receveur de la copie ; Entite *emetteur : accès à la mémoire du tableau emetteur qui permet de copier,int ligne, int k
 * \return rien
 */
void cpy(Entite *receveur, Entite *emetteur,int ligne, int k){
    strcpy(receveur[k].nom, emetteur[ligne].nom);
    strcpy(receveur[k].prenom, emetteur[ligne].prenom);
    strcpy(receveur[k].ville, emetteur[ligne].ville);
    strcpy(receveur[k].code_postal, emetteur[ligne].code_postal);
    strcpy(receveur[k].numero_tel, emetteur[ligne].numero_tel);
    strcpy(receveur[k].adr_mail, emetteur[ligne].adr_mail);
    strcpy(receveur[k].metier, emetteur[ligne].metier);
}

/**
 * \fn void tri(Entite *pt_personne, int taille)
 * \brief fonction procédure qui permet de trier le tableau
 * \param Entite *pt_personne : adresse mémoire du tableau actif; int taille
 * \referent Tasur sur https://forums.commentcamarche.net/forum/affich-27265828-tri-des-chaines-de-caractere-en-c qui nous a permis de copier le fonctionnement du tri
 * \return rien
 *
 * contrairement à ce qui était annoncé dans le rapport d'algo, la fonction tri se sert d'un algorithme basique et simple à complexité de O(n²) et à fonctionnenement linéaire. le tri shell a été beaucoup trop dur a essayer de le mettre en place pour des chaines de caractère
 *
 */
void tri(Entite *pt_personne, int taille){
    int i,j,choix,autre_choix;
    clock_t debut,fin;
    printf("Indiquez par quoi vous voulez effectuer le tri ?\n");
    printf(" (0) - Prenom\n (1) - Nom\n (2) - Ville\n (3) - Code postal\n (4) - Numero de telephone\n (5) - Adresse mail\n (6) - Metier\n (7) - Annuler\n");
    printf("Votre choix: ");
    scanf("%d",&choix);
    getchar();
    if(choix!=7){
        printf("Voulez-vous effectuez un tri:\n  (0) - Par ordre croissant\n  (1) - Par ordre decroissant\nVotre choix: ");
        scanf("%d",&autre_choix);
        getchar();
    }
    debut = clock();
    switch(autre_choix){
        case 0:
            switch(choix){
            case 0:
                for(i=0; i<taille; i++){
                    for(j=0; j<taille; j++){
                        if(strcmp(pt_personne[i].prenom,pt_personne[j].prenom)<0){
                            big_cpy(pt_personne,i,j);
                        }
                    }
                }
            break;
            case 1:
                for(i=0; i<taille; i++){
                    for(j=0; j<taille; j++){
                        if(strcmp(pt_personne[i].nom,pt_personne[j].nom)<0){
                            big_cpy(pt_personne,i,j);
                        }
                    }
                }
            break;
            case 2:
                for(i=0; i<taille; i++){
                    for(j=0; j<taille; j++){
                        if(strcmp(pt_personne[i].ville,pt_personne[j].ville)<0){
                            big_cpy(pt_personne,i,j);
                        }
                    }
                }
            break;
            case 3:
                for(i=0; i<taille; i++){
                    for(j=0; j<taille; j++){
                        if(strcmp(pt_personne[i].code_postal,pt_personne[j].code_postal)<0){
                            big_cpy(pt_personne,i,j);
                        }
                    }
                }
            break;
            case 4:
                for(i=0; i<taille; i++){
                    for(j=0; j<taille; j++){
                        if(strcmp(pt_personne[i].numero_tel,pt_personne[j].numero_tel)<0){
                            big_cpy(pt_personne,i,j);
                        }
                    }
                }
            break;
            case 5:
                for(i=0; i<taille; i++){
                    for(j=0; j<taille; j++){
                        if(strcmp(pt_personne[i].adr_mail,pt_personne[j].adr_mail)<0){
                            big_cpy(pt_personne,i,j);
                        }
                    }
                }
            break;
            case 6:
                for(i=0; i<taille; i++){
                    for(j=0; j<taille; j++){
                        if(strcmp(pt_personne[i].metier,pt_personne[j].metier)<0){
                            big_cpy(pt_personne,i,j);
                        }
                    }
                }
            break;
            case 7:
                break;
            default:
                printf("Valeur incorrect :/\n");
                break;
            }
        break;
        case 1:
            switch(choix){
                case 0:
                    for(i=0; i<taille; i++){
                        for(j=0; j<taille; j++){
                            if(strcmp(pt_personne[i].prenom,pt_personne[j].prenom)>0){
                                big_cpy(pt_personne,i,j);
                            }
                        }
                    }
                break;
                case 1:
                    for(i=0; i<taille; i++){
                        for(j=0; j<taille; j++){
                            if(strcmp(pt_personne[i].nom,pt_personne[j].nom)>0){
                                big_cpy(pt_personne,i,j);
                            }
                        }
                    }
                break;
                case 2:
                    for(i=0; i<taille; i++){
                        for(j=0; j<taille; j++){
                            if(strcmp(pt_personne[i].ville,pt_personne[j].ville)>0){
                                big_cpy(pt_personne,i,j);
                            }
                        }
                    }
                break;
                case 3:
                    for(i=0; i<taille; i++){
                        for(j=0; j<taille; j++){
                            if(strcmp(pt_personne[i].code_postal,pt_personne[j].code_postal)>0){
                                big_cpy(pt_personne,i,j);
                            }
                        }
                    }
                break;
                case 4:
                    for(i=0; i<taille; i++){
                        for(j=0; j<taille; j++){
                            if(strcmp(pt_personne[i].numero_tel,pt_personne[j].numero_tel)>0){
                                big_cpy(pt_personne,i,j);
                            }
                        }
                    }
                break;
                case 5:
                    for(i=0; i<taille; i++){
                        for(j=0; j<taille; j++){
                            if(strcmp(pt_personne[i].adr_mail,pt_personne[j].adr_mail)>0){
                                big_cpy(pt_personne,i,j);
                            }
                        }
                    }
                break;
                case 6:
                    for(i=0; i<taille; i++){
                        for(j=0; j<taille; j++){
                            if(strcmp(pt_personne[i].metier,pt_personne[j].metier)>0){
                                big_cpy(pt_personne,i,j);
                            }
                        }
                    }
                break;
                case 7:
                    break;
                default:
                    printf("Valeur incorrect :/\n");
                    break;
                }
            break;
        default:
            printf("Valeur incorrect :/\n");
    }
    fin = clock();
    printf("Temps d'execution: %ldms\n",fin-debut);
}

/**
 * \fn big_cpy(Entite *pt_personne,int i,int j)
 * \brief fonction procédure qui sert à optimiser pour éviter d'avoir beaucoup trop de répétitions de ligne de codes
 * \param Entite *pt_personne : adresse mémoire du tableau actif; int i ; int j
 * \return rien
 */
void big_cpy(Entite *pt_personne,int i,int j){
    char temp[NB_CARA];
    strcpy(temp, pt_personne[i].prenom);
    strcpy(pt_personne[i].prenom, pt_personne[j].prenom);
    strcpy(pt_personne[j].prenom, temp);

    strcpy(temp, pt_personne[i].nom);
    strcpy(pt_personne[i].nom, pt_personne[j].nom);
    strcpy(pt_personne[j].nom, temp);

    strcpy(temp, pt_personne[i].ville);
    strcpy(pt_personne[i].ville, pt_personne[j].ville);
    strcpy(pt_personne[j].ville, temp);

    strcpy(temp, pt_personne[i].code_postal);
    strcpy(pt_personne[i].code_postal, pt_personne[j].code_postal);
    strcpy(pt_personne[j].code_postal, temp);

    strcpy(temp, pt_personne[i].numero_tel);
    strcpy(pt_personne[i].numero_tel, pt_personne[j].numero_tel);
    strcpy(pt_personne[j].numero_tel, temp);

    strcpy(temp, pt_personne[i].adr_mail);
    strcpy(pt_personne[i].adr_mail, pt_personne[j].adr_mail);
    strcpy(pt_personne[j].adr_mail, temp);

    strcpy(temp, pt_personne[i].metier);
    strcpy(pt_personne[i].metier, pt_personne[j].metier);
    strcpy(pt_personne[j].metier, temp);
}
