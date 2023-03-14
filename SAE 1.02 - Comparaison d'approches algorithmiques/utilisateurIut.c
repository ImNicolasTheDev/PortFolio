#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iut.h"

//Cette fonction permet à l'utilisateur d'avoir un menu avec 5 choix différent (voir ci-dessous)
void MenuUtilisateur(VilleIUT *tiut[], int n){
    int choix, succes;
    while(choix!=5){
		printf("\n  >--------------------------------------------------<\n");
		printf("\n\t1 - Recherche d'un IUT");
		printf("\n\t2 - Départements dans chaque IUT");
		printf("\n\t3 - Nombre de places en première année");
		printf("\n\t4 - Recherche d'un département");
		printf("\n\t5 - Quitter\n");
		printf("\n  >--------------------------------------------------<\n");
		printf("\n\tVotre choix : ");//Demande à l'utilisateur d'entrer un nombre correspond à ce qu'il désire faire
		scanf("%d%*c",&choix);
		system("cls");
        system("clear");
		if(choix==1){
		    //Recherche de tel IUT
		    succes = rechercheIUT(tiut, n);
		}
		if(choix==2){
			//Recherche d'un département dans un IUT
			succes = rechercheDept(tiut, n);
		}
		if(choix==3){
			//Recherche du nombre de places dans un IUT
		    succes = recherchePlaces(tiut, n);
		}
		if(choix==4){
			//Recherche des infos complètes sur tel département dans tel ville
		    succes = rechercheMixed(tiut, n);
		}
		if(choix==5){
			//Ici, l'utilisateur retourne au menu précédent, c'est à dire le menu principal (dans le main)
		    return;
		}
	}
}

//Cette fonction de recherche permet simplement de trouver si il y a un IUT dans une ville.
//Retourne 0 si trouvé, sinon 1.
int rechercheIUT(VilleIUT *tiut[], int n){
	char rech[31];
	int i, trouve = 0;
	printf("\nEntrez le nom d'une ville ou d'un IUT : ");
	scanf("%s%*c", &rech);
	for(i=0;i<n && trouve!=1;i++){
		if(strcmp(tiut[i]->ville, rech)==0){
			printf("\nIl y a un IUT à %s.\n", rech);
			trouve = 1;
			return 0;
		}
		else if(i==n-1)
			printf("\nIl n'y pas d'IUT dans votre ville.\n");
	}
	return 1;
}

//Cette fonction de recherche permet de trouver une liste des départements d'un IUT.
//Retourne 0 si réussite, sinon 1.
int rechercheDept(VilleIUT *tiut[], int n){
	char rech[31];
	int i, trouve = 0, j = 0;
	ListeD ld;
	printf("\nEntrez le nom d'une ville : ");
	scanf("%s%*c", &rech);
	for(i=0;i<n && trouve!=1;i++){
		ld = tiut[i]->ldept;
		if(strcmp(tiut[i]->ville, rech)==0){
			printf("\nListe des départements :\n\n");
			while(ld!=NULL){
				printf("%s\t",ld->departement);
				printf("Responsable : %s\n",ld->resp);
				ld = ld->suivant;
			}
			trouve = 1;
		}
		else if(i==n-1)
			printf("\nAucun département trouvé, il n'y pas d'IUT dans votre ville.\n");
	}
	if(trouve==1)
		return 0;
	else
		return 1;
}

//Cette fonction de recherche permet à l'utilisateur de trouver lme nombre de places dans chaque départment du même nom.
int recherchePlaces(VilleIUT *tiut[], int n){
	char rech[31];
	int i, trouve = 0, j = 0;
	ListeD ld;
	printf("\nEntrez un département : ");
	scanf("%s%*c", &rech);
	for(i=0;i<n && trouve!=1;i++){
		ld = tiut[i]->ldept;
		if(strcmp(ld->departement, rech)){
			printf("\nÀ %s :\n", tiut[i]->ville);
			printf("%s\t", ld->departement);
			printf("Nombre de places : %d\n",ld->nbP);
		}
		ld = ld->suivant;
		if(i==n-1)
			printf("\nAucun département trouvé.\n");
	}
	return 1;
}

//Enfin, cette fonction permet de rechercher les infos complètes d'un département dans une ville précise, c'est à dire le nombre de places, le nom du responsable et le lieu.
int rechercheMixed(VilleIUT *tiut[], int n){
	char rech[31], rech2[31];
	int i, trouve = 0, j = 0, quit=0;
	ListeD ld;
	printf("\nEntrez le nom d'une ville : ");
	scanf("%s%*c", &rech);
	printf("\nEntrez le nom du département souhaité : ");
	scanf("%s%*c", &rech2);
	for(i=0;i<n && trouve!=1;i++){
		ld = tiut[i]->ldept;
		if(strcmp(tiut[i]->ville, rech)==0){
			while(ld!=NULL){
				if(strcmp(ld->departement, rech2)==0){
					printf("\nÀ %s :\n", tiut[i]->ville);
					printf("%s\t", ld->departement);
					printf("Nombre de places : %d\n",ld->nbP);
					printf("Responsable : %s\n",ld->resp);
					trouve = 1;
				}
				ld = ld->suivant;
			}
			if(trouve==0)
				printf("\nAucun département trouvé.\n");
				quit = 1;
		}
		else if(i==n-1 && quit==0)
			printf("\nAucun département trouvé pour la ville correspondante.\n");
	}
	printf("\n");
	return 1;
}