#include <stdio.h>
#include "menu.h"
#include <stdlib.h>
#include <string.h>
#define LEN 1000

/*	printf("Quel status avez-vous ?\n1 - Adhérent\t2 - Admin");
	scanf("%d%*c", *status);
	if(*status == 2){
		while(int mdp!=)
		printf("")
	}*/

int main(void){
	int trouve, rangId, choixMenu, rootChoice;
	system("clear");	//Pour avoir un aspect plus propre en effaçant les lignes du terminal au démarrage
	int t1[1000], t2[1000],t4[1000],t5[1000], tAct[10], tNbEntree[10];
	int nbActChoisi = 0, n = 0, identite, choix, result, error, codeErr;
	char t3[1000], mdp[15];
	char sauv;
	n = chargement(t1, t2, t3,t4 ,t5,LEN);
	error = chargementAct(tAct, tNbEntree, LEN);
	if(n<0)
		return 2;
	rootChoice = 1;
	while(rootChoice==1){
		printf("------------------------------------------------\n\n");
		printf("\tStatus :\n\n");
		printf("\t\t1 - Adhérent\n");
		printf("\t\t2 - Admin\n");
		printf("\t\t3 - Sauvegarder et quitter\n\n");
		printf("------------------------------------------------\n\n");
		printf("\tVotre status : ");
		scanf("%d%*c", &choix);
		
		if(choix==1){
			rangId = identificationClient(t1, t2, &n);
			system("clear");
			if(t3[rangId]=='D'){
				printf(">--------------------------------------------------------------<\n\n");
				printf("\t\tVotre carte est désactivée.\n\tContactez un administrateur pour la réactiver.\n\n");
				printf(">--------------------------------------------------------------<\n");
				choix = 0;
				choixMenu = 3;
			}
			if(t3[rangId]=='A'){
				if(rangId==-1)
					return -1;
				fage(rangId, t1,t2, t3, t4,t5, &n);
				if(t5[rangId]>1){
					printf(">----------------------------------------------------------------<\n\n");
					printf("\tVous êtes déjà venu(e) aujourd'hui, revenez demain\n\n");
					printf(">----------------------------------------------------------------<\n");
					printf("\t\n");
					choixMenu = 3;	
				}
				else{
					if(t2[rangId] <= 0){		// IL FAUT QUE LE CLIENT AIT OBLIGATOIREMENT DES POINTS EN SE CONNECTANT SINON REDIRECTION VERS RECHARGE CARTE
						choixMenu = 2;
					}
					else{
						choixMenu = 0;
					}
				}
				while(choixMenu!=3){
					if(choixMenu==1){
						result = choixActiv(t2, rangId, tAct, tNbEntree, &nbActChoisi, 8);
						choixMenu = 0;
						system("clear");
					}
					if(choixMenu==2){
						system("clear");
						rechargeCarte(t2, rangId);
						choixMenu = 0;
					}
					if(choixMenu==3){
						system("clear");
						printf("\tDéconnection effectuée avec succès.\n");
						choix==0;
					}
					choixMenu = menuClient();
				}
			}
		}
		
		if(choix==2){
			mdp[0] = 'A';
			printf("\tMot de passe : ");
			scanf("%s%*c", mdp);
			if(!strcmp(mdp, "mdp03")){ 	//LE MOT DE PASSE EST mdp03
				system("clear");
				MenuAdmin(t1, t2, t3,t4,t5, tNbEntree, &n, LEN);
				printf("\tVoulez vous sauvegarder? (O/N) : ");
				scanf("%c%*c",&sauv);
				if(sauv=='O')
					codeErr = fsauvegarde(t1, t2, t3,t4,t5, tAct, tNbEntree, &n, LEN, choix);
				
			}
			else{
				system("clear");
				printf(">------------------------------------------<\n");
				printf("\n\tMauvais mot de passe. >_<\n\n");
				printf(">------------------------------------------<\n");
			}
		}
		
		if(choix==3){
			codeErr = fsauvegarde(t1, t2, t3,t4,t5, tAct, tNbEntree, &n, LEN, choix);
			system("clear");
			printf(">----------------------------------------<\n\n");
			printf("\tTous les fichiers sauvegardés.\n\n");
			printf("\tMerci de votre visite.\n\n");
			printf("\t- Fin de journée -\n\n");
			printf(">----------------------------------------<\n");
			rootChoice = 0;
		}
	}
}
