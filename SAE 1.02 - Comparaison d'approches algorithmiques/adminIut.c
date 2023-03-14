#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iut.h"

void MenuAdministrateur(VilleIUT *tiut[],int n){
    char departement[30], respon[30], Vmodif[31],tVille[31], tdepartemnt[30], AouD;
    int choix = 1, nbp, i, j, Mnbp,good=0,reussi=0;
    VilleIUT V;
    while(choix>0 && choix<6){
        printf("\n  >--------------------------------------------------------<\n");
        printf("\n\t0 - Revenir au menu");
        printf("\n\t1 - Modifier une place");
        printf("\n\t2 - Créer un département");
        printf("\n\t3 - Supprimer un département");
        printf("\n\t4 - Lancer et arrêter la phase de canditature");
        printf("\n\t5 - Modifier le nom d'un responsable");
        printf("\n\t6 - Afficher différents tableaux => FONCTION DE DEV UNIQUEMENT\n");
        printf("\n  >--------------------------------------------------------<\n");
        printf("\n\tVotre choix : ");
        scanf("\n%d%*c",&choix);
        system("cls");
        system("clear");
        if(choix==1){
            char rech[31], rech2[31];
            int trouve = 0, trouveVille = 0;
            ListeD ld;
            printf("\nEntrez le nom d'une ville : ");
            scanf("%s%*c", &rech);//Lire Ville
            for(i=0;i<n && trouve!=1;i++){
                ld = tiut[i]->ldept;
                if(strcmp(tiut[i]->ville, rech)==0){
                    trouveVille = 1;
                    printf("IUT trouvé à %s !\n", rech);
                    printf("\nNom du département à modifier : ");
                    scanf("%s", rech2);
                    while(ld!=NULL){
                        if(strcmp(ld->departement, rech2)==0 && ld->AouD == 'D'){
                            trouve = 1;
                            printf("\nProblème, phase de candidature à l'arrêt pour ce département.\n");
                            good=1;
                        }else if(strcmp(ld->departement, rech2)==0 && ld->AouD == 'A'){
                            trouve = 1;
                            printf("\nNombre de place après modification : ");
                            scanf("%d",&Mnbp);
                            tiut[i]->ldept=ModifinbP(tiut[i]->ldept, rech2, Mnbp,n);
                            reussi=1;
                        }
                        ld = ld->suivant;
                    }
                    if(trouve == 0)
                        printf("Pas de département correspondant trouvé dans cette ville.\n");
                }
                else if(i==n-1 && trouveVille==0){
                    printf("Il n'y pas d'IUT dans cette ville.\n");
                }
            }
        }   
        if(choix==2){
            //creer departemement
            int quit = 0;
            ListeD ld;
            printf("\nVille où se situe le département : ");
            scanf("%s",Vmodif);
            for(i=0;i<n && quit==0;i++){
                ld = tiut[i]->ldept;
                if(strcmp(tiut[i]->ville, Vmodif)==0){//Si la ville existe
                    printf("\nNom du département à créer : ");
                    scanf("%s",departement);
                    while(ld!=NULL){
                        if(strcmp(ld->departement, departement)==0 && quit==0){
                            printf("\nProblème, ce département existe déjà.\n");
                            quit = 1;
                        }
                        ld = ld->suivant;
                    }
                    if(quit==0){
                        printf("\nNombre de place : ");
                        scanf("%d",&nbp);
                        printf("\nNom du responsable : ");
                        scanf("%s",respon);
                        tiut[i]->ldept=Enfiler(tiut[i]->ldept,departement,nbp,respon);//ajouter un departement avec ses caractéristiques
                        tiut[i]->nbDep=tiut[i]->nbDep+1;// ajouter 1 au nombre de departement de la ville
                        reussi=1;
                    }
                }
            }
            if(reussi==0 && quit==0)
                printf("Problème, cette ville ne possède pas déjà un IUT.\n");// si Ville non trouver ou probleme de syntaxe
        }
        if(choix==3){
            //supprimer departement et pauser condition pour choisir qui suppr
            int exist = 0;
            ListeD ld;
            printf("\nVille où se situe le département : ");
            scanf("%s",Vmodif);
            for(i=0;i<n;i++){
                ld = tiut[i]->ldept;
                if(strcmp(tiut[i]->ville, Vmodif)==0){//Si la ville existe
                    printf("\nNom du département à supprimer : ");
                    scanf("%s",departement);
                    while(ld!=NULL){
                        if(strcmp(ld->departement, departement)==0){
                            tiut[i]->ldept=suppression(tiut[i]->ldept,departement);//supprimer un departement avec ses caractéristiques
                            tiut[i]->nbDep=tiut[i]->nbDep-1;// enlever 1 au nombre de departement de la ville
                            reussi = 1;
                            exist = 1;
                        }
                        if(strcmp(ld->departement, departement)!=0 && exist == 0){
                            exist = 2;
                        }
                        ld = ld->suivant;
                    }
                }
            }
            if(exist==2)
                printf("Ce département n'existe pas.");
            if(reussi==0 && exist==0)
                printf("Problème, cette ville ne possède pas déjà un IUT.\n");// si probleme de syntaxe
        }
        if(choix==4){
            //Lancer et arreter phase de canditature
            int exist = 0, k;
            ListeD ld;
            printf("\nVille où se situe le département : ");
            scanf("%s%*c",Vmodif);
            for(i=0;i<n;i++){
                ld = tiut[i]->ldept;
                if(strcmp(tiut[i]->ville, Vmodif)==0){//Si la ville existe
                    printf("\nNom du département : ");
                    scanf("%s%*c",departement);
                    while(ld!=NULL){
                        if(strcmp(ld->departement, departement)==0){
                            printf("\nPour activer la phase d'admission, taper 'A'\nPour la désactiver, taper 'D' : ");
                            scanf("%c%*c",&AouD);
                            for(k=0;k<n;k++){
                                tiut[k]->ldept=ModifiAouD(tiut[k]->ldept,departement,AouD,n);//modification de L'etat du departement(fase de candidature activer ou desactiver) d'un departement 
                                reussi=1;
                            }
                            exist = 1;
                        }
                        if(strcmp(ld->departement, departement)!=0 && exist == 0){
                            exist = 2;
                        }
                        ld = ld->suivant;
                    }
                }
            }
            if(exist==2)
                printf("Ce département n'existe pas.");
            if(reussi==0 && exist==0)
                printf("Problème, cette ville ne possède pas déjà un IUT.\n");// si probleme de syntaxe
        }
        if(choix==5){
            //Modification responsable
            int exist = 0;
            ListeD ld;
            printf("\nVille où se situe le département : ");
            scanf("%s%*c",Vmodif);
            for(i=0;i<n;i++){
                ld = tiut[i]->ldept;
                if(strcmp(tiut[i]->ville, Vmodif)==0){//Si la ville existe
                    printf("\nNom du département : ");
                    scanf("%s%*c",departement);
                    while(ld!=NULL){
                        if(strcmp(ld->departement, departement)==0){
                            printf("\nNom du nouveau responsable : ");
                            scanf("%s",respon);
                            tiut[i]->ldept=ModifiRespon(tiut[i]->ldept,departement,respon,n);//modification du nom du responsable
                            reussi=1;
                            exist = 1;
                        }
                        if(strcmp(ld->departement, departement)!=0 && exist == 0){
                            exist = 2;
                        }
                        ld = ld->suivant;
                    }
                }
            }
            if(exist==2)
                printf("Ce département n'existe pas.");
            if(reussi==0 && exist==0)
                printf("Problème, cette ville ne possède pas déjà un IUT.\n");// si probleme de syntaxe
        }
        if(choix==6){
            //Fonction servant au développement du programme, fonction de test uniquement, à supprimer peut-être.
            affichage(tiut, n);
            char a[50];
            scanf("%c%*c", a);
        }
    }
}


