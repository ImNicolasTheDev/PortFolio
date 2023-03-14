#include <stdio.h>
#include "menu.h"

/*Cette fonction permet de se connecter à travers le menu principal. Si 
l'identifiant est trouvé, elle renvoit le rang/index du client et affiche
le nombre de points de l'adhérent. 
Si il y a plus de 3 tentatives de connexion sans succès, cette fonciton 
retourne le code d'erreur -1. Si le client n'est pas sur la liste, alors 
une 2ème chance est accordée pour rentrer un numéro valide.*/

int identificationClient(int *t1, int *t2, int *n){
    int i=0, client, found = -5, compteur=0;
    printf("\tEntrez votre n° d'adhérent : ");
    scanf("%d", &client);
    found = rechercheIdentificationClient(t1, n, client);
    while(found==-5){
    	if(compteur>=2){
    		printf("\tTrop de tentatives.\n");
    		return -1;
    	}
    	printf("\tVous n'êtes pas sur la liste. Réessayez : ");
    	scanf("%d",&client);
    	found = rechercheIdentificationClient(t1, n, client);
    	compteur++;
    	printf("%d", found);
    }
    //Continue si l'identifiant du client est trouvé
    printf("\tVous avez %d point(s)\n", t2[found]);
    return found;
}
/*Cette fonction permet d'identifier si le client existe déjà dans la 
base de données. Si oui, elle renvoit le rang/index du client. Sinon, 
cette fonction retourne le code d'erreur -5.*/
int rechercheIdentificationClient(int *t1, int *n, int client){
	int i = 0;
	while(i<=*n){
		if(client!=0){
			if(t1[i]==client){
				return i;	//client trouvé
			}
		}
		i++;
	}
	return -5;
}



/*Ces 2 fonctions permettent tout simplement de charger les 2 fichiers nécessaires :
le fichier contenant toutes les informations concernant les adhérents, et le
fichier concernant le nombre de points par activité et leur fréquentation, par 
activité. */

int chargement(int *t1, int *t2, char *t3, int *t4,int *t5, int tmax){
    FILE *fe;
    int nclient, nbpoints,age,visit, i=0;
    char activer;
    fe =fopen("Adherents.txt","r");
    if(fe==NULL){
    	printf("====> Problème à l'ouverture du fichier. <====\n");
    	return -1;
    }
    fscanf(fe,"%d\t%d\t%c%*c\t%d\t%d", &nclient, &nbpoints, &activer,&age,&visit);
    while(feof(fe)==0){
        if(i==tmax){
        	printf("====> Tableaux plein, fermeture en cours. <====\n");
        	fclose(fe);
        	return -2;
        }
        t1[i]=nclient;
        t2[i]=nbpoints;
        t3[i]=activer;
		t4[i]=age;
		t5[i]=visit;
        fscanf(fe,"%d\t%d\t%c%*c\t%d\t%d", &nclient, &nbpoints, &activer,&age,&visit);
        i++;
    }
    fclose(fe);
    return i;
}

int chargementAct(int *tAct, int *tNbEntree, int tmax){
    FILE *feAct;
    int numAct, nbEntree, i=0;
    feAct =fopen("Activites.txt","r");
    if(feAct==NULL){
    	printf("====> Problème à l'ouverture du fichier. <====\n");
    	return -1;
    }
    fscanf(feAct,"%d\t%d%*c", &numAct, &nbEntree);
    while(feof(feAct)==0){
        if(i==tmax){
        	printf("====> Tableaux plein, fermeture en cours. <====\n");
        	fclose(feAct);
        	return -2;
        }
        tAct[i]=numAct;
        tNbEntree[i]=nbEntree;
        fscanf(feAct,"%d\t%d", &numAct, &nbEntree);
        i++;
    }
    fclose(feAct);
    return 0;
}


/*La fonction menuClient permet d'afficher le menu du côté adhérent, et renvoit le
choix de celui-ci : c'est à dire soit Choisir les activités, soit Recharger sa carte,
soit Se déconnecter en quittant.*/

int menuClient(void){
	int choix;
	printf("\n>==================================================<\n\n");
	printf("\tMenu :\n\n");
	printf("\t\t1 - Choisir mes activités\n");
	printf("\t\t2 - Recharger ma carte\n");
	printf("\t\t3 - Quitter\n");
	printf("\n>==================================================<\n\n");
	printf("\tVotre choix : ");
	scanf("%d", &choix);
	return choix;
}

