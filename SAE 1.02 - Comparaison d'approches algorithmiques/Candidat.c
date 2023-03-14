#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iut.h"

//chargement candidat
int chargementcandidat(Candidat *tcandidat[],int tmax){
    int i = 0, j=0;
    Candidat C;
    Choix ch;
    FILE *fe1;
    fe1=fopen("Candidat.don","r");
    if(fe1==NULL){
        printf("Problème d'ouverture du fichier Candidat");
        return-1;
    }
    C = lireCandidat(fe1);
    while(!feof(fe1)){
        tcandidat[i] = (Candidat*)malloc(sizeof(Candidat));
        if(tcandidat[i]==NULL){
            printf("Problème de malloc");
            return -3;
        }
        
        *tcandidat[i] = C;
        for(j = 0; j < tcandidat[i]->nb_choix; j++){
            ch = lireChoix(fe1);
            tcandidat[i]->lchoix = InsertionCandidat(tcandidat[i]->lchoix, ch.ville, ch.departement, ch.decision, ch.validation);
        }
        C = lireCandidat(fe1);
        i++;
    }
   
    fclose(fe1);
    return i;
}
        Candidat lireCandidat(FILE *fe1){//lire Candidat avec numero, nom, prenom, note et nb de departement demander
            Candidat C;
            C.lchoix = NULL;
            fscanf(fe1,"%d %s %s %f %f %f %d", &C.numero, C.nom, C.prenom, &C.note.Francais, &C.note.Maths, &C.note.Anglais, &C.nb_choix);
            return C;
        }
        Choix lireChoix(FILE *fe1){// lire les demandes du candidat
            Choix ch;
            fscanf(fe1,"%s %s %d %d", ch.ville, ch.departement, &ch.decision, &ch.validation);
            return ch;
        }
        ListeC InsertionTeteCandidat(ListeC ld, char *ville, char *departement, int decision, int validation){
            Choix *ch;
            ch = (Choix*)malloc(sizeof(Choix));
            if(ch==NULL){
                printf("Problème malloc m");
                exit(1);
            }
            strcpy(ch->ville, ville);  
            strcpy(ch->departement, departement);
            ch->decision = decision;
            ch->validation = validation;
            ch->suivant = ld;
            return ch;
        }

        ListeC InsertionCandidat(ListeC ld, char *ville, char *departement, int decision, int validation){
            if(ld==NULL) 
                return InsertionTeteCandidat(ld, ville, departement, decision, validation);
            if(strcmp(ld->ville, ville)<0)
                return InsertionTeteCandidat(ld, ville, departement, decision, validation);
            ld->suivant = InsertionCandidat(ld->suivant, ville, departement, decision, validation);
            return ld;
        }
    //affichage Candidat+choix
    void affichageCandidatchoix(Candidat *tcandidat[],int n){
        int i;
        for(i=0;i<n;i++){
            afficheCandidat(tcandidat, i);//affichage d'un candiat avec info
            affichageListeCandidatchoix(tcandidat[i]->lchoix);//affiche les demande du candidat
        }
    }
    void afficheCandidat(Candidat *tcandidat[], int i){//la fonction affichage pour les info du candidat
        printf("\n%d\t", tcandidat[i]->numero);
        printf("%s ", tcandidat[i]->nom);
        printf("%s\t", tcandidat[i]->prenom);
        printf("%.2f\t", tcandidat[i]->note.Francais);
        printf("%.2f\t", tcandidat[i]->note.Maths);
        printf("%.2f\t", tcandidat[i]->note.Anglais);
        printf("%d\n", tcandidat[i]->nb_choix);
    }
    void affichageListeCandidatchoix(ListeC ld){// la fonction affichage des demande du candidat
        while(ld!=NULL){
            printf("%s\t",ld->ville);
            printf("%s\t",ld->departement);
            printf("%d\t",ld->decision);
            printf("%d\n",ld->validation);
            ld = ld->suivant;//demande suivante
        }
    }
