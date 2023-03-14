#include <stdio.h>
#include"menu.h"

/*  la fonction chargement permet ici d'initaialser les tableaux en fonction du fichier
    dans les 3 tableaux: id, points, carte activer ou non.
    Elle rencoit la valeur logique de la table si pas d'erreur, sinon renvoi un code d'erreur: 
    -1 probleme d'ouverture du fichier, -2 probleme d'espace.*/

void MenuAdmin(int *t1,int *t2,char *t3,int *t4,int *t5, int *tNbEntree, int *n,int tmax){
    int choisi, nfonction=0;
    printf("\n>==================================================<\n\n");
    printf("\tMenu :\n\n");
    printf("\t1 - Créer un adhérent\n");
    printf("\t2 - Désactiver/Activer une carte\n");
    printf("\t3 - Supprimer un adhérent\n");
    printf("\t4 - Afficher tout les adhérents\n");
    printf("\t5 - Afficher infos d'un adhérent\n");
    printf("\t6 - Afficher la fréquentation par activité\n");
    printf("\n>==================================================<\n\n");
    printf("\tChoix : ");
    scanf("%d",&choisi);
    while(choisi>0){
        if(choisi<1 || choisi>6){
        	printf("\tErreur, l'option n'existe pas.\n");
        }
        if(choisi==1) 
            Fcreer(n,t1,t2,t3,t4,t5,tmax);      
        if(choisi==2)    
            FDesactiverActiver(t1,t3,n);
        if(choisi==3)    
            Fsupprimer(t1,t2,t3,t4,t5,n);
        if(choisi==4)    
            affichage(t1,t2,t3,t4,t5,n);
        if(choisi==5)
            affichageUnA(t1,t2,t3,t4,t5,n);
        if(choisi==6)
            affichageFreq(tNbEntree);
        printf("\n\tVoulez-vous choisir une autre fonction ? Sinon taper 0 pour valider : ");
        scanf("%d%*c",&choisi);
        
    }
    affichage(t1,t2,t3,t4,t5,n);
    affichageFreq(tNbEntree);
    
}
/*  la fonction MenuAdmin sert de Menu à l'administarteur pour choisir quel tache faire 
    et les choix possible, elle renvoie la fonction choisi mais surtout appel les fonction désiré.
    Si cas d'erreur, renvoi du code d'erreur : -3 error activité non existante.*/


int RechercheInsertion(int *t, int n, int val,int *trouve){
    int i=0;
    *trouve=0;
    for(i=0;i<n;i++){
        if(val==t[i]){
            *trouve=1;
            return i;
        }
        if(val<t[i]){
            *trouve=0;
            return i;
        }
    }
    return i;
}

/*  La fonction RecherchInsertion permet de savoir si un identifiant est deja activer ou non 
    et renvoie où il se situe sur la table. */

int Fcreer(int *n, int *t1,int *t2,char *t3,int *t4,int *t5,int tmax){
    int r,trouve, i=0,nclient,nbpoints,age;
    printf("\tEntrer l'id :");
    scanf("%d",&nclient);
    r=RechercheInsertion(t1,*n,nclient,&trouve);
    if(trouve==1){
    	printf("\tId deja existant");
    	return-1;
    }
    printf("\tEntrer nb de point :");
    scanf("%d",&nbpoints);
    printf("\tEntrer votre age :");
    scanf("%d",&age);
    if(*n==tmax){
    	printf("\tTableaux plein");
    	return-2;
    }
    else for(i=*n+1;i>=r;i--){
	t1[i+1]=t1[i];
	t2[i+1]=t2[i];
	t3[i+1]=t3[i];
    t4[i+1]=t4[i];
	t5[i+1]=t5[i];
    }
    t1[r]=nclient;
    t2[r]=nbpoints;
    t3[r]='A';
    t4[r]=age;
    t5[r]=0;
    *n=*n+1;
    return 0;
}

/*  La fonction Fcreer regarde si il y a de l'espace pour ajouter une fonction 
    et si oui appel la fonction RecherchInsertion et grace à son code de retour
    va décaler les valeur plus grande que elle et ecrire dans la table le nouvelle identifiant. */

void affichage(int *t1,int *t2,char *t3, int *t4, int *t5,int *n){
    int i;
    printf("\n\tn°Id\t\tnombre points\t\tstatut\t\tAge\t\tVisite\n");
    for(i=0; i<*n; i++){
        printf("\t%d\t\t%d\t\t\t%c\t\t%d\t\t%d\n",t1[i], t2[i],t3[i],t4[i],t5[i]);
    }   
}
/* La fonction affichage affiche les tout les ligne du tableau avec l'id, le nombre de points
    et si la carte et activer ou non.*/