/*Cette fonction permet à chaque adhérent de recharger sa carte. Elle affiche d'abord le nombre de points,
puis demande à l'utilisateur de combien de points souhaite-t-il bénéficier. La valeur doit être supérieur 
à 2 points, soit supérieure ou égale à 1€. Ensuite, il y a une demande de confirmation, avec indication du
montant de la recharge, puis après validation l'enregistrement et l'affichage du nouveau solde.*/
void rechargeCarte(int *t2, int rangId){
	int ptsRecharge, aPayer;
	char verif;
	printf("\n\tVous avez %d point(s)\n", t2[rangId]);
	printf("\tDe combien de points voulez-vous recharger votre carte ? (5€ les 10 points)\n\t(2 points au minimum)\n\n\tNombre de points : ");
	scanf("%d%*c", &ptsRecharge);
	aPayer = 0.5 * ptsRecharge; //50 Centimes le point, arrondi à l'unité
	if(aPayer <= 0){
		printf("\n\tVous devez entrer une valeur correcte. Annulation...\n\n");
	}
	if(aPayer > 0){
		printf("\n\n\tVoulez-vous %d points pour un total de %d€ ? (O/N) ", ptsRecharge, aPayer);
		scanf("%c%*c", &verif);
		if(verif=='O'){
			printf("\tEnregistrement en cours...\n");
			t2[rangId] = t2[rangId] + ptsRecharge;
			printf("\tVotre nouveau solde s'élève à %d points\n", t2[rangId]);
		}
		//Annulation si l'utilisateur ne valide pas
	}
}


/*Cette grande fonction permet à l'adhérent de choisir son activité. Il a le choix entre 8 activités différentes, 
et ne peut pas entrer un autre nombre, sinon, la fonction retourne le code d'erreur -2. Ensuite, différents calculs
sont réalisés, à savoir l'ajout de 1 à la fréquentation de l'activité choisie et le calcul du montant des points restants
après avoir choisit l'activité. Cette fonction vérifie aussi si l'adhérent
a un nombre suffisant de points pour participer à ladite activité.*/
int choixActiv(int *t2, int nbPoints, int *tAct, int *tNbEntree, int *n, int tmax){
	int i, act, ptsRestants, ptsConso = 0, compt = 0, compt2 = 0;
	char finSaisie = 'N';
	printf("\n>==========================================<\n\n");
	printf("\tListe des activités :\n\n");
	printf("\t\t1 - Aquagym\t\t> 20 points\n");
	printf("\t\t2 - Musculation\t\t> 15 points\n");
	printf("\t\t3 - Foot en salle\t> 15 points\n");
	printf("\t\t4 - Badminton\t\t> 10 points\n");
	printf("\t\t5 - Spa\t\t\t> 20 points\n");
	printf("\t\t6 - Massage\t\t> 18 points\n");
	printf("\t\t7 - Relaxation\t\t> 12 points\n");
	printf("\t\t8 - Volleyball\t\t> 10 points\n\n");
	printf(">==========================================<\n\n");
	printf("\tVous avez actuellement %d point(s) restants.\n\n", t2[nbPoints]);
	printf("\tQuelle activité souhaitez-vous faire ? ");
	i=1;
	act=1;
	while(act!=0){
		if(act<0 || act>8)
			return -2;
		scanf("%d", &act);
		if(act!=0){
			tNbEntree[act - 1] = tNbEntree[act - 1] + 1;
			ptsRestants = t2[nbPoints] - tAct[act - 1];
			if(ptsConso < 110)
				ptsConso = ptsConso + tAct[act - 1];
			if(ptsConso >= 50){
				if(ptsConso >= 110 && compt2==0){
					printf("\n\tVous avez dépensé plus de 100 points, merci beaucoup !\n");
					printf("\tVoilà 20 points pour vous remercier de votre confiance :D\n\n");
					ptsRestants = ptsRestants + 20;
					compt2 = 1;
				}else if(compt==0){
					printf("\n\tVous avez dépensé plus de 50 points, merci !\n");
					printf("\tVoilà 10 points pour vous remercier de votre confiance :)\n\n");
					ptsRestants = ptsRestants + 10;
					compt = 1;
				}
			}
		}
		if(ptsRestants<0){
			printf("\tVous n'avez pas assez de points pour faire cette activité.\n");
			ptsRestants = t2[nbPoints] + tAct[act - 1];
		}else{
			t2[nbPoints] = ptsRestants;
		}
		if(*n>=8){
			printf("\n\tNombre maximum d'activité atteint.\n");
			return -1;
		}
		if(act>0){
			printf("\tPoints : %d", t2[nbPoints]);
			printf("\tUne autre activité ? (0 - Valider mes choix) ");
		}
		
	}
	printf("\tNombre de points actualisés !\n");
	return 0;
}

/*Cette fonction est un système de points bonus. Ce système est très simple : pour plus de 50 points dépensés,
une remise de 10 points, et pour plus de 100 points, une remise de 20 points. Elle est en lien direct avec la 
fonction précédente.*/
void fage(int rangId,int *t1,int *t2,char *t3,int *t4,int *t5,int *n){
	int i;
	for(i=0;i<*n;i++){
		if(rangId==t1[i]){
			if(t4[i]>61){
				printf(">----------------------------------------------------------------------------<\n\n");
				printf("\tMerci pour votre engagement, on vous rajoute 20 points de plus !\n");
				printf("\tContinuez à faire du sport !\n");
				t2[rangId]=t2[rangId]+20;
			}
			else if(t4[i]<21 || t4[i]>41){
				printf(">----------------------------------------------------------------------------<\n\n");
				printf("\tMerci pour votre engagement, on vous rajoute 10 points de plus !\n");
				printf("\tContinuez à faire du sport !\n");
				t2[rangId]=t2[rangId]+10;
			}
		}
	}
	t5[rangId]++; //Ajoute 1 au nombre de visite par utilisateur.
}