// Menu Candidat
void MenuCandidat(Candidat *tcandidat[],VilleIUT *tiut[],int nc){//Menu candidat
    int Achoix = 1, choix, i, j, comp, comp1, numero, place;
    char Ncandidat[30], PNcandidat[30], departement[30], newdepart[30], Vmodif[30], Ville[30];
    while(Achoix>0 && Achoix<3){
        printf("\n  >--------------------------------------------------<\n");
        printf("\n\t0 - Revenir au menu");
        printf("\n\t1 - Étudiant");
        printf("\n\t2 - Département\n");
        printf("\n  >--------------------------------------------------<\n");
        printf("\n\tVotre choix : ");
        scanf("%d",&Achoix);
        while(Achoix==1){//choix pour Candidat
            printf("\n\nVeuillez saisir votre numéro de dossier (0 - Revenir au menu) : ");
            scanf("%d",&numero);
            if(numero==0){
                Achoix=0;
                break;
            }
            place=verificationid(tcandidat, numero, nc);//Vérification de l'ID du candidat
            while(place==-1){
                printf("Numéro inconnu. Veuillez réessayer (0 - Revenir au menu) : ");
                scanf("%d",&numero);
                if(numero==0){
                    Achoix=0;
                    break;
                }
                place=verificationid(tcandidat, numero, nc);
            }
            system("cls");
            system("clear");
            printf("=================================================\n");
            printf("\n\t\tListe des voeux :\n\n");
            affichageListeCandidatchoix(tcandidat[place]->lchoix);
            printf("\n=================================================\n");
            printf("\n  >-------------------------------------------<\n");
            printf("\n\t0 - Déconnexion");
            printf("\n\t1 - Modifier mes voeux");
            printf("\n\t2 - Ajouter des voeux");
            printf("\n\t3 - Supprimer des voeux\n");
            printf("\n  >-------------------------------------------<\n");
            printf("\n\tChoix : ");
            scanf("%d",&choix);
            while(choix>0){
                if(choix==1){//Modifier demande
                    printf("\nVille où voulez modifier : ");
                    scanf("%s",Ville);
                    printf("\nDepartement lier : ");
                    scanf("%s",departement);
                    printf("\nNouvelle Ville : ");
                    scanf("%s",Vmodif);
                    printf("\nNouveau Departement lier : ");
                    scanf("%s",newdepart);
                    tcandidat[place]->lchoix=modifCandidat(tcandidat[place]->lchoix, departement, newdepart, Ville, Vmodif, nc);
                }
                if(choix==2){//Ajout d'une demande
                    printf("\nVille a ajouter : ");
                    scanf("%s",Ville);
                    printf("\nDepartement lier : ");
                    scanf("%s",departement);
                    tcandidat[place]->lchoix=ajoutCandidat(tcandidat[place]->lchoix, departement, Ville);
                }
                if(choix==3){//Supprimer une demande
                    printf("\nVille a supprimer : ");
                    scanf("%s",Ville);
                    printf("\nDepartement lier : ");
                    scanf("%s",departement);
                    tcandidat[place]->lchoix=suppressionCandidat(tcandidat[place]->lchoix, departement, Ville);
                }
                system("cls");
                system("clear");
                affichageListeCandidatchoix(tcandidat[place]->lchoix);//affichage des demande du candidat
                scanf("%d",&choix);
            }
            system("cls");
            system("clear");
            break;
        }
        while(Achoix==2){//Choix pour le departement
            printf("\n0-Revenir au menu\n1-Afficher Info pour un Candidat\n2-Afficher tout les Candidat par departement\n3-Afficher tout les Candidat avec leur information\n:");
            scanf("\n%d",&choix);
            if(choix==0){
                    Achoix=0;
                    break;
            }
            while(choix>0 && choix<4){
                if(choix==1){//Afficher Info pour un Candidat
                    printf("\nnom du candidat:");
                    scanf("%s",Ncandidat);
                    printf("\nprenom du candidat:");
                    scanf("%s",PNcandidat);
                    for(i=0;i<nc;i++){
                        comp=strcmp(tcandidat[i]->nom, Ncandidat);//recherche du candidat
                        comp1=strcmp(tcandidat[i]->prenom, PNcandidat);
                        if(comp==0 && comp1==0){
                            afficheCandidat(tcandidat, i);//affichage du candidat
                            affichageListeCandidatchoix(tcandidat[i]->lchoix);//affiche des demandes du candidat
                        }         
                    }  
                }
                if(choix==2){//afficher tout les candidat par departement
                    printf("\nnom du departement souhaiter :");
                    scanf("%s",departement);
                    for(i=0;i<nc;i++){
                        if(rechercheCandidatParDeaprtement(tcandidat[i]->lchoix,departement, nc) ==0){//fonction recherche
                            afficheCandidat(tcandidat, i);//affichage des candidat
                        }            
                    } 
                }
                if(choix==3){//afficher tout les candidat avec leur demande
                    printf("\n\n\n\t\tTableau Candidat et choix\n");
                    affichageCandidatchoix(tcandidat,nc);
                }
                printf("\nVoulez-vous choisir une autre fonction ? Sinon taper 0 pour valider : ");
                scanf("%d%*c",&choix);
                if(choix==0){//Pour revenir au Menu
                    Achoix=0;
                    break;
                }
            }
        }
    }
}