ListeD suppressionTete(ListeD ld){//suppression du maillon 
    ListeD ldsvt;
    ldsvt=ld->suivant;
    free(ld);
    return ldsvt;
}

ListeD suppression(ListeD ld,char *departement){//recherche du maillon a supprimer
    if(ld==NULL)
        return ld;
    if(strcmp(ld->departement,departement) ==0 )
        return suppressionTete(ld);
    ld->suivant=suppression(ld->suivant,departement);
    return ld;
}

ListeD ModifinbP(ListeD ld, char departement[31], int MnbP, int n){//modification du nombre de place
    int i;
    for(i=0;i<=n;i++){
        if(strcmp(ld->departement, departement)==0){
            ld->nbP=MnbP;
            return ld;
        }
        ld->suivant=ModifinbP(ld->suivant, departement, MnbP, n);//fonction recursive pour chercherdans le maillon suivant
    }
    return ld;
}

ListeD ModifiRespon(ListeD ld, char departement[30], char respon[30], int n){//modification de nom de responsable
    int i;
    for(i=0;i<=n;i++){
        if(strcmp(ld->departement,departement)==0){
            strcpy(ld->resp, respon);
            return ld;
        }
        ld->suivant=ModifiRespon(ld->suivant, departement, respon, n);//fonction recursive pour chercherdans le maillon suivant
    }
    return ld;      
}

