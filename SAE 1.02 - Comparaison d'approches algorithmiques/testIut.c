#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iut.h"


int main(){
    int n, nc, codeErr, rootChoice=1, choix;
    char sauv;
    VilleIUT *tiut[200];
    Candidat *tcandidat[200];

    //Affichage plus propre en effaçant l'historique du terminal
    system("cls");  // pour Windows
    system("clear");  // pour Unix

    n=chargement(tiut ,200);
    printf("==============================================================\n");
    printf("\n\tNombre de villes : %d\t",n);
    nc=chargementcandidat(tcandidat ,200);
    printf("Nombre de candidat : %d\n",nc);
    printf("\n==============================================================\n");
    while(rootChoice==1){/*  
        printf("\t\tTableau Ville et departement\n");
        printf("\nNombre de villes : %d\n",n);
        affichage(tiut,n);
        printf("\n\n\n\t\tTableau Candidat et choix\n");
        printf("\nNombre de candidat : %d\n",nc);
        affichageCandidatchoix(tcandidat,nc);*/
        printf("\n  >--------------------------------------<\n");
        printf("\n\t1 - Utilisateur / Invité");
        printf("\n\t2 - Administrateur");
        printf("\n\t3 - Candidat");
        printf("\n\t4 - Responsable");
        printf("\n\t5 - Sauvegarder et quitter\n");
        printf("\n  >--------------------------------------<\n");
        printf("\n\tVotre choix : ");
        scanf("%d",&choix);
        if(choix==1){
            //Menu Utilisateur
            system("cls");
            system("clear");
            MenuUtilisateur(tiut, n);
        }
        if(choix==2){
            //Menu Administrateur
            system("cls");
            system("clear");
            MenuAdministrateur(tiut, n);
        }
        if(choix==3){
            //Menu Candidat
            system("cls");
            system("clear");
            MenuCandidat(tcandidat, tiut, nc);
        }
        if(choix==4){
            printf("\nMenu Responsable");
            MenuRespon(tcandidat, tiut, n, nc);
        }
        if(choix==5){
            printf(">----------------------------------------<\n\n");
            codeErr = fsauvegarde(tiut, tcandidat, n, nc, choix, 200);
            printf("\tTous les fichiers sauvegardés.\n\n");
			printf("\tMerci de votre visite.\n\n");
			printf("\t- Fin de journée -\n\n");
			printf(">----------------------------------------<\n");
			rootChoice = 0;

        }
        system("cls");
        system("clear");
    }
}