int rechercheCandidatParDeaprtement(ListeC ld,char *departement, int nc){//fonction de recherche pour les candidats par departement
    int emp,i=0;
    while(ld!=NULL){
        emp = strcmp(departement, ld->departement);
        if(emp==0)
            return emp;
        ld = ld->suivant;
    }
    return-1;
}

int rechercheCandidatParVille(ListeC ld,char *departement ,char *Ville, int nc){//recherche de candidat par ville et departement
    int emp,emp1,i=0;
    while(ld!=NULL){
        emp = strcmp(Ville, ld->ville);
        emp1 = strcmp(departement, ld->departement);
        if(emp==0 && emp1==0)
            return emp;
        ld = ld->suivant;
    }
    return-1;
}

int verificationid(Candidat *tcandidat[], int numero, int nc){//verification de l'id du candidat
    int i;
    for(i=0;i<nc;i++){
        if(tcandidat[i]->numero==numero)
            return i;
    }
    return -1;
}

ListeC modifCandidat(ListeC ld, char *departement, char *newdepart, char *Ville, char *newVille, int n){
        int comp, comp1, trouv, i;
        for(i=0;i<=n;i++){
            comp=strcmp(ld->departement,departement);
            comp1=strcmp(ld->ville,Ville);
            if(comp==0 && comp1==0){
                strcpy(ld->departement, newdepart);//modification de departement
                strcpy(ld->ville, newVille);//modification de la ville
                return ld;
            }
            ld=ld->suivant;
        }
}

ListeC ajoutCandidat(ListeC ld, char *departement, char *ville){//ajout d'un maillon pour le candidat
    Choix *ch;
    ch = (Choix*)malloc(sizeof(Choix));
    if(ch==NULL){
        printf("pb ouv malloc");
        exit(1);
    }
    strcpy(ch->departement, departement);
    strcpy(ch->ville, ville);
    ch->decision=0;
    ch->validation=0;
    ch->suivant= NULL;
    if(ld == NULL)
        ld = ch;
    else{
        Choix *chD;
        chD = ld;
        while(chD->suivant != NULL)
            chD = chD->suivant;
        chD->suivant=ch;
    }
    return ld;
}

ListeC suppressionTeteCandidat(ListeC ld){//supprimer le candidat
    ListeC ldsvt;
    ldsvt=ld->suivant;
    free(ld);
    return ldsvt;
}

ListeC suppressionCandidat(ListeC ld,char *departement, char *ville){//recherche du candidat
    if(ld==NULL)
        return ld;
    if(strcmp(ld->departement, departement) ==0 && strcmp(ld->ville, ville) ==0)
        return suppressionTeteCandidat(ld);
    ld->suivant=suppressionCandidat(ld->suivant,departement, ville);
    return ld;
}