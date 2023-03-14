#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iut.h"

void MenuRespon(Candidat *tcandidat[],VilleIUT *tiut[], int n, int nc){
    int choix=1, i, j, m, comp, comp1;
    char Ncandidat[30], PNcandidat[30], departement[30],Ville[30];
    printf("\nVille où se situe le departement \n:");
    scanf("%s",Ville);
    printf("\nVotre Departement\n:");
    scanf("%s", departement);
    for(i=0;i<nc;i++){
        comp=strcmp(tiut[i]->ville, Ville);//Si Ville existe
        if(comp==0){
            for(j=0;j<=tiut[i]->nbDep;j++){
                if(strcmp(tiut[i]->ldept->departement, departement) == 0 && tiut[i]->ldept->AouD == 'D'){
                    for(m=0;m<nc;m++){
                        if(rechercheCandidatParVille(tcandidat[m]->lchoix,departement,Ville, nc) ==0){//appel de la fonction recherche
                            afficheCandidat(tcandidat, m);//afficher candidat qui sont dans le departement choisi
                        } 
                    } 
                }
                tiut[i]->ldept=tiut[i]->ldept->suivant;
            }
        }            
    }
    while(choix>0 && choix<3){
    printf("\n  >--------------------------------------------------------<\n");
    printf("\n\t0 - Revenir au menu");
    printf("\n\t1 - Ajouter un etudiant");
    printf("\n\t2 - refuser un etudiant");
    printf("\n\t3 - mettre en file d'attante un etudiant");
    printf("\n  >--------------------------------------------------------<\n");
    printf("\n\tVotre choix : ");
    scanf("\n%d",&choix);
    system("cls");
    system("clear");
    }
}