ListeD ModifiAouD(ListeD ld, char departement[30], char AouD,int n){//modification de l'etat du departement(A ou D)
    int i;
    for(i=0;i<=n;i++){
        if(strcmp(ld->departement,departement)==0){
            ld->AouD=AouD;
            return ld;
        }
        ld->suivant=ModifiAouD(ld->suivant, departement, AouD, n);//fonction recursive pour chercherdans le maillon suivant
    }
    return ld;
}

ListeD Enfiler(ListeD ld, char departement[30], int nbP, char resp[30]){//ajouter un maillon avec tout ses carachteristique
    MaillonDept *mN;
    mN = (MaillonDept*)malloc(sizeof(MaillonDept));
    if(mN==NULL){printf("pb ouv malloc");exit(1);}
    strcpy(mN->departement, departement);
    mN->nbP = nbP;
    strcpy(mN->resp, resp);
    mN->AouD = 'A';
    mN->suivant = NULL;
    if(ld == NULL)
        ld = mN;
        else {
        MaillonDept *mD;
        mD = ld;
        while(mD->suivant != NULL)
            mD = mD->suivant;
        mD->suivant = mN;
    }
    return ld;
}

int fsauvegarde(VilleIUT *tiut[], Candidat *tcandidat[], int n, int nc, int choix, int tmax){//sauvegarde des deux fichier
int i, k, j;   
    //Sauvegarde du fichier d'adhérents
    FILE *fe;
    fe=fopen("ville.don","w");
    if(fe==NULL){
    	printf("\tPb overture fichier");
    	return-1;
    }
    for(i=0;i<n;i++){
        if(i==tmax){
        	printf("\tPb espace");
        	fclose(fe);
        	return-2;
        }
        if(choix==5){
        	fprintf(fe,"%s %d\n",tiut[i]->ville, tiut[i]->nbDep);//ecrire dans le fichier le nom de la ville 
            while(tiut[i]->ldept!=NULL){
                fprintf(fe,"%s ",tiut[i]->ldept->departement);//ecrire dans le fichier les differents departement 
                fprintf(fe,"%d ",tiut[i]->ldept->nbP);
                fprintf(fe,"%s ",tiut[i]->ldept->resp);
                fprintf(fe,"%c\n",tiut[i]->ldept->AouD);
                tiut[i]->ldept = tiut[i]->ldept->suivant;
            }
        }
    }
    
    fclose(fe);   
    //Sauvegarde du fichier d'activités   
	    FILE *fe2;
	    fe2=fopen("Candidat.don","w");
	    if(fe2==NULL){
	    	printf("\tpb overture fichier");
	    	return-1;
	    }
	    for(j=0;j<nc;j++){
		if(j==tmax){
			printf("\tPb espace");
			fclose(fe2);
			return-2;
		}  
        if(choix==5){
            fprintf(fe2,"%d %s %s %.2f %.2f %.2f %d\n", tcandidat[j]->numero, tcandidat[j]->nom, tcandidat[j]->prenom, tcandidat[j]->note.Francais, tcandidat[j]->note.Maths, tcandidat[j]->note.Anglais, tcandidat[j]->nb_choix);
            while(tcandidat[j]->lchoix!=NULL){//ecrire les candidat
                fprintf(fe2,"%s ",tcandidat[j]->lchoix->ville);//ecrire leur choix
                fprintf(fe2,"%s ",tcandidat[j]->lchoix->departement);
                fprintf(fe2,"%d ",tcandidat[j]->lchoix->decision);
                fprintf(fe2,"%d\n",tcandidat[j]->lchoix->validation);
                tcandidat[j]->lchoix = tcandidat[j]->lchoix->suivant;
            }
	    }
        
	    
        }
    fclose(fe2);
    return 0; 
}