int FDesactiverActiver(int *t1,char *t3,int *n){
    int i,nId;
    char statut;
    printf("\n\tNuméro d'Id:");
    scanf("%d%*c",&nId);
    for (i=0; i<=*n;i++){
        if(nId==t1[i]){
            printf("\n\tChoisir statut (A/D):");
            scanf("%c",&statut);   
            if(statut == 'D'){
                t3[i]= 'D';
                return 0;}
            if(statut == 'A'){
                t3[i]= 'A';
                return 0;}
            printf("\tPb valeur incorect");
            return -1;
        }
        if(nId<t1[i]){
             printf("\n\tNuméro d'id incorect, réessayer :");
             scanf("%d",&nId);
             i=0;
        }

    }
    return 0;
}

/*  La fonction FDesactiverActiver permet de changer le statut d' utilisateur dans le tableau
    et si l'id incorrect permet de réssayer. */

int Fsupprimer(int *t1,int *t2,char *t3,int *t4,int *t5,int *n){
    int r,i,trouve,val;
    printf("\tId a supprimer :");
    scanf("%d",&val);

    r=RechercheInsertion(t1,*n,val,&trouve);
    if(trouve==0){printf("\tId non trouvé");return-1;}
    for(i=r;i<*n-1;i++){
        t1[i]=t1[i+1];
        t2[i]=t2[i+1];
        t3[i]=t3[i+1];
        t4[i]=t4[i+1];
        t5[i]=t5[i+1];
    }
    *n=*n-1;
    return 0;
}

/*  La fonction Fsupprimer demande la valeur a supprimer, ensuite appelle la fonction RechercheInsertion
    qui grace a son code retour va décaler les valeur plus grande de -1.
    Et si Id est non trouvé ecrire message d'erreur et renvoie -1.
    Sinon renvoie 0  */

int fsauvegarde(int *t1,int *t2,char *t3, int *t4,int *t5,int *tNbPoints, int *tNbEntree, int *n,int tmax, int choix){
    int i, j;
    
    //Sauvegarde du fichier d'adhérents
    FILE *fe;
    fe=fopen("Adherents.txt","w");
    if(fe==NULL){
    	printf("\tPb overture fichier");
    	return-1;
    }
    for(i=0;i<*n;i++){
        if(i==tmax){
        	printf("\tPb espace");
        	fclose(fe);
        	return-2;
        }
        if(choix==3)
        	fprintf(fe,"%d\t\t%d\t\t%c\t\t%d\t\t%d\n",t1[i], t2[i],t3[i],t4[i],0); //La valeur 0 permet de remettre à 0 les visites lors de la sauvegarde finale
        else
        	fprintf(fe,"%d\t\t%d\t\t%c\t\t%d\t\t%d\n",t1[i], t2[i],t3[i],t4[i],t5[i]);
    }
    fclose(fe);
    
    //Sauvegarde du fichier d'activités
    if(choix==3){
	    FILE *fe2;
	    fe2=fopen("ActivitesFinJournee.txt","a"); //Ici, le a permet d'écrire à la suite des informations précédentes dans le fichier sans les supprimer
	    if(fe==NULL){
	    	printf("\tpb overture fichier");
	    	return-1;
	    }
	    fprintf(fe2, "\nDate : --:--:--\n");
	    fprintf(fe2, "n°Act\tNb Visites\n");
	    for(j=0;j<8;j++){
		if(j==tmax){
			printf("\tPb espace");
			fclose(fe2);
			return-2;
		}
		fprintf(fe2,"%d\t%d\n",j+1, tNbEntree[j]);
	    }
	    fclose(fe2);
	    return 0;
    }
}

/*  La fonction fsauvegarde permet de réecrir tout les tableaux dans les fichiers et renvoie:
    -1 si probleme d'ouverture du fichier et -2 si espace insuffisant, sinon 0 si tout fonctionne */

void affichageUnA(int *t1,int *t2,char *t3,int *t4,int *t5,int *n){
    int i, r, trouve;
    printf("\tEntrer numero adhérent : ");
    scanf("%d",&i);
    if(i>0){
    	    r = RechercheInsertion(t1, *n, i, &trouve);
	    if(trouve==0){
		printf("\tProbleme non existant\n");
	    }
	    else{
		printf("\n\tn°Id\t\tnombre points\t\tstatut\t\tAge\t\tVisite\n");
		printf("\t%d\t\t%d\t\t\t%c\t\t%d\t\t%d\n",t1[r], t2[r],t3[r],t4[r],t5[r]);  
	    }
    }
    else{
	    printf("\tEntrez un identifiant valide.\n");
    }
}
/*  La fonction affichageUnA permet d'afficher les informations d'un identifiant préssisement */
void affichageFreq(int *tNbEntree){
    int i;
    printf("\n\tN°activité\tfréquentation\n");
    for(i=0; i<8; i++){
        printf("\t%d\t\t%d\n", i+1, tNbEntree[i]);
    }   
}
