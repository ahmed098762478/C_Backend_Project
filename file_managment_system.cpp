#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CATALMAX 100   // Taille maximale du catalogue des fichiers
#define ECHEC 0        // Booléans pour définir l'état de la fonction (échec)
#define SUCCES 1       // Booléans pour définir l'état de la fonction (succès)

typedef struct {
    char nomf[50];
    int id;
    char emp[50];
    char etatp[50];
} fichier;

fichier catal[CATALMAX]; // Déclaration du catalogue des fichiers

// Fonction qui permet de chercher un fichier dans un catalogue 
// Retourne SUCCES si un fichier est trouvé, sinon retourne ECHEC
int recherchef(fichier catal[], char *nomf1, int nbrf) {
    for (int i = 0; i < nbrf; i++) {
        if (strcmp(nomf1, catal[i].nomf) == 0) {
            printf("Fichier existant\n");
            return SUCCES;
        }
    }
    printf("Fichier introuvable\n");
    return ECHEC;
}

// Fonction qui permet d'ajouter un fichier 
// Retourne SUCCES si correctement ajouté, retourne ECHEC sinon
int ajoutf(fichier catal[], int *nbrf) {
    if (*nbrf >= CATALMAX) {
        return ECHEC; // Stockage insuffisant
    }

    char nomf[50];
    printf("Entrer le nom du fichier: ");
    scanf("%s", nomf);
    if (recherchef(catal, nomf, *nbrf) == SUCCES) {
        return ECHEC; // Fichier déjà existant
    }

    strcpy(catal[*nbrf].nomf, nomf);
    printf("Entrer votre identifiant: ");
    scanf("%d", &catal[*nbrf].id);
    printf("Entrer l'emplacement du fichier: ");
    scanf("%s", catal[*nbrf].emp);
    printf("Entrer l'état du fichier (public/prive): ");
    scanf("%s", catal[*nbrf].etatp);

    (*nbrf)++;
    return SUCCES;
}

// Fonction qui permet de changer le nom d'un fichier
// Retourne SUCCES si le changement est réussi, retourne ECHEC sinon
int changementnf(fichier catal[], char *nomf2, int nbrf) {
    int index = -1;
    for (int i = 0; i < nbrf; i++) {
        if (strcmp(nomf2, catal[i].nomf) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return ECHEC; // Fichier non trouvé
    }

    char nvnf[50];
    printf("Entrez le nouveau nom: ");
    scanf("%s", nvnf);
    strcpy(catal[index].nomf, nvnf);
    return SUCCES;
}

// Fonction qui permet de supprimer un fichier
// Retourne SUCCES si la suppression est réussie, retourne ECHEC sinon
int suppf(fichier catal[], int *nbrf) {
    char nomf3[50];
    printf("Entrez le nom du fichier: ");
    scanf("%s", nomf3);

    for (int i = 0; i < *nbrf; i++) {
        if (strcmp(nomf3, catal[i].nomf) == 0) {
            for (int j = i; j < *nbrf - 1; j++) {
                catal[j] = catal[j + 1];
            }
            (*nbrf)--;
            return SUCCES; // Fichier supprimé avec succès
        }
    }
    return ECHEC; // Fichier non trouvé
}

// Fonction qui permet de modifier l'état de partage d'un fichier
int partagef(fichier catal[], int nbrf, char *nomf4) {
    for (int i = 0; i < nbrf; i++) {
        if (strcmp(nomf4, catal[i].nomf) == 0) {
            printf("Fichier est public\n");
            strcpy(catal[i].etatp, "public");
            return SUCCES;
        }
    }
    return ECHEC;
}

// Fonction qui permet le retrait du partage d'un fichier
int retraitf(fichier catal[], int nbrf, char *nomf5) {
    for (int i = 0; i < nbrf; i++) {
        if (strcmp(nomf5, catal[i].nomf) == 0) {
            printf("Fichier est privé\n");
            strcpy(catal[i].etatp, "prive");
            return SUCCES;
        }
    }
    return ECHEC;
}

// Affichage des fichiers d'un utilisateur
void affichage(fichier catal[], int nbrf, int id) {
    for (int i = 0; i < nbrf; i++) {
        if (catal[i].id == id) {
            printf("%s %s\n", catal[i].nomf, catal[i].etatp);
        }
    }
}

// Affichage du menu
void affiche_menu() {
    printf("1- Rechercher un fichier\n");
    printf("2- Ajouter un fichier\n");
    printf("3- Changer le nom d'un fichier\n");
    printf("4- Supprimer un fichier\n");
    printf("5- Partager un fichier\n");
    printf("6- Retirer le partage d'un fichier\n");
    printf("7- Afficher les fichiers d'un utilisateur\n");
    printf("0- Quitter\n");
}

// Partie main
int main() {
    int nbrf = 0; // Au début, il n'y a aucun fichier stocké
    int choix;
    int id;
    char nomf[50];

    do {
        affiche_menu();
        printf("Entrer votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrer le nom du fichier: ");
                scanf("%s", nomf);
                recherchef(catal, nomf, nbrf);
                break;
            case 2:
                if (ajoutf(catal, &nbrf) == SUCCES) {
                    printf("Fichier ajouté avec succès\n");
                } else {
                    printf("Erreur d'ajout\n");
                }
                break;
            case 3:
                printf("Entrer le nom du fichier: ");
                scanf("%s", nomf);
                if (changementnf(catal, nomf, nbrf) == SUCCES) {
                    printf("Nom du fichier changé avec succès\n");
                } else {
                    printf("Erreur de changement de nom\n");
                }
                break;
            case 4:
                if (suppf(catal, &nbrf) == SUCCES) {
                    printf("Fichier supprimé avec succès\n");
                } else {
                    printf("Erreur de suppression\n");
                }
                break;
            case 5:
                printf("Entrer le nom du fichier: ");
                scanf("%s", nomf);
                if (partagef(catal, nbrf, nomf) == SUCCES) {
                    printf("Fichier partagé en état public\n");
                } else {
                    printf("Erreur de partage\n");
                }
                break;
            case 6:
                printf("Entrer le nom du fichier: ");
                scanf("%s", nomf);
                if (retraitf(catal, nbrf, nomf) == SUCCES) {
                    printf("Fichier partagé en état privé\n");
                } else {
                    printf("Erreur de retrait de partage\n");
                }
                break;
            case 7:
                printf("Entrer l'identifiant de l'utilisateur: ");
                scanf("%d", &id);
                affichage(catal, nbrf, id);
                break;
            case 0:
                printf("Quitter le programme\n");
                break;
            default:
                printf("Choix invalide\n");
                break;
        }
    } while (choix != 0);

    return 0;
}

