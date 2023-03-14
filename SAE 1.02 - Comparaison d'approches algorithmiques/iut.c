#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iut.h"




//Fonction qui teste si la liste est vide ou non, et renvoie 'Vrai si la liste est vide', sinon 'Faux'
Booleen testVide(VilleIUT V){
    if(V.ville == NULL)
        return vrai;
    return faux;
}

//chargement Ville+iut
int chargement(VilleIUT *tiut[],int tmax){
    int i = 0, j=0;
    VilleIUT V;
    MaillonDept m;
    FILE *fe;
    fe=fopen("ville.don","r");
    if(fe==NULL){
        printf("Problème d'ouverture du fichier");
        return-1;
    }
    V = lireVille(fe);
    while(!feof(fe)){
        tiut[i] = (VilleIUT*)malloc(sizeof(VilleIUT));
        if(tiut[i]==NULL){
            printf("Problème de malloc");
            return -3;
        }
        *tiut[i] = V;
        for(j = 0; j < tiut[i]->nbDep; j++){
            m = lireDep(fe);
            tiut[i]->ldept = Insertion(tiut[i]->ldept, m.departement, m.nbP, m.resp, m.AouD);
        }
        V = lireVille(fe);
        i++;
    }
    fclose(fe);
    return i;
}
        VilleIUT lireVille(FILE *fe){//lire la ligne de la ville avec ville et le nombre dedepartement
            VilleIUT V;
            V.ldept = NULL;
            fscanf(fe,"%s %d", V.ville, &V.nbDep);
            return V;
        }

        MaillonDept lireDep(FILE *fe){//lire departement avec le nombre de place le responsable et l'etat
            MaillonDept m;
            fscanf(fe,"%s %d %s %c", m.departement, &m.nbP, m.resp, &m.AouD);
            return m;
        }

        ListeD InsertionTete(ListeD ld, char *departement, int nbP,char *resp, char AouD){
            MaillonDept *m;
            m = (MaillonDept*)malloc(sizeof(MaillonDept));
            if(m==NULL){
                printf("Problème malloc m");
                exit(1);}
            strcpy(m->departement, departement);
            m->nbP = nbP;
            strcpy(m->resp, resp);
            m->AouD = AouD;
            m->suivant = ld;
            return m;
        }

        ListeD Insertion(ListeD ld, char *departement, int nbP,char *resp, char AouD){
            if(ld==NULL) 
                return InsertionTete(ld, departement, nbP, resp, AouD);
            if(strcmp(ld->departement, departement)<0)
                return InsertionTete(ld, departement, nbP, resp, AouD);
            ld->suivant = Insertion(ld->suivant, departement, nbP, resp, AouD);
            return ld;
        }
    //affichage Ville
     void affichage (VilleIUT *tiut[],int n){
        int i;
        for(i=0;i<n;i++){
            printf("\n%s\t%d\n", tiut[i]->ville, tiut[i]->nbDep);
            affichageListe(tiut[i]->ldept);//apel fonction affichage des departement
        }
    }
    void affichageListe(ListeD ld){//fonction affichage des departement
        while(ld!=NULL){
        printf("%s\t",ld->departement);
        printf("%d\t",ld->nbP);
        printf("%s\t",ld->resp);
        printf("%c\n",ld->AouD);
        ld = ld->suivant;}
    }
